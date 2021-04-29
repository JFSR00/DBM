; Función int sumar_diagonal(long *matriz, unsigned int num_filas_columnas, long *resultado);
;										RCX					RDX							R8

	global	sumar_diagonal

	section	.text

; Movimiento en diagonal: (num_col + 1) * 4

sumar_diagonal:
	xor		eax, eax

	test	rcx, rcx		; Verificamos que los punteros no son nulos
	jz		error
	test	r8, r8
	jz		error
	cmp		edx, 0
	jz		error

	mov		r10, rdx
	add		r10, 1
	shl		r10, 2

bucle:
	add		eax, [rcx]
	add		rcx, r10
	dec		rdx
	jnz		bucle

	mov		[r8], eax
	mov		eax, 1

error:						; Fin de la función
	ret
