/***************************************************************************//**
 * \file    main.c
 * \brief   Función main para la práctica sobre UART.
 */
#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "joystick.h"
#include "leds.h"
#include "error.h"
#include "uart_lpc40xx.h"
#include "timer_lpc40xx.h"
#include "stdlib.h"
#include "stdio.h"
#include "esp8266.h"
#include "adc_lpc40xx.h"
#include "termistor_ntc.h"
#include "ldr.h"
#include "sonido.h"

// main para el ejercicio 2.

int main(void)
{
	uint32_t counter = 0;
	uint32_t adcVal = 0;
	float32_t tension = 0.0, iluminancia = 0.0, temperatura = 0.0;
	
	uint8_t wifiRes;
	
	char buff[100];
	
	glcd_inicializar();
	glcd_borrar(NEGRO);
	
	adc_inicializar(1000000, SEL_CANAL_0);
	adc_inicializar(1000000, SEL_CANAL_2);

	uart_inicializar(UART3, UART_BAUDRATE_9600, UART_BITS_DATOS_8, UART_PARIDAD_NINGUNA, UART_BITS_STOP_1, PUERTO0, PIN2, PUERTO0, PIN3, NULL);
	
	timer_inicializar(TIMER0);
	
	glcd_xy_texto(0,0);
	glcd_borrar(NEGRO);
	
	//WIFI_connectWlan("iPhone", "Alvaro20");
	//WIFI_connectWlan("WLAN_J3A4", "20200430");
	
	/*wifiRes = WIFI_connectWlan("iPhone", "Alvaro20");
	if(wifiRes == WIFI_ERROR || wifiRes == WIFI_FAIL){
		sonido_emitir_pitido(1000, 100);
		wifiRes = WIFI_connectWlan("WLAN_J3A4", "20200430");
		if(wifiRes == WIFI_ERROR || wifiRes == WIFI_FAIL){
			sonido_emitir_pitido(2000, 100);
		}
	}
	timer_retardo_ms(TIMER0, 5000);*/

	while(TRUE){
		adcVal = adc_convertir(0);
		tension = adc_traducir_a_tension(adcVal);
		iluminancia = ldr_traducir_a_iluminancia(tension);
		
		adcVal = adc_convertir(2);
		tension = adc_traducir_a_tension(adcVal);
		temperatura = ntc_traducir_tension_a_temperatura(tension);
		
		sprintf(buff, "{\"iluminancia\":%f,\"temperatura\":%f}", iluminancia, temperatura);
		if(WIFI_sendJSON("172.20.10.7", 8080, "/sensors", buff) == WIFI_ERROR){
			sonido_emitir_pitido(1000, 100);
			uart_transmitir_cadena(UART3, "AT+CIPCLOSE");
			/*if(WIFI_sendJSON("192.168.43.107", 8080, "/sensors", buff) == WIFI_ERROR){
				sonido_emitir_pitido(1000, 100);
			}*/
		}
		
		glcd_printf("\nContador: %d", counter);
		counter++;
		timer_retardo_ms(TIMER0, 5000);
	}
}
  
    

