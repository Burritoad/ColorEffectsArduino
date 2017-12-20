#include <delay_x.h>
  #define START_BIT   PORTB = B111110; _delay_us(10);
  #define ZERO_BIT    PORTB = B000000; _delay_us(10); PORTB = B111110; _delay_us(20);
  #define ONE_BIT     PORTB = B000000; _delay_us(20); PORTB = B111110; _delay_us(10);
  
 void DATA_BIT(int bits){
  PORTB = B000000; 
  _delay_us(10); 
  PORTB = bits; 
  _delay_us(10); 
  PORTB = B111110; 
  _delay_us(10);
}
 
  int derp = 0;
  int color = 0;
  int rV = 0;
  int gV = 0;
  int bV = 0;
  int mode = 0;
  int slideR = A0; 
  int slideG = A1;   
  int slideB = A2;    
  int modepina = 7;
  int modepinb = 6;
  int modepinc = 5;
  int avg[9] = {0,0,0,0,0,0,0,0,0};
  int framebuffer[5][12] = {
  {0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
  {0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
  {4095,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,4095},
  {3840,240,15,0000,4095,0000,0000,0000,0000,0000,0000,4095},
  {4080,255,3855,0000,0000,4095,0000,0000,0000,0000,0000,4095}}; 
 

//  grab the info from the framebuffer and make a serialized output
void frame(int fx){ 
  //get the 5 color values out of the framebuffer for simulatenous writing
  int addr = fx;
  int A = framebuffer[0][fx];
  int B = framebuffer[1][fx];
  int C = framebuffer[2][fx];
  int D = framebuffer[3][fx];
  int E = framebuffer[4][fx];  
  
  
  //prepare all the bits beforehand to avoid screwing up the timings
  //blue
  int b1Bit = B111110;
  if (A & B1000) {b1Bit = b1Bit - B100000;}
  if (B & B1000) {b1Bit = b1Bit - B010000;}
  if (C & B1000) {b1Bit = b1Bit - B001000;}
  if (D & B1000) {b1Bit = b1Bit - B000100;}
  if (E & B1000) {b1Bit = b1Bit - B000010;}
  int b2Bit = B111110;
  if (A & B0100) {b2Bit = b2Bit - B100000;}
  if (B & B0100) {b2Bit = b2Bit - B010000;}
  if (C & B0100) {b2Bit = b2Bit - B001000;}
  if (D & B0100) {b2Bit = b2Bit - B000100;}
  if (E & B0100) {b2Bit = b2Bit - B000010;}
  int b3Bit = B111110;
  if (A & B0010) {b3Bit = b3Bit - B100000;}
  if (B & B0010) {b3Bit = b3Bit - B010000;}
  if (C & B0010) {b3Bit = b3Bit - B001000;}
  if (D & B0010) {b3Bit = b3Bit - B000100;}
  if (E & B0010) {b3Bit = b3Bit - B000010;}
  int b4Bit = B111110;
  if (A & B0001) {b4Bit = b4Bit - B100000;}
  if (B & B0001) {b4Bit = b4Bit - B010000;}
  if (C & B0001) {b4Bit = b4Bit - B001000;}
  if (D & B0001) {b4Bit = b4Bit - B000100;}
  if (E & B0001) {b4Bit = b4Bit - B000010;}
  //green
  A = A >> 4;
  B = B >> 4;
  C = C >> 4;
  D = D >> 4;
  E = E >> 4;
  int g1Bit = B111110;
  if (A & B1000) {g1Bit = g1Bit - B100000;}
  if (B & B1000) {g1Bit = g1Bit - B010000;}
  if (C & B1000) {g1Bit = g1Bit - B001000;}
  if (D & B1000) {g1Bit = g1Bit - B000100;}
  if (E & B1000) {g1Bit = g1Bit - B000010;}
  int g2Bit = B111110;
  if (A & B0100) {g2Bit = g2Bit - B100000;}
  if (B & B0100) {g2Bit = g2Bit - B010000;}
  if (C & B0100) {g2Bit = g2Bit - B001000;}
  if (D & B0100) {g2Bit = g2Bit - B000100;}
  if (E & B0100) {g2Bit = g2Bit - B000010;}
  int g3Bit = B111110;
  if (A & B0010) {g3Bit = g3Bit - B100000;}
  if (B & B0010) {g3Bit = g3Bit - B010000;}
  if (C & B0010) {g3Bit = g3Bit - B001000;}
  if (D & B0010) {g3Bit = g3Bit - B000100;}
  if (E & B0010) {g3Bit = g3Bit - B000010;}
  int g4Bit = B111110;
  if (A & B0001) {g4Bit = g4Bit - B100000;}
  if (B & B0001) {g4Bit = g4Bit - B010000;}
  if (C & B0001) {g4Bit = g4Bit - B001000;}
  if (D & B0001) {g4Bit = g4Bit - B000100;}
  if (E & B0001) {g4Bit = g4Bit - B000010;}
  //red
  A = A >> 4;
  B = B >> 4;
  C = C >> 4;
  D = D >> 4;
  E = E >> 4;
  int r1Bit = B111110;
  if (A & B1000) {r1Bit = r1Bit - B100000;}
  if (B & B1000) {r1Bit = r1Bit - B010000;}
  if (C & B1000) {r1Bit = r1Bit - B001000;}
  if (D & B1000) {r1Bit = r1Bit - B000100;}
  if (E & B1000) {r1Bit = r1Bit - B000010;}
  int r2Bit = B111110;
  if (A & B0100) {r2Bit = r2Bit - B100000;}
  if (B & B0100) {r2Bit = r2Bit - B010000;}
  if (C & B0100) {r2Bit = r2Bit - B001000;}
  if (D & B0100) {r2Bit = r2Bit - B000100;}
  if (E & B0100) {r2Bit = r2Bit - B000010;}
  int r3Bit = B111110;
  if (A & B0010) {r3Bit = r3Bit - B100000;}
  if (B & B0010) {r3Bit = r3Bit - B010000;}
  if (C & B0010) {r3Bit = r3Bit - B001000;}
  if (D & B0010) {r3Bit = r3Bit - B000100;}
  if (E & B0010) {r3Bit = r3Bit - B000010;}
  int r4Bit = B111110;
  if (A & B0001) {r4Bit = r4Bit - B100000;}
  if (B & B0001) {r4Bit = r4Bit - B010000;}
  if (C & B0001) {r4Bit = r4Bit - B001000;}
  if (D & B0001) {r4Bit = r4Bit - B000100;}
  if (E & B0001) {r4Bit = r4Bit - B000010;}
  
  
  //start writing the frame
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
  DATA_BIT(b1Bit);
  DATA_BIT(b2Bit);
  DATA_BIT(b3Bit);
  DATA_BIT(b4Bit);
  //green
  DATA_BIT(g1Bit);
  DATA_BIT(g2Bit);
  DATA_BIT(g3Bit);
  DATA_BIT(g4Bit);
  //red
  DATA_BIT(r1Bit);
  DATA_BIT(r2Bit);
  DATA_BIT(r3Bit);
  DATA_BIT(r4Bit);
  PORTB = B000000; //set low for end of frame
  _delay_us(32);
}
 
 void fb_output(){
     for (int x = 0; x < 12; x++) {
       frame(x);
     };
 }
  
 void colorize(int val,int brt){ //maps val as 0 to brt
   int R = 0;
   int G = 0;
   int B =0;
   if(val<85){
     B = map(val,0,85,brt,0);
     G = brt-B;
   }else if(val>170){
     B = map(val,170,255,0,brt);
     R = brt-B;
   }else{
     G = map(val,85,170,brt,0);
     R = brt-G;
   }
   R = R*256;
   G = G*16;
   
   color = R+G+B;
   
 }
 
 void blur(){
  int framebuffbuff[7][15] = {
  {0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
  {0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
  {0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
  {0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
  {0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
  {0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
  {0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},};
  for (int x = 11; x > -1; x--) { 
    for (int y = 0; y < 5; y++) {
      if(framebuffer[y][x] & B1100){
         framebuffbuff[y][x] = framebuffbuff[y][x] - 4;
         framebuffbuff[y-1][x] = framebuffbuff[y-1][x] + 1;
         framebuffbuff[y+1][x] = framebuffbuff[y+1][x] + 1; 
         framebuffbuff[y][x-1] = framebuffbuff[y][x-1] + 1; 
         framebuffbuff[y][x+1] = framebuffbuff[y][x+1] + 1; 
      }
      if(framebuffer[y][x] & B11000000){
        framebuffbuff[y][x] = framebuffbuff[y][x] - 64;
        framebuffbuff[y-1][x] = framebuffbuff[y-1][x] + 16;
        framebuffbuff[y+1][x] = framebuffbuff[y+1][x] + 16; 
        framebuffbuff[y][x-1] = framebuffbuff[y][x-1] + 16; 
        framebuffbuff[y][x+1] = framebuffbuff[y][x+1] + 16; 
      }
      if(framebuffer[y][x] & 3072){
        framebuffbuff[y][x] = framebuffbuff[y][x] - 1024;
          framebuffbuff[y-1][x] = framebuffbuff[y-1][x] + 256;
          framebuffbuff[y+1][x] = framebuffbuff[y+1][x] + 256; 
          framebuffbuff[y][x-1] = framebuffbuff[y][x-1] + 256; 
          framebuffbuff[y][x+1] = framebuffbuff[y][x+1] + 256; 
      }
    }
  }//close for loops
  for (int x = 11; x > -1; x--) { 
    for (int y = 0; y < 5; y++) {
      framebuffer[y][x] = framebuffer[y][x] + framebuffbuff[y][x];
    }
  }
 }
 void setup()  
 {
  Serial.begin(57600);
  delay(10);  
  DDRB = DDRB | B111110; 
  pinMode(modepina, INPUT);
  pinMode(modepinb, INPUT);
  pinMode(modepinc, INPUT);
 }  
 
   
 void loop(){
  int data[9] = {0,0,0,0,0,0,0,0,0}; // raw serial data <>
  rV = analogRead(slideR);
  gV = analogRead(slideG);
  bV = analogRead(slideB);
  
  mode = 0;
  if (digitalRead(modepina) == HIGH){
    mode = 1; //first pin high manual modes
  }
  if (digitalRead(modepinb) == HIGH){
    mode += 2; // firefly
  }
  
   
  if (Serial.available() >10) {
    byte i = Serial.read();
    if (int(i) == 255) {
      for (int c = 0; c < 9; c++){
      data[c] = int(Serial.read());
      }
    }
  }
    
    if (mode == 0){
      if (data[0] + data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7] + data[8] > 0){ //vis if nonzero
      //coaster
        int lvl = (data[0] + data[1]) / 2;
        int lvl2 = (data[2] + data[3] + data[4]) / 3;
        int lvl3 = (data[4] + data[5] + data[6]) / 3;
        int lvl4 = (data[7] + data[8]) / 2;
        //a bit of tweaking to get more color out of it
        /*lvl = map(lvl,64,250,0,255);
        lvl2 = map(lvl2,64,250,0,255);
        lvl3 = map(lvl3,64,250,0,255);
        lvl4 = map(lvl4,64,250,0,255);
        */
        int bright = lvl+lvl2+lvl3+lvl4;
        bright = map(bright,0,1000,0,15);
        colorize(lvl,bright);
        framebuffer[0][0] = color;
        colorize(lvl2,bright);
        framebuffer[1][0] = color;
        colorize(lvl3,bright);
        framebuffer[2][0] = color;
        colorize(lvl4,bright);
        framebuffer[3][0] = color;
        for (int x = 11; x > 0; x--) { 
           for (int y = 0; y < 4; y++) { 
              framebuffer[y][x] = framebuffer[y][x-1];
           }
        }
      }
    }else if(mode == 1){ //Basic manual lighting
     rV = map(rV,0,1024,0,15);
     gV = map(gV,0,1024,0,15);
     bV = map(bV,0,1024,0,15);
     for (int x = 0; x < 12; x++) { 
         for (int y = 0; y < 4; y++) {
         framebuffer[y][x]= (rV*256)+(gV*16)+bV;
         }
     }
    }else if(mode == 3){ //manual firefly mode
    delay(bV/4); //speed based on "blue" slider
     rV = rV/4;
     colorize(rV,15); //color based on "red" slider
     int derp = random(0,1023); // frequency based on "green" slider
     if(derp < gV){
      framebuffer[random(0,4)][random(0,12)]|= 4096; 
     }
     if(derp+50 < gV*.8){
      framebuffer[random(0,4)][random(0,12)]|= 4096; 
     }
     if(derp+100 < gV*.6){
      framebuffer[random(0,4)][random(0,12)]|= 4096; 
     }
     if(derp+200 < gV*.3){
      framebuffer[random(0,4)][random(0,12)]|= 4096; 
     }
     for (int x = 0; x < 12; x++) { 
         for (int y = 0; y < 4; y++) {
           if(framebuffer[y][x]>=4096){ 
             int R = color&3840 - framebuffer[y][x]&3840;
             int G = color&240 - framebuffer[y][x]&240;
             int B = color&15 - framebuffer[y][x]&15;
             if (B>0){
              framebuffer[y][x] = framebuffer[y][x] + 1;
             }
             if (G>0){
              framebuffer[y][x] = framebuffer[y][x] + 16;
             }
             if (R>0){
              framebuffer[y][x] = framebuffer[y][x] + 256;
             }
             if (R+G+B == 0){//go into decay cycle after reaching color
               framebuffer[y][x] = color;
             }
           }else{ //decay
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
     }
    }else if(mode == 2){//music synced firefly
    delay(bV/4); //speed based on "blue" slider
    //average the vu level
    for (int x = 0; x < 9; x++) {
    avg[x] = avg[x]*.999 + data[x]*.001;
    if(data[x]>avg[x]*1.5){
      colorize(x*28,16);
      framebuffer[random(0,4)][random(0,12)]= color;
    }
    
    }
    
    for (int x = 0; x < 12; x++) { 
         for (int y = 0; y < 4; y++) {
           //decay
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
    }
   fb_output();
   //delay(2);  
 }   
