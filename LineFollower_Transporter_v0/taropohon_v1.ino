#include <Servo.h>

// Motor pins
#define PWMA D1  // PWM Motor Kiri
#define PWMB D2  // PWM Motor Kanan
#define DA D3    // Direction Motor Kiri
#define DB D4    // Direction Motor Kanan

// Line sensor pins
#define S1 D0
#define S2 D6
#define S3 A0
#define S4 D7
#define S5 D8

// Servo pins
#define SERVO1_PIN D9  // Arm

// Motor speed calibration
#define SPEED_FORWARD_LEFT 140
#define SPEED_FORWARD_RIGHT 130
#define SPEED_BACKWARD_LEFT 50
#define SPEED_BACKWARD_RIGHT 50
#define SPEED_TURN_FAST 100
#define SPEED_TURN_SLOW 100

// Servo Posisi Gripper
// Posisi Griiper NAIK
#define GRIPPER_DOWN 35
// Posisi Gripper TURUN
#define GRIPPER_UP 120

// Sensor threshold untuk jalur PUTIH
#define ANALOG_THRESHOLD 500

Servo servo1;  // Arm

int step = 0;

void setup() {

  Serial.begin(115200);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DA, OUTPUT);
  pinMode(DB, OUTPUT);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  // Library Servo Ke mikrokontroler Pin yang sesuai
  servo1.attach(SERVO1_PIN);  // Arm

  // // Posisi Awal Gripper

  servo1.write(GRIPPER_UP);  //
}

void loop() {
  int s1 = digitalRead(S1);
  int s2 = digitalRead(S2);
  int s4 = digitalRead(S4);
  int s5 = digitalRead(S5);

  int s3Analog = analogRead(S3);
  int s3 = (s3Analog > ANALOG_THRESHOLD) ? 1 : 0;

  // Kotak putih start dahhh betull
  switch (step) {
    case 0:
      if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1) {
        stopMotor();
        delay(1500);
        maju();
        delay(800);
        step++;
        Serial.print("Step 1 : ");
        Serial.println(step);
      } else {
        followLine(s1, s2, s3, s4, s5);
      }
      break;

      // Simpang Neraka dahh betull
    case 1:
      if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1) {
        maju();
        delay(200);
        belokKanan();
        delay(500);
        step++;
        Serial.print("Step 2 : ");
        Serial.println(step);
      } else {
        followLine(s1, s2, s3, s4, s5);
      }
      break;

      // Ambek Pohon susahhhh dahh betull
    case 2:
      if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1) {
        maju();
        delay(500);
        stopMotor();
        delay(1000);
        ambilBarangPohon();
        // taruhBarang();
        mundur();
        delay(900);
        belokKanan();
        delay(500);
        maju();
        delay(200);
        step++;
        Serial.print("Step 3 : ");
        Serial.println(step);
      } else {
        followLine(s1, s2, s3, s4, s5);
      }
      break;

      //  pass mundur kebaca ini
      // case 3:
      //   if (s3 == 1 && s4 == 1 && s5 == 1) {
      //     maju();
      //     delay(200);
      //     belokKanan();
      //     delay(200);
      //     maju();
      //     delay(300);
      //     step++;
      //     Serial.print("Step 4 : ");
      //     Serial.println(step);
      //   } else {
      //     followLine(s1, s2, s3, s4, s5);
      //   }
      //   break;

      // Habis maju kebaca ini
    case 3:
      if (s3 == 1 && s4 == 1 && s5 == 1) {
        belokKanan();
        delay(400);
        maju();
        delay(500);
        step++;
        Serial.print("Step 4: ");
        Serial.println(step);
      } else {
        followLine(s1, s2, s3, s4, s5);
      }
      break;
      // Tarok Pohon
    case 4:
      if (s1 == 1 && s2 == 1 && s3 == 1) {
        maju();
        delay(300);
        belokKiri();
        delay(500);
        maju();
        delay(100);
        step++;
        Serial.print("Step 5 : ");
        Serial.println(step);
      } else {
        followLine(s1, s2, s3, s4, s5);
      }
      break;
      // Kotak Pohon
    case 5:
      if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1) {
        stopMotor();
        delay(1000);
        // ambilBarang();
        taruhBarangPohon();
        mundur();
        delay(2000);
        belokKanan();
        delay(500);
        maju();
        delay(200);
        step++;
        Serial.print("Step 6 : ");
        Serial.println(step);
      }
      break;
      // Masuk Lingkaran
    case 6:
      if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1) {
        belokKanan();
        delay(200);
        step++;
        Serial.print("Step 6 : ");
        Serial.println(step);
      } else {
        followLine(s1, s2, s3, s4, s5);
      }
      break;

      //Keluar Lingkaran
    case 7:
      if (s1 == 1 && s2 == 1 && s3 == 1) {
        maju();
        delay(250);
        belokKanan();
        delay(800);
        maju();
        delay(300);
        step++;
        Serial.print("Step 7 : ");
        Serial.println(step);
      } else {
        followLine(s1, s2, s3, s4, s5);
      }
      break;

      // Setelah lingkaran
    case 8:
      if (s3 == 1 && s4 == 1 && s5 == 1) {
        maju();
        delay(300);
        belokKanan();
        delay(600);
        maju();
        delay(200);
        step++;
        Serial.print("Step 8 : ");
        Serial.print(step);
      } else {
        followLine(s1, s2, s3, s4, s5);
      }
      break;
      //   Simpang Kelereng
    case 9:
      if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1) {
        stopMotor();
        delay(3000);
        mundur();
        delay(1500);
        belokKanan();
        delay(800);
        maju();
        delay(500);
        step++;
        Serial.print("Step 9 : ");
        Serial.println(step);
      } else {
        followLine(s1, s2, s3, s4, s5);
      }
      break;
      // keluar lingkaran setan
    // case 10:
    //   if (s1 == 1 && s3 == 1 && s5 == 1) {
    //     maju();
    //     delay(200);
    //     step++;
    //     Serial.print("Step 10 : ");
    //     Serial.println(step);
    //   } else {
    //     followLine(s1, s2, s3, s4, s5);
    //   }
    //   break;
      // Belum program 10-14
    default:
      followLine(s1, s2, s3, s4, s5);
      break;
  }
}

void followLine(int s1, int s2, int s3, int s4, int s5) {
  if ((s3 == 1 || s2 == 1 && s3 == 1 || s3 == 1 && s4 == 1)) {
    maju();
  } else if ((s3 == 1 || s2 == 1 && s3 == 1 || s3 == 1 && s4 == 1)) {
    maju();
  } else if ((s1 == 1 || s1 == 1 && s2 == 1)) {
    belokKiri();
  } else if ((s5 == 1 || s4 == 1 && s5 == 1)) {
    belokKanan();
  } else if ((s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0)) {
    belokKiri();
  } else {
    maju();
  }
}


void ambilBarangPohon() {
  for (int pos = 120; pos >= 35; pos--){
    servo1.write(pos);
    delay(3);
  }
}

void taruhBarangPohon() {
  for (int pos = 35; pos <= 120; pos++){
    servo1.write(pos);
    delay(3);
  }
}

void maju() {
  digitalWrite(DA, HIGH);
  analogWrite(PWMA, SPEED_FORWARD_RIGHT);
  digitalWrite(DB, HIGH);
  analogWrite(PWMB, SPEED_FORWARD_LEFT);
}

void mundur() {
  digitalWrite(DA, LOW);
  analogWrite(PWMA, SPEED_BACKWARD_RIGHT);
  digitalWrite(DB, LOW);
  analogWrite(PWMB, SPEED_BACKWARD_LEFT);
}

void belokKiri() {
  digitalWrite(DA, LOW);
  analogWrite(PWMA, SPEED_TURN_SLOW);
  digitalWrite(DB, HIGH);
  analogWrite(PWMB, SPEED_TURN_FAST);
}

void belokKanan() {
  digitalWrite(DA, HIGH);
  analogWrite(PWMA, SPEED_TURN_FAST);
  digitalWrite(DB, LOW);
  analogWrite(PWMB, SPEED_TURN_SLOW);
}

void stopMotor() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}