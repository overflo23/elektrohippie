#include "OneButton.h"


const int button1=38;
const int button2=39;
const int button3=37;


OneButton b1(button1, true);
OneButton b2(button2, true);
OneButton b3(button3, true);




void setup_buttons()
{ 
    Serial.println("setup_buttons()");
    
 b1.attachLongPressStart(b1click);
 b2.attachLongPressStart(b2click);
 b3.attachLongPressStart(b3click);

 b1.attachLongPressStop(b1clickstop);
 b2.attachLongPressStop(b2clickstop);
 b3.attachLongPressStop(b3clickstop);

 b1.setPressTicks(1);
 b2.setPressTicks(1);
 b3.setPressTicks(1);
 
}


// called from b_delay
void handle_buttons()
{
 b1.tick();
 b2.tick();
 b3.tick(); 
}






void b1click()
{
//  button_down=true;
  Serial.println("button1 click");
  drawLeft(true);

  file_index--;
  if(file_index<0)
   file_index=(nSongs-1);
  resetPlayback(); 
    delay(100);
  
}

void b1clickstop()
{
  Serial.println("button1 click stop");
  drawLeft(false);
}





void b2click()
{
  //button_down=true;
  Serial.println("button2 click");
//  drawEnter(true);

/*
  if(gong_running)
  {
   drawHeader("Aus."); 
  }

  else
  {
   drawHeader("Yippie!");
    
  }
  gong_running = !gong_running;
 */


  delay(100);


}

void b2clickstop()
{
  Serial.println("button2 click stop");
//  drawEnter(false);
  if(playback)
  {
   playback =false;
   drawMiddle("PLAY");
  }
  else
  {
   playback = true;
   drawMiddle("STOP");   
  } 
  delay(100);
}





void b3click()
{
//  button_down=true;
  Serial.println("button3 click");
  drawRight(true);

  file_index++;
  if(file_index>nSongs-1)
   file_index=0;
  resetPlayback(); 
    delay(100);
}

void b3clickstop()
{
  Serial.println("button3 click stop");
  drawRight(false);
}
