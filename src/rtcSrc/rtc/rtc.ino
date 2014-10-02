/* RTC Control v1.00 
 * by <http://www.combustory.com> John Vaughters
 *
 * THIS CODE IS FREE FOR ANYTHING  - There is no Rocket Science here. No need to create some long GPL statement.
 *
 * Credit to:
 * Maurice Ribble - http://www.glacialwanderer.com/hobbyrobotics for RTC DS1307 code
 * BB Riley - Underhill Center, VT  <brianbr@wulfden.org> For simplification of the Day of Week and month
 *                                                        and updating to Arduino 1.0 
 * peep rada - from Arduino Forum - Found that only 32 registers per I2C connection was possible 
 * 
 * With this code you can set the date/time, retreive the date/time and use the extra memory of an RTC DS1307 chip.  
 * The program also sets all the extra memory space to 0xff.
 * Serial Communication method with the Arduino that utilizes a leading CHAR for each command described below. 
 *
 * Commands:
 * T(00-59)(00-59)(00-23)(1-7)(01-31)(01-12)(00-99) - T(sec)(min)(hour)(dayOfWeek)(dayOfMonth)(month)(year) -
 * T - Sets the date of the RTC DS1307 Chip. 
 * Example to set the time for 25-Jan-2012 @ 19:57:11 for the 4 day of the week, use this command - T1157194250112
 * Q(1-2) - (Q1) Memory initialization  (Q2) RTC - Memory Dump  
 * R - Read/display the time, day and date
 *
 * ---------------------------------------------------------
 * Notes:
 * Version 1.0
 *    Moving this code to Version 1.0 because this code has been updated to Arduino v1.0 and the features have
 *    been well tested and improved in a collaborative effort.
 *    - Fixed the issue of not being able to access all the registers - JWV
 *    - Added initialization for all non-time registers - JWV
 *    - Added Dump of all 64 registers - JWV
 *    - Some Date/Time reformatting and cleanup of display, added Day/Month texts - BBR
 *    - Made compatible with Arduino 1.0 - BBR
 *    - Added Rr command for reading date/time - BBR
 *    - Made commands case insensitive - BBR
 *    - Create #define varibles to support pre Arduino v1.0 - JWV
 * Version 0.01
 *    Inital code with basics of setting time and the first 37 registers and dumping the first 32 registers. 
 *    The code was based on Maurice Ribble's original code.
 * 
 */

#include "Wire.h"
#define DS1307_I2C_ADDRESS 0x68  // This is the I2C address

byte minute, hour;
byte prev_minute; /* Is used for tracking when a minute has elapsed */

byte i2c_minute_address = 0x01;

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

/* RTC module API */

/* Sets the time using 24 hour format, seconds set to 0 */
void RTC_set_time(byte hour, byte minute){
  prev_minute = minute; 

  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(i2c_minute_address); /* Write start address */
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));      // If you want 12 hour am/pm you need to set
  // bit 6 (also need to change readDateDs1307)
  Wire.endTransmission();  


}

/* Get hours using 24 hour format and minutes from RTC */
void RTC_get_time(byte* hour_ptr, byte* minute_ptr){

  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(i2c_minute_address);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_I2C_ADDRESS, 2); /* Request 2 bytes */

  // A few of these need masks because certain bits are control bits
  *minute_ptr     = bcdToDec(Wire.read());
  *hour_ptr       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm

}

boolean RTC_minute_elapsed(){
  byte hour_tmp, minute_tmp;
  boolean return_value = false;

  RTC_get_time(&hour_tmp, &minute_tmp);

  if(minute_tmp != prev_minute){
    return_value = true;
    prev_minute = minute_tmp;
  }
  return return_value;
}


void setup() {
  Wire.begin();
  Serial.begin(57600); 

  hour = 23;
  minute = 11;

  RTC_set_time(hour, minute);
}

byte hour_tmp, minute_tmp;

void loop() {

  if(RTC_minute_elapsed()){
    RTC_get_time(&hour_tmp, &minute_tmp);


    Serial.print(hour_tmp);
    Serial.print(" : ");
    Serial.println(minute_tmp);   
  }



}



