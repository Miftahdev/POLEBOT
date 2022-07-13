void kinematika() {

  //PID heading

  errorH   =  ((pos_z)*-1)- (pv_theta); // perhitungan PID sampe MV
  MVH = (KpH * errorH);
//  MVH = min(max(MVH, -360), 360);

  errorX   = (pos_x) - (pv_x); // perhitungan PID sampe MV
  MVX = (KpX * errorX);
  MVX = min(max(MVX, -400), 400);

  errorY   = (pos_y) - (pv_y); // perhitungan PID sampe MV
  MVY = (KpY * errorY);
  MVY = min(max(MVY, -400), 400);


//kinematika
  targetVel1 = -0.333 * MVX + 0.5774 * MVY + 0.045* MVH;
  targetVel2 = -0.333 * MVX + (-0.5774) * MVY + 0.045*MVH;
  targetVel3 = 0.667 * MVX + 0.045*MVH;

//  Serial.print("MVX : ");
//  Serial.print(MVX);
//  Serial.print(" MVY : ");
//  Serial.print(MVY);
//  Serial.print(" MVH : ");
//  Serial.println(MVH);
  
//    Serial.print("nilai v1 : ");
//    Serial.print(v1);
//    Serial.print("nilai v2 : ");
//    Serial.print(v2);
//    Serial.print("nilai v3 : ");
//    Serial.println(v3);

}
