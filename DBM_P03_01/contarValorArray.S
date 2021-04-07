; Función int contar_valor_en_array(int valor, int *array, unsigned int longitud, int *resultado);
;										RCX			RDX					R8				R9

	global	_contar_valor_en_array

	section	.text

_contar_valor_en_array:
	xor		eax, eax

	test	rdx, rdx		; Verificamos que los punteros no son nulos
	jz		error
	test	r9, r9
	jz		error
	test	r8, r8
	jz		error

bucle:
	cmp		[rdx], ecx
	jnz		no_inc
	inc		eax
no_inc:
	add		rdx, 4
	dec		r8
	jnz		bucle

	mov		[r9], eax
	mov		eax, 1

error:						; Fin de la función
	ret
