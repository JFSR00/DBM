/***************************************************************************//**
 * \file    main.c
 *
 * \brief   Función main para la práctica 8.
 */

#include <LPC407x_8x_177x_8x.h>
#include <stdlib.h>
#include <string.h>
#include "glcd.h"
#include "adc_lpc40xx.h"
#include "timer_lpc40xx.h"
#include "ldr.h"
#include "leds.h"
#include "teclado_4x4.h"
#include "sonido.h"

int main(void)
{
	uint32_t adcVal = 0;
	float32_t tension = 0.0, iluminancia = 0.0;
	
	adc_inicializar(1000000, SEL_CANAL_0);
	
	sonido_inicializar();
	
	glcd_inicializar();
	glcd_borrar(NEGRO);
	
	timer_inicializar(TIMER0);
	timer_iniciar_ciclos_ms(TIMER0, 1000);
	
	//sonido_emitir_pitido(1000, 100);
	
	while(TRUE){
		adcVal = adc_convertir(0);
		tension = adc_traducir_a_tension(adcVal);
		iluminancia = ldr_traducir_a_iluminancia(tension);
		
		/*
		if(iluminancia < 100){
			sonido_emitir_pitido(1000, 100);
		}
		*/
		
		glcd_xy_texto(0,0);
		glcd_printf("Resultado ADC:\t\t%4d\nTensión:\t\t%.2f\nIluminancia:\t%9.3f\n", adcVal, tension, iluminancia);
		
		timer_esperar_fin_ciclo(TIMER0);
	}
}
