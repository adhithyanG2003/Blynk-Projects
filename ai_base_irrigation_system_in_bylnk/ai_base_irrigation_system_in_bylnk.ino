#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "usLyA2Gomx79Z_pLo5wGuho3OQpeIoNf";  //Enter your Blynk Auth token
char ssid[] = "123456789";  //Enter your WIFI SSID
char pass[] = "123456789";  //Enter your WIFI Password


DHT dht(D2, DHT11);//(DHT sensor pin,sensor type)  D4 DHT11 Temperature Sensor
BlynkTimer timer;
#define soil A0     //A0 Soil Moisture Sensor 
#define waterPump D5 //relay pin

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump,HIGH);
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();
 timer.setInterval(100L, soilMoistureSensor);
 timer.setInterval(100L, DHT11sensor);
}

//Get the DHT11 sensor values
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h); 
  Serial.println("\n temperature=");
  Serial.println(t);
  Serial.println("\n humidity=");
  Serial.println(h);
  }
  
  
  //Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(soil);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;
  Serial.println("\n moisture=");
  Serial.println(value);
  Blynk.virtualWrite(V2, value);
  if (value <= 30){
      digitalWrite(D5,HIGH);
      delay(1000);
      Serial.println("relay  moisture sensor on \n");
    }
  else{
      digitalWrite(D5,LOW);
       Serial.println("relay  moisture sensor off \n");
    } 
    }
  void loop() {
    
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer

  }
