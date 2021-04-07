/*
 * main.c
 *
 *  Created on: 11 mar. 2021
 *      Author: JFSR00
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	short a;
	char b[3];
	int c;
	long long d;
}estructura;

typedef struct __attribute((packed))__{
	short a;
	char b[3];
	int c;
	long long d;
}estructura_empaquetada;

int empaquetar(const estructura *origen, estructura_empaquetada *destino);
int desempaquetar(const estructura_empaquetada *origen, estructura *destino);

int main(){
	estructura un_pack;
	estructura_empaquetada pack;
	int ret = 0;

	un_pack.a = 12;
	un_pack.b[0] = 'a';
	un_pack.b[1] = 'b';
	un_pack.b[2] = '\0';
	un_pack.c = 45;
	un_pack.d = 67;
	printf("\n%d %s %d %I64i", un_pack.a, un_pack.b, un_pack.c, un_pack.d);

	/*
	pack.a = 12;
	pack.b[0] = 'a';
	pack.b[1] = 'b';
	pack.b[2] = '\0';
	pack.c = 45;
	pack.d = 67;
	printf("\n%d %s %d %I64i", pack.a, pack.b, pack.c, pack.d);
	*/

	//ret = desempaquetar(&pack, &un_pack);
	ret = empaquetar(&un_pack, &pack);

	printf("\n");
	if (ret != 0){
		//printf("\n%d %s %d %I64i", un_pack.a, un_pack.b, un_pack.c, un_pack.d);
		printf("\n%d %s %d %I64i", pack.a, pack.b, pack.c, pack.d);
	}
	else{
		printf("\nError");
	}

	return 0;
}
