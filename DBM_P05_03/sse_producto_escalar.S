
; int sse_producto_escalar(	const float *vector_1,	RCX
;							const float *vector_2,	RDX
;							unsigned int dimension,	R8
;							float *resultado);		R9

;---------| No funciona |---------

        global      sse_producto_escalar

        section    .text

sse_producto_escalar:
		test	rcx, rcx		; Puntero NULL
		jz		error
		test	rcx, 15			; Alineado a 16
		jnz		error
		test	rdx, rdx		; Puntero NULL
		jz		error
		test	rdx, 15			; Alineado a 16
		jnz		error

		cmp		r8d, 16
		jl		menor_16

		mov		eax, r8d		; Calculamos la cantidad de bloques, dividimos entre 16 mediante 4 desplazamientos a la derecha,
		shr		eax, 4			; resultado en EAX

		mov		r10d, r8d		; Guardamos lo que sería el resto de la división en R10D
		and		r10d, 0x0000000f

		pxor	xmm2, xmm2		; Acumulador

bucle:
		movaps	xmm0, [rcx]		; Realizamos las multiplicaciones entre elementos
		movaps	xmm1, [rdx]
		mulps	xmm0, xmm1
		addps	xmm2, xmm0		; Sumamos los resultados de las multiplicaciones

		add		rcx, 16			; Actualización
		add		rdx, 16
		dec		eax
		jnz		bucle

		haddps	xmm2, xmm2		; Sumamos todos los resultados anteriores
		haddps	xmm2, xmm2

menor_16:
		test	r10d, r10d		; Comprobamos que el resto es distinto de 0
		jz		salir
bucle_:
		movss	xmm0, [rcx]		; Multiplicamos los elementos de mismo índice de nuevo
		movss	xmm1, [rdx]
		mulss	xmm0, xmm1
		addss	xmm2, xmm0		; Sumamos los resultados de las multiplicaciones

		add		rcx, 4
		add		rdx, 4
		dec		r10d
		jnz		bucle_

		movss	[r9d], xmm2		; Almacenamos el resultado de la función en la variable proporcionada en los parámetros

salir:
		mov		eax, 1
		jmp		fin
error:
		xor		eax, eax
fin:
		ret
