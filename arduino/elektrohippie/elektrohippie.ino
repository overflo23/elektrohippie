
// is this a debug build? -> no actual triggers on solenoids
#define DEBUG false

int led=13;

int button_down = false;




// clockwise  from display

int note1 = 2;
int note2 = 5;
int note3 = 3;
int note4 = 4;
int note5 = 6;
int note6 = 14;
int note7 = 9;
int note8 = 7;

//unten
int note9 = 23;
int note10 = 10;


void setup() {
  Serial.begin(115200);

  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);


setup_midi();
setup_gong();
setup_buttons();
setup_display();

setup_sdcard();

 //gong_init();

}


int counter=0;


// where in the menu are we?
int menustate=0;
int submenustate=0;



boolean gong_running = false;

void loop() {
  // Add your MIDI application here...
  handle_buttons();
  handle_midi();
  handle_gong();
  
  handle_sdcard();

  if(gong_running)  gong_init();


}



// global helpers 

boolean b_delay(int wait)
{

 for(int i=0;i<wait;i++) 
 {
  delay(1);
  handle_buttons();
  handle_gong();
  handle_midi();
  if(button_down)
  {
   button_down=false;
   return true;
  }
 }
 return false;
}
