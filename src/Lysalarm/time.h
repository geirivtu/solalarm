/*! \file time.h
 *
 *  \brief Handles commnication with the RTC and helper functions.
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */


#ifndef H_TIME
#define H_TIME



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

#endif //H_TIME
