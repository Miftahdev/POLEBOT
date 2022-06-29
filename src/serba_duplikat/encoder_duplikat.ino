void encoder3() { // fungsi encoder
  if (digitalRead(encb3) == digitalRead(enca3)) {
    pulse3 --; // saat digital read 2 dan tiga sama maka motor akan putar kiri encoder baca negatf
    pulse_odom3 --;
  }
  else {
    pulse3 ++; // selain saat digital read 2 dan tiga sama maka motor akan putar kanan encoder baca positif
    pulse_odom3 ++;
  }
}

void encoder2() { // fungsi encoder
  if (digitalRead(encb2) == digitalRead(enca2)) {
    pulse2 --; // saat digital read 2 dan tiga sama maka motor akan putar kiri encoder baca negatf
    pulse_odom2 --;
  }
  else {
    pulse2 ++; // selain saat digital read 2 dan tiga sama maka motor akan putar kanan encoder baca positif
    pulse_odom2 ++;
  }
}

void encoder1() { // fungsi encoder
  if (digitalRead(encb1) == digitalRead(enca1)) {
    pulse1 --; // saat digital read 2 dan tiga sama maka motor akan putar kiri encoder baca negatf
    pulse_odom1 --;
  }
  else {
    pulse1 ++; // selain saat digital read 2 dan tiga sama maka motor akan putar kanan encoder baca positif
    pulse_odom1 ++;
  }
}
