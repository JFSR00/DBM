/*
 * main.c
 *
 *  Created on: 6 mar. 2021
 *      Author: Juan Francisco Santos Relinque
 */

#include <stdio.h>

unsigned int fun(unsigned int num1, unsigned int num2);

int main(int argc, char *argv[]){
	unsigned int num1, num2, res;
	char t;

	/* Desactivar el buffer de stdout para facilitar la depuración a través de
	*  la consola de Eclipse.
	*/
	setvbuf(stdout, NULL,_IONBF, 0);

	printf("\nIntroduzca numero 1 en hexadecimal sin 0x: "); scanf("%x", &num1);
	printf("\nIntroduzca numero 2 en hexadecimal sin 0x: "); scanf("%x", &num2);

	res = fun(num1, num2);

	printf("\nEl resultado es 0x%x", res);
	printf("\nPulse 's' y ENTER para salir. ");
	do{
		scanf("%c", &t);
	}while(t != 's' && t != 'S');

	return 0;
}
