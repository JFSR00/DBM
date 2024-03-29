; Funci�n void uint_a_cadena_binario(unsigned int dato, char* buffer)

	global	_uint_a_cadena_binario

	section	.text

_uint_a_cadena_binario:
	push	ebp
	mov		ebp, esp
	push	esi
	push	ecx
	push	edx

	%define	dato	dword [ebp + 8]		; Definimos dato y buff para facilitarnos el acceso a los par�metros de la funci�n
	%define	buff	dword [ebp + 12]

	mov		esi, buff					; Cargamos en registros nuestros par�metros
	test	esi, esi					; Comprobamos que el puntero a buffer no es nulo, y en caso de serlo terminar
	jz		fin							; La ejecuci�n de la funci�n

	mov		edx, dato
	mov		ecx, 32						; ECX ser� contador

bucle:


	xor		al, al						; Vamos rotando el n�mero para ir ley�ndolo bit a bit mediante el flag de acarreo
	shl		edx, 1
	adc		al, '0'						; Cargamos en AL el car�cter a almacenar a partir de sumar el c�digo ASCII del
										; car�cter 0 y el acarreo obtenido de la instrucci�n anterior
	mov		[esi], al
	inc		esi

	dec		ecx
	jnz		bucle

	mov		byte [esi], 0x00			; Cargamos al final de la cadena el car�cter nulo

fin:
	pop		edx
	pop		ecx
	pop		esi
	pop		ebp
	ret
