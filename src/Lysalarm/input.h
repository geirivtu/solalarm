/*! \file input.h
 *
 *  \brief Functions for reading button, switch and encoder.  
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */

#ifndef H_INPUT
#define H_INPUT

#include <arduino.h>


void input_init();

boolean input_select_button();
boolean input_alarm_button();
boolean input_get_alarm_button_status();
int8_t input_read_encoder(void);


#endif //H_INPUT
