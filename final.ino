// https://github.com/tabvn/arduino-lighting-control/blob/master/lightControl.ino
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

int leds =  D1;
int states;
int totalDevices = 1;

#define firebaseURl "fir-project-01-e38ce-default-rtdb.firebaseio.com"
#define authCode "XO9wHjuPpWZVR56fN28tsjHipuhOm5exbhsmK0sh"

#define wifiName "Incubator"
#define wifiPass "Incubator#2013"

String chipId = "123";

void setupFirebase() {

  Firebase.begin(firebaseURl, authCode);
}

void setupWifi() {

  WiFi.begin(wifiName, wifiPass);

  Serial.println("Hey i 'm connecting...");

  while (WiFi.status() != WL_CONNECTED) {

    Serial.println(".");
    delay(500);
  }

  Serial.println();
  Serial.println("I 'm connected and my IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {

  Serial.begin(9600);

  setupWifi();
  setupFirebase();

  setupPinsMode();

}

void getData() {

  String path = chipId + "/states";
  FirebaseObject object = Firebase.get(path);

  bool led1 = object.getBool("001");


  Serial.print("Led");
  //               Serial.println(led1);



  Serial.println("-------------------------------- -");

  // write output high or low to turn on or off led
  digitalWrite(leds, led1);



}
void loop() {

  getData();

}

void setupPinsMode() {

  // setup Pin mode as output.

  for (int i; i < totalDevices; i++) {

    Serial.printf("Setup Output for pin % d", leds);
    pinMode(leds, OUTPUT);
  }
}
