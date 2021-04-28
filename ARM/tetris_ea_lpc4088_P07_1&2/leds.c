/***************************************************************************//**
 * \file    leds.c
 *
 * \brief   Funciones para manejar cuatro de los LEDs de la tarjeta Embedded
 *          Artist LPC4088.
 *
 * Las conexiones entre dos de los LEDs de la tarjeta y el microcontrolador son
 * las siguientes:
 *
 *      P1[5]   --> LED1 (ROJO)
 *      P0[14] 	--> LED2 (VERDE)
 *      P0[13]  --> LED3 (VERDE)
 *			P1[18]  -->	LED4 (VERDE)
 *
 * Los LEDs son activos a nivel bajo: cuando uno de estos pines del
 * microcontrolador se pone a 1 el correspondiente LED se apaga y cuando se
 * pone a 0 el LED se enciende.
 */

#include <LPC407x_8x_177x_8x.h>
#include "leds.h"
#include "gpio_lpc40xx.h"
#include "error.h"

// Definimos los pines correspondientes a cada pulsador del joystick
#define P_LED1 5
#define P_LED2 14
#define P_LED3 13
#define P_LED4 18

/***************************************************************************//**
 * \brief   Configurar como salidas los pines del microcontrolador que están
 *          conectados a los LEDs y apagar todos los LEDs.
 */
void leds_inicializar(void)
{
	LPC_GPIO1->DIR |= (1 << P_LED1)|(1 << P_LED4);
	LPC_GPIO0->DIR |= (1 << P_LED2)|(1 << P_LED3);
	LPC_GPIO1->SET |= (1 << P_LED1)|(1 << P_LED4);
	LPC_GPIO0->SET |= (1 << P_LED2)|(1 << P_LED3);
}

/***************************************************************************//**
 * \brief       Encender un LED.
 *
 * \param[in]   numero_led  número del LED a encender. Debe estar entre 1 y 4.
 */
void led_encender(int32_t numero_led)
{
	switch(numero_led){
		case LED1:LPC_GPIO1->CLR |= (1 << P_LED1);break;
		case LED2:LPC_GPIO0->CLR |= (1 << P_LED2);break;
		case LED3:LPC_GPIO0->CLR |= (1 << P_LED3);break;
		case LED4:LPC_GPIO1->CLR |= (1 << P_LED4);break;
		default:break;
	}
}

/***************************************************************************//**
 * \brief       Apagar un LED.
 *
 * \param[in]   numero_led  número del LED a apagar. Debe estar entre 1 y 4.
 */
void led_apagar(int32_t numero_led)
{
	switch(numero_led){
		case LED1:LPC_GPIO1->SET |= (1 << P_LED1);break;
		case LED2:LPC_GPIO0->SET |= (1 << P_LED2);break;
		case LED3:LPC_GPIO0->SET |= (1 << P_LED3);break;
		case LED4:LPC_GPIO1->SET |= (1 << P_LED4);break;
		default:break;
	}
}

/***************************************************************************//**
 * \brief       Invertir el estado de un LED.
 *
 * \param[in]   numero_led  número del LED a invertir. Debe estar entre 1 y 4.
 */
void led_invertir(int32_t numero_led)
{
	switch(numero_led){
		case LED1:LPC_GPIO1->PIN ^= (1 << P_LED1);break;
		case LED2:LPC_GPIO0->PIN ^= (1 << P_LED2);break;
		case LED3:LPC_GPIO0->PIN ^= (1 << P_LED3);break;
		case LED4:LPC_GPIO1->PIN ^= (1 << P_LED4);break;
		default:break;
	}
}

/***************************************************************************//**
 * \brief       Ajustar el estado de una LED
 *
 * \param[in]   numero_led  número del LED a ajustar. Debe estar entre 1 y 4.
 * \param[in]   estado      estado que debe adoptar el LED. TRUE => encendido
 *                          FALSE => apagado.
 */
void led_ajustar(int32_t numero_led, bool_t estado)
{
    switch(numero_led){
		case LED1:
			if(estado)
				LPC_GPIO1->CLR |= (1 << P_LED1);
			else
				LPC_GPIO1->SET |= (1 << P_LED1);
			break;
		case LED2:
			if(estado)
				LPC_GPIO0->CLR |= (1 << P_LED2);
			else
				LPC_GPIO0->SET |= (1 << P_LED2);
			break;
		case LED3:
			if(estado)
				LPC_GPIO0->CLR |= (1 << P_LED3);
			else
				LPC_GPIO0->SET |= (1 << P_LED3);
			break;
		case LED4:
			if(estado)
				LPC_GPIO1->CLR |= (1 << P_LED4);
			else
				LPC_GPIO1->SET |= (1 << P_LED4);
			break;
		default:
			break;
	}
}
