////====ROS====
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int64.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Pose2D.h>

//deklarasi motor 3
int pulse3; //deklarasi nilai pulsa encoder
float maxpulse3 = 268; // pulsa satu putaran penuh
#define rpwm3  8
#define lpwm3  9

//Encoder 3
int interval3 = 100; // interval waktu 0.1 second
unsigned int waktulama3, waktusekarang3; // variabel deklarasi waktu update kecepatan encoder
int rpm3; // proses value atau input feedback
#define enca3  20
#define encb3  21

//PID control motor 3
float Kp3 = 0.4;
float Ki3 = 0.095;
float Kd3 = 0.000005;
//    int targetVel3; // setpoint lah - jem
int error3;
int prevError3; // integral error
float integral3;
int derivative3;
float MV3; // manipulated variabel nilai kalkulasi pid
float targetVel3;

//deklarasi motor 2
int pulse2; //deklarasi nilai pulsa encoder
float maxpulse2 = 268; // pulsa satu putaran penuh
#define rpwm2  10
#define lpwm2  11

//Encoder 2
int interval2 = 100; // interval waktu 0.1 second
unsigned int waktulama2, waktusekarang2; // variabel deklarasi waktu update kecepatan encoder
int rpm2; // proses value atau input feedback
#define enca2  18
#define encb2  19

//PID control motor 2
float Kp2 = 0.4;
float Ki2 = 0.095;
float Kd2 = 0.000005;
int error2 ;
int prevError2; // integral error
int integral2;
int derivative2;
float MV2 = 0; // manipulated variabel nilai kalkulasi pid
float targetVel2;

//deklarasi motor 1
int pulse1; //deklarasi nilai pulsa encoder
float maxpulse1 = 268; // pulsa satu putaran penuh
#define rpwm1 12
#define lpwm1 7

//Encoder 1
int interval1 = 100; // interval waktu 0.1 second
unsigned int waktulama1, waktusekarang1; // variabel deklarasi waktu update kecepatan encoder
int rpm1; // proses value atau input feedback
#define enca1 3
#define encb1 2

//PID control motor 1
float Kp1 = 0.4;
float Ki1 = 0.095;
float Kd1 = 0.000005;
int error1;
int prevError1; // integral error
int integral1;
int derivative1;
float MV1 = 0; // manipulated variabel nilai kalkulasi pid
float targetVel1;

float dt = 0.001;

//odometri declare
float pulse_odom1, pulse_odom2, pulse_odom3; // pulse pada odometri roda 1 2 dan 3

//=====ROS=====
ros::NodeHandle nh;
//=====encoder=====
geometry_msgs::Vector3 pulse_encoder;
ros::Publisher encoder("/pulse_encoder" , &pulse_encoder);
//=================
void setPoint_Cb3(std_msgs::Float64 &msg_motor3){
  targetVel3 = msg_motor3.data;
}
void setPoint_Cb2(std_msgs::Float64 &msg_motor2){
  targetVel2 = msg_motor2.data;
}
void setPoint_Cb1(std_msgs::Float64 &msg_motor1){
  targetVel1 = msg_motor1.data;
}
  
ros::Subscriber<std_msgs::Float64> m1("/Polebot/V1_controller/command", setPoint_Cb1);
ros::Subscriber<std_msgs::Float64> m2("/Polebot/V2_controller/command", setPoint_Cb2);
ros::Subscriber<std_msgs::Float64> m3("/Polebot/V3_controller/command", setPoint_Cb3);

 

//====ROS====



void setup() {

  Serial.begin(57600);
  // motor 3
  pinMode(enca3, INPUT_PULLUP); // pullup buat interrupt
  pinMode(encb3, INPUT_PULLUP);
  pinMode(rpwm3, OUTPUT);
  pinMode(lpwm3, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(enca3), encoder3, CHANGE); // mmanggil prograrm encoder ketika pin intterupt terpicu
  delay(100);

  // motor 2
  pinMode(enca2, INPUT_PULLUP); // pullup buat interrupt
  pinMode(encb2, INPUT_PULLUP);
  pinMode(rpwm2, OUTPUT);
  pinMode(lpwm2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(enca2), encoder2, CHANGE); // mmanggil prograrm encoder ketika pin intterupt terpicu
  delay(100);

  // motor 1
  pinMode(enca1, INPUT_PULLUP); // pullup buat interrupt
  pinMode(encb1, INPUT_PULLUP);
  pinMode(rpwm1, OUTPUT);
  pinMode(lpwm1, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(enca1), encoder1, CHANGE); // mmanggil prograrm encoder ketika pin intterupt terpicu
  delay(100);

  //ROS
  nh.subscribe(m1);
  nh.subscribe(m2);
  nh.subscribe(m3);
  nh.advertise(encoder);

}

void loop() {
 
  PIDrpm3(targetVel3);// memanggil fungsi pid dan baca kecepatan
  PIDrpm2(targetVel2);
  PIDrpm1(targetVel1);

  //ros pulse encoder
  pulse_encoder.x = pulse_odom1;
  pulse_encoder.y = pulse_odom2;
  pulse_encoder.z = pulse_odom3;
  encoder.publish(&pulse_encoder);

  nh.spinOnce();
  delay(1);

}
