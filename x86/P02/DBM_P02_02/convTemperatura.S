; Función void convertir_celcius_fahrenheit(int temperatura_entrada, int sentido_conversion, int *temperatura_salida)

	global	_convertir_celcius_fahrenheit

	section	.text

_convertir_celcius_fahrenheit:
	push	ebp
	mov		ebp, esp
	push	esi

	%define	temp_entrada	dword [ebp + 8]			; Definimos parármetros de la función
	%define	sentido_conversion	dword [ebp + 12]
	%define	p_temp_salida	dword [ebp + 16]

	mov		esi, p_temp_salida				; Comprobamos que la dirección donde se debe devolver
	test	esi, esi						; el resultado no es nula
	jz		fin

	mov		eax, temp_entrada				; Comprobamos qué tipo de conversión se debe realizar
	cmp		sentido_conversion, 0
	je		c_a_f

;f_a_c
	mov		ecx, 5							; Realizamos la fórmula de conversión de fahrenheit a celsius
	sub		eax, 32
	imul	eax, ecx
	mov		ecx, 9
	cdq										; Realizamos la extensión de signo de EAX a EDX para evitar errores de signo
	idiv	ecx

	jmp		fin


c_a_f:										; Realizamos la fórmula de conversión de celsius a fahrenheit
	mov		ecx, 9
	imul	eax, ecx
	mov		ecx, 5
	idiv	ecx
	cdq										; Realizamos la extensión de signo de EAX a EDX para evitar errores de signo
	add		eax, 32

fin:
	shl		edx, 1							; Redondeamos el resultado
	cmp		edx, ecx
	jl		fin2
	add		eax, 1
fin2:
	mov		[esi], eax						; Devolvemos el resultado en la dirección indicada

final:										; Fin de la función
	pop		esi
	pop		ebp
	ret
