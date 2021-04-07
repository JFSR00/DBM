; Función int desempaquetar(const estructura_empaquetada *origen, estructura *destino);
;															RCX					RDX

; Estructura desempaquetada
;	short	2bytes		{0,	1}
;	char[3]	1bytesx3	{2,	4}
;	int		4bytes		{8,	11}
;	long	8bytes		{16,23}
;
; Estructura empaquetada
;	short	2bytes		{0,	1}
;	char[3]	1bytesx3	{2,	4}
;	int		4bytes		{5,	8}
;	long	8bytes		{9,16}

	global	desempaquetar
	section	.text

desempaquetar:
	xor		rax, rax		; En caso de error se devuelve 0
	test	rcx, rcx		; Verificamos que los punteros que nos han pasado son distintos de 0
	jz		fin
	test	rdx, rdx
	jz		fin

	xor		r8, r8

	mov		r8w, [rcx]		; Movemos short
	mov		[rdx], r8w

	mov		r8d, [rcx + 2]	; Movemos char[3]
	mov		[rdx + 2], r8w
	shr		r8, 16
	mov		[rdx + 4], r8b

	mov		r8d, [rcx + 5]	; Movemos int
	mov		[rdx + 8], r8d

	mov		r8, [rcx + 9]	; Movemos long
	mov		[rdx + 16], r8

	mov		rax, 1			; En caso de no haber errores se devuelve 1
fin:
	ret
