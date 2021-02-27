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
	mov		cl, caracter	; CL = car�cter a buscar.

bucle:
	mov		ch, [edx]		; Leer un car�cter de la cadena.
	inc		edx				; Incrementar el puntero a la cadena para acceder al sig. car�cter.
	cmp		ch, 0			; Si el car�cter que se ha le�do es el terminador 0 ...
	je		salida			; salir retornando NULL => car�cter no encontrado.
	cmp		ch, cl			; Comparar el car�cter le�do con el buscado.
	jne		bucle			; Si no son iguales, repetir.

	; Si la instrucci�n JNE anterior no salta significa que se ha encontrado el car�cter buscado.
	; Debido al INC EDX dentro del bucle, EDX no sale apuntando a la posici�n dentro de la cadena
	; donde se encontr� el car�cter si no a la posici�n siguiente. Por ello, EDX se decrementa en
	; una unidad antes de cargarlo en EAX.

	dec		edx
	mov		eax, edx		; EAX retorna un puntero a la posici�n donde se encontr� el car�cter.

salida:
	pop		ebp
	ret

