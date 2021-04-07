; Función int ordenar(int *array, unsigned int longitud);
;							RCX					RDX
	global	ordenar
	section	.text

ordenar:
	push	rsi
	push	rdi

	xor		rax, rax

	test	rcx, rcx	; Verificamos que los punteros no son nulos
	jz		error

	cmp		rdx, 1		; Verificamos que la longitud del array sea mayor que 1
	jle		error

	mov		r9, rcx		; Preparar puntero R9
	add		r9, 4

	mov		rdi, rcx	; Guardar punteros RCX y R9 en RDI y RSI respectivamente
	mov		rsi, r9

	sub		rdx, 1		; Guardar RDX en RAX, longitud del array para el bucle externo
	mov		rax, rdx

bucle:
	mov		r10d, [rcx]	; Almacenar los elementos a comparar en r10 y r11
	mov		r11d, [r9]
	cmp		r10d, r11d	; Comparamos si el siguiente dato es menor que su anterior
	jle		no_inter	; En caso de que el dato anterior sea mayor, se intercambian

	mov		[rcx], r11d	; Intercambio de memoria
	mov		[r9], r10d

no_inter:
	add		rcx, 4		; Incrementamos los punteros para que apunten al siguiente elemento del array
	add		r9, 4
	dec		rdx			; Decrementamos el contador de elementos restantes
	jnz		bucle		; Si el contador es distinto de 0 seguimos iterando

	mov		rcx, rdi	; Reiniciar los punteros a los valores iniciales
	mov		r9, rsi

	dec		rax			; Actualizar contador
	mov		rdx, rax
	cmp		rdx, 0
	jnz		bucle

	mov		eax, 1		; Salida de la función

error:					; Fin de la función
	pop		rdi
	pop		rsi

	ret
