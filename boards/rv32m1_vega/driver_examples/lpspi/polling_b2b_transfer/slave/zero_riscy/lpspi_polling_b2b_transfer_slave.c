/*
 * Copyright 2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_lpspi.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_LPSPI_SLAVE_BASEADDR LPSPI3
#define EXAMPLE_LPSPI_SLAVE_IRQN LPSPI3_IRQn
#define EXAMPLE_LPSPI_SLAVE_PCS_FOR_INIT kLPSPI_Pcs1
#define EXAMPLE_LPSPI_SLAVE_PCS_FOR_TRANSFER kLPSPI_SlavePcs1

#define EXAMPLE_LPSPI_SLAVE_CLOCK_NAME (kCLOCK_Lpspi3)
#define EXAMPLE_LPSPI_SLAVE_CLOCK_SOURCE (kCLOCK_IpSrcFircAsync)
#define TRANSFER_SIZE 64U /*! Transfer dataSize */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* LPSPI user callback */
void LPSPI_SlaveUserCallback(LPSPI_Type *base, lpspi_slave_handle_t *handle, status_t status, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t slaveRxData[TRANSFER_SIZE] = {0U};

lpspi_slave_handle_t g_s_handle;
volatile bool isTransferCompleted = false;

/*******************************************************************************
 * Code
 ******************************************************************************/


void LPSPI_SlaveUserCallback(LPSPI_Type *base, lpspi_slave_handle_t *handle, status_t status, void *userData)
{
    if (status == kStatus_Success)
    {
        PRINTF("This is LPSPI slave transfer completed callback. \r\n");
        PRINTF("It's a successful transfer. \r\n\r\n");
    }

    if (status == kStatus_LPSPI_Error)
    {
        PRINTF("This is LPSPI slave transfer completed callback. \r\n");
        PRINTF("Error occured in this transfer. \r\n\r\n");
    }

    isTransferCompleted = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /*Set clock source for LPSPI*/
    CLOCK_SetIpSrc(EXAMPLE_LPSPI_SLAVE_CLOCK_NAME, EXAMPLE_LPSPI_SLAVE_CLOCK_SOURCE);

    PRINTF("LPSPI board to board polling example.\r\n");

    uint32_t i;
    lpspi_slave_config_t slaveConfig;
    lpspi_transfer_t slaveXfer;

    /*Slave config*/
    slaveConfig.bitsPerFrame = 8 * TRANSFER_SIZE;
    slaveConfig.cpol = kLPSPI_ClockPolarityActiveHigh;
    slaveConfig.cpha = kLPSPI_ClockPhaseFirstEdge;
    slaveConfig.direction = kLPSPI_MsbFirst;

    slaveConfig.whichPcs = EXAMPLE_LPSPI_SLAVE_PCS_FOR_INIT;
    slaveConfig.pcsActiveHighOrLow = kLPSPI_PcsActiveLow;

    slaveConfig.pinCfg = kLPSPI_SdiInSdoOut;
    slaveConfig.dataOutConfig = kLpspiDataOutRetained;

    LPSPI_SlaveInit(EXAMPLE_LPSPI_SLAVE_BASEADDR, &slaveConfig);

    LPSPI_SlaveTransferCreateHandle(EXAMPLE_LPSPI_SLAVE_BASEADDR, &g_s_handle, LPSPI_SlaveUserCallback, NULL);

    while (1)
    {
        PRINTF("\r\n Slave example is running...\r\n");

        /* Reset the receive buffer */
        for (i = 0U; i < TRANSFER_SIZE; i++)
        {
            slaveRxData[i] = 0U;
        }

        /* Set slave transfer ready to receive data */
        isTransferCompleted = false;

        slaveXfer.txData = NULL;
        slaveXfer.rxData = slaveRxData;
        slaveXfer.dataSize = TRANSFER_SIZE;
        slaveXfer.configFlags = EXAMPLE_LPSPI_SLAVE_PCS_FOR_TRANSFER | kLPSPI_SlaveByteSwap;

        /* Slave start receive */
        LPSPI_SlaveTransferNonBlocking(EXAMPLE_LPSPI_SLAVE_BASEADDR, &g_s_handle, &slaveXfer);

        while (!isTransferCompleted)
        {
        }

        /* Set slave transfer ready to send back data */
        isTransferCompleted = false;

        slaveXfer.txData = slaveRxData;
        slaveXfer.rxData = NULL;
        slaveXfer.dataSize = TRANSFER_SIZE;
        slaveXfer.configFlags = EXAMPLE_LPSPI_SLAVE_PCS_FOR_TRANSFER | kLPSPI_SlaveByteSwap;

        /* Slave start send */
        LPSPI_SlaveTransferNonBlocking(EXAMPLE_LPSPI_SLAVE_BASEADDR, &g_s_handle, &slaveXfer);

        while (!isTransferCompleted)
        {
        }

        /* Print out receive buffer */
        PRINTF("\r\n Slave received:");
        for (i = 0U; i < TRANSFER_SIZE; i++)
        {
            /* Print 16 numbers in a line */
            if ((i & 0x0FU) == 0U)
            {
                PRINTF("\r\n    ");
            }
            PRINTF(" %02X", slaveRxData[i]);
        }
        PRINTF("\r\n");
    }
}
