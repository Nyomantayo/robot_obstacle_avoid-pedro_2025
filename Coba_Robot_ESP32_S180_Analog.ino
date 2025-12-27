// // Tahap Riset
// // ============   IMPORT LIBRARY    ============
// #include <ESP32Servo.h>

// // ============   SET PIN KOMPONEN  ============
// // Ultrasonic
// #define TRG 21
// #define ECH 19
// // Motor Driver (L298N)
// #define PINA 18
// #define PINB 5
// #define PINC 2
// #define PIND 15
// // Servo
// #define SERVO1 23

// // ============   DEFINE VARIABEL  ============
// // Variabel Simpan Jarak Ultrasonik
// int Jdepan;
// int Jkiri;
// int Jkanan;

// // Variabel Cek Jarak Minimum Robot (Agar Berhenti)
// int cek = 25;

// // ============   PWM MOTOR (ESP32 Core 3.x)  ============
// // PWM config
// const int PWM_FREQ = 20000; // 20 kHz
// const int PWM_RES  = 8;     // 8-bit => 0..255

// // Speed (0..255)
// int SPEED_MAJU = 180;
// int SPEED_TURN = 170;
// int SPEED_BACK = 160;
// int pwmA, pwmB;

// // ============   DEKLARASI OBJECT ============
// // Object Servo
// Servo myServo;

// void setup() {
//   Serial.begin(115200);

//   // Konfig Pin Ultrasonic
//   pinMode(TRG, OUTPUT);
//   pinMode(ECH, INPUT);

//   // Attach PWM ke pin-pin motor (WAJIB untuk core 3.x)
//   ledcAttach(PINA, PWM_FREQ, PWM_RES);
//   ledcAttach(PINB, PWM_FREQ, PWM_RES);
//   ledcAttach(PINC, PWM_FREQ, PWM_RES);
//   ledcAttach(PIND, PWM_FREQ, PWM_RES);

//   // Stop motor dulu
//   stop();

//   // Hubungkan servo
//   myServo.attach(SERVO1, 500, 2400);
//   myServo.write(SERVO_STOP);

//   delay(800);
// }

// void loop() {
//   Jdepan = jarak();

//   if (Jdepan > 0 && Jdepan < cek) {
//     back();
//     delay(200);

//     stop();
//     delay(500);

//     // === Cek Jarak Sebelah Kiri ===
//     myServo.write(180); // -> 0 Paling Kanan, 180 Paling Kiri
//     delay(500);
//     Jkiri = jarak();
//     Serial.println("Robot Nengok ke Kiri!");
//     delay(2000);

//     // === Cek Jarak Sebelah Kanan ===
//     myServo.write(0); // -> 0 Paling Kanan, 180 Paling Kiri
//     delay(500);
//     Jkanan = jarak();
//     Serial.println("Robot Nengok ke Kanan!");
//     delay(2000);

//     // === Kembali Ke Depan ===
//     myServo.write(90); // -> 0 Paling Kanan, 180 Paling Kiri
//     delay(500);
//     Serial.println("Robot Kembali ke Tengah!");
//     delay(2000);

//     if (Jkiri > Jkanan) {
//       Jdepan = jarak();
//       while (Jdepan > 0 && Jdepan <= 20) {
//         Serial.print("Jarak Depan : ");
//         Serial.println(Jdepan);
//         left();
//         Jdepan = jarak();
//         delay(10);
//       }
//     } else if (Jkanan > Jkiri) {
//       Jdepan = jarak();
//       while (Jdepan > 0 && Jdepan <= 20) {
//         Serial.print("Jarak Depan : ");
//         Serial.println(Jdepan);
//         right();
//         Jdepan = jarak();
//         delay(10);
//       }
//     } else {
//       stop();
//       delay(200);
//     }
//   } else {
//     maju();
//   }

//   delay(20);
// }

// int jarak() {
//   long duration, distance;

//   digitalWrite(TRG, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRG, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRG, LOW);

//   duration = pulseIn(ECH, HIGH, 30000);
//   distance = (duration * 0.0343) / 2;

//   Serial.print("Distance sensor : ");
//   Serial.println(distance);

//   delay(100);
//   return (int)distance;
// }

// // ===== Gerak robot (PWM) =====
// void maju() {
//   int spdKiri, spdKanan;
//   spdKiri = 90;
//   spdKanan = 116;
//   Serial.println("Maju");
//   motorKiri(spdKiri);
//   motorKanan(spdKanan);
// }

// void right() {
//   int spdKiri, spdKanan;
//   spdKiri = 100;
//   spdKanan = -126;
//   Serial.println("Kanan");
//   motorKiri(spdKiri);
//   motorKanan(-spdKanan); // spin kanan
// }

// void left() {
//   int spdKiri, spdKanan;
//   spdKiri = -100;
//   spdKanan = 126;
//   Serial.println("Kiri");
//   motorKiri(-spdKiri);  // spin kiri
//   motorKanan(spdKanan);
// }

// void stop() {
//   Serial.println("Berhenti");
//   motorKiri(0);
//   motorKanan(0);
// }

// void back() {
//   Serial.println("Mundur");
//   motorKiri(-SPEED_BACK);
//   motorKanan(-SPEED_BACK);
// }

// // ===== Helper PWM =====
// void pwmWritePin(int pin, int duty) {
//   duty = constrain(duty, 0, 255);
//   ledcWrite(pin, duty);   // core 3.x: ledcWrite pakai "pin"
// }

// // speed: -255..255
// void motorKiri(int speed) {
//   speed = constrain(speed, -255, 255);
//   if (speed > 0) {            // maju
//     pwmWritePin(PINA, speed);
//     pwmWritePin(PINB, 0);
//   } else if (speed < 0) {     // mundur
//     pwmWritePin(PINA, 0);
//     pwmWritePin(PINB, -speed);
//   } else {                    // stop
//     pwmWritePin(PINA, 0);
//     pwmWritePin(PINB, 0);
//   }
// }

// void motorKanan(int speed) {
//   speed = constrain(speed, -255, 255);
//   if (speed > 0) {            // maju
//     pwmWritePin(PINC, speed);
//     pwmWritePin(PIND, 0);
//   } else if (speed < 0) {     // mundur
//     pwmWritePin(PINC, 0);
//     pwmWritePin(PIND, -speed);
//   } else {                    // stop
//     pwmWritePin(PINC, 0);
//     pwmWritePin(PIND, 0);
//   }
// }