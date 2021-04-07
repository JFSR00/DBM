/*
 * main.c
 *
 *  Created on: 11 mar. 2021
 *      Author: JFSR00
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _contar_valor_en_array(int valor, int *array, unsigned int longitud, int *resultado);

int main(){
	int array[10] = {1, 2, 3, 3, 3, 4, 5, 6, 7, 3};
	int valor = 3;
	int ret;
	int cuenta;

	ret = _contar_valor_en_array(valor, array, 10, &cuenta);

	if (ret != 0)
		printf("\nEl valor %d aparece %u veces.", valor, cuenta);
	else
		printf("\nError");

	return 0;
}
