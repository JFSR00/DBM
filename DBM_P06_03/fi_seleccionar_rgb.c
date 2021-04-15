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
///                                 debe estar alineado a una posici�n divisible entre 32. 
///
/// \param[in]      ancho           ancho de la imagen en pixels.
///
/// \param[in]      alto            alto de la imagen en pixels.
///
/// \param[in]      seleccion_rgb   m�scara para seleccionar qu� componentes de color se conservan:
///                                 Si el bit 0 de seleccion_rgb est� a 1 se conserva la componente azul.
///                                 Si est� a 0 se elimina.
///                                 Si el bit 1 de seleccion_rgb est� a 1 se conserva la componente verde.
///                                 Si est� a 1 se elimina.
///                                 Si el bit 2 de seleccion_rgb est� a 1 se conserva la componente roja.
///                                 Si est� a 2 se elimina.
///
/// \return			0 => error (ptr_imagen nulo o no alineado o ancho == 0 o alto == 0), 1 => �xito.
//

int fi_seleccionar_rgb(unsigned char *ptr_imagen,
                       unsigned int ancho,
                       unsigned int alto,
                       unsigned char seleccion_rgb)
{
    // C O M P L E T A R
}

