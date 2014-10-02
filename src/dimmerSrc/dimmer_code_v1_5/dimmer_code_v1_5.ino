/*
 * Lysalarm 
 * Author: Eirin, Geir
 * Date: 06 mars 2014
 */


int led = 13;
int ledMode = 0;

int AC_LOAD = 3;    // Output to Opto Triac pin
int dimming = 5;  // Dimming level (0-100)  0 = ON, 100 = OFF



char tcnt2 = 0;
/* Toggle HIGH or LOW digital write */
int toggle = 0;

void setup() {               
 
  
  /* Dimmercode  */
  pinMode(AC_LOAD, OUTPUT);	      // Set the AC Load as output
  attachInterrupt(0, zero_crosss_int, RISING);  // Attach interrupt on pin 2


  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);   
  

 /* First disable the timer overflow interrupt while we're configuring */
  TIMSK2 &= ~(1<<TOIE2);
 
  /* Configure timer2 in normal mode (pure counting, no PWM etc.) */
  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
  TCCR2B &= ~(1<<WGM22);
 
  /* Select clock source: internal I/O clock */
  ASSR &= ~(1<<AS2);
 
  /* Disable Compare Match A interrupt enable (only want overflow) */
  TIMSK2 &= ~(1<<OCIE2A);
 
  /* Now configure the prescaler to CPU clock divided by 128 */
  TCCR2B |= (1<<CS22)  | (1<<CS20) | (1<<CS21); // Set bits
 
  /* We need to calculate a proper value to load the timer counter.
   * The following loads the value 131 into the Timer 2 counter register
   * The math behind this is:
   * (CPU frequency) / (prescaler value) = 125000 Hz = 8us.
   * (desired period) / 8us = 125.
   * MAX(uint8) + 1 - 125 = 131;
   */
  /* Save value globally for later reload in ISR */
  /* TCNT value of 157 gives overflow after 10 ms
  tcnt2 = 99; 
 
  /* Finally load end enable the timer */
  TCNT2 = tcnt2;
  TIMSK2 |= (1<<TOIE2);
}

/*
 * Install the Interrupt Service Routine (ISR) for Timer2 overflow.
 * This is normally done by writing the address of the ISR in the
 * interrupt vector table but conveniently done by using ISR()  */
ISR(TIMER2_OVF_vect) {
  /* Stop timer */
  /* Write to a digital pin so that we can confirm our timer */
  
  /*  */
  digitalWrite(AC_LOAD, HIGH);   // triac firing
  delayMicroseconds(10);         // triac On propogation delay
  digitalWrite(AC_LOAD, LOW);    // triac Off
  toggle = ~toggle;
}
 

void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
{
  /* Load value into tcnt2 and start timer2 */
  
  TCNT2 = set_dimming(dimming);
    digitalWrite(AC_LOAD, HIGH);   // triac firing
  delayMicroseconds(100);         // triac On propogation delay
  digitalWrite(AC_LOAD, LOW);    // triac Off
  //TIMSK2 |= (1<<TOIE2);
}


/* main loop checks for events and sends them to the state machine. */
void loop(){
  /*
  int i;
  for(i=0; i<100; i++){
    dimming = i;
    delay(100);
  }
  for(i=100; i>0; i--){
    dimming = i;
    delay(100);
  }
  */
}

uint8_t set_dimming(uint8_t dimmingDC){
  
   return 155 +  dimmingDC;
  
}








