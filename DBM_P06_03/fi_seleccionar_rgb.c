//-----------------------------------------------------------------------------------------------------
/// \file	fi_seleccionar_rgb.h
//

#include "fi_seleccionar_rgb.h"
#include <immintrin.h>

//-----------------------------------------------------------------------------------------------------
/// \brief          Seleccionar componentes de color de una imagen RGB.
///
/// \param[in,out]  ptr_imagen      Puntero a los datos de la imagen. Cada pixel ocupa tres bytes
///                                 con las componentes azul, verde y roja (en ese orden). El puntero
///                                 debe estar alineado a una posición divisible entre 32. 
///
/// \param[in]      ancho           ancho de la imagen en pixels.
///
/// \param[in]      alto            alto de la imagen en pixels.
///
/// \param[in]      seleccion_rgb   máscara para seleccionar qué componentes de color se conservan:
///                                 Si el bit 0 de seleccion_rgb está a 1 se conserva la componente azul.
///                                 Si está a 0 se elimina.
///                                 Si el bit 1 de seleccion_rgb está a 1 se conserva la componente verde.
///                                 Si está a 1 se elimina.
///                                 Si el bit 2 de seleccion_rgb está a 1 se conserva la componente roja.
///                                 Si está a 2 se elimina.
///
/// \return			0 => error (ptr_imagen nulo o no alineado o ancho == 0 o alto == 0), 1 => éxito.
//

int fi_seleccionar_rgb(unsigned char *ptr_imagen, unsigned int ancho, unsigned int alto, unsigned char seleccion_rgb)
{
	unsigned int i, num_pixels = ancho * alto;
	unsigned int num_bloques = num_pixels/32;		// Número de bloques de 32 pixels
	unsigned int resto = num_pixels % 32;			// Resto del número de pixeles fuera de un bloque

	__m256i maskblanco, maskblanco1, maskblanco2;	// Variables de AVX que serán usadas para las máscaras
	__m256i *ptr = (__m256i*) ptr_imagen;

	// Declaramos las máscaras para las operaciones posteriores
	unsigned char azul[] = 	{0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0};
	unsigned char verde[] = {0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF};
	unsigned char rojo[] = 	{0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0};

	if(ptr_imagen == NULL || ancho == 0 || alto == 0){
		return 0;
	}

	maskblanco = _mm256_setzero_si256();
	maskblanco1 = _mm256_setzero_si256();
	maskblanco2 = _mm256_setzero_si256();

	if(num_bloques > 0){

	}
}



