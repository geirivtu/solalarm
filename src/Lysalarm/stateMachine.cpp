/*! \file statemachine.cpp
 *
 *  \brief 
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */

#include "stateMachine.h"  

enum state_t {
  S_NORMAL,
  S_SET_MIN_CLOCK,
  S_SET_HOUR_CLOCK,  
  S_SET_MIN_ALARM,
  S_SET_HOUR_ALARM,
  S_ALARM_ON,
  S_SUNRISE,
  S_WAKEUP,
  S_SNOOZE,
  S_DISPLAY_OFF
};

static enum state_t State = S_NORMAL;
static enum state_t PrevState = State; 
/* States END */

/* State variable  */

static void changeState(enum state_t newState){
  //Serial.println("State --> %d", (int)newState);
  Serial.println("Hi from SM");
  PrevState = State;
  State = newState;
}

void event_EncoderUp(void){

  switch(State){
  case S_NORMAL:
    // LightUp
    break;
  case S_SET_MIN_CLOCK:
  // IncMinClock
    break;
  case S_SET_HOUR_CLOCK:
  //IncHourClock
    break;
  case S_SET_MIN_ALARM:
  // IncMinAlarm
    break;
  case S_SET_HOUR_ALARM:
  // IncHourAlarm
    break;
  case S_ALARM_ON:
  // LightUp
    break;
  case S_SUNRISE:
  // LightUp
    break;
  case S_WAKEUP:
    // LightUp
    break;
  case S_SNOOZE:
    // LightUp
    break;
  case S_DISPLAY_OFF:
    // DisplayShow
    changeState(PrevState);
    break;
  }
}


void event_EncoderDown(void){
  switch(State){
  case S_NORMAL:
  // LightDown
    break;
  case S_SET_MIN_CLOCK:
  // DecMinClock
    break;
  case S_SET_HOUR_CLOCK:
  // DecHourClock
    break;
  case S_SET_MIN_ALARM:
  // DecMinAlarm
    break;
  case S_SET_HOUR_ALARM:
  // DecHourAlarm
    break;
  case S_ALARM_ON:
  // LightDown
    break;
  case S_SUNRISE:
  // LightDown
    break;
  case S_WAKEUP:
  // LightDown
    break;
  case S_SNOOZE:
  // LightDown
    break;
  case S_DISPLAY_OFF:
    // DisplayShow
    changeState(PrevState);
    break;
  }
}

void event_EncoderButton(void){
  switch(State){
  case S_NORMAL:
    break;
  case S_SET_MIN_CLOCK:
    break;
  case S_SET_HOUR_CLOCK:
    break;
  case S_SET_MIN_ALARM:
    break;
  case S_SET_HOUR_ALARM:
    break;
  case S_ALARM_ON:
    break;
  case S_SUNRISE:
    break;
  case S_WAKEUP:
    break;
  case S_SNOOZE:
    break;
  case S_DISPLAY_OFF:
    // DisplayShow
    changeState(PrevState);
    break;
  }
}



void event_SetButton(void){
  switch(State){
  case S_NORMAL:
    changeState(S_SET_MIN_CLOCK);
    break;
  case S_SET_MIN_CLOCK:
    changeState(S_SET_HOUR_CLOCK);
    break;
  case S_SET_HOUR_CLOCK:
    changeState(S_NORMAL);
    break;
  case S_SET_MIN_ALARM:
    changeState(S_SET_HOUR_ALARM);
    break;
  case S_SET_HOUR_ALARM:
    changeState(S_ALARM_ON);
    break;
  case S_ALARM_ON:
    changeState(S_SET_MIN_ALARM);
    break;
  case S_SUNRISE:
    break;
  case S_WAKEUP:
  // SoundOff
    changeState(S_SNOOZE);
    break;
  case S_SNOOZE:
    break;
  case S_DISPLAY_OFF:
    // DisplayShow
    changeState(PrevState);
    break;
  }
}

void event_AlarmOn(void){
  switch(State){
  case S_NORMAL:
    changeState(S_ALARM_ON);
    break;
  case S_SET_MIN_CLOCK:
    changeState(S_ALARM_ON);
    break;
  case S_SET_HOUR_CLOCK:
    changeState(S_ALARM_ON);
    break;
  case S_SET_MIN_ALARM:
    break;
  case S_SET_HOUR_ALARM:
    break;
  case S_ALARM_ON:
    break;
  case S_SUNRISE:
    break;
  case S_WAKEUP:
    break;
  case S_SNOOZE:
    break;
  case S_DISPLAY_OFF:
    // DisplayShow
    changeState(S_ALARM_ON);
    break;
  }
}

void event_AlarmOff(void){
  switch(State){
  case S_NORMAL:
    break;
  case S_SET_MIN_CLOCK:
    break;
  case S_SET_HOUR_CLOCK:
    break;
  case S_SET_MIN_ALARM:
    changeState(S_NORMAL);
    break;
  case S_SET_HOUR_ALARM:
    changeState(S_NORMAL);
    break;
  case S_ALARM_ON:
  // SoundOff
    changeState(S_NORMAL);
    break;
  case S_SUNRISE:
    changeState(S_NORMAL);
    break;
  case S_WAKEUP:
  // SoundOff
    changeState(S_NORMAL);
    break;
  case S_SNOOZE:
    changeState(S_NORMAL);
    break;
  case S_DISPLAY_OFF:
    // DisplayShow
    changeState(S_NORMAL);
    break;
  }
}

void event_Wakeuptime(void){
  switch(State){
  case S_NORMAL:
    break;
  case S_SET_MIN_CLOCK:
    break;
  case S_SET_HOUR_CLOCK:
    break;
  case S_SET_MIN_ALARM:
    break;
  case S_SET_HOUR_ALARM:
    break;
  case S_ALARM_ON:
    // SoundOn
    changeState(S_WAKEUP);
    break;
  case S_SUNRISE:
  // SoundOn
    changeState(S_WAKEUP);
    break;
  case S_WAKEUP:
    break;
  case S_SNOOZE:
    break;
  case S_DISPLAY_OFF:
    // DisplayShow
    changeState(S_WAKEUP);
    break;
  }
}

void event_SnoozeTimeout(void){
  switch(State){
  case S_NORMAL:
    break;
  case S_SET_MIN_CLOCK:
    break;
  case S_SET_HOUR_CLOCK:
    break;
  case S_SET_MIN_ALARM:
    break;
  case S_SET_HOUR_ALARM:
    break;
  case S_ALARM_ON:
    break;
  case S_SUNRISE:
    break;
  case S_WAKEUP:
    break;
  case S_SNOOZE:
    // SoundOn
    changeState(S_WAKEUP);
    break;
  case S_DISPLAY_OFF:
  // DisplayShow
  // SoundOn
    changeState(S_WAKEUP);
    break;
  }
}

void event_Sunrisetime(void){
  switch(State){
  case S_NORMAL:
    break;
  case S_SET_MIN_CLOCK:
    break;
  case S_SET_HOUR_CLOCK:
    break;
  case S_SET_MIN_ALARM:
    break;
  case S_SET_HOUR_ALARM:
    break;
  case S_ALARM_ON:
    changeState(S_SUNRISE);
    break;
  case S_SUNRISE:
    break;
  case S_WAKEUP:
    break;
  case S_SNOOZE:
    break;
  case S_DISPLAY_OFF:
  // DisplayShow 
    changeState(S_SUNRISE);
    break;
  }
}

void event_MinuteElapsed(void){
  switch(State){
  case S_NORMAL:
    break;
  case S_SET_MIN_CLOCK:
    break;
  case S_SET_HOUR_CLOCK:
    break;
  case S_SET_MIN_ALARM:
    break;
  case S_SET_HOUR_ALARM:
    break;
  case S_ALARM_ON:
    break;
  case S_SUNRISE:
    // LightUp
    break;
  case S_WAKEUP:
    break;
  case S_SNOOZE:
    break;
  case S_DISPLAY_OFF:
    break;
  }
}

void event_DisplayOffTimeout(void){
  switch(State){
  case S_NORMAL:
  // DisplayHide
    changeState(S_DISPLAY_OFF);
    break;
  case S_SET_MIN_CLOCK:
    break;
  case S_SET_HOUR_CLOCK:
    break;
  case S_SET_MIN_ALARM:
    break;
  case S_SET_HOUR_ALARM:
    break;
  case S_ALARM_ON:
    break;
  case S_SUNRISE:
    break;
  case S_WAKEUP:
    break;
  case S_SNOOZE:
    break;
  case S_DISPLAY_OFF:
    break;
  }
}
