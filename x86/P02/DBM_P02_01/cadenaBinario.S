; Función void uint_a_cadena_binario(unsigned int dato, char* buffer)

	global	_uint_a_cadena_binario

	section	.text

_uint_a_cadena_binario:
	push	ebp
	mov		ebp, esp
	push	esi
	push	ecx
	push	edx

	%define	dato	dword [ebp + 8]		; Definimos dato y buff para facilitarnos el acceso a los parámetros de la función
	%define	buff	dword [ebp + 12]

	mov		esi, buff					; Cargamos en registros nuestros parámetros
	test	esi, esi					; Comprobamos que el puntero a buffer no es nulo, y en caso de serlo terminar
	jz		fin							; La ejecución de la función

	mov		edx, dato
	mov		ecx, 32						; ECX será contador

bucle:


	xor		al, al						; Vamos rotando el némero para ir leyéndolo bit a bit mediante el flag de acarreo
	shl		edx, 1
	adc		al, '0'						; Cargamos en AL el carácter a almacenar a partir de sumar el código ASCII del
										; carácter 0 y el acarreo obtenido de la instrucción anterior
	mov		[esi], al
	inc		esi

	dec		ecx
	jnz		bucle

	mov		byte [esi], 0x00			; Cargamos al final de la cadena el carácter nulo

fin:
	pop		edx
	pop		ecx
	pop		esi
	pop		ebp
	ret
