// Library LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//Library RTC
#include <DS3231.h>
DS3231  rtc(SDA, SCL);
Time waktu;
int dataJam, dataMenit, dataDetik, dm=0, dk=0;     
//library ldr
byte ldr1= A1;
byte ldr2= A0;
int n_ldr1, n_ldr2, dhm, dmm, dkk, ddr;



void setup() {

  Serial.begin(115200); 
  lcd.begin(16,4); 

  //Sensor RTC
  rtc.begin();
  // Seting waktu saat pertama kali RTC digunakan
  //rtc.setDOW(THURSDAY);           // Set Hari
  //rtc.setTime(23, 01, 00);      // Set waktu JJ:MM:DD (24hr format)
  //rtc.setDate(20, 9, 2016);     // Set tanggal 20 September 2016
  
  //Sensor LDR
}

void loop() {
  // put your main code here, to run repeatedly:
nldr();
algo_ldr();
algo_dmk();
algo_ruangan();
wakturtc();
display();
serial_monitor();
}

void nldr() {
  n_ldr1= analogRead(ldr1);
  n_ldr2= analogRead(ldr2);  
  }


void wakturtc() {
  waktu = rtc.getTime();
  dataJam = waktu.hour;     
  dataMenit = waktu.min;
  dataDetik = waktu.sec;
  }
void algo_ldr() {
  if (n_ldr1 > 100) {
    n_ldr2=0;
    dm = 1;
    delay(900);
    }else {
      dm = 0;
      }
  if (n_ldr2 > 100) {
    n_ldr1=0;
    delay(900);
    dk = 1;
    }else {
      dk = 0;
      }
  }

  void algo_dmk() {
    if (dm == 1){
      dmm = dmm+1;
      }else {
        dmm = dmm+0;
        }
     
     if (dk == 1){
      dkk = dkk+1;
      }else {
        dkk = dkk+0;
        }  
    }

void algo_ruangan() {
  ddr = dmm - dkk;
  if (ddr < 0) {
    ddr = 0;
    }else {
      ddr = ddr;
      }
  }
  
void serial_monitor() {
  Serial.print("Nilai LDR1: ");
  Serial.println(n_ldr1);
  Serial.print("Nilai LDR2: ");
  Serial.println(n_ldr2);
  Serial.print("Data LDRm: ");
  Serial.println(dmm);  
  Serial.print("Data LDRk: ");
  Serial.println(dkk);
  Serial.print("Di Ruangan: ");
  Serial.println(ddr);
  delay(400);
  }  
  
void display() {
  lcd.setCursor(0,0); 
  lcd.print("Waktu =");
  lcd.print(" ");
  lcd.print(dataJam);
  lcd.print(":");
  lcd.print(dataMenit);
  lcd.print(":");
  lcd.print(dataDetik); 
  
  lcd.setCursor(0,1); 
  lcd.print("Masuk  =");
  lcd.setCursor(9,1); 
  lcd.print(dmm); 

  lcd.setCursor(0,2); 
  lcd.print("Keluar =");
  lcd.setCursor(9,2); 
  lcd.print(dkk);

  lcd.setCursor(0,3); 
  lcd.print("Di Ruangan =");
  lcd.setCursor(13,3); 
  lcd.print(ddr);
  }
  
