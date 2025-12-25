// ============   IMPORT LIBRARY    ============
// Library untuk kontrol servo pada ESP32
#include <ESP32Servo.h>

// ============   SET PIN KOMPONEN  ============
// Ultrasonic
#define TRG 21
#define ECH 19
// Motor Driver (L289N)
#define PINA 18
#define PINB 5
#define PINC 2
#define PIND 15
// Servo
#define SERVO1 23

// ============   DEFINE VARIABEL  ============
// Variabel Simpan Jarak Ultrasonik
int Jdepan;
int Jkiri;
int Jkanan;
// Variabel Cek Jarak Minimum Robot (Agar Berhenti)
int cek = 15;

// ============   DEKLARASI OBJECT ============
// Object Servo
Servo myServo;

void setup() {
  // Mulai Komunikasi Serial dengan Baud Rate 115200
  // -> Agar bisa melakukan debug menggunakan serial monitor nantinya
  Serial.begin(115200);

  // Konfig Pin Ultrasonic (Sensor Jarak)
  pinMode(TRG, OUTPUT); // -> Trigger set sebagai output (mengeluarkan gelombang)
  pinMode(ECH, INPUT); // -> Echo set sebagai input (menerima gelombang)

  // Konfig Pin Motor Driver (Penggerak Ban)
  pinMode(PINA, OUTPUT);
  pinMode(PINB, OUTPUT);
  pinMode(PINC, OUTPUT);
  pinMode(PIND, OUTPUT);

  // Set motor sebagai LOW dulu semuanya
  // Karena default adalah HIGH (Mencegah ban langsung bergerak)
  stop();

  // Hubungkan Object Servo (yang sudah dibuat sebelumnya) ke Pin SERVO1(23)
  myServo.attach(SERVO1);

  // Set arah servo ke depan (90 derajat) terlebih dahulu
  myServo.write(90);
  delay(800);
}

void loop() {
  // Baca Jarak Depan
  Jdepan = jarak();

  // Jika di depan ada obstacle (Halangan)
  if (Jdepan > 0 && Jdepan < cek) {
    back();
    delay(200);
    stop();
    delay(500);

    // cek kiri
    myServo.write(180);
    Jkiri = jarak();
    delay(1000);
    Serial.println("Ini Kondisi Servo Kiri!");

    // cek kanan
    myServo.write(0);
    Jkanan = jarak();
    delay(1000);
    Serial.println("Ini Kondisi Servo Kanan!");

    // balik tengah
    myServo.write(90);
    delay(1000);
    Serial.println("Ini Kondisi Servo Tengah!");

    if (Jkiri > Jkanan) {
      left();
      delay(250);
      stop();
      delay(100);
    } else if (Jkanan > Jkiri) {
      right();
      delay(250);
      stop();
      delay(100);
    } else {
      stop();
      delay(200);
    }
  } else {
    maju();
  }

  delay(20);
}

int jarak() {
  int duration, distance;

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
  return distance;
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