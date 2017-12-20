  #include <delay_x.h>
  #define START_BIT   PORTB = B110000; _delay_us(10);
  #define ZERO_BIT    PORTB = B000000; _delay_us(10); PORTB = B110000; _delay_us(20);
  #define ONE_BIT     PORTB = B000000; _delay_us(20); PORTB = B110000; _delay_us(10);
  #define IO_BIT      PORTB = B000000; _delay_us(10); PORTB = B010000; _delay_us(10); PORTB = B110000; _delay_us(10); //upper not lower
  #define OI_BIT      PORTB = B000000; _delay_us(10); PORTB = B100000; _delay_us(10); PORTB = B110000; _delay_us(10);
 
 
  int rV = 0;
  int gV = 0;
  int bV = 0;
  int framebuffer[8][8] = {
  {0000,0000,0000,0000,0000,0000,0000,3840},
  {0000,0000,0000,0000,0000,0000,0000,4080},
  {0000,0000,0000,0000,0000,0000,0000,240},
  {0000,0000,0000,0000,0000,0000,0000,255},
  {0000,0000,0000,0000,0000,0000,0000,15},
  {0000,0000,0000,0000,0000,0000,0000,3855},
  {0000,0000,0000,0000,0000,0000,0000,3840},
  {0000,0000,0000,0000,0000,0000,0000,4080}}; 
 
  
//  grab the info from the framebuffer and make a serialized output
void frame(int fy, int fx){ 
  //get the 2 color values out of the framebuffer
  int addr = fx+(fy*8);
  int A = framebuffer[fy][fx];
  int B = framebuffer[fy+4][fx];
  
  
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
  if (A & B1000) {if (B & B1000) {ONE_BIT;} else {IO_BIT;}}else{if (B & B1000) {OI_BIT;} else {ZERO_BIT;}}
  if (A & B0100) {if (B & B0100) {ONE_BIT;} else {IO_BIT;}}else{if (B & B0100) {OI_BIT;} else {ZERO_BIT;}}
  if (A & B0010) {if (B & B0010) {ONE_BIT;} else {IO_BIT;}}else{if (B & B0010) {OI_BIT;} else {ZERO_BIT;}}
  if (A & B0001) {if (B & B0001) {ONE_BIT;} else {IO_BIT;}}else{if (B & B0001) {OI_BIT;} else {ZERO_BIT;}}
  A = A >> 4;
  B = B >> 4;
  //green
  if (A & B1000) {if (B & B1000) {ONE_BIT;} else {IO_BIT;}}else{if (B & B1000) {OI_BIT;} else {ZERO_BIT;}}
  if (A & B0100) {if (B & B0100) {ONE_BIT;} else {IO_BIT;}}else{if (B & B0100) {OI_BIT;} else {ZERO_BIT;}}
  if (A & B0010) {if (B & B0010) {ONE_BIT;} else {IO_BIT;}}else{if (B & B0010) {OI_BIT;} else {ZERO_BIT;}}
  if (A & B0001) {if (B & B0001) {ONE_BIT;} else {IO_BIT;}}else{if (B & B0001) {OI_BIT;} else {ZERO_BIT;}}
  A = A >> 4;
  B = B >> 4;
  //red
  if (A & B1000) {if (B & B1000) {ONE_BIT;} else {IO_BIT;}}else{if (B & B1000) {OI_BIT;} else {ZERO_BIT;}}
  if (A & B0100) {if (B & B0100) {ONE_BIT;} else {IO_BIT;}}else{if (B & B0100) {OI_BIT;} else {ZERO_BIT;}}
  if (A & B0010) {if (B & B0010) {ONE_BIT;} else {IO_BIT;}}else{if (B & B0010) {OI_BIT;} else {ZERO_BIT;}}
  if (A & B0001) {if (B & B0001) {ONE_BIT;} else {IO_BIT;}}else{if (B & B0001) {OI_BIT;} else {ZERO_BIT;}}
  PORTB = B000000; //set low for end of frame
  _delay_us(32);
}
 
 void fb_output(){
   for (int y = 0; y < 4; y++) { 
     for (int x = 0; x < 8; x++) {
       frame(y,x);
     };
   };
 }
  
   
 void setup()  
 {
   delay(10);  
  DDRB = DDRB | B110000; 
 }  
 
   
 void loop(){
   int derp = random(0,6);
   if(derp == 5){  
     int y = random(0,8);
     if(framebuffer[y][7] == 0){
       rV = random(0,15)*256;
       gV = random(0,15)*16;
       bV = random(0,15);
       framebuffer[y][7] = rV+gV+bV;
     }
   }
   for (int x = 0; x < 8; x++) { 
     for (int y = 0; y < 8; y++) {
       if(x > 0){
         framebuffer[y][x-1] = framebuffer[y][x];
       }
       int R = framebuffer[y][x]&3840;
       int G = framebuffer[y][x]&240;
       int B = framebuffer[y][x]&15;
       if (B>0){
       framebuffer[y][x] = framebuffer[y][x] - 1;
       }
       if (G>0){
       framebuffer[y][x] = framebuffer[y][x] - 16;
       }
       if (R>0){
       framebuffer[y][x] = framebuffer[y][x] - 256;
       }
     }
   }
   fb_output();
   //delay(2);  
 }   
