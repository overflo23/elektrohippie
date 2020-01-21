#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 8
#define TFT_CS 15

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);


void setup_display()
{
  Serial.println("setup_display()");
 
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  drawMenu();
}



void drawMenu() {

  drawHeader("Hello!");

  drawGong();
 
  drawLeft(false);
  //drawEnter(false);
  drawMiddle("START");
  drawRight(false);  
}



void drawGong()
{
      tft.drawCircle(240, 112, 70, ILI9341_MAGENTA);
      for(int i=0;i<10;i++)
      {
       drawNote(i,false);
      }
}

void drawNote(int note,boolean onoff)
{

  uint16_t color = ILI9341_MAGENTA;
  if(onoff) color = ILI9341_GREEN;
  
  switch(note)
  {

//bass
   case 0:
    tft.fillCircle(240, 112, 10, color);
   break;
    
//bass #2 (ring)
   case 1:
    tft.fillCircle(240, 112, 20, color);
   break; 

 // uhrzeigersinn ab vorne links  
   case 2:
    tft.fillCircle(220, 160, 10, color);
   break; 

   case 4:
    tft.fillCircle(190, 130, 10, color);
   break; 

   case 6:
    tft.fillCircle(190, 90, 10, color);
   break;   
   
   case 8:
    tft.fillCircle(220, 64, 10, color);
   break; 

   case 9:
    tft.fillCircle(262, 64, 10, color);
   break;   

   case 7:
    tft.fillCircle(290, 90, 10, color);
   break; 

   case 5:
    tft.fillCircle(290, 130, 10, color);
   break; 

   case 3:
    tft.fillCircle(262, 160, 10, color);
   break; 
   
  }

  
}


void drawHeader(String text)
{

// first dark
tft.fillRect(0, 0, 400, 40, ILI9341_BLACK);

  
tft.setTextSize(2);
tft.setTextColor(ILI9341_WHITE);
tft.setCursor(10, 5);
tft.println(text);
  
}


void drawLeft(boolean highlight)
{
  tft.setTextSize(4);
  tft.setTextColor(ILI9341_GREEN);
  if(highlight)   tft.setTextColor(ILI9341_RED);
  tft.setCursor(50, 200);
  tft.println("<");
}





void drawMiddle(String text)
{

 // first dark
 tft.fillRect(100, 200, 130, 50, ILI9341_BLACK);


 tft.setTextSize(3);
 tft.setTextColor(ILI9341_GREEN);
 tft.setCursor(125, 205);
 tft.println(text);
  
}

/*
void drawEnter(boolean highlight)
{
  tft.setTextSize(3);  
  tft.setTextColor(ILI9341_GREEN);
  if(highlight)   tft.setTextColor(ILI9341_RED);
  tft.setCursor(120, 205);
  tft.println("ENTER");
}
*/

void drawRight(boolean highlight)
{
  tft.setTextSize(4);
  tft.setTextColor(ILI9341_GREEN);
  if(highlight)   tft.setTextColor(ILI9341_RED);
  tft.setCursor(270, 200);
  tft.println(">");
}


void display_songinfo()
{
// first dark
tft.fillRect(0, 0, 160, 180, ILI9341_BLACK);

  
tft.setTextSize(2);
tft.setTextColor(ILI9341_WHITE);
tft.setCursor(10, 9);
tft.println("Currently playing:");

tft.setTextSize(2);
tft.setTextColor(ILI9341_RED);
tft.setCursor(10, 35);
tft.println(songname);

tft.setTextSize(2);
tft.setTextColor(ILI9341_WHITE);
tft.setCursor(10, 65);
tft.println("Author:");


tft.setTextSize(2);
tft.setTextColor(ILI9341_RED);
tft.setCursor(10, 90);
tft.println(author);


}
