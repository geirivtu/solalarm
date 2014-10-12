/*! \file time.cpp
 *
 *  \brief Handles commnication with the RTC and helper functions.
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */
 
#include "time.h"



struct time_t Clock;
struct time_t Alarm;


void time_init(){
  
  Clock.sec = 1;
  Clock.minute = 11;
  Clock.hour = 22;
  Clock.day = 4;
  Clock.month = 4;
  Clock.year = 2014;
  
  Alarm.sec = 4;
  Alarm.minute = 3;
  Alarm.hour = 4;
  Alarm.day = 4;
  Alarm.month = 4;
  Alarm.year = 2014;
  
}


void time_inc_min(struct time_t *time){
  
  (*time).minute++;
  if((*time).minute==60){
    (*time).minute = 0;
    (*time).hour++;
    if((*time).hour==24){
     (*time).hour = 0; 
    }
  }
}

void time_dec_min(struct time_t *time){
  
  (*time).minute--;
  if((*time).minute < 0){
    (*time).minute = 59;
    (*time).hour--;
    if((*time).hour<0){
     (*time).hour = 23; 
    }
  }
}

void time_inc_hour(struct time_t *time){
  
  (*time).hour++;
  if((*time).hour==24){
     (*time).hour = 0; 
    }
}

void time_dec_hour(struct time_t *time){
  
  (*time).hour--;
  if((*time).hour < 0){
     (*time).hour = 23; 
    }
}


