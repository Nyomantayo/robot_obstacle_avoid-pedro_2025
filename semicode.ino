// ============   IMPORT LIBRARY    ============
// Library untuk kontrol servo pada ESP32
#include <ESP32Servo.h>

// ============   SET PIN KOMPONEN  ============
// Ultrasonic
// << Definisikan Pin Trigger >>
// << Definisikan Pin Echo >>

// Motor Driver (L289N)
// << Definisikan Pin dari Motor Kiri pertama >>
// << Definisikan Pin dari Motor Kiri kedua >>
// << Definisikan Pin dari Motor Kanan pertama >>
// << Definisikan Pin dari Motor Kanan kedua >>

// Servo
// << Definisikan Pin Servo >>

// ============   DEFINE VARIABEL  ============
// Variabel Simpan Jarak Ultrasonik
// << Buat Variabel Jarak Depan >>
// << Buat Variabel Jarak Kiri >>
// << Buat Variabel Jarak Kanan >>

// Variabel Cek Jarak Minimum Robot (Agar Berhenti)
int cek = 20;

// ============   DEKLARASI OBJECT ============
// Object Servo
// << Buat Object untuk Servo >>

void setup() {
  // Mulai Komunikasi Serial dengan Baud Rate 115200
  // -> Agar bisa melakukan debug menggunakan serial monitor nantinya
  Serial.begin(115200);

  // Konfig Pin Ultrasonic (Sensor Jarak)
  // << SET PINMODE UNTUK ULTRASONIK BAGIAN TRIGGER >>
  // << SET PINMODE UNTUK ULTRASONIK BAGIAN ECHO >>

  // Konfig Pin Motor Driver (Penggerak Ban)
  // << SET PINMODE UNTUK MOTOR 1 >>
  // << SET PINMODE UNTUK MOTOR 2 >>
  // << SET PINMODE UNTUK MOTOR 3 >>
  // << SET PINMODE UNTUK MOTOR 4 >>

  // Set motor sebagai LOW dulu semuanya
  // Karena default adalah HIGH (Mencegah ban langsung bergerak)
  stop();

  // Hubungkan Object Servo (yang sudah dibuat sebelumnya) ke Pin Servo
  // << ATTACH SERVO KE PIN >>

  // Set arah servo ke depan (90 derajat) terlebih dahulu
  // << SET ARAH SERVO KE 90 >>
  // << BERIKAN SEDIKIT DELAY, 800 CUKUP >>
}

void loop() {
  // ===========================================================================
  // ====    Di Bagian Paling Bawah Ada Fungsi yang Bisa Langsung Digunakan ====
  // ====           Gunakan Fungsi-Fungsi Tersebut Sebagai Referensi        ====
  // ===========================================================================

  // Baca Jarak Depan
  // << ISI VARIABEL JARAK DEPAN DENGAN FUNGSI JARAK >>

  // Jika di depan ada obstacle (Halangan)
  if (jarak depan < variabel cek) {
    // Robot Mundur sedikit
    back();
    delay(200);
    // Robot Stop, untuk melihat jarak
    stop();
    delay(500);

    // === Cek Jarak Sebelah Kiri ===
    // Sesuaikan Kodingan di Bawah dengan Variabel yang Kalian Buat
    myServo.write(180); // -> 0 Paling Kanan, 180 Paling Kiri, 90 Arah Depan
    delay(500);
    Jkiri = jarak();
    Serial.println("Robot Nengok ke Kiri!");
    delay(2000);

    // === Cek Jarak Sebelah Kanan ===
    /*
    Masukkan Kodingan
    */

    // === Kembali Ke Arah Depan ===
    /*
    Masukkan Kodingan
    */

    if (Jkiri > Jkanan) {
      // Sesuaikan Kodingan di Bawah dengan Variabel yang Kalian Buat
      Jdepan = jarak();
      while (Jdepan <= 20) {
        Serial.print("Jarak Depan : ");
        Serial.println(Jdepan);
        left();
        Jdepan = jarak();
        delay(10);
      }
    } else if (Jkanan > Jkiri) {
      /*
      Masukkan Kodingan
      */
    } else {
      /*
      Masukkan Kodingan
      */
    }
  } else {
    // Kalo gaada halangan, buat kodingan agar maju saja
  }
  delay(20);
}

int jarak() {
  long duration, distance;

  // ===== Mengirim gelombang dari trigger untuk memulai pengukuran =====
  digitalWrite(TRG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRG, LOW);

  // pulseIn membaca waktu tempuh gelombang dan disimpan di duration
  duration = pulseIn(ECH, HIGH, 30000);

  // Ukur jarak menggunakan rumus fisika; 
  // Jarak = Kecepatan x Waktu
  // -> Karena cara kerja Ultrasonik adalah memantulkan gelombang, maka jarak/2
  // -> Kecepatan didapat dari kecepatan gelombang suara (0.0343)
  distance = (duration * 0.0343) / 2;

  Serial.print("Distance sensor : ");
  Serial.println(distance);

  // Berikan sedikit delay
  delay(100);
  return (int)distance;
}

void maju() {
  digitalWrite(PINA, HIGH);
  digitalWrite(PINB, LOW);
  digitalWrite(PINC, HIGH);
  digitalWrite(PIND, LOW);
}

void right() {
  Serial.println("Kanan");
  digitalWrite(PINA, HIGH);
  digitalWrite(PINB, LOW);
  digitalWrite(PINC, LOW);
  digitalWrite(PIND, HIGH);
}

void left() {
  Serial.println("Kiri");
  digitalWrite(PINA, LOW);
  digitalWrite(PINB, HIGH);
  digitalWrite(PINC, HIGH);
  digitalWrite(PIND, LOW);
}

void stop() {
  Serial.println("Berhenti");
  digitalWrite(PINA, LOW);
  digitalWrite(PINB, LOW);
  digitalWrite(PINC, LOW);
  digitalWrite(PIND, LOW);
}

void back() {
  Serial.println("Mundur");
  digitalWrite(PINA, LOW);
  digitalWrite(PINB, HIGH);
  digitalWrite(PINC, LOW);
  digitalWrite(PIND, HIGH);
}