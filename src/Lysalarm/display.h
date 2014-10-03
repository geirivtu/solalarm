 /*! \file display.h
 *
 *  \brief Driver for 7-segment led display, controlled by an 7-seg driver 
 *  \author Geir Turtum
 *  \date   06.mars.2014
 */



#ifndef H_DISPLAY
#define H_DISPLAY


void disp_init();

void disp_on();
void disp_off();

void disp_write(int hour, int minute);

void disp_digit_int();

void disp_blink_int();

void disp_min_blink();
void disp_hour_blink();


#endif //H_DISPLAY
