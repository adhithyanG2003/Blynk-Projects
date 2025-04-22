//library file by project planner adhithyan
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "DQLX6RuKA3mILs8JTPsnF8KqZGSdsdBl";//Enter your Auth token
char ssid[] = "POCO M6 Pro 5G";  //Enter your WIFI SSID
char pass[] = "passw@rd";  //Enter your WIFI Password

//pin connection
DHT dht(D2, DHT11);//(DHT sensor pin,sensor type)  D2 DHT11 Temperature Sensor
BlynkTimer timer;


void setup() {
  Serial.begin(9600);  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();
  

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



void loop(){
  
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}
