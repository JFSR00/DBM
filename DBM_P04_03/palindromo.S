; Función int es_palindromo(const char *cadena);
;										RCX
	global	es_palindromo
	section	.text

es_palindromo:
	push	rdi

	xor		rax, rax
	test	rcx, rcx		; Verificamos que los punteros que nos han pasado son distintos de 0
	jz		error

; Longitud de cadena
	mov		rdi, rcx
	cld

	repne	scasb

; ptr inicio y fin de cadena y contador long/2
;	r11				r8				rax
	mov		r8, rdi
	mov		r11, rcx

	mov		rax, rdi		; Hacemos la diferencia de fin - inicio
	sub		rax, rcx		; para poder calcular long/2
	shr		rax, 1			; Realizamos la división entre dos

; Comparar caracteres
; r10 contador de la comparación de caracteres
; r9 carárcter comp r9==[r8]
;	mov		r10, rax
;	dec		r8
bucle:
	mov		r9b, [r8]
	cmp		[r11], r9b
	jne		no_pal
	inc		r11
	dec		r8

	dec		rax
	jnz		bucle

palindromo:
	mov		eax, 1			; En caso de no haber errores se devuelve 1
	jmp		fin
error:
	mov		eax, -1
	jmp		fin
no_pal:
	xor		eax, eax
fin:
	pop		rdi
	ret
