/*
 * Copyright 2016 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: RV32M1
package_id: RV32M1
mcu_data: ksdk2_0
processor_version: 0.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/*FUNCTION**********************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 *END**************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}

#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */
#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port */
#define PIN19_IDX                       19u   /*!< Pin number for pin 19 in a port */
#define PIN25_IDX                       25u   /*!< Pin number for pin 25 in a port */
#define PIN27_IDX                       27u   /*!< Pin number for pin 27 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: N2, peripheral: LPUART0, signal: RX, pin_signal: LPCMP0_IN0/PTC7/LLWU_P15/LPSPI0_PCS3/LPUART0_RX/LPI2C1_HREQ/TPM0_CH0/LPTMR1_ALT1}
  - {pin_num: P3, peripheral: LPUART0, signal: TX, pin_signal: LPCMP0_IN1/PTC8/LPSPI0_SCK/LPUART0_TX/LPI2C0_HREQ/TPM0_CH1}
  - {pin_num: C2, peripheral: LPSPI0, signal: SCK, pin_signal: ADC0_SE1/PTB4/LLWU_P6/RF0_RF_OFF/RF0_DFT_RESET/LPSPI0_SCK/LPUART1_CTS_b/SAI0_TX_BCLK/FB_AD9/TPM0_CH2}
  - {pin_num: D2, peripheral: LPSPI0, signal: OUT, pin_signal: PTB5/RF0_ACTIVE/LPSPI0_SOUT/LPUART1_RTS_b/SAI0_MCLK/FB_AD8/TPM0_CH3}
  - {pin_num: E1, peripheral: LPSPI0, signal: PCS2, pin_signal: PTB6/LLWU_P7/LPSPI0_PCS2/LPI2C1_SDA/SAI0_RX_BCLK/FB_AD7/TPM0_CH4/RF0_BSM_FRAME}
  - {pin_num: E2, peripheral: LPSPI0, signal: IN, pin_signal: ADC0_SE2/PTB7/LLWU_P8/LPSPI0_SIN/LPI2C1_SDAS/SAI0_RX_FS/FB_AD6/TPM0_CH5/RF0_BSM_DATA}
  - {pin_num: D7, peripheral: LPSPI3, signal: SCK, pin_signal: PTA19/LPSPI2_PCS3/LPSPI3_SCK/EMVSIM0_VCCEN/FB_AD19/TPM2_CH5}
  - {pin_num: A3, peripheral: LPSPI3, signal: IN, pin_signal: PTA27/LPUART1_CTS_b/LPSPI3_SIN/FB_AD29}
  - {pin_num: B5, peripheral: LPSPI3, signal: OUT, pin_signal: PTA25/LPUART1_RX/LPSPI3_SOUT/LPI2C2_SDAS/FB_AD31}
  - {pin_num: F7, peripheral: LPSPI3, signal: PCS1, pin_signal: PTA17/LPI2C2_HREQ/LPSPI3_PCS1/EMVSIM0_CLK/FB_AD21}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Clock Gate Control: 0x01u */
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Gate Control: 0x01u */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTA, PIN17_IDX, kPORT_MuxAlt3);           /* PORTA17 (pin F7) is configured as LPSPI3_PCS1 */
  PORT_SetPinMux(PORTA, PIN19_IDX, kPORT_MuxAlt3);           /* PORTA19 (pin D7) is configured as LPSPI3_SCK */
  PORT_SetPinMux(PORTA, PIN25_IDX, kPORT_MuxAlt3);           /* PORTA25 (pin B5) is configured as LPSPI3_SOUT */
  PORT_SetPinMux(PORTA, PIN27_IDX, kPORT_MuxAlt3);           /* PORTA27 (pin A3) is configured as LPSPI3_SIN */
  PORT_SetPinMux(PORTB, PIN4_IDX, kPORT_MuxAlt2);            /* PORTB4 (pin C2) is configured as LPSPI0_SCK */
  PORT_SetPinMux(PORTB, PIN5_IDX, kPORT_MuxAlt2);            /* PORTB5 (pin D2) is configured as LPSPI0_SOUT */
  PORT_SetPinMux(PORTB, PIN6_IDX, kPORT_MuxAlt2);            /* PORTB6 (pin E1) is configured as LPSPI0_PCS2 */
  PORT_SetPinMux(PORTB, PIN7_IDX, kPORT_MuxAlt2);            /* PORTB7 (pin E2) is configured as LPSPI0_SIN */
  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_MuxAlt3);            /* PORTC7 (pin N2) is configured as LPUART0_RX */
  PORT_SetPinMux(PORTC, PIN8_IDX, kPORT_MuxAlt3);            /* PORTC8 (pin P3) is configured as LPUART0_TX */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
