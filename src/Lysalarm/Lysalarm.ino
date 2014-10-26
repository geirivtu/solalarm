  /*! \file Lysalarm.ino
 *
 *  \brief Main file for Lysalarm prosjekt. 
 *  \author Geir and Eirin
 *  \date   06.mars.2014
 */

//IDE: Bruke en av de hjemmeautomasjons systemene til å dimme lampe
// Hvis lysalarm har en sender som kan styre og dimme lamper

#include <TimerOne.h>
#include <Wire.h>

#include "display.h"
#include "input.h"
#include "sound.h"
#include "time.h"
#include "light.h"
#include "stateMachine.h"

/* Every task added to scheduler have a firing period.
 * The period is set in the setup() function. 
 * 
 */
volatile uint8_t Display_int = 0;
uint32_t period_display_int = 0; 

volatile uint8_t Display_blink_int = 0;
uint32_t period_display_blink_int = 0; 

volatile uint8_t Set_button_int = 0;
uint32_t period_Set_button_int = 0; 

volatile uint8_t Alarm_switch_int = 0;
uint32_t period_Alarm_switch_int = 0; 

volatile int8_t Encoder_int = 0;
uint32_t period_encoder_int = 0; 

volatile int8_t Time_minute_int = 0;
uint32_t period_time_minute_int = 0; 

const uint32_t Timebase_scheduler_us = 1000;


int led = 13;
int ledMode = 0;

void setup() {                
  


  /* Init display driver */
  disp_init();
  
  light_init();
  
  input_init();
  
  sound_init();
  
  time_init();
  
  
  stateMachine_init();
  
  

  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);   

  Timer1.initialize(Timebase_scheduler_us); //Fires every x us
  Timer1.attachInterrupt( scheduler ); // attach the service routine here


  /* Set period for tasks */

  /* Period for updating display digits */
  period_display_int = set_period_us(3000);

  /* Period for blinking the digits */
  period_display_blink_int = set_period_us(120000);

  /* Period for Select button */
  period_Set_button_int = set_period_us(50000);
  
  /* Period for Alarm switch read  */
  period_Alarm_switch_int = set_period_us(50000);
  
  /* Period for encoder read */
  period_encoder_int = set_period_us(10000);
  
  /* Period for time minute interrupt */
  period_time_minute_int = set_period_us(500000);
  
  
  Serial.begin (115200);
  Serial.println("Welcome to sunalarm");
}


/* main loop checks for events and sends them to the state machine. */
void loop(){
  
 static int8_t encoder = 0;      //this variable will be changed by encoder input


  if( Encoder_int ){    
    encoder = input_read_encoder();
    if(encoder==1) event_EncoderUp();
    else if(encoder==-1) event_EncoderDown();
   
    Encoder_int = 0;
  }


  /* Display State machine */
  if(Display_int)
  {
    disp_digit_int();
    Display_int = 0;  
  }

  if(Display_blink_int)
  {
    disp_blink_int();
    Display_blink_int = 0; 
  }
  /* Display State machine END */

  if( Alarm_switch_int )
  {
    if(input_get_alarm_button_status()) event_AlarmOff();
    else event_AlarmOn();
    
    Alarm_switch_int = 0;
  }
  
   if(Set_button_int)
   {
    event_SetButton();
    Set_button_int = 0;
  }
  
   if(Time_minute_int)
   {
     if(RTC_minute_elapsed()){
       event_MinuteElapsed(); 
	   
	   if(time_alarm()){
			event_Wakeuptime();
	   }
     }
    Time_minute_int = 0;
   }
   
  
  digitalWrite(led, ledMode); //Debug
}






/* --------------------------
 * Scheduler ISR Timer Routine
 * 
 * --------------------------
 */
void scheduler(){
  static uint32_t ticks = 0;

  ticks++; /* ticks keep track of time */

  if((ticks % period_display_int) == 0){
    Display_int = 1;
  }

  if((ticks % period_display_blink_int) == 0){
     Display_blink_int = 1;
  }
  
  if((ticks % period_Set_button_int) == 0){
    Set_button_int = input_select_button();
  }
  
  if((ticks % period_Alarm_switch_int) == 0){
    Alarm_switch_int = input_alarm_button();
  }

  if((ticks % period_encoder_int) == 0){
    Encoder_int = 1;
  }
  
  if((ticks % period_time_minute_int) == 0){
    Time_minute_int = 1;
  }

}

/* --------------------------
 * Function declarations
 * --------------------------
 */
uint32_t set_period_us(uint32_t period_us){
  if(period_us < Timebase_scheduler_us){
    error_alarm();
  } 

  return period_us/Timebase_scheduler_us;
}


/* Puts the program in an while loop, used for debugging */
void error_alarm(){
  int pin_on = 0;  

  //noInterrupts();  crashed the function, why?

  pinMode(13, OUTPUT); 

  while(1){
    digitalWrite(  13, pin_on);
    pin_on = !pin_on; 
    delay(250);
  }
}








