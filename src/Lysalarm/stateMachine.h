/*! \file statemachine.h
 *
 *  \brief 
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */

#ifndef H_STATEMACHINE
#define H_STATEMACHINE

void event_EncoderUp(void);
void event_EncoderDown(void);
void event_EncoderButton(void);
void event_SetButton(void);
void event_AlarmOn(void);
void event_AlarmOff(void);
void event_Wakeuptime(void);
void event_SnoozeTimeout(void);
void event_Sunrisetime(void);
void event_MinuteElapsed(void);
void event_DisplayOffTimeout(void);

#endif //H_STATEMACHINE
