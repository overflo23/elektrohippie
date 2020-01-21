//i use the midifilestream lib from the "glockenspiel" project found on github:wq

#include <MidiFileStream.h>

#include <SD.h>
//#include <SPI.h>

const int pinSelectSD = BUILTIN_SDCARD ; // Sparkfun SD shield Chip Select pin.


char fName[] = ""; // The SD card Midi file to read.

boolean errorOccurred;  // if true, there's a problem.
boolean isFinished;     // if true, we successfully finished reading the file.


MidiFileStream midiFile; // the current Midi file being read.
File file;




// add all .mid files in /PLAY folder to  songList[] Array
void listSongs()
{

  File folder = SD.open("/PLAY");

  
  nSongs = 0;

  while(true){
    File entry = folder.openNextFile();
    if(!entry){
      folder.rewindDirectory();
      break;
    }
    else
    {
      Serial.println(entry.name());
      if(entry.name()[0] !='_')
      {
       nSongs++;
      }
    }   
    entry.close();
  }

  Serial.print("Songs found:");
  Serial.println(nSongs);

  songList = new String[nSongs];

  int count=0;
  while(true)
  {
    File entry = folder.openNextFile();
    if(!entry){
      folder.rewindDirectory();
      break;
    }
    else
    {

      if(entry.name()[0] !='_')
      {     
       songList[count] = entry.name();
       count++;
      Serial.println(entry.name());
      }
    }   
    entry.close();
  }

  
}






void setup_sdcard() {

    Serial.println("setup_sdcard()");
  // If the setup succeeds, we'll update errorOccurred.
  errorOccurred = true;
  isFinished = false;
  
  pinMode(pinSelectSD, OUTPUT);

  // Setup the SD card
  
  Serial.println("Calling SD.begin()...");
  if (!SD.begin(pinSelectSD)) {
    Serial.println("SD.begin() failed. Check: ");
    Serial.println("  Card insertion,");
    Serial.println("  SD shield I/O pins and chip select,");
    Serial.println("  Card formatting.");
    return;
  }
  Serial.println("...succeeded.");



  listSongs();
  //playFile(0);
  
}



void playFile(int index)
{
  
  // Open the file to read

  Serial.println(songList[index]);
  load_json_songinfo();
  display_songinfo();
//drawHeader(songList[index]);
  
  String play = "/PLAY/" + songList[index] +"/file.mid";
//  file = SD.open("/PLAY/MMLN.MID", FILE_READ);
  file = SD.open(play.c_str(), FILE_READ);
  if (!file) {
    Serial.print("Failed to open SD card file ");
    Serial.println(fName);
    Serial.println("Does that file exist?");
    return;
  }

  /*
   * Read the Midi header from that file
   * and prepare to read Midi events from that file.
   */
  
  if (!midiFile.begin(file)) {
    Serial.print("Failed to open Midi file: ");
    Serial.println(fName);
    Serial.print("Check: is it a Midi-format file?");
    
    // Clean up
    midiFile.end();
    file.close();
    
    return;
  }


  
  // Say what the Midi Header told us.
  Serial.print("Midi file format: ");
  Serial.println(midiFile.getFormat());
  Serial.print("Number of tracks: ");
  Serial.println(midiFile.getNumTracks());
  Serial.print("Ticks per beat: ");
  Serial.println(midiFile.getTicksPerBeat());


  // Open the first track of the file.
  if (midiFile.openChunk() != CT_MTRK) {
    Serial.println("Failed to open the first track of the file.");
    
    // Clean up
    midiFile.end();
    file.close();
    
    return;
  }
  
  // remember that everything is ok so far.
  errorOccurred = false;

}

void handle_sdcard() {


  // set from button #2
  if(!playback) return;

  // If we're finished reading, do nothing.
  if (isFinished) {
    Serial.println("FINISHED");
    b_delay(1000);
    resetPlayback();
    return;
  }
  
  // If there is a problem, just blink the LED.
  if (errorOccurred) {

   // Serial.println("ERROR");
    b_delay(1000);
    
    return;
  }
  
  // read the next Midi event from the file.
  event_t eventType = midiFile.readEvent();
  if (eventType == ET_END) {
    
    // The track has ended; open the next track.
    chunk_t chunkType = midiFile.openChunk();
    if (chunkType != CT_MTRK) {
      if (chunkType == CT_END) {
        Serial.println("File ended normally.");
        
        // Clean up
        midiFile.end();
        file.close();
        
        isFinished = true;
        return;
      }
      
      // File error: Chunk is not a track.
      Serial.println("Failed to open file track.");
    
      // Clean up
      midiFile.end();
      file.close();
    
      errorOccurred = true;
      return;
    }
    
    // Successfully opened the track
    // loop again to read the next event.
    
    return;
  }


  int del = midiFile.getEventDeltaTicks();
  if(del)
  {
  //  Serial.print("delay ");
  //  Serial.println(del);
    b_delay(del*playback_speed);  
  }



  
  if (eventType == ET_END_TRACK) {
    Serial.println("End of Track event.");
    
    return;
  }
  
  if (eventType == ET_CHANNEL) {
    char code = midiFile.getEventDataP()->channel.code;
    
    if (code == CH_NOTE_ON) {
      sd_note((int) midiFile.getEventDataP()->channel.param1);
      
   //   myNoteOn(1,(int) midiFile.getEventDataP()->channel.param1,127);
  //    Serial.print("SD PLAY ");
  //    Serial.println(midiFile.getEventDataP()->channel.param1);
      
      return;
    }
    
    
    // Otherwise, it's a Channel event that we don't care about
    // Ignore it.
    
    return;
  }
  

}



void resetPlayback()
{

 midiFile.end();
 file.close(); 

 errorOccurred = false;
 isFinished=false;
 
 //Serial.print("Now we play file:" );
 //Serial.println(file_index);
 playFile(file_index);

}









void sd_note(int note) {

  Serial.print("SDCARD: ");
  Serial.print(note, DEC);

  if(tone_mapping[note] != -1)
  {
   Serial.println(" OK"); 
    // note set
   note_on(tone_mapping[note]);
  }
  else
  {
   Serial.println(" UNSET (FAILED)"); 
  }

}
