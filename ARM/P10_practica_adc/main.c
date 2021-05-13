/***************************************************************************//**
 * \file    main.c
 *
 * \brief   Función main para la práctica 10.
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "adc_lpc40xx.h"
#include "timer_lpc40xx.h"
#include "termistor_ntc.h"

int main(void)
{
	uint32_t adcVal = 0, i;
	float32_t tension = 0.0, temp = 0.0, acumulador;
	
	adc_inicializar(1000000, SEL_CANAL_0);
	
	glcd_inicializar();
	glcd_borrar(NEGRO);
	
	timer_inicializar(TIMER0);
	timer_iniciar_ciclos_ms(TIMER0, 10);
	
	while(TRUE){
		for(i = 0, acumulador = 0.0; i < 100; i++){
			adcVal = adc_convertir(0);
			tension = adc_traducir_a_tension(adcVal);
			temp = ntc_traducir_tension_a_temperatura(tension);
			glcd_xy_texto(0,0);
			glcd_printf("Resultado ADC:\t\t%4d\nTensión potenciómetro:\t%.2f\nTemperatura:\t\t%.3f\n", adcVal, tension, temp);
			
			acumulador += temp;
			
			timer_esperar_fin_ciclo(TIMER0);
		}
		acumulador /= 100;
		glcd_printf("Temperatura media:\t%.3f", acumulador);
	}
}
