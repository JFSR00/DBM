
/*
 * Auto generated Run-Time-Environment Configuration File
 *      *** Do not modify ! ***
 *
 * Project: 'HTTP_Server' 
 * Target:  'LCD PB1 TFT 4.3 inch' 
 */

#ifndef RTE_COMPONENTS_H
#define RTE_COMPONENTS_H


/*
 * Define the Device Header File: 
 */
#define CMSIS_device_header "LPC407x_8x_177x_8x.h"

/* ARM::CMSIS:RTOS:Keil RTX:4.82.0 */
#define RTE_CMSIS_RTOS                  /* CMSIS-RTOS */
        #define RTE_CMSIS_RTOS_RTX              /* CMSIS-RTOS Keil RTX */
/* Keil.LPC4088-32 Developers Kit::Board Support:Graphic LCD:TFT 800x480:1.0.0 */
#define RTE_EA_LCD_TFT_800x480
/* Keil.MDK-Pro::Network:CORE:IPv4/IPv6 Release:7.14.0 */
#define RTE_Network_Core                /* Network Core */
          #define RTE_Network_IPv4                /* Network IPv4 Stack */
          #define RTE_Network_IPv6                /* Network IPv6 Stack */
          #define RTE_Network_Release             /* Network Release Version */
/* Keil.MDK-Pro::Network:Interface:ETH:7.14.0 */
#define RTE_Network_Interface_ETH_0     /* Network Interface ETH 0 */

/* Keil.MDK-Pro::Network:Service:Web Server Compact:HTTP:7.14.0 */
#define RTE_Network_Web_Server_RO       /* Network Web Server with Read-only Web Resources */
/* Keil.MDK-Pro::Network:Socket:TCP:7.14.0 */
#define RTE_Network_Socket_TCP          /* Network Socket TCP */
/* Keil.MDK-Pro::Network:Socket:UDP:7.14.0 */
#define RTE_Network_Socket_UDP          /* Network Socket UDP */
/* Keil::CMSIS Driver:Ethernet MAC:1.1 */
#define RTE_Drivers_ETH_MAC0            /* Driver ETH_MAC0 */
/* Keil::CMSIS Driver:Ethernet PHY:LAN8720:6.2.0 */
#define RTE_Drivers_PHY_LAN8720         /* Driver PHY LAN8720 */
/* Keil::CMSIS Driver:I2C:1.0 */
#define RTE_Drivers_I2C0                /* Driver I2C0 */
        #define RTE_Drivers_I2C1                /* Driver I2C1 */
        #define RTE_Drivers_I2C2                /* Driver I2C2 */


#endif /* RTE_COMPONENTS_H */
