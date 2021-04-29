//-----------------------------------------------------------------------------------------------------
/// \file	fi_seleccionar_rgb.h
//

#include "fi_seleccionar_rgb.h"
#include <immintrin.h>
#include <stdio.h>

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
	unsigned char a1[] = {0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0};
	unsigned char a2[] = {0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF};
	unsigned char a3[] = {0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0};

	if(ptr_imagen == NULL || ancho == 0 || alto == 0){
		return 0;
	}

	maskblanco = _mm256_setzero_si256();
	maskblanco1 = _mm256_setzero_si256();
	maskblanco2 = _mm256_setzero_si256();

	if(num_bloques > 0){
		if(seleccion_rgb & 0x01){
			maskblanco = _mm256_or_si256(maskblanco, *(__m256i*)a1);
			maskblanco1 = _mm256_or_si256(maskblanco1, *(__m256i*)a2);
			maskblanco2 = _mm256_or_si256(maskblanco2, *(__m256i*)a3);
		}

		if(seleccion_rgb & 0x02){
			maskblanco = _mm256_or_si256(maskblanco, *(__m256i*)a2);
			maskblanco1 = _mm256_or_si256(maskblanco1, *(__m256i*)a3);
			maskblanco2 = _mm256_or_si256(maskblanco2, *(__m256i*)a1);
		}

		if(seleccion_rgb & 0x04){
			maskblanco = _mm256_or_si256(maskblanco, *(__m256i*)a3);
			maskblanco1 = _mm256_or_si256(maskblanco1, *(__m256i*)a1);
			maskblanco2 = _mm256_or_si256(maskblanco2, *(__m256i*)a2);
		}

		for(i = 0; i < num_bloques; i++){
			_mm256_store_si256(ptr, _mm256_and_si256(_mm256_load_si256(ptr), maskblanco));
			ptr += 1;
			_mm256_store_si256(ptr, _mm256_and_si256(_mm256_load_si256(ptr), maskblanco1));
			ptr += 1;
			_mm256_store_si256(ptr, _mm256_and_si256(_mm256_load_si256(ptr), maskblanco2));
			ptr += 1;
		}
	}

	if(resto > 0){
		ptr_imagen += num_bloques * 96;
		for(i = 0; i < resto; i++){
			if(!(seleccion_rgb & 0x01)){
				*ptr_imagen = 0;
			}
			ptr_imagen++;

			if(!(seleccion_rgb & 0x02)){
				*ptr_imagen = 0;
			}
			ptr_imagen++;

			if(!(seleccion_rgb & 0x04)){
				*ptr_imagen = 0;
			}
			ptr_imagen++;

		}
	}

	return 1;
}

