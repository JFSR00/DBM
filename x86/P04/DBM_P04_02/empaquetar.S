; Función int empaquetar(const estructura *origen, estructura_empaquetada *destino);
;											RCX								RDX

; Estructura desempaquetada
;	short	2bytes		{0,	1}
;	char[3]	1bytesx3	{2,	4}
;	int		4bytes		{8,	11}
;	llong	8bytes		{16,23}
;
; Estructura empaquetada
;	short	2bytes		{0,	1}
;	char[3]	1bytesx3	{2,	4}
;	int		4bytes		{5,	8}
;	llong	8bytes		{9,16}

	global	empaquetar
	section	.text

empaquetar:
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

	mov		r8d, [rcx + 8]	; Movemos int
	mov		[rdx + 5], r8d

	mov		r8, [rcx + 16]	; Movemos long
	mov		[rdx + 9], r8

	mov		rax, 1			; En caso de no haber errores se devuelve 1
fin:
	ret
