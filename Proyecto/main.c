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
#include "rtc_lpc40xx.h"
#include "termistor_ntc.h"
#include "ldr.h"
#include "sonido.h"
#include "watchdog.h"

// Configuración de red WiFi ---------------------------------------------------------------
//#define WLAN	"WLAN_J3A4"
//#define PASS	"20200430"
#define WLAN	"iPhone"
#define PASS	"Alvaro20"

// Configuración host ----------------------------------------------------------------------
#define	HOST	"172.20.10.7"
#define	PORT	8080
#define	URL		"/sensors"

int main(void)
{
	// Declaración de variables --------------------------------------------------------------
	uint32_t counter = 0;
	uint32_t adcVal = 0;
	float32_t tension = 0.0, iluminancia = 0.0, temperatura = 0.0;
	
	uint32_t dia, mes, anno, horas, minutos, segundos;
	
	uint8_t wifiRes;
	
	char buff[100];
	
	// Inicialización de componentes ---------------------------------------------------------
	// Reiniciamos módulo WiFi
	gpio_ajustar_dir(PORT0, PIN21, DIR_SALIDA);
	gpio_escribir_pin(PORT0, PIN21, 0);
	gpio_escribir_pin(PORT0, PIN21, 1);
	
	// Inicializamos módulo Real Time Clock
	rtc_inicializar();
	rtc_ajustar_fecha(7, 6, 2021);
	rtc_ajustar_hora(12, 00, 00);
	
	// Inicializamos watchdog a 30 segundos
	// Este watchdog será el encargado de reiniciar el microcontrolador en caso de que se quede bloqueado esperando alguna respuesta del módulo WiFi
	WD_set(30);
	
	// Inicializamos pantalla LCD
	glcd_inicializar();
	glcd_xy_texto(0,0);
	glcd_borrar(NEGRO);
	
	// Inicializamos conversor analógico digital
	adc_inicializar(1000000, SEL_CANAL_0);
	adc_inicializar(1000000, SEL_CANAL_2);

	// Inicializamos UART 3
	uart_inicializar(UART3, UART_BAUDRATE_9600, UART_BITS_DATOS_8, UART_PARIDAD_NINGUNA, UART_BITS_STOP_1, PUERTO0, PIN2, PUERTO0, PIN3, NULL);
	
	// Inicializamos Timer 0 para realizar retardos
	timer_inicializar(TIMER0);
	
	// Configuración de conexión red WiFi
	glcd_printf("Conectando WiFi ...\n\r");
	wifiRes = WIFI_connectWlan(WLAN, PASS);
	if(wifiRes == WIFI_ERROR || wifiRes == WIFI_FAIL){
		sonido_emitir_pitido(1000, 100);	// En caso de error se notifica metiante un pitido, pero no se bloquea el funcionamiento, pues puede conectarse a dicha red
	}																		// de manera asíncrona posteriormente, ya que ha sido configurada
	
	WD_feed();											// Reiniciamos el watchdog
	timer_retardo_ms(TIMER0, 5000);	// Esperamos a que se complete la conexión WiFi antes de enviar el primer paquete

	// Bucle principal -----------------------------------------------------------------------
	while(TRUE){
		// Leemos el LDR y convertimos dicha lectura a iluminancia
		adcVal = adc_convertir(0);
		tension = adc_traducir_a_tension(adcVal);
		iluminancia = ldr_traducir_a_iluminancia(tension);
		
		// Leemos el termistor NTC y convertimos dicha lectura a temperatura
		adcVal = adc_convertir(2);
		tension = adc_traducir_a_tension(adcVal);
		temperatura = ntc_traducir_tension_a_temperatura(tension);
		
		// Leemos la fecha y hora actual para marcar el paquete a enviar
		rtc_leer_fecha(&dia, &mes, &anno);
		rtc_leer_hora(&horas, &minutos, &segundos);
		
		// Creamos el paquete JSON a enviar a partir de los datos que hemos cargado en variables, tales como la iluminancia, temperatura y fecha de la captura
		sprintf(buff, "{\"iluminancia\":%f,\"temperatura\":%f,\"fecha\":\"%4d/%02d/%02d - %02d:%02d:%02d\"}", iluminancia, temperatura, anno, mes, dia, horas, minutos, segundos);
		wifiRes = WIFI_sendJSON(HOST, PORT, URL, buff);
		if(wifiRes == WIFI_ERROR || wifiRes == WIFI_FAIL){	// En caso de error o fallo de envío se emite un pitido como señal de notificación
			sonido_emitir_pitido(1000, 100);									// Para solventar este error se cierra la conexión en caso de que estuviese abierta
			uart_transmitir_cadena(UART3, "AT+CIPCLOSE");			// y seguidamente se esperan 5 segundos para que el módulo WiFi esté listo para
			timer_retardo_ms(TIMER0, 5000);										// enviar el siguiente paquete
		}else if(wifiRes == WIFI_BUSY){											// En caso de que el código de error sea debido a que el módulo WiFi se encuentre ocupado
			timer_retardo_ms(TIMER0, 15000);									// se esperan 15 segundos para que el módulo WiFi termine la tarea que esté realizando
		}
		
		// Mostramos el contador de paquetes enviados
		glcd_printf("\nContador: %d", counter);
		counter++;
		
		// Reiniciamos el watchdog de nuevo
		WD_feed();
		
		// Esperamos 5 segundos con el objetivo de que el módulo WiFi termine el envío del paquete
		timer_retardo_ms(TIMER0, 5000);
	}
}
  
    

