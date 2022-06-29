void readEncoder1 (){ // membuat void encoder
  int b = digitalRead(ENCO1B); // pembacaan dengan pin digital untuk encoder 1
  if (b > 0){
    encoderPos_1++;
    encReal_Pos1++;
  }
  else {
    encoderPos_1--;
    encReal_Pos1--;
  }
}

void readEncoder2 (){
  int b = digitalRead(ENCO2B); // pembacaan dengan pin digital untuk encoder 1
  if (b > 0){
    encoderPos_2++;
    encReal_Pos2++;
  }
  else {
    encoderPos_2--;
    encReal_Pos2--;
  }
}

void readEncoder3 (){
  int b = digitalRead(ENCO3B); // pembacaan dengan pin digital untuk encoder 1
  if (b > 0){
    encoderPos_3++;
    encReal_Pos3++;
  }
  else {
    encoderPos_3--;
    encReal_Pos3--;
  }
}
