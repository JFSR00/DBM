/*
 * main.c
 *
 *  Created on: 11 mar. 2021
 *      Author: JFSR00
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcular_histograma(const unsigned char *ptr_datos, unsigned int num_datos, unsigned int *ptr_histograma);

int main(){
	unsigned int histograma[256];
	unsigned char array[10] = {1, 2, 3, 3, 3, 4, 5, 6, 7, 3};
	unsigned int n= 10;
	int ret;

	ret = calcular_histograma(array, n, histograma);

	printf("\n");
	if (ret != 0){
		for(int i = 0; i<n; i++){
			printf("%d ", histograma[i]);
		}
	}
	else{
		printf("\nError");
	}

	return 0;
}
