; Función int calcular_histograma(const unsigned char *ptr_datos, unsigned int num_datos, unsigned int *ptr_histograma);
;															RCX					RDX							R8
	global	calcular_histograma
	section	.text

calcular_histograma:
	test	rcx, rcx					; Verificamos que los punteros que nos han pasado son distintos de 0
	jz		error
	test	r8, r8
	jz		error

	mov		r9, 256
	mov		r10, r8
bucle_ini:								; Ponemos a 0 el array donde se almacenarán los resultados
	mov		dword [r8], 0
	add		r8, 4
	dec		r9
	jnz		bucle_ini

	xor		r11, r11
computo:								; Comenzamos el cómputo de las repeticiones
	mov		r11b, [rcx]
	add		dword [r10 + r11 * 4], 1	; Incrementamos en memoria el número de repeticiones
	inc		rcx
	dec		rdx
	jnz		computo

	mov		eax, 1						; En caso de no haber errores se devuelve 1
	jmp		fin
error:
	xor		eax, eax					; En caso de error se devuelve 0
fin:
	ret
