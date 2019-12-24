
// how long to tune a tone
// might migrtea to array vor individual lengths on each tone..
//int tone_on = 10; 

int tone_on[10] = {
 20,
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


int notes[10] = {
 note1,
 note2,
 note3,
 note4,
 note5,
 note6,
 note7,
 note8,
 note9,
 note10
};


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
  // cycle trough sound array of al 10 notes decrement playconuter, foinally set to 0 afet 100ms
  // fianlly pull pin low
  for(int i=0;i<10;i++)
  {
   uint32_t onsince =  playnotes[i];
   if((onsince>0) && (millis()-onsince) > tone_on[i])
   {
    note_off(i);    
   }
   
  }

  
}



// pin duration (10-100)  pwm (0-256)
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

for(int i=0;i<10;i++)
{
 note_on(i);
 b_delay(300);
 if(!gong_running) return;
}


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
  
 drawNote(note, false); 
 playnotes[note] = 0;
 digitalWrite(notes[note],LOW);
}



void gong_random()
{

 int index=random(0,10);
 int wait=random(200,1000);
 gong(index);
 b_delay(wait);
}
