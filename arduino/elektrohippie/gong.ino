

// how long each tone is triggered
int tone_on[10] = {
 50,
 50,
 50,
 50,
 50,
 50,
 50,
 50,
 50,
 50
};




//CDEFGAH 
int notes[10] = {         // MIDI  
 note10, // A2 444 hz     // 38
 note9,  // D2 ?          // 45 
                         //laut sonsti
 note1, //D3 / A3  //0   A3  57
 note8, //C4       //7   C4  60
 note2, //D4       //1   D4  62
 note7, //E4       //6   E4  64
 note3, //F4       //2   F4  65
 note6, //G4       //5   G4  67
 note4, //A4       //3   A4  69
 note5, //C5       //4   C5  72
};







// contains WHEN a note i striggered millis()
uint32_t playnotes[10] = {0,0,0,0,0,0,0,0,0,0};


void setup_gong()
{
    Serial.println("setup_gong()");
    
pinMode(note1, OUTPUT);
pinMode(note2, OUTPUT);
pinMode(note3, OUTPUT);
pinMode(note4, OUTPUT);
pinMode(note5, OUTPUT);
pinMode(note6, OUTPUT);
pinMode(note7, OUTPUT);
pinMode(note8, OUTPUT);
pinMode(note9, OUTPUT);
pinMode(note10, OUTPUT);

}

void handle_gong()
{
  // cycle trough sound array of al 10 notes decrement playcounter, finally set to 0 after 100ms
  // fianlly pull pin low
  for(int i=0;i<10;i++)
  {
   uint32_t onsince =  playnotes[i];


  // went from 50 to 20 ms for testing 
    if((onsince>0) && (millis()-onsince) > tone_on[i])
  //if((onsince>0) && (millis()-onsince) > 20)
  {
    note_off(i);    


     // integrated in note_off
    //reset note 
   // if((millis()-onsince+100) > tone_on[i])
   // { 
   //   
   // }
    
   }
   
  }

  
}



void gong(int note)
{
  Serial.print("GONG: ");
  Serial.println(notes[note]);
  if(!DEBUG)    digitalWrite(notes[note],HIGH);
 // delay(duration);
 // analogWrite(pin,0);    
}





void gong_init()
{
  // von tief nach hoch

 for(int i =0;i<10;i++)
 { 
  note_on(i);
  b_delay(200);
  if(!gong_running) return;
 }
 
   b_delay(1000);
 

}




void note_on(int note)
{

  Serial.print("ON: ");
  Serial.println(note);
 drawNote(note, true); 
 playnotes[note] = millis();
 gong(note);
}


void note_off(int note)
{
  Serial.print("OFF: ");
  Serial.println(note);
 playnotes[note] = 0; 
 drawNote(note, false); 
 digitalWrite(notes[note],LOW);
}



void gong_random()
{

 int index=random(0,10);
 int wait=random(200,1000);
 gong(index);
 b_delay(wait);
}
