
// is this a debug build? -> no actual triggers on solenoids
#define DEBUG true
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






// sd card midi file read
//factor delay*factor between notes. the higher the factor the slower the song..
int playback_speed = 1;
char songname[100];
char author[100];



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



// for SDCARD
int counter=0;

// currently selected file
int file_index=0;
// total songs
int nSongs=0;
// list of fiels in /PLAY folder
String *songList;


boolean playback = false;


//boolean gong_running = false;

void loop() {
  // Add your MIDI application here...
  handle_buttons();
  handle_midi();
  handle_gong();
  
  handle_sdcard();

  //if(gong_running)  gong_init();


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
