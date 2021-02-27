; buscarCaracter.s
;
;  Created on: 27 feb. 2021
;      Author: JFSR00

global b32_buscar_caracter_en_cadena

section .text

b32_buscar_caracter_en_cadena:
	push	ebp
	mov		ebp, esp

%define cadena[ebp+8]
%define caracter[ebp+12]

	xor		eax, eax		; Si error, salir retornando NULL.
	mov		edx, cadena		; EDX = puntero a la cadena.
	test	edx, edx
	jz		salida			; Si puntero a cadena es NULL, salir retornando NULL.
	mov		cl, caracter	; CL = carácter a buscar.

bucle:
	mov		ch, [edx]		; Leer un carácter de la cadena.
	inc		edx				; Incrementar el puntero a la cadena para acceder al sig. carácter.
	cmp		ch, 0			; Si el carácter que se ha leído es el terminador 0 ...
	je		salida			; salir retornando NULL => carácter no encontrado.
	cmp		ch, cl			; Comparar el carácter leído con el buscado.
	jne		bucle			; Si no son iguales, repetir.

	; Si la instrucción JNE anterior no salta significa que se ha encontrado el carácter buscado.
	; Debido al INC EDX dentro del bucle, EDX no sale apuntando a la posición dentro de la cadena
	; donde se encontró el carácter si no a la posición siguiente. Por ello, EDX se decrementa en
	; una unidad antes de cargarlo en EAX.

	dec		edx
	mov		eax, edx		; EAX retorna un puntero a la posición donde se encontró el carácter.

salida:
	pop		ebp
	ret

