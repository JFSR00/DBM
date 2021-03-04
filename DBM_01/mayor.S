/*
 * mayor.S
 *
 *  Created on: 4 mar. 2021
 *      Author: JFSR00
 */

	global	_mayor

	section	.text

_mayor:
	push	ebp
	mov		ebp, esp

	mov		eax, [ebp + 8]
	cmp		eax, [ebp + 12]
	jge		short el_primero_es_mayor
	mov		eax, [ebp + 12]

el_primero_es_mayor:
	pop	ebp
	ret
