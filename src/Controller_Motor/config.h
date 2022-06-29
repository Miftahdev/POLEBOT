#ifndef CONFIG_H
#define CONFIG_H

#define LOOPTIME 100

#define K_P 0.6 // coba perhitungkan lagi dengan robot sendiri
#define K_I 0.3 // coba perhitungkan lagi dengan robot sendiri
#define K_D 0.5 // coba perhitungkan lagi dengan robot sendiri

#define DEBUG 1 
#define DEBUG_RATE 5

#define MAX_RPM 800 // kecepatan maksimal motor
#define WHEEL_DIAMETER 0.06 // coba ukur lagi diameter roda
#define ENCODER_PULSE 112 // hitung lagi pulsa dari encoder
#define PWM_BITS 8 // bit dalam pwm sebesar 8 bit

#define PWM_MAX 250 // batas pwm yang menjadi input
#define PWM_MIN -250 // batas pwm yang menjadi input

#define MOTOR_DRIVER BTS7960 // deklarasi motor driver 

//motor 1
#define RPWM1 7
#define LPWM1 6

//motor 2
#define RPWM2 10
#define LPWM2 9

//motor 3
#define RPWM3 12
#define LPWM3 11

//encoder1
#define ENCO1A 2
#define ENCO1B 3

//encoder2
#define ENCO2A 19
#define ENCO2B 18

//encoder3
#define ENCO3A 21
#define ENCO3B 20

#endif
