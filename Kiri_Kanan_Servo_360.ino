// // ============   IMPORT LIBRARY    ============
// // Library untuk kontrol servo pada ESP32
// #include <ESP32Servo.h>

// // ============   SET PIN KOMPONEN  ============
// // Servo
// #define SERVO1 23

// // ============   DEFINE VARIABEL  ============
// // Kalibrasi servo 360 kamu
// const int SERVO_STOP = 95;

// // Sesuaikan besar speed (jarak dari STOP).
// // Kalau arah kebalik, tukar nilai SERVO_KANAN dan SERVO_KIRI.
// const int SERVO_KANAN = SERVO_STOP - 25;  // muter satu arah
// const int SERVO_KIRI = SERVO_STOP + 25;   // muter arah sebaliknya

// // Lama muter untuk "tengok" (semakin besar = semakin jauh)
// const int DURASI_TENGOK_MS = 350;

// // Jeda saat berhenti/menahan posisi
// const int JEDA_MS = 600;

// // ============   DEKLARASI OBJECT ============
// // Object Servo
// Servo myServo;

// void setup() {
//   Serial.begin(115200);

//   // Hubungkan Object Servo ke Pin SERVO1(23)
//   myServo.attach(SERVO1);

//   // Pastikan stop dulu
//   myServo.write(SERVO_STOP);
//   delay(1000);
// }

// void loop() {
//   // Tengok kanan
//   myServo.write(SERVO_KANAN);
//   delay(DURASI_TENGOK_MS);
//   myServo.write(SERVO_STOP);
//   Serial.println("Posisi Kanan!");
//   delay(JEDA_MS);

//   // Balik ke tengah
//   myServo.write(SERVO_KIRI);
//   delay(DURASI_TENGOK_MS);
//   myServo.write(SERVO_STOP);
//   Serial.println("Posisi Tengah!");
//   delay(JEDA_MS);

//   // Tengok kiri
//   myServo.write(SERVO_KIRI);
//   delay(DURASI_TENGOK_MS);
//   myServo.write(SERVO_STOP);
//   Serial.println("Posisi Kiri!");
//   delay(JEDA_MS);

//   // Balik ke tengah
//   myServo.write(SERVO_KANAN);
//   delay(DURASI_TENGOK_MS);
//   myServo.write(SERVO_STOP);
//   Serial.println("Posisi Tengah!");
//   delay(JEDA_MS);
// }
