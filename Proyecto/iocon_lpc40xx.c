/***************************************************************************//**
 * \file   iocon_lpc40xx.c
 *
 * \brief  Funciones de configuración de pines del LPC40xx.
 */

#include "iocon_lpc40xx.h"
#include "gpio_lpc40xx.h"
#include "error.h"
#include <LPC407x_8x_177x_8x.h>

/* Funciones de cada pin de cada puerto.
 */
static const uint16_t tabla_funciones_pines[GPIO_NUMERO_PUERTOS]
                                           [GPIO_MAXIMO_PINES_POR_PUERTO]
                                           [IOCON_MAXIMO_FUNCIONES_POR_PIN] =
{
    /* Puerto 0. */
    {
        {GPIO, CAN_RD1, U3_TXD, I2C1_SDA, U0_TXD, RESERVED, RESERVED, RESERVED},
        {GPIO, CAN_TD1, U3_RXD, I2C1_SCL, U0_RXD, RESERVED, RESERVED, RESERVED},
        {GPIO, U0_TXD, U3_TXD, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, U0_RXD, U3_RXD, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, I2S_RX_SCK, CAN_RD2, T2_CAP0, RESERVED, CMP_ROSC, RESERVED, LCD_VD_0},
        {GPIO, I2S_RX_WS, CAN_TD2, T2_CAP1, RESERVED, CMP_RESET, RESERVED, LCD_VD_1},
        {GPIO, I2S_RX_SDA, SSP1_SSEL, T2_MAT0, U1_RTS, CMP_ROSC, RESERVED, LCD_VD_8},
        {GPIO, I2S_TX_SCK, SSP1_SCK, T2_MAT1, RTC_EV0, CMP_VREF, RESERVED, LCD_VD_9},
        {GPIO, I2S_TX_WS, SSP1_MISO, T2_MAT2, RTC_EV1, CMP1_IN_4, RESERVED, LCD_VD_16},
        {GPIO, I2S_TX_SDA, SSP1_MOSI, T2_MAT3, RTC_EV2, CMP1_IN_3, RESERVED, LCD_VD_17},
        {GPIO, U2_TXD, I2C2_SDA, T3_MAT0, RESERVED, RESERVED, RESERVED, LCD_VD_5},
        {GPIO, U2_RXD, I2C2_SCL, T3_MAT1, RESERVED, RESERVED, RESERVED, LCD_VD_10},
        {GPIO, USB_PPWR2, SSP1_MISO, AD0_6, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, USB_UP_LED2, SSP1_MOSI, AD0_7, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, USB_HSTEN2, SSP1_SSEL, USB_CONNECT2, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, U1_TXD, SSP0_SCK, RESERVED, RESERVED, SPIFI_IO_2, RESERVED, RESERVED},
        {GPIO, U1_RXD, SSP0_SSEL, RESERVED, RESERVED, SPIFI_IO_3, RESERVED, RESERVED},
        {GPIO, U1_CTS, SSP0_MISO, RESERVED, RESERVED, SPIFI_IO_1, RESERVED, RESERVED},
        {GPIO, U1_DCD, SSP0_MOSI, RESERVED, RESERVED, SPIFI_IO_0, RESERVED, RESERVED},
        {GPIO, U1_DSR, SD_CLK, I2C1_SDA, RESERVED, RESERVED, RESERVED, LCD_VD_13},
        {GPIO, U1_DTR, SD_CMD, I2C1_SCL, RESERVED, RESERVED, RESERVED, LCD_VD_14},
        {GPIO, U1_RI, SD_PWR, U4_OE, CAN_RD1, U4_SCLK, RESERVED, RESERVED},
        {GPIO, U1_RTS, SD_DAT_0, U4_TXD, CAN_TD1, SPIFI_CLK, RESERVED, RESERVED},
        {GPIO, AD0_0, I2S_RX_SCK, T3_CAP0, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, AD0_1, I2S_RX_WS, T3_CAP1, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, AD0_2, I2S_RX_SDA, U3_TXD, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, AD0_3, DAC_OUT, U3_RXD, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, I2C0_SDA, USB_SDA1, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, I2C0_SCL, USB_SCL1, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, USB_DP1, EINT0, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, USB_DM1, EINT1, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, USB_DP2, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED}
    }, 
    /* Puerto 1. */
    {
        {GPIO, ENET_TXD0, RESERVED, T3_CAP1, SSP2_SCK, RESERVED, RESERVED, RESERVED},
        {GPIO, ENET_TXD1, RESERVED, T3_MAT3, SSP2_MOSI, RESERVED, RESERVED, RESERVED},
        {GPIO, ENET_TXD2, SD_CLK, PWM0_1, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, ENET_TXD3, SD_CMD, PWM0_2, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, ENET_TX_EN, RESERVED, T3_MAT2, SSP2_MISO, RESERVED, RESERVED, RESERVED},
        {GPIO, ENET_TX_ER, SD_PWR, PWM0_3, RESERVED, CMP1_IN_2, RESERVED, RESERVED},
        {GPIO, ENET_TX_CLK, SD_DAT_0, PWM0_4, RESERVED, CMP0_IN_4, RESERVED, RESERVED},
        {GPIO, ENET_COL, SD_DAT_1, PWM0_5, RESERVED, CMP1_IN_1, RESERVED, RESERVED},
        {GPIO, ENET_CRS, RESERVED, T3_MAT1, SSP2_SSEL, RESERVED, RESERVED, RESERVED},
        {GPIO, ENET_RXD0, RESERVED, T3_MAT0, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, ENET_RXD1, RESERVED, T3_CAP0, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, ENET_RXD2, SD_DAT_2, PWM0_6, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, ENET_RXD3, SD_DAT_3, PWM0_CAP0, RESERVED, CMP1_OUT, RESERVED, RESERVED},
        {GPIO, ENET_RX_DV, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, ENET_RX_ER, RESERVED, T2_CAP0, RESERVED, CMP0_IN_1, RESERVED, RESERVED},
        {GPIO, ENET_RX_CLK, RESERVED, I2C2_SDA, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, ENET_MDC, I2S_TX_MCLK, RESERVED, RESERVED, CMP0_IN_2, RESERVED, RESERVED},
        {GPIO, ENET_MDIO, I2S_RX_MCLK, RESERVED, RESERVED, CMP0_IN_3, RESERVED, RESERVED},
        {GPIO, USB_UP_LED1, PWM1_1, T1_CAP0, RESERVED, SSP1_MISO, RESERVED, RESERVED},
        {GPIO, USB_TX_E1, USB_PPWR1, T1_CAP1, MC_0A, SSP1_SCK, U2_OE, RESERVED},
        {GPIO, USB_TX_DP1, PWM1_2, QEI_PHA, MC_FB0, SSP0_SCK, LCD_VD_6, LCD_VD_10},
        {GPIO, USB_TX_DM1, PWM1_3, SSP0_SSEL, MC_ABORT, RESERVED, LCD_VD_7, LCD_VD_11},
        {GPIO, USB_RCV1, USB_PWRD1, T1_MAT0, MC_0B, SSP1_MOSI, LCD_VD_8, LCD_VD_12},
        {GPIO, USB_RX_DP1, PWM1_4, QEI_PHB, MC_FB1, SSP0_MISO, LCD_VD_9, LCD_VD_13},
        {GPIO, USB_RX_DM1, PWM1_5, QEI_IDX, MC_FB2, SSP0_MOSI, LCD_VD_10, LCD_VD_14},
        {GPIO, USB_LS1, USB_HSTEN1, T1_MAT1, MC_1A, CLKOUT, LCD_VD_11, LCD_VD_15},
        {GPIO, USB_SSPND1, PWM1_6, T0_CAP0, MC_1B, SSP1_SSEL, LCD_VD_12, LCD_VD_20},
        {GPIO, USB_INT1, USB_OVRCR1, T0_CAP1, CLKOUT, LCD_VD_13, LCD_VD_21},
        {GPIO, USB_SCL1, PWM1_CAP0, T0_MAT0, MC_2A, SSP0_SSEL, LCD_VD_14, LCD_VD_22},
        {GPIO, USB_SDA1, PWM1_CAP1, T0_MAT1, MC_2B, U4_TXD, LCD_VD_15, LCD_VD_23},
        {GPIO, USB_PWRD2, USB_VBUS, AD0_4, I2C0_SDA, U3_OE, RESERVED, RESERVED},
        {GPIO, USB_OVRCR2, SSP1_SCK, AD0_5, I2C0_SCL, RESERVED, RESERVED, RESERVED}
    },     
    /* Puerto 2. */
    {
        {GPIO, PWM1_1, U1_TXD, RESERVED, RESERVED, RESERVED, RESERVED, LCD_PWR},
        {GPIO, PWM1_2, U1_RXD, RESERVED, RESERVED, RESERVED, RESERVED, LCD_LE},
        {GPIO, PWM1_3, U1_CTS, T2_MAT3, RESERVED, TRACEDATA_3, RESERVED, LCD_DCLK},
        {GPIO, PWM1_4, U1_DCD, T2_MAT2, RESERVED, TRACEDATA_2, RESERVED, LCD_FP},
        {GPIO, PWM1_5, U1_DSR, T2_MAT1, RESERVED, TRACEDATA_1, RESERVED, LCD_ENAB_M},
        {GPIO, PWM1_6, U1_DTR, T2_MAT0, RESERVED, TRACEDATA_0, RESERVED, LCD_LP},
        {GPIO, PWM1_CAP0, U1_RI, T2_CAP0, U2_OE, TRACECLK, LCD_VD_0, LCD_VD_4},
        {GPIO, CAN_RD2, U1_RTS, RESERVED, SPIFI_CS, LCD_VD_1, LCD_VD_5},
        {GPIO, CAN_TD2, U2_TXD, U1_CTS, ENET_MDC, RESERVED, LCD_VD_2, LCD_VD_6},
        {GPIO, USB_CONNECT1, U2_RXD, U4_RXD, ENET_MDIO, RESERVED, LCD_VD_3, LCD_VD_7},
        {GPIO, EINT0, NMI, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EINT1, SD_DAT_1, I2S_TX_SCK, RESERVED, RESERVED, RESERVED, LCD_CLKIN},
        {GPIO, EINT2, SD_DAT_2, I2S_TX_WS, LCD_VD_4, LCD_VD_3, LCD_VD_8, LCD_VD_18},
        {GPIO, EINT3, SD_DAT_3, I2S_TX_SDA, RESERVED, LCD_VD_5, LCD_VD_9, LCD_VD_19},
        {GPIO, EMC_CS2, I2C1_SDA, T2_CAP0, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_CS3, I2C1_SCL, T2_CAP1, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_CAS, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_RAS, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_CLK0, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_CLK1, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_DYCS0, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_DYCS1, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_DYCS2, SSP0_SCK, T3_CAP0, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_DYCS3, SSP0_SSEL, T3_CAP1, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_CKE0, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_CKE1, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_CKE2, SSP0_MISO, T3_MAT0, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_CKE3, SSP0_MOSI, T3_MAT1, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_DQM0, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_DQM1, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_DQM2, I2C2_SDA, T3_MAT2, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_DQM3, I2C2_SCL, T3_MAT3, RESERVED, RESERVED, RESERVED, RESERVED}
    },     
    /* Puerto 3. */
    {
        {GPIO, EMC_D_0, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_1, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_2, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_3, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_4, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_5, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_6, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_7, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_8, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_9, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_10, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_11, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_12, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_13, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_14, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_15, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_16, PWM0_1, U1_TXD, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_17, PWM0_2, U1_RXD, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_18, PWM0_3, U1_CTS, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_19, PWM0_4, U1_DCD, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_20, PWM0_5, U1_DSR, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_21, PWM0_6, U1_DTR, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_22, PWM0_CAP0, U1_RI, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_23, PWM1_CAP0, T0_CAP0, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_24, PWM1_1, T0_CAP1, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_25, PWM1_2, T0_MAT0, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_26, PWM1_3, T0_MAT1, STCLK, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_27, PWM1_4, T1_CAP0, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_28, PWM1_5, T1_CAP1, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_29, PWM1_6, T1_MAT0, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_30, U1_RTS, T1_MAT1, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_D_31, RESERVED, T1_MAT2, RESERVED, RESERVED, RESERVED, RESERVED}
    },     
    /* Puerto 4. */
    {
        {GPIO, EMC_A_0, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_1, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_2, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_3, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_4, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_5, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_6, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_7, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_8, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_9, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_10, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_11, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_12, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_13, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_14, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_15, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_16, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_17, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_18, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_19, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_20, I2C2_SDA, SSP1_SCK, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_21, I2C2_SCL, SSP1_SSEL, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_22, U2_TXD, SSP1_MISO, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_23, U2_RXD, SSP1_MOSI, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_OE, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_WE, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_BLS0, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_BLS1, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_BLS2, U3_TXD, T2_MAT0, RESERVED, LCD_VD_6, LCD_VD_10, LCD_VD_2},
        {GPIO, EMC_BLS3, U3_RXD, T2_MAT1, I2C2_SCL, LCD_VD_7, LCD_VD_11, LCD_VD_3},
        {GPIO, EMC_CS0, RESERVED, RESERVED, RESERVED, CMP0_OUT, RESERVED, RESERVED},
        {GPIO, EMC_CS1, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED}
    }, 
    /* Puerto 5. */
    {
        {GPIO, EMC_A_24, SSP2_MOSI, T2_MAT2, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, EMC_A_25, SSP2_MISO, T2_MAT3, RESERVED, RESERVED, RESERVED, RESERVED},
        {GPIO, RESERVED, RESERVED, T3_MAT2, RESERVED, I2C0_SDA, RESERVED, RESERVED},
        {GPIO, RESERVED, RESERVED, RESERVED, U4_RXD, I2C0_SCL, RESERVED, RESERVED},
        {GPIO, U0_OE, RESERVED, T3_MAT3, U4_TXD, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED},
        {RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED}
    }
};

/***************************************************************************//**
 * \brief       Configurar la función de un pin.
 *
 * \param[in]   gpio_regs         puntero a bloque de registros GPIO del puerto.
 * \param[in]   mascara_pin       máscara de selección de pin.
 * \param[in]   funcion           función deseada para el pin.
 * \param[in]   configuracion_es  configuracion de pull-up/pull-down, modo
 *                                analógico, histéresis, filtro de glitch,
 *                                slew-rate, drenador abierto, inversión, etc.
 *
 * \note        La razón de especificar el puerto y el pin mediante el puntero
 *              a los registros GPIO y una máscara de pin en lugar de un número
 *              de puerto y un número de pin es conseguir que la forma de
 *              especificar un pin sea igual para los módulos gpio_lpc40xx e
 *              iocon_lpc40xx. Esto permite usar los mismos símbolos PUERTOx
 *              y PINx definidos en gpio_lpc40xx.h al usar las funciones de
 *              iocon_lpc40xx. Esto tiene el inconveniente de que en las
 *              funciones de iocon_lpc40xx hay que transformar el puntero a
 *              registros GPIO en un número de pin y la máscara de selección de
 *              pin en un número de pin.
 */
void iocon_configurar_pin(LPC_GPIO_TypeDef *gpio_regs,
                          uint32_t mascara_pin,
                          funcion_pin_t funcion,
                          uint32_t configuracion_es)
{
    uint32_t i;
    uint32_t *ptr;
    uint32_t numero_puerto;
    uint32_t numero_pin;
    
    /* Transformar el puntero al bloque de registros GPIO a un número de puerto.
     */
    if (gpio_regs == PUERTO0)
    {
        numero_puerto = 0;
    }
    else if (gpio_regs == PUERTO1)
    {
        numero_puerto = 1;
    }
    else if (gpio_regs == PUERTO2)
    {
        numero_puerto = 2;
    }
    else if (gpio_regs == PUERTO3)
    {
        numero_puerto = 3;
    }
    else if (gpio_regs == PUERTO4)
    {
        numero_puerto = 4;
    }
    else if (gpio_regs == PUERTO5)
    {
        numero_puerto = 5;
    }
    else
    {
        ERROR("Puntero a bloque de registros GPIO incorrecto.");
    }
    
    /* Transformar la mascara de pin a un número de pin.
     */
    ASSERT(mascara_pin != 0,
           "La máscara de selección de pin no selecciona ningún pin.");
    for (numero_pin = 0; numero_pin < 32; numero_pin++)
    {
        if ((mascara_pin & 1) != 0)
        {
            ASSERT((mascara_pin & 0xFFFFFFFEu) == 0,
                   "La máscara de selección de pin selecciona más de un pin.");
            break;            
        }
        mascara_pin >>= 1;
    }    
       
    /*--------------------------------------------------------------------------
     */    
    ASSERT((uint32_t)funcion < (uint32_t)RESERVED, "Función no válida.");
    
    /* Obtener el número de función correspondiente a la función indicada
     * para el pin.
     */
    i = 0;
    while (i < IOCON_MAXIMO_FUNCIONES_POR_PIN)
    {
        if (tabla_funciones_pines[numero_puerto][numero_pin][i] == funcion)
        {
            break;
        }
        i++;
    }
    
    ASSERT(i < IOCON_MAXIMO_FUNCIONES_POR_PIN,
        "El pin no tiene la función indicada.");
    
    /* Los bits ADMODE (bit 7), FILTER (bit 8) y HS (bit 8) actúan invertidos.
     */
    configuracion_es ^= (1 << 7) | (1 << 8);
          
    ptr = (uint32_t*)LPC_IOCON;
    ptr[numero_puerto*32 + numero_pin] = i | configuracion_es;
}

/***************************************************************************//**
 * \brief       Configurar la función de varios pines.
 *
 * \param[in]   pf  puntero a array de estructuras de tipo
 *                  configuracion_funcion_pin_t con la descripción de pines
 *                  y funciones a configurar. Después de la última entrada
 *                  válida del array debe haber una marcada con un campo
 *                  puerto igual a 0.
 */
void iocon_configurar_grupo_pines(const configuracion_funcion_pin_t *pf)
{
    ASSERT(pf != NULL, "Puntero a array de configuración nulo.");
    
    while (pf->gpio_regs != NULL)
    {
        iocon_configurar_pin(pf->gpio_regs,
                             pf->mascara_pin,
                             pf->funcion, 
                             pf->configuracion_es);
        pf++;
    }
}
