/***************************************************************************//**
 * \file    main.c
 *
 * \brief   Función main para probar el teclado.
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "teclado_4x4.h"

int main(void)
{
		glcd_inicializar();
		tec4x4_inicializar();
    while (1)
    {
				glcd_xprintf(0, 0, WHITE, BLACK, FONT16X32, "Carácter:");
				glcd_xprintf(9, 0, WHITE, BLACK, FONT16X32, "%c", tec4x4_esperar_pulsacion());
        //glcd_printf("%c", tec4x4_esperar_pulsacion());
    }
}
