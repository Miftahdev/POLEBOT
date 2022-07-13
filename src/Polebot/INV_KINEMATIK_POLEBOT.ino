void kinematika(int pos_x, int pos_y, int heading) {

  //PID heading

  errorH   =  ((heading)*-1)- (pv_theta); // perhitungan PID sampe MV
  MVH = (KpH * errorH);
// MVH = min(max(MVH, 0), 360);

  errorX   = (pos_x) - (pv_x); // perhitungan PID sampe MV
  MVX = (KpX * errorX);
  MVX = min(max(MVX, -400), 400);

  errorY   = (pos_y) - (pv_y); // perhitungan PID sampe MV
  MVY = (KpY * errorY);
  MVY = min(max(MVY, -400), 400);


//kinematika
  v1 = -0.333 * MVX + 0.5774 * MVY + 0.045* MVH;
  v2 = -0.333 * MVX + (-0.5774) * MVY + 0.045*MVH;
  v3 = 0.667 * MVX + 0.045*MVH;

  // convert rad/s to rpm
  //  v_1 = v1 * 9.5492965964254;
  //  v_2 = v2 * 9.5492965964254;
  //  v_3 = v3 * 9.5492965964254;


  Serial.print("MVX : ");
  Serial.print(MVX);
  Serial.print(" MVY : ");
  Serial.print(MVY);
  Serial.print(" MVH : ");
  Serial.println(MVH);
  
//    Serial.print("nilai v1 : ");
//    Serial.print(v1);
//    Serial.print("nilai v2 : ");
//    Serial.print(v2);
//    Serial.print("nilai v3 : ");
//    Serial.println(v3);

}
