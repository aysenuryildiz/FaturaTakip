/***ESP8266 WiFi Kütüphane Dosyası ***/
//#include <Arduino.h>
#include <ESP8266WiFi.h>
/*** Firebase Kütüphane Dosyaları ***/
//#include <Firebase.h>
#include <FirebaseArduino.h>
//#include <FirebaseError.h>

/*** Kablosuz Ağ Bilgileri ***/
#define WLAN_SSID "selam"
#define WLAN_PASSWORD "hopasinanay"

/***  -Firebase Kurulumu-  ***/
#define FIREBASE_HOST "elektriksayaci-70dd1.firebaseio.com"  //url
#define FIREBASE_AUTH "OlA7aYkoEuzkS2wuz2jZWdsVRibdaGdLVDV0E4X3"  //firebasede türetilen key

/*** Değişken ve Pin Tanımlaması ***/

//#define LED D2

/*** ESP8266 WiFi Kurulum Fonksiyonu ***/
 String saniyeveri="saniyeveri";
void WiFi_Setup ()
{
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println(); Serial.print(WLAN_SSID);
  Serial.print("Kablosuz Agina Baglaniyor...");
  WiFi.begin(WLAN_SSID, WLAN_PASSWORD);

  // WiFi durum kontrolü
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println();Serial.print(WLAN_SSID);
Serial.println("Kablosuz Agina Baglandi...");
Serial.println("IP adresi: ");
Serial.println(WiFi.localIP());

}

void setup() 
{
  Serial.begin(115200);  // Seri port baud rate ayarı
  WiFi_Setup();          //Kablosuz ağ bağlantı fonks.

  //pinMode(LED,OUTPUT);

 // digitalWrite(LED,LOW);

  Firebase.begin (FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setString ("ElektrikSayaci","false");
  Firebase.setString("saniyeveri","null");
}
unsigned long t,x,y;
int a,b;
float sonuc;
float saniye;
float kullanimtutari;
void loop() 
{ 

  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
    WiFi.begin(WLAN_SSID, WLAN_PASSWORD);

}
  
  if (Firebase.getString("ElektrikSayaci")=="true")
  {
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("Yandi");
    if(a==0){
     x=millis(); 
     a=1;
     b=0;
    }
    
        

   
  }  
      else
      {
        digitalWrite(LED_BUILTIN,LOW);
        if(b==0){
          y=millis();
          b=1;

          a=0;
          StaticJsonBuffer < 200 > jsonBuffer;
  JsonObject & valueObject = jsonBuffer. createObject ();
                 saniye=y-x;
                 t=t+y-x; 
                 kullanimtutari= (y-x)*(0.001)*(0.128);    
                 valueObject [ "saniye" ] = saniye;
                 valueObject [ "kullanimtutari" ] = kullanimtutari;
                 Firebase.push(saniyeveri+"/value",valueObject);
        }
               
        
       
 
     
  
   
    sonuc=t*0.001; //milisaniye to saniye dönüşüm.
    sonuc=sonuc*0.128;  //saniye başına fiyat çarpanı
    
      Firebase.setFloat("sonuc",sonuc);

  
  
  
      }
      if (Firebase.failed())
      {
        Serial.print("setting /number failed:");
        Serial.println(Firebase.error());
        return;
        
      }
      delay(100);
    }
