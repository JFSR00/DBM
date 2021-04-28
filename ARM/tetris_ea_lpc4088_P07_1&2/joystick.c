/***************************************************************************//**
 * \file    joystick.c
 *
 * \brief   Función básica de lectura del joystick de la tarjeta Embedded
 *          Artist LPC4088.
 *
 * Las conexiones entre el joystick el microcontrolador son las siguientes:
 *
 *     	ARRIBA  	--> P2[25]
 *      ABAJO   	--> P2[27]
 *      IZQUIERDA	--> P2[23]
 *      DERECHA		--> P2[26]
 *      CENTRAL		--> P2[22]
 *
 *
 * Los pulsadores del joystick son activos a nivel bajo: cuando se pulsan ponen
 * el correspondiente pin del microcontrolador a 0 y cuando están sin pulsar
 * ponen el correspondiente pin a 1.
 */

#include <LPC407x_8x_177x_8x.h>
#include "joystick.h"
#include "gpio_lpc40xx.h"
#include "leds.h"
#include "tipos.h"

// Definimos los pines correspondientes a cada pulsador del joystick
#define P_ARR 25
#define P_ABJ 27
#define P_IZQ 23
#define P_DCH 26
#define P_CTR 22

/***************************************************************************//**
 *
 * \brief   Leer el joystick y retornar un número diferente según la dirección
 *          que se esté pulsando.
 *
 * \return  0 si no se está pulsando ningúna dirección.
 *          1 si el joystick está pulsado hacia ARRIBA.
 *          2 si el joystick está pulsado hacia ABAJO.
 *          3 si el joystick está pulsado hacia la IZQUIERDA.
 *          4 si el joystick está pulsado hacia la DERECHA.
 *          5 si el joystick está pulsado hacia el CENTRO.
 */
 /*
// Versión problema 1
int32_t leer_joystick(void)
{
	if		 (!(LPC_GPIO2->PIN & (1 << P_ARR))){return JOYSTICK_ARRIBA;}
	else if(!(LPC_GPIO2->PIN & (1 << P_ABJ))){return JOYSTICK_ABAJO;}
	else if(!(LPC_GPIO2->PIN & (1 << P_IZQ))){return JOYSTICK_IZQUIERDA;}
	else if(!(LPC_GPIO2->PIN & (1 << P_DCH))){return JOYSTICK_DERECHA;}
	else if(!(LPC_GPIO2->PIN & (1 << P_CTR))){return JOYSTICK_CENTRO;}
	else																		 {return JOYSTICK_NADA;}
}
*/

// Versión problema 2
int32_t leer_joystick(void)
{
	if		 (!(LPC_GPIO2->PIN & (1 << P_ARR))){return JOYSTICK_ARRIBA;}
	else if(!(LPC_GPIO2->PIN & (1 << P_ABJ))){return JOYSTICK_ABAJO;}
	else if(!(LPC_GPIO2->PIN & (1 << P_IZQ))){return JOYSTICK_IZQUIERDA;}
	else if(!(LPC_GPIO2->PIN & (1 << P_DCH))){return JOYSTICK_DERECHA;}
	
	if(!(LPC_GPIO2->PIN & (1 << P_CTR))){
		led_encender(LED1);
		led_encender(LED2);
		led_encender(LED3);
		led_encender(LED4);
		return JOYSTICK_CENTRO;
	}
	else{
		led_apagar(LED1);
		led_apagar(LED2);
		led_apagar(LED3);
		led_apagar(LED4);
	}
	return JOYSTICK_NADA;
}
