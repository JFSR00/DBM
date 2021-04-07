/*
 * main.c
 *
 *  Created on: 11 mar. 2021
 *      Author: JFSR00
 */


#include <stdio.h>

void convertir_celcius_fahrenheit(int temperatura_entrada, int sentido_conversion, int *temperatura_salida);

int main(int argc, char *argv[]){
	int t_entr, s_conv, t_sali[1];
	char t;

	/* Desactivar el buffer de stdout para facilitar la depuración a través de
	*  la consola de Eclipse.
	*/
	setvbuf(stdout, NULL,_IONBF, 0);

	printf("\nIntroduzca unidad de entrada (0= Celsius, 1= Fahrenheit): "); scanf("%d", &s_conv);
	printf("\nIntroduzca temperatura: "); scanf("%d", &t_entr);

	convertir_celcius_fahrenheit(t_entr, s_conv, t_sali);

	if(s_conv != 0){
		printf("\nEl el cambio de temperatura es %d C", t_sali[0]);
	}else{
		printf("\nEl el cambio de temperatura es %d F", t_sali[0]);
	}
	printf("\nPulse 's' y ENTER para salir. ");
	do{
		scanf("%c", &t);
	}while(t != 's' && t != 'S');
	return 0;
}
