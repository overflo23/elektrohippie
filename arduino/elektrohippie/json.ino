#include <ArduinoJson.h>
#include <SD.h>




int tone_mapping[150] = {
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
};


void load_json_songinfo()
{
  

  
  Serial.print("Reading config file @ ");
  String infofile = "/PLAY/" + songList[file_index] +"/ehippie.txt";
  Serial.println(infofile);

  File file = SD.open(infofile.c_str(), FILE_READ);

  StaticJsonBuffer<512> jsonBuffer;

  // Parse the root object
  JsonObject &root = jsonBuffer.parseObject(file);

  if (!root.success())
    Serial.println("Could not parse JSON");


   playback_speed = root["speed"];
   Serial.print("[JSON] speed: ");
   Serial.println(playback_speed);

   strlcpy(songname, root["name"], sizeof(songname));          // <- destination's capacity
   Serial.print("[JSON] songname: ");
   Serial.println(songname);

   strlcpy(author, root["author"], sizeof(author));          // <- destination's capacity
   Serial.print("[JSON] author: ");
   Serial.println(author);


   reset_note_mapping();

   set_note_mapping((int) root["mapping"]["D2_M"], 0);
   set_note_mapping((int) root["mapping"]["D2_R"], 1);
   set_note_mapping((int) root["mapping"]["A3"], 2);   
   set_note_mapping((int) root["mapping"]["C4"], 3);  
   set_note_mapping((int) root["mapping"]["D4"], 4);
   set_note_mapping((int) root["mapping"]["E4"], 5);
   set_note_mapping((int) root["mapping"]["F4"], 6);
   set_note_mapping((int) root["mapping"]["G4"], 7);
   set_note_mapping((int) root["mapping"]["A4"], 8);
   set_note_mapping((int) root["mapping"]["C5"], 9);



   file.close();
  
}

// set standard mapping
void reset_note_mapping()
{
 for(int i=0;i<150;i++)
 {
  tone_mapping[i]=-1;
 }

tone_mapping[45]=0;
tone_mapping[38]=1;
tone_mapping[57]=2;
tone_mapping[60]=3;
tone_mapping[62]=4;
tone_mapping[64]=5;
tone_mapping[65]=6;
tone_mapping[67]=7;
tone_mapping[69]=8;
tone_mapping[72]=9;


}


void set_note_mapping(int midinote, int hang_position)
{
 Serial.print("[Note mapping] Setting "); 
 Serial.print(midinote); 
 Serial.print(" to "); 
 Serial.println(hang_position); 
 tone_mapping[midinote] = hang_position;
}
