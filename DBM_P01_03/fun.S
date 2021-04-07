	global	_fun

	section	.text

_fun:
	push	ebp
	mov		ebp, esp

	%define	n1	dword [ebp + 8]		; Definimos n1 y n2 para facilitarnos el acceso a los parámetros de la función
	%define	n2	dword [ebp + 12]

	mov		eax, n1					; Aplicamos la máscara 0xFF000000 a n1 para así quedarnos solo con los 8 bits
	and		eax, 0xFF000000			; más significativos, seguidamente se le aplica la máscara 0x00FFFFFF a n2
	and		n2, 0x00FFFFFF			; (esta última operación se realiza en memoria, ya que la instrucción lo
	or		eax, n2					; permite, ahorrándonos usar el registro EBX o cualquier otro), de esta manera
									; obtenemos los 24 bits menos significativos de n2. Finalmente se realiza la
									; operación OR entre n1 y n2, para así obtener un número formado por los 8 bits
									; más significativos de n1 y los 24 bits menos significativos de n2, tal y
									; como requería el enunciado.

	pop		ebp
	ret
