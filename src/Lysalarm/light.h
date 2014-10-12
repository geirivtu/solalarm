/*! \file light.h
 *
 *  \brief Functions for reading button, switch and encoder.  
 *  \author Geir Turtum
 *  \date   12.okt.2014
 */

#ifndef H_LIGHT
#define H_LIGHT

#include <Arduino.h>


void light_init(void);
void light_on(void);
void light_off(void);
void light_inc(void);
void light_dec(void);


#endif //H_LIGHT
