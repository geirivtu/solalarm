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
#include "light.h"
#include "stateMachine.h"

 
#define NR_OF_TASK 10 
 
struct task_t {
  char name[20];
  uint8_t execute=0;
  uint8_t period;
  void (*function)(void);
 };
 
 

struct task_t Tasks[NR_OF_TASK];
 
 /*
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
*/


const uint32_t Timebase_scheduler_us = 1000;


int led = 13;
int ledMode = 0;

void taskAdd(char * taskName, uint32_t taskPeriod, void (*functionPtr)(void)){
  static uint8_t i = 0;
  
  if(i >= NR_OF_TASK){
    Serial.println("To many tasks!");
  }
  
  strcpy(Tasks[i].name, taskName);
  Tasks[i].period = taskPeriod;
  Tasks[i].function = functionPtr;
  

  i++;
}

void encFunc(){
  int8_t encoder = 0;      //this variable will be changed by encoder input
  encoder = input_read_encoder();
  if(encoder==1) event_EncoderUp();
  else if(encoder==-1) event_EncoderDown();

}

void alarmFunc(){
  if(input_get_alarm_button_status()){
    event_AlarmOff();
  }
  else{
    event_AlarmOn();
  }

}

void timeFunc(){


}

void setup() {                

  /* Init display driver */
  disp_init();
  
  light_init();
  
  input_init();
  
  sound_init();
  
  time_init();

  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);   



  
  taskAdd("display_int", 3000, &disp_digit_int);
  taskAdd("display_blink_int", 250000, &disp_blink_int);
  taskAdd("Set_button_int", 50000, &event_SetButton);
  taskAdd("Alarm_switch_int", 50000, &alarmFunc);
  taskAdd("encoder_int", 10000, &encFunc);
  taskAdd("time_minute_int", 500000, &timeFunc);


  /* Set period for tasks */

  /* Period for updating display digits */
  //period_display_int = set_period_us(3000);

  /* Period for blinking the digits */
  //period_display_blink_int = set_period_us(250000);

  /* Period for Select button */
  //period_Set_button_int = set_period_us(50000);
  
  /* Period for Alarm switch read  */
 // period_Alarm_switch_int = set_period_us(50000);
  
  /* Period for encoder read */
 // period_encoder_int = set_period_us(10000);
  
  /* Period for time minute interrupt */
  //period_time_minute_int = set_period_us(500000);
  
  Timer1.initialize(Timebase_scheduler_us); //Fires every x us
  Timer1.attachInterrupt( scheduler ); // attach the service routine here
  
  
  Serial.begin (115200);
  Serial.println("Welcome to sunalarm");
}


/* main loop checks for events and sends them to the state machine. */
void loop(){
  

  /*
  
  if( Encoder_int ){    
    encoder = input_read_encoder();
    if(encoder==1) event_EncoderUp();
    else if(encoder==-1) event_EncoderDown();
   
    Encoder_int = 0;
  }

  
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
     
    Time_minute_int = 0;
   }
   */
   
   uint8_t i;
   for(i=0; i<NR_OF_TASK; i++){
    if(Tasks[i].execute == 1){
    
      (*Tasks[i].function)();
      Tasks[i].execute = 0;
    }
   }
  
  //digitalWrite(led, ledMode); //Debug
}






/* --------------------------
 * Scheduler ISR Timer Routine
 * 
 * --------------------------
 */
void scheduler(){
  static uint32_t ticks = 0;

  ticks++; /* ticks keep track of time */
  
  uint8_t i;
  for(i=0; i<NR_OF_TASK; i++){
    if((ticks % Tasks[i].period) == 0){
      Tasks[i].execute = 1;
    }
  }

  /*
  if((ticks % period_display_int) == 0){
    Display_int = 1;
  }

  if((ticks % period_display_blink_int) == 0){
    Display_blink_int  = 1;
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
*/
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








