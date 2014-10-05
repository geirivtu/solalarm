/*! \file sound.h
 *
 *  \brief Controls the sound card. 
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */

#ifndef H_SOUND
#define H_SOUND

#include "Arduino.h"

void sound_init(void);
void sound_play(void);
void sound_reset(void);


#endif //H_SOUND
