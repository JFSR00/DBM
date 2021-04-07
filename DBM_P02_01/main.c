/*
 * main.c
 *
 *  Created on: 11 mar. 2021
 *      Author: JFSR00
 */


#include <stdio.h>

void uint_a_cadena_binario(unsigned int dato, char* buffer);

int main(int argc, char *argv[]){
	unsigned int num;
	char t, buffer[33];

	/* Desactivar el buffer de stdout para facilitar la depuración a través de
	*  la consola de Eclipse.
	*/
	setvbuf(stdout, NULL,_IONBF, 0);

	printf("\nIntroduzca numero en hexadecimal sin 0x: "); scanf("%x", &num);

	uint_a_cadena_binario(num, buffer);

	printf("\nEl resultado es 0b%s", buffer);
	printf("\nPulse 's' y ENTER para salir. ");
	do{
		scanf("%c", &t);
	}while(t != 's' && t != 'S');
	return 0;
}
