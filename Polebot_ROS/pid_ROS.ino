void PIDrpm3(float targetVel3) { // fungsi PID rpm
  waktusekarang3 = millis(); // waktu sekarang , millis befungsi untuk ngitung waktu
  if (waktusekarang3 - waktulama3 >= interval3) {
    rpm3 = (pulse3 / maxpulse3) * 600; // perhitungan RPM

    // PID motor 3 Program
    error3   = abs(targetVel3) - abs(rpm3); // perhitungan PID sampe MV
    integral3 += error3;
    derivative3 = (error3 - prevError3);
    MV3 = (Kp3 * error3) + (Ki3 * integral3) + (Kd3 * derivative3);

    prevError3 = error3;

    MV3 = min(max(MV3, 0), 255);

    if (targetVel3 >= 0) {
      analogWrite(rpwm3, MV3);
    }

    else if (targetVel3 < 0) {
      analogWrite(lpwm3, MV3);
    }

    //    Serial.print(" Nilai Kecepatan3 : ");
    //    Serial.print(rpm3);
    //    Serial.print(" MV3 : ");
    //    Serial.print(MV3);
    //    Serial.print(" targetVel3 : ");
    //    Serial.println(targetVel3);

    pulse3 = 0;
    waktulama3 = waktusekarang3;
  }
}

void PIDrpm2(float targetVel2) { // fungsi PID rpm
  waktusekarang2 = millis(); // waktu sekarang , millis befungsi untuk ngitung waktu
  if (waktusekarang2 - waktulama2 >= interval2) {
    rpm2 = (pulse2 / maxpulse2) * 600; // perhitungan RPM

    // PID motor 2 Program
    error2   = abs(targetVel2) - abs(rpm2); // perhitungan PID sampe MV
    integral2 += error2;
    derivative2 = (error2 - prevError2);
    MV2 = (Kp2 * error2) + (Ki2 * integral2) + (Kd2 * derivative2);

    prevError2 = error2;
    MV2 = min(max(MV2, 0), 255);

    if (targetVel2 >= 0) {
      analogWrite(rpwm2, MV2);
    }

    else if (targetVel2 < 0) {
      analogWrite(lpwm2, MV2);
    }

    //    Serial.print("Nilai Kecepatan2 : ");
    //    Serial.print(rpm2);
    //    Serial.print(" MV2 : ");
    //    Serial.print(MV2);
    //    Serial.print(" targetVel2 : ");
    //    Serial.println(targetVel2);

    pulse2 = 0;
    waktulama2 = waktusekarang2;
  }
}

void PIDrpm1(float targetVel1) { // fungsi PID rpm
  waktusekarang1 = millis(); // waktu sekarang , millis befungsi untuk ngitung waktu
  if (waktusekarang1 - waktulama1 >= interval1) {
    rpm1 = (pulse1 / maxpulse1) * 600; // perhitungan RPM

    // PID motor 1 Program
    error1   = abs(targetVel1) - abs(rpm1); // perhitungan PID sampe MV
    integral1 += error1;
    derivative1 = (error1 - prevError1);
    MV1 = (Kp1 * error1) + (Ki1 * integral1) + (Kd1 * derivative1);

    prevError1 = error1;
    MV1 = min(max(MV1, 0), 255);

    if (targetVel1 >= 0) {
      analogWrite(rpwm1, MV1);
    }

    else if (targetVel1 < 0) {
      analogWrite(lpwm1, MV1);
    }

    pulse1 = 0;
    waktulama1 = waktusekarang1;
  }
}
