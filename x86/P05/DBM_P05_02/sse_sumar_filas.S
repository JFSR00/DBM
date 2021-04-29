
; int sse_sumar_filas(const float *ptr_matriz, float *ptr_suma);
;									RCX					RDX


        global      sse_sumar_filas

        section    .text

sse_sumar_filas:
		test	rcx, rcx		; Puntero NULL
		jz		error
		test	rcx, 15			; Alineado a 16
		jnz		error
		test	rdx, rdx		; Puntero NULL
		jz		error
		test	rdx, 15			; Alineado a 16
		jnz		error

		movaps	xmm0, [rcx]		; Cargamos las filas a los registros XMM
		movaps	xmm1, [rcx + 16]
		movaps	xmm2, [rcx + 32]
		movaps	xmm3, [rcx + 48]

		addps	xmm0, xmm1		; Sumamos en XMM0 el resto de registros
		addps	xmm0, xmm2
		addps	xmm0, xmm3

		movaps	[rdx], xmm0		; Almacenamos en ptr_suma el resultado de la suma

salir:
		mov		eax, 1
		jmp		fin
error:
		xor		eax, eax
fin:
		ret
