

void setup_midi()
{ 
  Serial.println("setup_midi()");
  usbMIDI.setHandleNoteOn(myNoteOn);



}


void handle_midi()
{
 usbMIDI.read();
  
}



void myNoteOn(byte channel, byte note, byte velocity) {
  // When using MIDIx4 or MIDIx16, usbMIDI.getCable() can be used
  // to read which of the virtual MIDI cables received this message.
  Serial.print("Note On, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
  digitalWrite(led,HIGH);


  switch(note)
  {

   case 40: // pad 1 
   case 62: //D3
   case 69: //A3
    note_on(0); 
   break; 

   case 41: // pad 2 
   case 74: // D4
    note_on(1); 
   break; 
   
   case 42: // pad 3 
   case 77: //F4
    note_on(2); 
   break; 

   
   case 43: // pad 4 
   case 81: //A4
    note_on(3); 
   break;  

   case 48: // pad 5 
   case 60: //C3
    note_on(4); 
   break;
    
   case 49: // pad 6 
   case 79: //G4
    note_on(5); 
   break; 

   case 50: // pad 7 
   case 76: //E4
    note_on(6); 
   break; 
   
   case 51: // pad 8    
   case 72: //C4
    note_on(7); 
   break;  

   case 36: // pad 9    
   case 57:  //A2 BASS
    note_on(8); 
   break; 
   
   case 37: // pad 10    
   case 58://A2#
    note_on(9); 
   break; 
   
  }


  
}


/*
void myNoteOff(byte channel, byte note, byte velocity) {
  Serial.print("Note Off, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
  digitalWrite(led,LOW);
}

void myControlChange(byte channel, byte control, byte value) {
  Serial.print("Control Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", control=");
  Serial.print(control, DEC);
  Serial.print(", value=");
  Serial.println(value, DEC);
}
*/
