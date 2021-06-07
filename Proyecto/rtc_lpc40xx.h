/***************************************************************************//**
 * \file	rtc_lpc40xx.h
 * 
 * \brief	Funciones de acceso al RTC del LPC40xx.
 */

#ifndef RTC_LPC40XX_H
#define RTC_LPC40XX_H

#include "tipos.h"

void rtc_inicializar(void);

void rtc_leer_hora(uint32_t *horas,
                   uint32_t *minutos,
                   uint32_t *segundos);

void rtc_ajustar_hora(uint32_t horas,
                      uint32_t minutos,
                      uint32_t segundos);

void rtc_leer_fecha(uint32_t *dia,
                    uint32_t *mes,
                    uint32_t *ano);

void rtc_ajustar_fecha(uint32_t dia,
                       uint32_t mes,
                       uint32_t ano);


#endif  /* RTC_LPC40XX_H */
