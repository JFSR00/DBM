/*
 * main.c
 *
 *  Created on: 27 feb. 2021
 *      Author: JFSR00
 */

#include <stdio.h>
#include <stdlib.h>

#include "buscarCaracter.s"

char* b32_buscar_caracter_en_cadena(const char* cadena, char caracter);

int main(){
	char *str = "prueba";

	printf("str = %h \ncaracter = %h", str, b32_buscar_caracter_en_cadena(str, 'a'));

	return 0;
}
