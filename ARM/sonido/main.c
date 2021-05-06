/***************************************************************************//**
 * \file    main.c
 * \brief   Función main para la práctica 9. */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "sonido.h"
#include "error.h"
#include "leds.h"

int main(void)
{
	const uint8_t melodia_mario[] =
  {     NOTA_E7, NOTA_E7, NOTA_PAUSA, NOTA_E7,
        NOTA_PAUSA, NOTA_C7, NOTA_E7, NOTA_PAUSA,
        NOTA_G7, NOTA_PAUSA, NOTA_PAUSA,  NOTA_PAUSA,
        NOTA_G6, NOTA_PAUSA, NOTA_PAUSA, NOTA_PAUSA,

        NOTA_C7, NOTA_PAUSA, NOTA_PAUSA, NOTA_G6,
        NOTA_PAUSA, NOTA_PAUSA, NOTA_E6, NOTA_PAUSA,
        NOTA_PAUSA, NOTA_A6, NOTA_PAUSA, NOTA_B6,
        NOTA_PAUSA, NOTA_AS6, NOTA_A6, NOTA_PAUSA,

        NOTA_G6, NOTA_E7, NOTA_G7,
        NOTA_A7, NOTA_PAUSA, NOTA_F7, NOTA_G7,
        NOTA_PAUSA, NOTA_E7, NOTA_PAUSA, NOTA_C7,
        NOTA_D7, NOTA_B6, NOTA_PAUSA, NOTA_PAUSA,

        NOTA_C7, NOTA_PAUSA, NOTA_PAUSA, NOTA_G6,
        NOTA_PAUSA, NOTA_PAUSA, NOTA_E6, NOTA_PAUSA,
        NOTA_PAUSA, NOTA_A6, NOTA_PAUSA, NOTA_B6,
        NOTA_PAUSA, NOTA_AS6, NOTA_A6, NOTA_PAUSA,

        NOTA_G6, NOTA_E7, NOTA_G7,
        NOTA_A7, NOTA_PAUSA, NOTA_F7, NOTA_G7,
        NOTA_PAUSA, NOTA_E7, NOTA_PAUSA, NOTA_C7,
        NOTA_D7, NOTA_B6, NOTA_PAUSA, NOTA_PAUSA, NOTA_FIN
    };    
    
    sonido_inicializar();
   //sonido_reproducir_melodia(melodia_mario, 150);
   //sonido_emitir_pitido(200, 300);
    while (TRUE) {}
}

