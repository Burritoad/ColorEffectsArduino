	#include <delay_x.h>
	#define START_BIT   PORTB = B100000; _delay_us(10);
	#define ZERO_BIT    PORTB = B000000; _delay_us(10); PORTB = B100000; _delay_us(20);
	#define ONE_BIT     PORTB = B000000; _delay_us(20); PORTB = B100000; _delay_us(10);
 
//  make a serialized output
void setLed(int addr, int r, int g, int b){ 
	START_BIT;
	//address
	if (addr & B100000) {ONE_BIT;} else {ZERO_BIT;}
	if (addr & B010000) {ONE_BIT;} else {ZERO_BIT;}
	if (addr & B001000) {ONE_BIT;} else {ZERO_BIT;}
	if (addr & B000100) {ONE_BIT;} else {ZERO_BIT;}
	if (addr & B000010) {ONE_BIT;} else {ZERO_BIT;}
	if (addr & B000001) {ONE_BIT;} else {ZERO_BIT;}
	//Brightness
	ONE_BIT;
	ONE_BIT;
	ONE_BIT;
	ONE_BIT;
	ONE_BIT;
	ONE_BIT;
	ZERO_BIT;
	ZERO_BIT;
	//blue
	if (b & B100000) {ONE_BIT;} else {ZERO_BIT;}
	if (b & B010000) {ONE_BIT;} else {ZERO_BIT;}
	if (b & B001000) {ONE_BIT;} else {ZERO_BIT;}
	if (b & B000100) {ONE_BIT;} else {ZERO_BIT;}
	//green
	if (g & B100000) {ONE_BIT;} else {ZERO_BIT;}
	if (g & B010000) {ONE_BIT;} else {ZERO_BIT;}
	if (g & B001000) {ONE_BIT;} else {ZERO_BIT;}
	if (g & B000100) {ONE_BIT;} else {ZERO_BIT;}
	//red
	if (r & B100000) {ONE_BIT;} else {ZERO_BIT;}
	if (r & B010000) {ONE_BIT;} else {ZERO_BIT;}
	if (r & B001000) {ONE_BIT;} else {ZERO_BIT;}
	if (r & B000100) {ONE_BIT;} else {ZERO_BIT;}
	PORTB = B000000; //set low for end of frame
	_delay_us(32);
}