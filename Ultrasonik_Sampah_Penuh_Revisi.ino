#include <ESP8266HTTPClient.h>

//include library wifi nodemcu esp8266
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h> // memanggil library LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);//menentukan jenis lcdi2c

//setting jaringan
const char* ssid = "SIAHAAN";
const char* password = "Siahaan15";
const char* host =  "monitoringtempatsampah.site"; //alamat IP server laptop

  //deklarasi variabel untuk perulangan durasi waktu sensor dan jarak sensor

//sediakan variabel untuk indikator koneksi, untuk mengetahui sudah terkoneksi ke jaringan 
//#define Indikator_Logam D6



//pin ultrasonik
#define tringPinLogam D0
#define echoPinLogam D1

#define tringPinOrganik D2 
#define echoPinOrganik D3

#define tringPinAnorganik D4
#define echoPinAnorganik D5




#define Indikator_Logam D6
//Akhir pin ultrasonik


long durasiLogam,durasiAnorganik,durasiOrganik,jarakLogam,jarakAnorganik,jarakOrganik;
int konversi_logam, konversi_anorganik, konversi_organik;

int ukuranlogam, ukurananorganik, ukuranorganik;

void setup() {
  Serial.begin(9600);
  pinMode(Indikator_Logam, OUTPUT);

  
  //koneksi ke wifi
  WiFi.hostname("NodeMCU");
  WiFi.begin(ssid, password);

  //cek koneksi apakah berhasil atau tidak
  while(WiFi.status() != WL_CONNECTED)
  {
    //selama tidak terkoneksi lampu led nya mati
    digitalWrite(Indikator_Logam,LOW);
    
    //coba koneksi terus
    Serial.print(".");
    delay(500);
  }
  // apabila berhasil terkoneksi
  digitalWrite(Indikator_Logam,HIGH);
  //apabila sudah terkoneksi
//  Serial.println("Berhasil Koneksi");

  //setup untuk LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(7,0);// memilih kolom ke 7 baris ke 1 pada LCD
  lcd.print("HALO");// menampilkan kalimat periksa sampah pada LCD
  lcd.setCursor(0,1);// memilih kolom ke 0 baris ke 2 pada LCD
  lcd.print("SELAMAT DATANG");// menampilkan kalimat periksa sampah pada LCD
  delay(2000);
  lcd.clear();

  //setup untuk ultrasonik
  pinMode(tringPinLogam, OUTPUT);
  pinMode(tringPinAnorganik, OUTPUT);
  pinMode(tringPinOrganik, OUTPUT);
  
  pinMode(echoPinLogam, INPUT);
  pinMode(echoPinAnorganik, INPUT);
  pinMode(echoPinOrganik, INPUT);

}

void loop() {
  //koneksi ke server / web server apache
  WiFiClient client;
  const int httpPort = 80;
  //uji koneksi ke server
  if(!client.connect(host,httpPort))//jika tidak terkoneksi ke host/ip address dan port xampp
  {
    Serial.println("Gagal Koneksi ke Server");
    return;
  }
  //apabila berhasil koneksi ke server
//  Serial.println("Berhasil Koneksi ke Server");


//baca ukuran logam
  String LinkLogam;
  HTTPClient httpLogam;
  LinkLogam = "http://" + String(host) + "/tempatsampah/monitoring/bacalogam.php";
  httpLogam.begin(LinkLogam);
  //ambil isi posisi servo di bacaservo.php
  httpLogam.GET();
  //Baca status response
  String responseLogam = httpLogam.getString();
   Serial.println();
  Serial.print("Ukuran Logam : ");
  Serial.print(responseLogam);
 Serial.println();
  Serial.println();
  httpLogam.end();

  //set posisi servo
  ukuranlogam = responseLogam.toInt();






  //baca ukuran organik
  String LinkOrganik;
  HTTPClient httpOrganik;
  LinkOrganik = "http://" + String(host) + "/tempatsampah/monitoring/bacaorganik.php";
  httpOrganik.begin(LinkOrganik);
  //ambil isi posisi servo di bacaservo.php
  httpOrganik.GET();
  //Baca status response
  String responseOrganik = httpOrganik.getString();
  Serial.print("Ukuran Organik : ");
  Serial.print(responseOrganik);
  Serial.println();
  Serial.println();
  
  
  httpOrganik.end();

  //set posisi servo
  ukuranorganik = responseOrganik.toInt();
 


  //baca ukuran anorganik
  String LinkAnorganik;
  HTTPClient httpAnorganik;
  LinkAnorganik = "http://" + String(host) + "/tempatsampah/monitoring/bacaanorganik.php";
  httpAnorganik.begin(LinkAnorganik);
  //ambil isi posisi servo di bacaservo.php
  httpAnorganik.GET();
  //Baca status response
  String responseAnorganik = httpAnorganik.getString();
   Serial.print("Ukuran Anorganik : ");
  Serial.print(responseAnorganik);
  Serial.println();
  Serial.println();
  httpAnorganik.end();

  //set posisi servo
  ukurananorganik = responseAnorganik.toInt();
  


//Sensor Ultrasonik Logam
//Menghapus/mematikan tringpin selama 2 micro detik
  digitalWrite(tringPinLogam, LOW);
  delayMicroseconds(2);//delay waktu

  //Mengset/menghidupkan tringpin selama 10 micro detik
  digitalWrite(tringPinLogam, HIGH);
  delayMicroseconds(10);//delay waktu
  digitalWrite(tringPinLogam, LOW);

  durasiLogam = pulseIn(echoPinLogam,HIGH); // data echoPin di masukkan ke variabel durasi
  jarakLogam = durasiLogam*0.034/2; //rumus mengukur jarak
    Serial.println();
//  Serial.print("Jarak Logam : ");
//  Serial.println(jarakLogam);
  konversi_logam = map(jarakLogam,ukuranlogam,0,0,100);
//  konversi_logam = 100 - jarakLogam*100/26;
  Serial.print("Kapasitas Logam : ");
  Serial.print(konversi_logam);
  Serial.print(" %");
  Serial.println();

//  if(jarakLogam <= 2){
//    digitalWrite(Indikator_Logam, HIGH);
//    Serial.println("SAMPAH PENUH");
//  }else{
//    digitalWrite(Indikator_Logam, LOW);
//    Serial.println("SAMPAH KOSONG");
//  }
  
//Akhir Sensor Ultrasonik Logam



//Sensor Ultrasonik Organik
//Menghapus/mematikan tringpin selama 2 micro detik
  digitalWrite(tringPinOrganik, LOW);
  delayMicroseconds(2);//delay waktu

  //Mengset/menghidupkan tringpin selama 10 micro detik
  digitalWrite(tringPinOrganik, HIGH);
  delayMicroseconds(10);//delay waktu
  digitalWrite(tringPinOrganik, LOW);

  durasiOrganik = pulseIn(echoPinOrganik,HIGH); // data echoPin di masukkan ke variabel durasi
  jarakOrganik = durasiOrganik*0.034/2; //rumus mengukur jarak
    Serial.println();
//  Serial.print("Jarak Organik : ");
//  Serial.println(jarakOrganik);

  konversi_organik = map(jarakOrganik,ukuranorganik,0,0,100);
  Serial.print("Kapasitas Organik : ");
  Serial.print(konversi_organik);
  Serial.print(" %");
  Serial.println();

//Akhir Sensor Ultrasonik Organik

//Sensor Ultrasonik Anorganik
//Menghapus/mematikan tringpin selama 2 micro detik
  digitalWrite(tringPinAnorganik, LOW);
  delayMicroseconds(2);//delay waktu

  //Mengset/menghidupkan tringpin selama 10 micro detik
  digitalWrite(tringPinAnorganik, HIGH);
  delayMicroseconds(10);//delay waktu
  digitalWrite(tringPinAnorganik, LOW);

  durasiAnorganik = pulseIn(echoPinAnorganik,HIGH); // data echoPin di masukkan ke variabel durasi
  jarakAnorganik = durasiAnorganik*0.034/2; //rumus mengukur jarak
    Serial.println();
//  Serial.print("Jarak Anorganik : ");
//  Serial.println(jarakAnorganik);
  konversi_anorganik = map(jarakAnorganik,ukurananorganik,0,0,100);
  Serial.print("Kapasitas Anorganik : ");
  Serial.print(konversi_anorganik);
  Serial.print(" %");
  Serial.println();


//  if(jarakAnorganik <= 2){
//    digitalWrite(Indikator_Anorganik, HIGH);
//    Serial.println("SAMPAH PENUH");
//  }else{
//    digitalWrite(Indikator_Anorganik, LOW);
//    Serial.println("SAMPAH KOSONG");
//  }
//Akhir Sensor Ultrasonik Anorganik

  String Link;
  HTTPClient http;
  Link = "http://" + String(host) + "/tempatsampah/monitoring/kirimdataultrasonik.php?kapasitas_logam=" + String(konversi_logam) + "&kapasitas_anorganik=" + String(konversi_anorganik) + "&kapasitas_organik=" + String(konversi_organik); // berisi "alamat host,/nama folder program yang di htdocs,/nama file(file ini yang akan di eksekusi oleh nodemcu untuk menyimpan data ke dalam database"
  //eksekusi link
  http.begin(Link);
  //mode GET (karna parameter "kirimdata.php?sensor" adalah get.karna di php ada get dan post
  http.GET();
  String respon = http.getString();
  Serial.println(respon);
//  Serial.println(respon.toInt());
  http.end();

  delay(1000);

}
