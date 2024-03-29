; Funci�n void * copiar_bloque_memoria(void * destino, void * origen, unsigned int longitud);

	global	_copiar_bloque_memoria

	section	.text

_copiar_bloque_memoria:
	push	ebp
	mov		ebp, esp

	push	esi
	push	edi

	%define	origen		dword [ebp + 8]		; Definimos par�rmetros de la funci�n
	%define	destino		dword [ebp + 12]
	%define	longitud	dword [ebp + 16]

	mov		esi, origen						; Cargamos las direcciones de memoria de origen y destino a registros
	mov		edi, destino					; para la funci�n MOVSD

	mov		ecx, longitud					; Calculamos la cantidad de bloques de 4 bytes a copiar
	shr		ecx, 2
	jz		long_menor_4

	rep		movsd							; Procedemos a la copia de memoria a partir de las direcciones de los
											; registros ESI y EDI. La instrucci�n REP nos permite repetir la copia
											; mientras el registro ECX sea distinto de 0.
long_menor_4:
	mov		ecx, longitud					; Para tama�os menores a 4 bytes copiamos la memoria byte a byte
	and		ecx, 3
	jz		final

	rep		movsb							; Realizamos la misma operaci�n de antes, pero byte a byte

final:										; Fin de la funci�n
	pop		edi
	pop		esi
	pop		ebp
	ret
