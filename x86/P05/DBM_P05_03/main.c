/*
 * main.c
 *
 *  Created on: 11 mar. 2021
 *      Author: JFSR00
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sse_producto_escalar(const float *vector_1, const float *vector_2, unsigned int dimension, float *resultado);

int main(){
	const float ptr_matriz[][4] __attribute__ ((aligned (64)))=
			{	{1.0, 	2.0, 	3.0, 	4.0},
				{5.0, 	6.0, 	7.0, 	8.0},
				{9.0, 	10.0, 	11.0, 	12.0},
				{13.0, 	14.0, 	15.0, 	16.0}};
	float res = 0.0;
	int ret = 0;

	ret = sse_producto_escalar(ptr_matriz, ptr_matriz, 16, &res);

	if(ret){
		printf("%.2f\t", res);
	}else{
		printf("\nERROR");
	}
	return 0;
}
