/*
 * main.c
 *
 *  Created on: 11 mar. 2021
 *      Author: JFSR00
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void * copiar_bloque_memoria(void * destino, void * origen, unsigned int longitud);

int main(int argc, char *argv[]){
	int orig[20], dest[20];
	//char t;

	/* Desactivar el buffer de stdout para facilitar la depuración a través de
	*  la consola de Eclipse.
	*/
	setvbuf(stdout, NULL,_IONBF, 0);

	for(int i = 0; i < 20; i++){
		orig[i]=i;
		printf("%d ", i);
	}

	copiar_bloque_memoria(orig, dest, sizeof(int)*20);

	printf("\nResultado copia: %d", memcmp(orig, dest, sizeof(int)*20));
	printf("\n");
	for(int i = 0; i < 20; i++){
		printf("%d ", dest[i]);
	}
	printf("\nPulse 's' y ENTER para salir. ");
	/*do{
		scanf("%c", &t);
	}while(t != 's' && t != 'S');*/
	return 0;
}
