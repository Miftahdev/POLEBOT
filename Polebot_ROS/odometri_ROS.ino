void odometry(){
  x_pos = -0.5 * pulse_odom1 - 0.5 * pulse_odom2 + 1 * pulse_odom3;
  //x_pos = pulse_odom3;
  y_pos = 0.866 * pulse_odom1 - 0.866 * pulse_odom2;
  h_pos = pulse_odom1  + pulse_odom2 + 1.5* pulse_odom3;


  // heading (sudut hadap)
  pv_theta = 360 * (h_pos / h_max);

  if (pv_theta >= 360) {
    pv_theta = 0;
  }

  else if (pv_theta <= -360) {
    pv_theta = 0;
  }

  // gerak sumbu x
  pv_x = 30 * (x_pos / x_max);


  // gerak sumbu Y
  pv_y = 30 * (y_pos / y_max);
}
