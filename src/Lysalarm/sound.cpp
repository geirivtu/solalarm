/*! \file sound.cpp
 *
 *  \brief Controls the sound card. 
 *  \author Geir Turtum
 *  \date   03.okt.2014
 */

 #define PLAY_PIN 10
 #define RESET_PIN 11 
 
 
 void sound_init(void){
 
  /* Set pin to tristate input. To pull pins low set pinMode to output.
  * DO NOT write HIGH to pins. Soundcard does not work on 5V.
  */

  pinMode(PLAY_PIN, INPUT); 
  pinMode(RESET_PIN, INPUT); 
  digitalWrite(PLAY_PIN, LOW);
  digitalWrite(RESET_PIN, LOW);
}
 

 
void sound_play(void){
  /* Tristate RESET_PIN and pull PLAY_PIN low */
  pinMode(RESET_PIN, INPUT); 
  pinMode(PLAY_PIN, OUTPUT); 
}
 
 
 
void sound_reset(void){
  /* Tristate PLAY_PIN and pull RESET_PIN low */
  pinMode(PLAY_PIN, INPUT); 
  pinMode(RESET_PIN, OUTPUT); 
}
