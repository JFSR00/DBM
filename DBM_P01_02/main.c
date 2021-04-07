/*
 * main.c
 *
 *  Created on: 6 mar. 2021
 *      Author: Juan Francisco Santos Relinque
 */

#include <stdio.h>

int det(int a11, int a12, int a21, int a22);

int main(int argc, char *argv[]){
	int a11, a12, a21, a22, res;
	char t;

	/* Desactivar el buffer de stdout para facilitar la depuración a través de
	*  la consola de Eclipse.
	*/
	setvbuf(stdout, NULL,_IONBF, 0);

	printf("\nIntroduzca elemento 11: "); scanf("%d", &a11);
	printf("\nIntroduzca elemento 12: "); scanf("%d", &a12);
	printf("\nIntroduzca elemento 21: "); scanf("%d", &a21);
	printf("\nIntroduzca elemento 22: "); scanf("%d", &a22);

	res = det(a11, a12, a21, a22);

	printf("\nEl determinante es %d", res);
	printf("\nPulse 's' y ENTER para salir. ");
	do{
		scanf("%c", &t);
	}while(t != 's' && t != 'S');

	return 0;
}
