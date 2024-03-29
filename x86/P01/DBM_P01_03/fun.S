	global	_fun

	section	.text

_fun:
	push	ebp
	mov		ebp, esp

	%define	n1	dword [ebp + 8]		; Definimos n1 y n2 para facilitarnos el acceso a los par�metros de la funci�n
	%define	n2	dword [ebp + 12]

	mov		eax, n1					; Aplicamos la m�scara 0xFF000000 a n1 para as� quedarnos solo con los 8 bits
	and		eax, 0xFF000000			; m�s significativos, seguidamente se le aplica la m�scara 0x00FFFFFF a n2
	and		n2, 0x00FFFFFF			; (esta �ltima operaci�n se realiza en memoria, ya que la instrucci�n lo
	or		eax, n2					; permite, ahorr�ndonos usar el registro EBX o cualquier otro), de esta manera
									; obtenemos los 24 bits menos significativos de n2. Finalmente se realiza la
									; operaci�n OR entre n1 y n2, para as� obtener un n�mero formado por los 8 bits
									; m�s significativos de n1 y los 24 bits menos significativos de n2, tal y
									; como requer�a el enunciado.

	pop		ebp
	ret
