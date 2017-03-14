//jingle bells

void mode13(){

  for (int thisNote = 0; thisNote < 22; thisNote++) { 
    
    int noteDuration = 1000/jingle_duration[thisNote];
    tone(35, jingle_melody[thisNote],noteDuration);

    if(thisNote < 21){
      for(int i = 0; i < 4; i++)
        digitalWrite(all[random(17)], HIGH);
    }else{
      for(int i = 0; i < 17; i++)
        digitalWrite(all[i], HIGH);
    }
    
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    //turn off the LEDs
    for(int i = 0; i < 17; i++)
      digitalWrite(all[i], LOW);
      
    //stop tone playing
    noTone(35);
  }

}
