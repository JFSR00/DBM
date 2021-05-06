/***************************************************************************//**
 * \file    termistor_ntc.h
 *
 * \brief   Conversión de la tensión en un divisor de tensión con NTC a la
 *          temperatura correspondiente.
 */

#ifndef TERMISTOR_NTC_H
#define TERMISTOR_NTC_H

/*===== Prototipos de funciones ================================================
 */

float ntc_traducir_tension_a_temperatura(float V_s);

#endif  /* TERMISTOR_NTC_H */
