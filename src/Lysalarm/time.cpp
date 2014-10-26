/*! \file time.cpp
 *
 *  \brief Handles commnication with the RTC and helper functions.
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */
 
#include "time.h"

#define DS1307_I2C_ADDRESS 0x68  // This is the I2C address

static byte i2c_minute_address = 0x01;

static byte zero = 0x00;

struct time_t Clock;
struct time_t Alarm;
struct time_t Sunrise;


// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}
 
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}



void time_init(void){
  
  Wire.begin();
  
  byte hour, minute;
  RTC_get_time(&hour, &minute);
  
  
  
  //Clock.sec = 1;
  Clock.minute = minute;
  Clock.hour = hour;
  //Clock.day = 4;
  //Clock.month = 4;
  //Clock.year = 2014;
  
  //Alarm.sec = 4;
  Alarm.minute = 50;
  Alarm.hour = 8;
  //Alarm.day = 4;
  //Alarm.month = 4;
  //Alarm.year = 2014;
  
  RTC_set_time(&Clock);
  
}

void time_print(struct time_t *time){
  
  Serial.print("Time -> ");
  Serial.print(time->hour, DEC);
  Serial.print(":");
  Serial.println(time->minute, DEC);
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

void time_set(struct time_t *time, int hour, int minute){
  
  if(hour < 0) hour = 0;
  if(hour > 23) hour = 23;
  if(minute < 0) minute = 0;
  if(minute > 59) minute = 59;
    
  (*time).minute = minute;
  (*time).hour = hour;
}


bool time_alarm(){
  
  return (Clock.hour == Alarm.hour) && (Clock.minute == Alarm.minute);
  
}


void time_update_clock(struct time_t *time){

  byte hour, minute;
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(i2c_minute_address-1); //Now second
  Wire.endTransmission();

  Wire.requestFrom(DS1307_I2C_ADDRESS, 2+1); /* Request 2 bytes */ //TODO

  // A few of these need masks because certain bits are control bits
  minute     = bcdToDec(Wire.read() & 0x7f);
  Wire.read();
  hour      = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm

  time->minute = minute;
  time->hour = hour;

}
  







/* Get hours using 24 hour format and minutes from RTC */
void RTC_get_time(byte* hour_ptr, byte* minute_ptr){

  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(i2c_minute_address-1); //TODO
  Wire.endTransmission();

  Wire.requestFrom(DS1307_I2C_ADDRESS, 2+1); /* Request 2 bytes */ //TODO

  // A few of these need masks because certain bits are control bits
  *minute_ptr     = bcdToDec(Wire.read() & 0x7f);
  Wire.read();
  *hour_ptr       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm

}

bool RTC_minute_elapsed(){
  byte hour_tmp, minute_tmp, prev_minute;
  prev_minute = 0;
  
  RTC_get_time(&hour_tmp, &minute_tmp);

  if(minute_tmp != prev_minute){

    prev_minute = minute_tmp;
    return true;
  }else{
    return false;
  }

}


void RTC_set_time(struct time_t *time)                
{
  
   Wire.beginTransmission(DS1307_I2C_ADDRESS);
   Wire.write(zero);
   Wire.write(decToBcd(0) & 0x7f);    //sec. bit 7 enables clocks when low
   Wire.write(decToBcd(time->minute));
   Wire.write(decToBcd(time->hour));      // If you want 12 hour am/pm you need to set
                                   // bit 6 (also need to change readDateDs1307)

   Wire.endTransmission();
}
 
 

