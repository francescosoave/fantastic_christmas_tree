void mode4(){
  
  unsigned long del = 150;
  byte j = 0;
  
  for(int i = 0; i< 6; i++)
      digitalWrite(big[i], HIGH);

  for(int i = 0; i< 4; i++)
      digitalWrite(green[i], LOW);

  for(int i=0; i<red; i++)
     digitalWrite(red[i], HIGH);

  for(int i=0; i<7; i++){
    digitalWrite(red[i], LOW);
    if(i % 2 == 0){
      digitalWrite(green[j++], HIGH);
    
    }
    delay(150);
    digitalWrite(red[i], HIGH);
  }

}
