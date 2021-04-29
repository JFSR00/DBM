
; int sse_imagen_a_blanco_y_negro(unsigned char *ptr_imagen,	RCX
;                                 int ancho,					RDX
;                                 int alto,						R8
;                                 unsigned char umbral);		R9


        global      sse_imagen_a_blanco_y_negro

        section    .text

sse_imagen_a_blanco_y_negro:
		test	rcx, rcx		; Puntero NULL
		jz		error
		test	rcx, 15			; Alineado a 16
		jnz		error
		cmp		edx, 0			; Ancho > 0
		jz		error
		cmp		r8d, 0			; Alto > 0
		jz		error

		imul	edx, r8d
		mov		eax, edx

		movd	xmm1, r9d		; Cargamos el umbral en registro para la conversión de la imagen
		pxor	xmm0, xmm0
		pshufb	xmm1, xmm0

		shr		eax, 4			; Dividimos el número de píxeles en bloques de 16 bytes
		mov		r10d, eax
		cmp		eax, 0
		jz		menor_16_pixeles

bucle:
		movdqa	xmm0, [rcx]		; Cargamos primer bloque de 16 bytes
		pminub	xmm0, xmm1		; Igualamos al umbral los bytes que estén por encima del mismo
		pcmpeqb	xmm0, xmm1		; Igualamos a 255 los bytes que sean iguales al umbral y a 0 el resto
		movdqa	[rcx], xmm0		; Almacenamos bloque modificado

		add		rcx, 16
		dec		r10d
		jnz		bucle


menor_16_pixeles:
		and		edx, 0xF
		jz		salir
bucle_:
		mov		al, [rcx]		; Realizamos las mismas operaciones anteriores byte a byte
		cmp		al, r9b
		jl		negro
		mov		byte[rcx], 0xFF
		jmp		bucle_1
negro:
		mov		byte[rcx], 0x00
bucle_1:
		inc		rcx
		dec		edx
		jnz		bucle_

salir:
		mov		eax, 1
		jmp		fin
error:
		xor		eax, eax
fin:
		ret
