#include <Arduino.h>
#include <Wire.h>

// Definisikan pin yang digunakan
#define STEP_PIN 9   // Pin untuk sinyal STEP
#define DIR_PIN 8    // Pin untuk sinyal DIR
#define ENABLE_PIN 7 // Pin untuk sinyal ENABLE
#define POT_PIN A0   // Pin untuk potensiometer

#define DIR_INPUT 11    // INPUT untuk sinyal DIR
#define ENABLE_INPUT 12 // INPUT untuk sinyal ENABLE

int stepDelay; // Variabel untuk mengatur delay antara langkah (kecepatan)
int potValue;  // Nilai dari potensiometer

// Variabel untuk debounce
unsigned long lastDebounceEna = 0; // Waktu terakhir debounce untuk tombol 1
unsigned long lastDebounceDir = 0; // Waktu terakhir debounce untuk tombol 2
unsigned long debounceDelay = 50;  // Delay untuk debounce (50 ms)

int lastButtonDir = LOW; // Status terakhir tombol 1
int lastButtonEna = LOW; // Status terakhir tombol 2

int buttonStateDir = LOW; // Status saat ini untuk tombol 1
int buttonStateEna = LOW; // Status saat ini untuk tombol 2

void setup()
{
  // Mengatur pin output untuk kontrol stepper
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  // Mengatur pin INPUT untuk kontrol stepper
  pinMode(DIR_INPUT, INPUT_PULLUP);
  pinMode(ENABLE_INPUT, INPUT_PULLUP);

  // Mengaktifkan motor (ENABLE pin low untuk mengaktifkan)
  digitalWrite(ENABLE_PIN, LOW);

  // Inisialisasi arah motor
  digitalWrite(DIR_PIN, HIGH); // Set HIGH untuk searah jarum jam (CW)
}

void loop()
{
  // Membaca nilai dari potensiometer (0-1023)
  potValue = analogRead(POT_PIN);

  // Membaca status tombol dir
  int readingDir = digitalRead(DIR_INPUT);
  if (readingDir != lastButtonDir)
    lastDebounceDir = millis(); // Reset waktu debounce
  if ((millis() - lastDebounceDir) > debounceDelay)
  {
    if (readingDir != buttonStateDir)
    {
      buttonStateDir = readingDir;
      (buttonStateDir == HIGH) ? digitalWrite(DIR_PIN, HIGH) : digitalWrite(DIR_PIN, LOW);
    }
  }
  lastButtonDir = readingDir;

  // Membaca status tombol ena
  int readingEna = digitalRead(ENABLE_INPUT);
  if (readingEna != lastButtonEna)
    lastDebounceEna = millis(); // Reset waktu debounce
  if ((millis() - lastDebounceEna) > debounceDelay)
  {
    if (readingEna != buttonStateEna)
    {
      buttonStateEna = readingEna;
      (buttonStateEna == HIGH) ? digitalWrite(ENABLE_PIN, HIGH) : digitalWrite(ENABLE_PIN, LOW);
    }
  }
  lastButtonEna = readingEna;

  // Mengonversi nilai potensiometer menjadi delay yang sesuai
  // Nilai potensiometer akan dikonversi menjadi delay antara langkah (0-1000 us)
  stepDelay = map(potValue, 0, 1023, 10000, 10); // Mengubah nilai 0-1023 menjadi 100-1000 microseconds

  // jika lebih dari 900 us matikan motor
  // if (stepDelay > 900)
  // {
  //   digitalWrite(STEP_PIN, LOW); // STEP low
  // }
  // else
  // {
    digitalWrite(STEP_PIN, HIGH); // STEP high
    delayMicroseconds(3);         // Delay sesuai kecepatan yang diatur
    digitalWrite(STEP_PIN, LOW);  // STEP low
    delayMicroseconds(stepDelay); // Delay sesuai kecepatan yang diatur
  // }
}
