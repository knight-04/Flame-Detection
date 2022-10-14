#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int RELAY = D4;
int Flame_sensor = D1;
int Flame_detected;
int Flame_State = 0;

BlynkTimer timer;
char auth[] = "ROxKff15shIAsKUPGhcWA2ZJTjrr7YIV"; 
char ssid[] = "Mr.Dumm007_2.4GHz";
char pass[] = "family555";

void notifyOnFire()
{
  Flame_detected = digitalRead(Flame_sensor);
  Flame_State = digitalRead(Flame_sensor);
  Serial.println(Flame_detected);
  if (Flame_detected == 0) {
    Serial.println("Flame detected!!!");
    Blynk.notify("Alert : Flame detected!!!");
    digitalWrite(RELAY, HIGH);
  }
  else
  {
    Serial.println("No Flame detected.");
    digitalWrite(RELAY, LOW);
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  pinMode(Flame_sensor, INPUT_PULLUP);
  timer.setInterval(1000L, notifyOnFire);
}

void loop()
{
  Blynk.run();
  timer.run();
}
