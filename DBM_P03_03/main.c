/*
 * main.c
 *
 *  Created on: 11 mar. 2021
 *      Author: JFSR00
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ordenar(int *array, unsigned int longitud);

int main(){
	int array[10] = {1, -2, 3, 3, 3, 4, 5, 6, -7, 3};
	unsigned int n= 10;
	int ret;

	ret = ordenar(array, n);

	printf("\n");
	if (ret != 0){
		for(int i = 0; i<n; i++){
			printf("%d ", array[i]);
		}
	}
	else{
		printf("\nError");
	}

	return 0;
}
