// control with polebot_keyboard_control
// stop = value 0.000001 or 10^-6
// stop = value -0.000001 or -(10^-6)
// non zero stop

#include <ros.h> //masukkan library ros
#include <std_msgs/Float64.h> // memasukkan tipe data float
#include <std_msgs/Int64.h> // memasukkan tipe data int
#include <geometry_msgs/Vector3.h> // memasukkan tipe data geometry dan vektor
#include "config.h" // memasukkan koding config.h yang ada pada tab 

// deklarasi bahwa konstanta PID menggunakan tipe data float
float Kp1, Ti1, Td1, Ki1, Kd1;
float interval_elapsed1;
float interval_limit1;

float Kp2, Ti2, Td2, Ki2, Kd2;
float interval_elapsed2;
float interval_limit2;

float Kp3, Ti3, Td3, Ki3, Kd3;
float interval_elapsed3;
float interval_limit3;

unsigned long lasttimepub, now; // digunakan untuk memperluas penyimpanan bilangan namun tidak akan menyimpan bilangan negatif

// -- PID M1
float PID1; // deklarasi PID menggunakan tipe data float
float et1, et1_prev;
float eint1, eint1_prev, eint1_update;
float edif1;
float setPointVel1, SV1, PV1;
float setPointRpm1;
int MV1;
unsigned long t1;
double t_1, Ts1;
float maxRpm1 = 800;
volatile int encoderPos_1 = 0, encReal_Pos1 = 0;
float V1, rpm_m1, ppr = 7;
unsigned long previousMillis1 = 0, previousMillis2 = 0;
const long interval1 = 100, interval2 = 100;

// -- PID M2
float PID2;
float et2, et2_prev;
float eint2, eint2_prev, eint2_update;
float edif2;
float setPointVel2, SV2, PV2;
float setPointRpm2;
int MV2;
unsigned long t2;
double t_2, Ts2;
float maxRpm2 = 800;
volatile int encoderPos_2 = 0, encReal_Pos2 = 0;
float V2, rpm_m2;
unsigned long previousMillis3 = 0 , previousMillis4 = 0;
const long interval3 = 100, interval4 = 100;

// --PID M3
float PID3;
float et3, et3_prev;
float eint3, eint3_prev, eint3_update;
float edif3;
float setPointVel3, SV3, PV3;
float setPointRpm3;
int MV3;
unsigned long t3;
double t_3, Ts3;
float maxRpm3 = 800;
volatile int encoderPos_3 = 0, encReal_Pos3 = 0;
float V3 , rpm_m3;
unsigned long previousMillis5 = 0, previousMillis6 = 0;
const long interval5 = 100, interval6 = 100;
int resetenc;

//================================== ROS ================================
//RPM and Velocity
ros::NodeHandle nh;
std_msgs::Float64 rpm1_state;
std_msgs::Float64 vel1_state;
//geometry_msgs::Vector3 enc1_state;
std_msgs::Float64 pid_1;

std_msgs::Float64 rpm2_state;
std_msgs::Float64 vel2_state;
//geomtry_msgs::Vector3 enc2_state;
std_msgs::Float64 pid_2;

std_msgs::Float64 rpm3_state;
std_msgs::Float64 vel3_state;
//geomtery_msgs::Vector  enc3_state;
std_msgs::Float64 pid_3;

//=============================== ENCODER ================================
geometry_msgs::Vector3 enc;
ros::Publisher encoder ("encoder", &enc);
//========================================================================

//ros::Publisher rpm1("/rpm_m1", &rpm1_state); // -- rpm
ros::Publisher vel1("/vel_m1", &vel1_state); //--vel (pwm)
ros::Publisher pid1("/pid_m1" , &pid_1); // -- pid

//ros::Publisher(rpm2("/rpm_m2", &rpm2_state); // -- rpm
ros::Publisher vel2("/vel_m2" , &vel2_state); // --vel (pwm)
ros::Publisher pid2("/pid_m2" , &pid_2); // -- pid

//ros::Publisher rpm3("/rpm_3" , &rpm3_state); //-- rpm
ros::Publisher vel3("/vel_m3" , &vel3_state); //-- vel (pwm)
ros::Publisher pid3("/pid_m3" , &pid_3); // -- pid

void setPoint_Cb1(std_msgs::Float64 &msg_motor1){
  setPointVel1 = msg_motor1.data;
  if (setPointVel1 <= 1 and setPointVel1 >=-1){
    setPointRpm1 = 0;
  }
  else {
    setPointRpm1 = setPointVel1 * 9.5492965964254; //rad/s to rpm
  }
}

void setPoint_Cb2(std_msgs::Float64 &msg_motor2){
  setPointVel2 = msg_motor2.data;
  if (setPointVel2 <= 1 and setPointVel2 >= -1){
    setPointRpm2 = 0;
  }
  else {
    setPointRpm2 = setPointVel2 * 9.5492965964254; // rad/s to rpm
  }
}

void setPoint_Cb3(std_msgs::Float64 &msg_motor3){
  setPointVel3 = msg_motor3.data;
  if (setPointVel3 <= 1 and setPointVel3 >=-1){
    setPointRpm3 = 0;
  }
  else{
    setPointRpm3 = setPointVel3 * 9.5492965964254;
  }
}

void reset_encoder(std_msgs::Int64 &data){
  resetenc=data.data;
}

ros::Subscriber<std_msgs::Float64> m1("/polebot/right_joint_velocity_controller/command", setPoint_Cb1);
ros::Subscriber<std_msgs::Float64> m2("/polebot/left_joint_velocity_controller/command", setPoint_Cb2);
ros::Subscriber<std_msgs::Float64> m3("/polebot/back_joint_velocity_controller/command", setPoint_Cb3);
//ros::Subscriber<std_msgs::Float64> pwm_m1("/pid_m1", motor1_Cb);
//ros::Subscriber<std_msgs::Float64> pwm_m2("/pid_m2", motor2_Cb);
//ros::Subscriber<std_msgs::Float64> pwm_m3("/pid_m2", motor3_Cb);

ros::Subscriber<std_msgs::Int64> reset_enc("/reset_enc", reset_encoder);

//================================== ROS ================================

void setup(){
  setup_output();

  nh.initNode();

  nh.advertise(encoder);
  Kp1 = 0.015;  // 0.0105,0.065
  Ti1  = 6.51 ;  // 6.51,45
  Td1 = 8.95 ;  // 8.95,7

  if (Ti1 == 0){
    Ki1 = 0;
  }
  else {
    Ki1 = Kp1/Ti1;
  }
  //--> Hitung Kd
  Kd1 = Kp1*Td1;
  et1_prev = 0;
  eint1_prev = 0;

  interval_limit1   = 0.05;
  interval_elapsed1 = 0;
  //nh.advertise(rmp1);
  nh.advertise(vel1);
  nh.advertise(pid1);
  nh.subscribe(m1);
  //nh.subsciber(pwm_m1);
  t1 = millis();
  //delay10


  Kp2 = 0.015; //0.0105,0.065
  Ti2 = 6.51;  //6.51,4.5
  Td2 = 7.4405; // 8.95,7.4405

  if (Ti2 == 0){
    Ki2 = 0;
  }
  else {
    Ki2 = Kp2/Ti2;
  }
  //-- Hitung Kd
  Kd2 = Kp2 *Td2;
  et2_prev = 0;
  eint2_prev = 0;

  interval_limit2   = 0.05;
  interval_elapsed2 = 0;
  nh.advertise(vel2);
  nh.advertise(pid2);
  nh.subscribe(m2);
  // nh. subscribe(pwm_m2);
  t2  = millis();
  //delay (10);

  Kp3 = 0.015;  //0.00105,0.065
  Td3 = 6.51;   //6.51,45
  Ti3 = 8.95;   //9.95,73

  if (Ti3 == 0) {
    Ki3 = 0;
  }
  else{
    Ki3 = Kp3 / Ti3;
  }
  //--> Hitung Kd
  Kd3 = Kp3 * Td3;
  et3_prev    = 0;
  eint3_prev  = 0;

  interval_limit3   = 0.05;
  interval_elapsed3 = 0;
  //nh.advertise(rpm3);
  nh.advertise(vel3);
  nh.advertise(pid3);
  nh.subscribe(m3);
  //nh.subscribe(pwm_m2);
  t3  = millis();

  nh.subscribe(reset_enc);
  delay(10);
}

void loop() {
  
  //  ===== MOTOR1 =====
  unsigned long currentMillis1 = millis();
  unsigned long currentMillis2 = millis();

  pid_m1();

  if (currentMillis1 - previousMillis1 >= interval1){
    previousMillis1 = currentMillis1;

    if (setPointVel1 > 0.00001){
      pid_1.data      = PID1;
      pid1.publish(&pid_1);
      vel1_state.data  = MV1;
      vel1.publish(&vel1_state);
      analogWrite(RPWM1, MV1);
      analogWrite(LPWM1, 0);
    }
    else if (setPointVel1 < -0.00001){
      pid_1.data      = (PID1* -1);
      pid1.publish(&pid_1);
      vel1_state.data = (MV1 * -1);
      vel1.publish(&vel1_state);
      analogWrite(RPWM1, 0);
      analogWrite(LPWM1, MV1);
    }
    else {
      pid_1.data = 0;
      pid1.publish(&pid_1);
      vel1_state.data = 0.01;
      vel1.publish(&vel1_state);
      analogWrite(RPWM1, 0);
      analogWrite(LPWM1, 0);
    }
  }

  //nh.spinonce ();

  if (currentMillis2 - previousMillis2 >= interval2){
    previousMillis2 = currentMillis2;
    rpm_m1 = abs(encoderPos_1 / ppr) * 600;
    //rpm_state.data = setPointRmp1;
    //rpm1.publish(&rpm1_state);
    encoderPos_1 = 0;
  }

  nh.spinOnce();

  //  ===== MOTOR2 =====
  unsigned long currentMillis3 = millis();
  unsigned long currentMillis4 = millis();

  pid_m2();

  if (currentMillis3 - previousMillis3 >= interval3) {
    previousMillis3 = currentMillis3;

    if (setPointVel2 > 0.00001){
      pid_2.data = PID2;
      pid2.publish (&pid_2);
      vel2_state.data = MV2;
      vel2.publish(&vel2_state);
      analogWrite(RPWM2, MV2);
      analogWrite(LPWM2, 0);
    }
    else if (setPointVel2 < -0.00001){
      pid_2.data = (PID2 *-1);
      pid2.publish(&pid_2);
      vel2_state.data = (MV2 * -1);
      vel2.publish(&vel2_state);
      analogWrite(RPWM2, 0);
      analogWrite(LPWM2, MV2);
    }
    else {
      pid_2.data = 0;
      pid2.publish(&pid_2);
      vel2_state.data = 0.01;
      vel2.publish(&vel2_state);
      analogWrite(RPWM2, 0);
      analogWrite(LPWM2, 0);
    }
  }
  
  //nh. spinOnce;

  if (currentMillis4 - previousMillis4 >= interval4){
    previousMillis4 = currentMillis4;
    rpm_m2 = abs(encoderPos_2 / ppr) * 600;
    //rpwm_state.data = setPointRpm2;
    //rpm2.publish(&rpm2_state);
    encoderPos_2 = 0;
  }
  nh.spinOnce();

  //  ===== MOTOR3 =====
  
  unsigned long currentMillis5 = millis();
  unsigned long currentMillis6 = millis();

  pid_m3 ();

  if (currentMillis5 - previousMillis5 >= interval5){
    previousMillis5 = currentMillis5;

    if (setPointVel3 > 0.00001){
      pid_3.data = PID3;
      pid3.publish(&pid_3);
      vel3_state.data = MV3;
      vel3.publish(&vel3_state);
      analogWrite(RPWM3, MV3);
      analogWrite(LPWM3, 0);
    }
    else if (setPointVel3 < -0.00001){
      pid_3.data = (PID3 * -1);
      pid3.publish(&pid_3);
      vel3_state.data = MV3;
      vel3.publish(&vel3_state);
      analogWrite(RPWM3, 0);
      analogWrite(LPWM3, MV3);
    }
    else {
      pid_3.data = 0;
      pid3.publish(&pid_3);
      vel3_state.data = 0.01;
      vel3.publish(&vel3_state);
      analogWrite(RPWM3, 0);
      analogWrite(LPWM3, 0);
    }
  }
  
  //nh.spinOnce();

  if (currentMillis6 - previousMillis6 >= interval6){
    previousMillis6 = currentMillis6;
    rpm_m3 = abs(encoderPos_3 / ppr) * 600;
    //rpm3_state_data = setPointRpm3;
    //rpm3.publish(&rpm3_state);
    encoderPos_3 = 0;
  }
  nh.spinOnce();
  now = millis();
  if ((now - lasttimepub) > 100 ){
    enc.x = encReal_Pos1;
    enc.y = encReal_Pos2;
    enc.z = encReal_Pos3;
    encoder.publish(&enc);
    lasttimepub = now ;
  }

  if (resetenc == 1){
    encReal_Pos1 = 0;
    encReal_Pos2 = 0;
    encReal_Pos3 = 0;
    encoder.publish (&enc);
  }
  delay(1);  
}
