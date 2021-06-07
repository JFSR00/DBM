/***************************************************************************//**
 * \file	rtc_lpc40xx.c 
 * 
 * \brief	Funciones para usar el RTC del LPC40xx.
 *
 */

#include <LPC407x_8x_177x_8x.h>
#include "rtc_lpc40xx.h"

/***************************************************************************//**
 * \brief   Inicializar el RTC.
 */
void rtc_inicializar(void)
{
    LPC_RTC->CCR = 1;
}

/***************************************************************************//**
 * \brief   Leer la hora del RTC.
 *
 * \param[out]  horas       puntero a la variable donde guardar las horas.
 * \param[out]  minutos     puntero a la variable donde guardar los minutos.
 * \param[out]  segundos    puntero a la variable donde guardar los segundos.
 */
void rtc_leer_hora(uint32_t *horas,
                   uint32_t *minutos,
                   uint32_t *segundos)
{
   
    uint32_t lecturahora;
   
    lecturahora = LPC_RTC->CTIME0;
		*segundos = lecturahora & 0x3F;
    *minutos = (lecturahora >> 8) & 0x3F;
    *horas = (lecturahora >> 16) & 0x1F; 

}

/***************************************************************************//**
 * \brief   Ajustar la hora del RTC.
 *
 * \param[in]   horas       Horas a ajustar.
 * \param[in]   minutos     Minutos a ajustar.
 * \param[in]   segundos    Segundos a ajustar.
 */
void rtc_ajustar_hora(uint32_t horas,
                      uint32_t minutos,
                      uint32_t segundos)
{
    LPC_RTC->CCR &= ~1;     /* Deshabilitar el avance del RTC mientras se ajusta
                             * la hora. */
   
    
    LPC_RTC->SEC = segundos;
    LPC_RTC->MIN = minutos;
    LPC_RTC->HOUR = horas;
    

    LPC_RTC->CCR |= 1;      /* Volver a permitir que el RTC avance. */
}

/***************************************************************************//**
 * \brief   Leer la fecha del RTC.
 *
 * \param[out]  dia     puntero a la variable donde guardar el día del mes.
 * \param[out]  mes     puntero a la variable donde guardar el mes.
 * \param[out]  ano     puntero a la variable donde guardar el año.
 */
void rtc_leer_fecha(uint32_t *dia,
                    uint32_t *mes,
                    uint32_t *ano)
{
    
    uint32_t lecturafecha;
    
    lecturafecha = LPC_RTC->CTIME1;
    *dia = lecturafecha & 0x1F;
    *mes = (lecturafecha >> 8) & 0x0F;
    *ano = (lecturafecha >> 16) & 0xFFF;

}

/***************************************************************************//**
 * \brief   Ajustar la fecha del RTC.
 *
 * \param[in]   dia     Día a ajustar.
 * \param[in]   mes     Mes a ajustar.
 * \param[in]   ano     Año a ajustar.
 */
void rtc_ajustar_fecha(uint32_t dia,
                       uint32_t mes,
                       uint32_t ano)
{
    LPC_RTC->CCR &= ~1;     /* Deshabilitar el avance del RTC mientras se ajusta
                             * la fecha. */
    
    LPC_RTC->DOY = dia;
    LPC_RTC->MONTH = mes;
    LPC_RTC->YEAR = ano;
    

    LPC_RTC->CCR |= 1;      /* Volver a permitir que el RTC avance. */
}
