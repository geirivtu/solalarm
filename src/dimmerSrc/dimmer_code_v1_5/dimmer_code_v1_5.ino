/*
 * Lysalarm 
 * Author: Eirin, Geir
 * Date: 06 mars 2014
 */



int LED_STROBE = 10;
int LED_POWER = 9;

#define MAX_LED_POWER 153
#define MIN_LED_STROBE_DC 230 

int i = 0;

void setup() {               
 
 
  // initialize the digital pin as an output.
  pinMode(LED_STROBE, OUTPUT);
  pinMode(LED_POWER, OUTPUT);
  set_led_strobe_dc(230);
  set_led_power_current_draw(MAX_LED_POWER/2);
}

/* main loop checks for events and sends them to the state machine. */
void loop(){

  set_led_strobe_dc(MIN_LED_STROBE_DC+i);
  i++;
  if((MIN_LED_STROBE_DC+i)==255) i = 0;
  
  delay(50);
}


/*
* Controls the LED dc. Max pulse width = 500 us
*/
void set_led_strobe_dc(int dc){
  
  if(dc < MIN_LED_STROBE_DC) dc = MIN_LED_STROBE_DC;
  
  analogWrite(LED_STROBE, dc); 
 
}

/*
* Controls max current drawn by the LEDs. 
* Argument = [0, 153]
*/
void set_led_power_current_draw(int dc){
  
 if(dc > MAX_LED_POWER) dc = MAX_LED_POWER;
  
 analogWrite(LED_POWER, dc); 

}








