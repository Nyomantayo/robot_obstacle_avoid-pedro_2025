// #include <ESP32Servo.h>

// #define SERVO1 23
// Servo s;

// int lastVal = 90;

// void setup() {
//   Serial.begin(115200);
//   s.attach(SERVO1, 500, 2400);

//   s.write(lastVal);
//   delay(500);

//   Serial.println("=== Servo 360 Serial Control ===");
//   Serial.println("Ketik angka 0..180 lalu Enter.");
//   Serial.println("Catatan: sekitar 90 itu biasanya STOP, <90 dan >90 beda arah.");
//   Serial.print("Current: "); Serial.println(lastVal);
// }

// void loop() {
//   // Kalau ada input masuk
//   if (Serial.available()) {
//     String line = Serial.readStringUntil('\n');
//     line.trim();
//     if (line.length() == 0) return;

//     int v = line.toInt();

//     // Validasi range 0..180
//     if (v < 0 || v > 180) {
//       Serial.println("Input harus 0..180");
//       return;
//     }

//     lastVal = v;
//     s.write(lastVal);

//     Serial.print("Set write(");
//     Serial.print(lastVal);
//     Serial.println(")");
//   }
// }
