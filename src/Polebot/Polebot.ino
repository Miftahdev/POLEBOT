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
int MV3; // manipulated variabel nilai kalkulasi pid

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
int MV2 = 0; // manipulated variabel nilai kalkulasi pid

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
int MV1 = 0; // manipulated variabel nilai kalkulasi pid

float dt = 0.001;

// kinematika

int v1 , v2 , v3;
int v_1 , v_2 , v_3;

//odometri declare
int x_pos, y_pos, h_pos; // deklarasi odom
int s1, s2, s3; // deklarasi jarak untuk penjumlahan
//int jarak_x,jarak_y,heading;// deklarasi jarak untuk mengetahui jarak yang ditempuh
int pulse_odom1, pulse_odom2, pulse_odom3; // pulse pada odometri roda 1 2 dan 3

float h_max = 3407; //360 derajat
float y_max = 375;  //30cm
float x_max = 392;  //30cm

float pv_theta, pv_x, pv_y;

//PID control motor 1
#define KpX  3
#define KpY  3
#define KpH  10

// error posisi
int errorX;
int errorY;
int errorH;

//hasil perhitungan posisi X, Y dan heading
int MVX = 0; // manipulated variabel nilai kalkulasi pid
int MVY = 0;
int MVH = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//baudrate
  // motor 3
  pinMode(enca3, INPUT_PULLUP); // pullup buat interrupt
  pinMode(encb3, INPUT_PULLUP);
  pinMode(rpwm3, OUTPUT);
  pinMode(lpwm3, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(enca3), encoder3, CHANGE); // mmanggil prograrm encoder ketika pin intterupt terpicu
  delay(100);
  //  targetVel3 = 200; // set point tadi yng rpm klo yng rpm atas mah cuma deklarasi pariabel

  // motor 2
  pinMode(enca2, INPUT_PULLUP); // pullup buat interrupt
  pinMode(encb2, INPUT_PULLUP);
  pinMode(rpwm2, OUTPUT);
  pinMode(lpwm2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(enca2), encoder2, CHANGE); // mmanggil prograrm encoder ketika pin intterupt terpicu
  delay(100);
  //  targetVel2 = 200; // set point tadi yng rpm klo yng rpm atas mah cuma deklarasi pariabel

  // motor 1
  pinMode(enca1, INPUT_PULLUP); // pullup buat interrupt
  pinMode(encb1, INPUT_PULLUP);
  pinMode(rpwm1, OUTPUT);
  pinMode(lpwm1, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(enca1), encoder1, CHANGE); // mmanggil prograrm encoder ketika pin intterupt terpicu
  delay(100);
  //  targetVel1 = 200; // set point tadi yng rpm klo yng rpm atas mah cuma deklarasi pariabel
}


void loop() {
  // put your main code here, to run repeatedly:
  //=========x, y , z======
  kinematika(30, 0, 0); // input pada kinematika
  odometri();
  PIDrpm3(v3);// memanggil fungsi pid dan baca kecepatan
  PIDrpm2(v2);
  PIDrpm1(v1);

  //Serial.print("pulse odom1 = ");
  //Serial.print(pulse_odom1);
  //Serial.print(" pulse odom2= ");
  //Serial.print(pulse_odom2);
  //Serial.print(" pulse odom3 = ");
  //Serial.println(pulse_odom3);
  //Serial.println("Jemjem");
}
