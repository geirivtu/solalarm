/*! \file statemachine.cpp
 *
 *  \brief 
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */

#include "stateMachine.h"  

#include "display.h"
#include "input.h"
#include "sound.h"
#include "time.h"
#include "light.h"

extern struct time_t Clock;
extern struct time_t Alarm;

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

char * stateStr[] = {  "S_NORMAL",
  "S_SET_MIN_CLOCK",
  "S_SET_HOUR_CLOCK",  
  "S_SET_MIN_ALARM",
  "S_SET_HOUR_ALARM",
  "S_ALARM_ON",
  "S_SUNRISE",
  "S_WAKEUP",
  "S_SNOOZE",
  "S_DISPLAY_OFF"};

static enum state_t State = S_NORMAL;
static enum state_t PrevState = State; //Keeps track of the previous state of the system
/* States END */

/* State variable  */

void stateMachine_init(void){
  
  disp_write(Clock.hour, Clock.minute);
  
}

static void changeState(enum state_t newState){
  Serial.print("State --> ");
  Serial.println(stateStr[newState]);
  PrevState = State;
  State = newState;
}

void event_EncoderUp(void){

  // DisplayShow
  disp_on();

  switch(State){
  case S_NORMAL:
  //light up
    light_inc();
    break;
  case S_SET_MIN_CLOCK:
    // IncMinClock
    time_inc_min(&Clock);
	RTC_set_time(&Clock);
    disp_write(Clock.hour, Clock.minute);
    break;
  case S_SET_HOUR_CLOCK:
    //IncHourClock
    time_inc_hour(&Clock);
	RTC_set_time(&Clock);
    disp_write(Clock.hour, Clock.minute);
    break;
  case S_SET_MIN_ALARM:
    // IncMinAlarm
    time_inc_min(&Alarm);
	time_inc_min(&Sunrise);
    disp_write(Alarm.hour, Alarm.minute);
    break;
  case S_SET_HOUR_ALARM:
    // IncHourAlarm
    time_inc_hour(&Alarm);
	time_inc_hour(&Sunrise);
    disp_write(Alarm.hour, Alarm.minute);
    break;
  case S_ALARM_ON:
    // LightUp
    light_inc();
    break;
  case S_SUNRISE:
    // LightUp
    light_inc();
    break;
  case S_WAKEUP:
    // LightUp
    light_inc();
    break;
  case S_SNOOZE:
    // LightUp
    light_inc();
    break;
  }
}


void event_EncoderDown(void){

  // DisplayShow
  disp_on();

  switch(State){
  case S_NORMAL:
  //light down
    light_dec();
    break;
  case S_SET_MIN_CLOCK:
    // DecMinClock
    time_dec_min(&Clock);
	RTC_set_time(&Clock);
    disp_write(Clock.hour, Clock.minute);
    break;
  case S_SET_HOUR_CLOCK:
    // DecHourClock
    time_dec_hour(&Clock);
	RTC_set_time(&Clock);
    disp_write(Clock.hour, Clock.minute);
    break;
  case S_SET_MIN_ALARM:
  // DecMinAlarm
    time_dec_min(&Alarm);
	time_dec_min(&Sunrise);
    disp_write(Alarm.hour, Alarm.minute);
    break;
  case S_SET_HOUR_ALARM:
    // DecHourAlarm
    time_dec_hour(&Alarm);
	time_dec_hour(&Sunrise);
    disp_write(Alarm.hour, Alarm.minute);
    break;
  case S_ALARM_ON:
  // LightDown
    light_dec();
    break;
  case S_SUNRISE:
  // LightDown
    light_dec();
    break;
  case S_WAKEUP:
  // LightDown
    light_dec();
    break;
  case S_SNOOZE:
  // LightDown
    light_dec();
    break;
  }
}

void event_EncoderButton(void){

  // DisplayShow
  disp_on();

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
  }
}



void event_SetButton(void){

  // DisplayShow
  disp_on();

  switch(State){
  case S_NORMAL:
    disp_min_blink();
    changeState(S_SET_MIN_CLOCK);
    break;
  case S_SET_MIN_CLOCK:
    disp_hour_blink();
    changeState(S_SET_HOUR_CLOCK);
    break;
  case S_SET_HOUR_CLOCK:
    disp_on();
    changeState(S_NORMAL);
    break;
  case S_SET_MIN_ALARM:
    disp_hour_blink();
    changeState(S_SET_HOUR_ALARM);
    break;
  case S_SET_HOUR_ALARM:
    disp_write(Clock.hour, Clock.minute);
    disp_on();
    changeState(S_ALARM_ON);
    break;
  case S_ALARM_ON:
    disp_write(Alarm.hour, Alarm.minute);
    disp_min_blink();
    changeState(S_SET_MIN_ALARM);
    break;
  case S_SUNRISE:
    break;
  case S_WAKEUP:
    // SoundOff
    sound_reset();
    changeState(S_SNOOZE);
    break;
  case S_SNOOZE:
	sound_play();    //TODO remove
	changeState(S_WAKEUP); //TODO remove
    break;
  }
}

void event_AlarmOn(void){

  // DisplayShow
  disp_on();

  switch(State){
  case S_NORMAL:
    changeState(S_ALARM_ON);
    break;
  case S_SET_MIN_CLOCK:
    disp_on();
    changeState(S_ALARM_ON);
    break;
  case S_SET_HOUR_CLOCK:
    disp_on();
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
    disp_on();
    disp_write(Clock.hour, Clock.minute);
    changeState(S_NORMAL);
    break;
  case S_SET_HOUR_ALARM:
    disp_on();
    disp_write(Clock.hour, Clock.minute);
    changeState(S_NORMAL);
    break;
  case S_ALARM_ON:
    // SoundOff
    sound_reset();
    //disp_write(Clock.hour, Clock.minute);
    changeState(S_NORMAL);
    break;
  case S_SUNRISE:
    changeState(S_NORMAL);
    break;
  case S_WAKEUP:
    // SoundOff
    sound_reset();
    changeState(S_NORMAL);
    break;
  case S_SNOOZE:
    changeState(S_NORMAL);
    break;
  }
}

void event_Wakeuptime(void){

  // DisplayShow
  disp_on();

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
	//Light on
	light_on();
    // SoundOn
    sound_play();
    changeState(S_WAKEUP);
    break;
  case S_SUNRISE:
	//Light on
	light_on();
    // SoundOn
    sound_play();
    changeState(S_WAKEUP);
    break;
  case S_WAKEUP:
    break;
  case S_SNOOZE:
    break;
  }
}

void event_SnoozeTimeout(void){

  // DisplayShow
  disp_on();

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
    sound_play();
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
  }
}

void event_MinuteElapsed(void){
  switch(State){
  case S_NORMAL:
	time_update_clock(&Clock);
	disp_write(Clock.hour, Clock.minute);
	
    break;
  case S_SET_MIN_CLOCK:
    break;
  case S_SET_HOUR_CLOCK:
    break;
  case S_SET_MIN_ALARM:
	time_update_clock(&Clock);
    break;
  case S_SET_HOUR_ALARM:
	time_update_clock(&Clock);
    break;
  case S_ALARM_ON:
	time_update_clock(&Clock);
	disp_write(Clock.hour, Clock.minute);	
	
    break;
  case S_SUNRISE:
	time_update_clock(&Clock);
	disp_write(Clock.hour, Clock.minute);
    // LightUp
    light_inc();
    break;
  case S_WAKEUP:
	time_update_clock(&Clock);
	disp_write(Clock.hour, Clock.minute);
    break;
  case S_SNOOZE:
	time_update_clock(&Clock);
	disp_write(Clock.hour, Clock.minute);
    break;
  }
}

void event_DisplayOffTimeout(void){
  switch(State){
  case S_NORMAL:
    // DisplayHide
    disp_off();
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
  }
}
