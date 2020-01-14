

void setup_midi()
{ 
  Serial.println("setup_midi()");
  usbMIDI.setHandleNoteOn(myNoteOn);



}


void handle_midi()
{
 usbMIDI.read();
  
}



void myNoteOn(byte channel, byte midisignal, byte velocity) {
  // When using MIDIx4 or MIDIx16, usbMIDI.getCable() can be used
  // to read which of the virtual MIDI cables received this message.
  Serial.print("Note On, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(midisignal, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
  //digitalWrite(led,HIGH);



/*
Note On, ch=1, note=85, velocity=57
Note On, ch=1, note=87, velocity=43
Note On, ch=1, note=89, velocity=65
Note On, ch=1, note=91, velocity=60
Note On, ch=1, note=93, velocity=42
Note On, ch=1, note=95, velocity=65
Note On, ch=1, note=97, velocity=71
Note On, ch=1, note=99, velocity=73
//bass
Note On, ch=1, note=84, velocity=82
Note On, ch=1, note=86, velocity=55
*/


  switch(midisignal)
  {


   case 84: // pad 8    
   case 38: // A2 BASS MITTE
    note_on(0); 
   break; 

   case 86: // pad 9    
   case 45: // D2 BASS RING
    note_on(1); 
   break; 


   case 85: // pad 0 
   case 57: // A3
    note_on(2); 
   break; 

   case 87: // pad 1 
   case 60: // C4
    note_on(3); 
   break; 

   case 89: // pad 2 
   case 62: // D4
    note_on(4); 
   break; 

   case 91: // pad 3 
   case 64: // E4
    note_on(5); 
   break;  
 
   case 93: // pad 4 
   case 65: // F4
    note_on(6); 
   break;

   case 95: // pad 5 
   case 67: // G4
    note_on(7); 
   break; 

   case 97: // pad 6 
   case 69: // A4
    note_on(8); 
   break;  
  
   case 99: // pad 7    
   case 72: // C5
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
