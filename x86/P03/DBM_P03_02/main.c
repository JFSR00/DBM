/*
 * main.c
 *
 *  Created on: 11 mar. 2021
 *      Author: JFSR00
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sumar_diagonal(long *matriz, unsigned int num_filas_columnas, long *resultado);

int main(){
	long array[3][3] = {{1,2,3}, {2,1,3}, {3,2,1}};
	unsigned int n= 3;
	long res;
	int ret;

	ret = sumar_diagonal(array, n, &res);

	if (ret != 0)
		printf("\nResultado: %li", res);
	else
		printf("\nError");

	return 0;
}
