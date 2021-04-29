	global	_mayor

	section	.text

_mayor:
	push	ebp
	mov		ebp, esp

	mov		eax, [ebp + 8]
	cmp		eax, [ebp + 12]
	cmovl	eax, [ebp + 12]		; Haciendo uso de esta instrucción nos ahorramos el salto que está actualmente
								; comentado, ya que esta instrucción se encarga de realizar el movimiento al
								; registro EAX en función del contenido del registro de estado, el cual ha sido
								; actualizado mediante la anterior instrucción CMP

;	jge		short el_primero_es_mayor
;	mov		eax, [ebp + 12]

;el_primero_es_mayor:
	pop	ebp
	ret
