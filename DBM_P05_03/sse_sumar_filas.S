
; int sse_producto_escalar(	const float *vector_1,	RCX
;							const float *vector_2,	RDX
;							unsigned int dimension,	R8
;							float *resultado);		R9


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

		mov		r11, rdx		; Guardamos RDX para no perder su contenido por la división siguiente

		mov		eax, r8d		; Calculamos la cantidad de bloques, cociente en EAX, resto en EDX, divisor en R10D
		mov		r10d, 16
		div		r10d

		mov		r10d, edx		; Guardamos el resto en R10D
		mov		rdx, r11		; Restauramos el valor de RDX


		pxor	xmm2, xmm2		; Acumulador

bucle:
		movaps	xmm0, [rcx]
		movaps	xmm1, [rdx]
		mulps	xmm0, xmm1
		addps	xmm2, xmm0

		add		rcx, 16			; Actualización
		add		rdx, 16
		dec		eax
		jnz		bucle

		haddps	xmm2, xmm2
		haddps	xmm2, xmm2

menor_16:
		test	r10d, r10d		; Comprobamos que el resto es distinto de 0
		jz		salir
bucle_:
		movss	xmm0, [rcx]
		movss	xmm1, [rdx]
		mulss	xmm0, xmm1
		addss	xmm2, xmm0

		add		rcx, 4
		add		rdx, 4
		dec		r10d
		jnz		bucle_

		movss	[r9d], xmm2

salir:
		mov		eax, 1
		jmp		fin
error:
		xor		eax, eax
fin:
		ret
