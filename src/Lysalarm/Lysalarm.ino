 /*! \file Lysalarm.ino
 *
 *  \brief Main file for Lysalarm prosjekt. 
 *  \author Geir and Eirin
 *  \date   06.mars.2014
 */



#include <TimerOne.h>

#include "display.h"
#include "input.h"
#include "sound.h"
#include "time.h"

/* Every task added to scheduler have a firing period.
 * The period is set in the setup() function. 
 * 
 */
volatile uint8_t Display_int = 0;
uint32_t period_display_int = 0; 

volatile uint8_t Display_blink_int = 0;
uint32_t period_display_blink_int = 0; 

volatile uint8_t Select_button_int = 0;
uint32_t period_Select_button_int = 0; 

volatile int8_t Encoder_int = 0;
uint32_t period_encoder_int = 0; 

const uint32_t Timebase_scheduler_us = 1000;


int led = 13;
int ledMode = 0;

void setup() {                

  /* Init display driver */
  //disp_init();
  input_init();
  
  sound_init();

  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);   

  Timer1.initialize(Timebase_scheduler_us); //Fires every x us
  Timer1.attachInterrupt( scheduler ); // attach the service routine here


  /* Set period for tasks */

  /* Period for updating display digits */
  period_display_int = set_period_us(3000);

  /* Period for blinking the digits */
  period_display_blink_int = set_period_us(250000);

  /* Period for Select button read the digits */
  period_Select_button_int = set_period_us(50000);
  
  /* Period for encoder read */
  period_encoder_int = set_period_us(10000);
  
  
  Serial.begin (115200);
  Serial.println("Welcome to sunalarm");
}


/* main loop checks for events and sends them to the state machine. */
void loop(){
  
  static uint8_t counter = 0;      //this variable will be changed by encoder input

  if( Encoder_int ) {
    Serial.print("Counter value: ");
    Serial.println(counter, DEC);
    counter += Encoder_int;
  }


  /* Display State machine */
  if(Display_int){
    //disp_digit_int();
    Display_int = 0;  
  }

  if(Display_blink_int){
    //disp_blink_int();
    Display_blink_int = 0; 
  }
  /* Display State machine END */

  if( input_alarm_button()){
	//event
    //Do something
  }
  
   if(Select_button_int){
    //Do something
	//event
    Select_button_int = 0;
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
  
  if((ticks % period_Select_button_int) == 0){
    Select_button_int = input_select_button();
  }

  if((ticks % period_encoder_int) == 0){
    Encoder_int = input_read_encoder();
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








