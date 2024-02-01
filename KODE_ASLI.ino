#include "DHT.h"            //Library DHT
#define DHTPIN 2            //Inisialisasi DHT pada pin D5
#define DHTTYPE DHT22       //Inisialisasi tipe DHT
DHT dht (DHTPIN,DHTTYPE);   //Mengenalkan pin dan tipe DHT
float t;
const int BUZZERPIN = 7;
int LEDM = 3;   //LED merah pada pin D2
int LEDK = 4;   //LED kuning pada pin D3
int LEDH = 5;   //LED hijau pada pin D4
const int PIRPIN = 6;
const int ldrPin = A0;    // Pin sensor LDR terhubung ke pin A0 Arduino
const int relayPin1 = 11; 
const int relayPin2 = 12;



void suhu(float t){
  if (t <= 35){                 //Jika suhu <= 35*C, maka
    digitalWrite(LEDM, LOW); 
    digitalWrite(LEDK, LOW);
    digitalWrite(LEDH, HIGH);   //LED hijau menyala
  }
  else if (t <= 37){            //Jika suhu <= 37*C, maka
    digitalWrite(LEDM, LOW);
    digitalWrite(LEDK, HIGH);   //LED kuning menyala
    digitalWrite(LEDH, LOW);
  }
  else if (t > 41){             //Jika suhu > 41*C, maka
    digitalWrite(LEDM, HIGH);   //LED merah menyala
    digitalWrite(LEDK, LOW);
    digitalWrite(LEDH, LOW);
  }

}

void pir(int pirStatus){
  if (pirStatus == HIGH) {
    // Sensor PIR mendeteksi gerakan

    Serial.println("Gerakan terdeteksi!");
    
    // Memutar bunyi buzzer
    digitalWrite(BUZZERPIN, HIGH);
    delay(1000); // Buzzer aktif selama 1 detik
    digitalWrite(BUZZERPIN, LOW);
  }
}

void ldr(int ldrValue){
    if (ldrValue >= 500) { // LED menyala jika nilai LDR lebih besar atau sama dengan 500
    digitalWrite(relayPin1, HIGH;
  } else {// LED mati jika nilai LDR kurang dari 500
    digitalWrite(relayPin1, LOW);
  }
}

void setup() {
  Serial.begin(9600);     //Mulai komunikasi serial
  dht.begin();            //Mulai DHT
  pinMode(LEDM, OUTPUT);  //Setting LED sebagai output
  pinMode(LEDK, OUTPUT);
  pinMode(LEDH, OUTPUT);
  pinMode(PIRPIN, INPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
}

void loop() {
  int pirStatus = digitalRead(PIRPIN);
  t = dht.readTemperature();    //Baca suhu
  int ldrValue = analogRead(ldrPin);
 

  Serial.print("Suhu : ");
  Serial.print(t);              //Tampilkan suhu
  Serial.println(" *C");
  Serial.print("Nilai LDR: ");
  Serial.println(ldrValue);
  digitalWrite(relayPin2, LOW);
  suhu(t);
  delay(500);
  pir(pirStatus);
  ldr(ldrValue);
   
}