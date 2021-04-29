/*
 * main.c
 *
 *  Created on: 11 mar. 2021
 *      Author: JFSR00
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sse_sumar_filas(const float *ptr_matriz, float *ptr_suma);

int main(){
	const float ptr_matriz[][4] __attribute__ ((aligned (64)))=
			{	{1.0, 	2.0, 	3.0, 	4.0},
				{5.0, 	6.0, 	7.0, 	8.0},
				{9.0, 	10.0, 	11.0, 	12.0},
				{13.0, 	14.0, 	15.0, 	16.0}};
	float ptr_suma[4] __attribute__ ((aligned (16))) = {0.0, 0.0, 0.0, 0.0};
	int ret = 0;

	ret = sse_sumar_filas(ptr_matriz, ptr_suma);

	if(ret){
		for(int i=0; i<4; i++){
			printf("%.2f\t", ptr_suma[i]);
		}
	}else{
		printf("\nERROR");
	}
	return 0;
}
