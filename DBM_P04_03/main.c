/*
 * main.c
 *
 *  Created on: 11 mar. 2021
 *      Author: JFSR00
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int es_palindromo(const char *cadena);

int main(){
	//char palabra[128];
	char *palabra = "holaloh";
	int ret = 0;

	/* Desactivar el buffer de stdout para facilitar la depuración a través de
	*  la consola de Eclipse.
	*/
	setvbuf(stdout, NULL,_IONBF, 0);

	printf("\nIntroduzca una palabra: ");
	//scanf("%s", palabra);

	ret = es_palindromo(palabra);

	switch(ret){
	case 1:
		printf("\nLa palabra introducida es un palindromo");
		break;
	case 0:
		printf("\nLa palabra introducida NO es un palindromo");
		break;
	default:
		printf("\nERROR");
		break;
	}

	return 0;
}
