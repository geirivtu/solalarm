/*! \file light.cpp
 *
 *  \brief Functions for reading button, switch and encoder.  
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */



#include "light.h"

#define LIGHT_PIN 11


static int Brightness = 0;

void light_init(){
  
  pinMode(LIGHT_PIN, OUTPUT); 
 
}



void light_on(){
  
  Brightness = 255;
  analogWrite(LIGHT_PIN, Brightness);
  
}


void light_off(){
  
  Brightness = 0;
  analogWrite(LIGHT_PIN, Brightness);
  
}

void light_inc(){
  
  Brightness +=15;
  if(Brightness > 255) Brightness = 255;
  analogWrite(LIGHT_PIN, Brightness);
  
}

void light_dec(){
  
  Brightness -= 15;
  if(Brightness < 0) Brightness=0; 
  analogWrite(LIGHT_PIN, Brightness);
  
}


