	global	_det

	section	.text

_det:
	push	ebp
	mov		ebp, esp
	push	ebx						; Almacenamos en la pila el contenido de EBX, ya que será sobreescrito

	%define	a11	dword [ebp + 8]		; Definimos los nombres a11, a12, a21 y a22 para facilitarnos el acceso
	%define	a12	dword [ebp + 12]	; a los parámetros de la función
	%define	a21	dword [ebp + 16]
	%define	a22	dword [ebp + 20]

	mov		eax, a11
	mov		ebx, a12				; Hacemos uso del registro EBX para almacenar la multiplicación de la segunda
	imul	eax, a22				; diagonal. Seguidamente las multiplicamos.
	imul	ebx, a21
	sub		eax, ebx				; Realizamos la resta de las diagonales y almacenamos en EAX

	pop		ebx						; Restauramos el valor de EBX y retornamos la función
	pop		ebp
	ret
