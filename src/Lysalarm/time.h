/*! \file time.h
 *
 *  \brief Handles commnication with the RTC and helper functions.
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */


#ifndef H_TIME
#define H_TIME

#include <Arduino.h>
#include <Wire.h>

struct time_t {
  int sec;
  int minute;
  int hour;
  int day;
  int month;
  int year;
};

extern struct time_t Clock;
extern struct time_t Alarm;

void time_init(void);
void time_inc_min(struct time_t *time);
void time_dec_min(struct time_t *time);
void time_inc_hour(struct time_t *time);
void time_dec_hour(struct time_t *time);
void time_print(struct time_t *time);
bool time_alarm(void);

void time_update_clock(struct time_t *time);


void RTC_get_time(byte* hour_ptr, byte* minute_ptr);
bool RTC_minute_elapsed();
void RTC_set_time(struct time_t *time);

#endif //H_TIME
