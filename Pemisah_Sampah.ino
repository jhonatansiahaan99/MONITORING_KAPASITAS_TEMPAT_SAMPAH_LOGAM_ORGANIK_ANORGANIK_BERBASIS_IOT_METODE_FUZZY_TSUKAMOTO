#include <LiquidCrystal_I2C.h>
#include <Servo.h> // memanggil library servo

LiquidCrystal_I2C lcd(0x27, 16, 2);


#define sensorKapasitif 8
#define sensorInduktif 9
#define sensorInfrared 10
int sensorLDR = A2;

Servo servopertama; //buat variabel servo dengan nama servoInduktif
Servo servokedua; //buat variabel servo dengan nama servoOrganik

bool nilaisensorInduktif = 0;
bool nilaisensorKapasitif = 0;
bool nilaisensorInfrared;

void setup() {
  Serial.begin(9600);
  servopertama.attach(11);// servo terletak di pin 11
  servokedua.attach(12);// servo terletak di pin 12

  pinMode(8,INPUT);//sensorKapasitif
  pinMode(9,INPUT);//sensorInduktif
  pinMode(10,INPUT);//sensorInfraredLogam
  
  servopertama.write(90);
  servokedua.write(90);

  lcd.begin();
//  lcd.backlight();
  lcd.setCursor(7,0);// memilih kolom ke 7 baris ke 1 pada LCD
  lcd.print("HALO");// menampilkan kalimat periksa sampah pada LCD
  lcd.setCursor(0,1);// memilih kolom ke 0 baris ke 2 pada LCD
  lcd.print("SELAMAT DATANG");// menampilkan kalimat periksa sampah pada LCD
  delay(2000);
  lcd.clear();
}

void loop() {

//  lcd.backlight();
  lcd.setCursor(5,0);// memilih kolom ke 5 baris ke 0 pada LCD
  lcd.print("SILAHKAN");// menampilkan kalimat periksa sampah pada LCD
  lcd.setCursor(0,1);// memilih kolom ke 0 baris ke 2 pada LCD
  lcd.print("Masukkan Sampah!");// menampilkan kalimat periksa sampah pada LCD

  nilaisensorKapasitif = digitalRead(8);  
  nilaisensorInduktif = digitalRead(9);
  nilaisensorInfrared = digitalRead(10);
  int nilaisensorLDR = analogRead(sensorLDR);
  
  delay (1000);
  
  Serial.print("Infrared = ");
  Serial.println(nilaisensorInfrared);
  Serial.print("Induktif = ");
  Serial.println(nilaisensorInduktif);
  Serial.print("Kapasitif = ");
  Serial.println(nilaisensorKapasitif);
  Serial.print("LDR = ");
  Serial.println(nilaisensorLDR);

  Serial.println();

    if(nilaisensorInfrared == 0){
    Serial.print("Ada Sampah");
    Serial.println();
    delay(100);
    nilaisensorKapasitif = digitalRead(8);  
    nilaisensorInduktif = digitalRead(9);
    nilaisensorInfrared = digitalRead(10);
    nilaisensorLDR = digitalRead(13);

    if(nilaisensorInduktif == 0 && nilaisensorKapasitif == 1 && nilaisensorLDR >= 0){
      lcd.clear();
//      lcd.backlight();
      lcd.setCursor(0,0);// memilih kolom ke 0 baris ke 0 pada LCD
      lcd.print("Terdeteksi !!");// menampilkan kalimat periksa sampah pada LCD
      lcd.setCursor(0,1);// memilih kolom ke 0 baris ke 1 pada LCD
      lcd.print("SAMPAH LOGAM");// menampilkan kalimat periksa sampah pada LCD
  
      servopertama.write(0);
      Serial.println("SAMPAH LOGAM");
      Serial.print("Sebelah Kanan");
      Serial.println();
      Serial.println();
      delay(2000);
      servopertama.write(90);
      lcd.clear();
    }
    else if(nilaisensorInduktif == 0 && nilaisensorLDR >= 0){
      lcd.clear();
//      lcd.backlight();
      lcd.setCursor(0,0);// memilih kolom ke 0 baris ke 0 pada LCD
      lcd.print("Terdeteksi !!");// menampilkan kalimat periksa sampah pada LCD
      lcd.setCursor(0,1);// memilih kolom ke 0 baris ke 1 pada LCD
      lcd.print("SAMPAH LOGAM");// menampilkan kalimat periksa sampah pada LCD
  
      servopertama.write(0);
      Serial.println("SAMPAH LOGAM");
      Serial.print("Sebelah Kanan");
      Serial.println();
      Serial.println();
      delay(2000);
      servopertama.write(90);
      lcd.clear();
    }
    else if(nilaisensorKapasitif == 1 && nilaisensorLDR >= 0){
      lcd.clear();
//      lcd.backlight();
      lcd.setCursor(0,0);// memilih kolom ke 0 baris ke 0 pada LCD
      lcd.print("Terdeteksi !!");// menampilkan kalimat periksa sampah pada LCD
      lcd.setCursor(0,1);// memilih kolom ke 0 baris ke 1 pada LCD
      lcd.print("SAMPAH ORGANIK");// menampilkan kalimat periksa sampah pada LCD
  
      servopertama.write(180);
      Serial.println("SAMPAH ORGANIK");
      Serial.print("Putar Sebelah Kiri Dulu");
      Serial.println();
      Serial.println();
      delay(2000);
      servopertama.write(90);
      servokedua.write(0);
      Serial.println("SAMPAH ORGANIK");
      Serial.print("Sebelah Kanan");
      Serial.println();
      Serial.println();
      delay(2000);
      servokedua.write(90);
      lcd.clear();
    }
    else if(nilaisensorLDR >= 0 ){
      lcd.clear();
//      lcd.backlight();
      lcd.setCursor(0,0);// memilih kolom ke 0 baris ke 0 pada LCD
      lcd.print("Terdeteksi !!");// menampilkan kalimat periksa sampah pada LCD
      lcd.setCursor(0,1);// memilih kolom ke 0 baris ke 1 pada LCD
      lcd.print("SAMPAH ANORGANIK");// menampilkan kalimat periksa sampah pada LCD
  
      servopertama.write(180);
      Serial.println("SAMPAH ANORGANIK");
      Serial.print("Putar Sebelah Kiri Dulu");
      Serial.println();
      Serial.println();
      delay(2000);
      servopertama.write(90);
      servokedua.write(180);
      Serial.println("SAMPAH ANORGANIK");
      Serial.print("Sebelah Kiri");
      Serial.println();
      Serial.println();
      delay(2000);
      servokedua.write(90);
      lcd.clear();
    }
  }else{
    servopertama.write(90);
    Serial.println("Tidak Ada Sampah");
    Serial.println();
  }
  delay(1000);
  Serial.println();
  Serial.println("----");
  Serial.println();
  
}
