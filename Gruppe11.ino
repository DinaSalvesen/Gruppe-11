
///////////////
// Gruppe 11 //
///////////////


#include <Servo.h>                 // For å bruke servo-motorene
#include <stdlib.h>                // For å bruke random-funksjonen
#include <Adafruit_NeoPixel.h>     // For å bruke ledstripen og ledringen
#include <avr/power.h>             // Nødvendig for 16 MHz Adafruit


#ifdef __AVR__
#endif



#define PIN_WS2812B 12              // Arduino pin som kobles til WS2812B (led-stripe)
#define NUM_PIXELS 24               // Antall LEDs (pixler) til WS2812B
#define DELAY_INTERVAL 250          // 250ms pause mellom hver piksel
#define LED_PIN 6                   // Arduino pin til neopixel ring
#define LED_COUNT 24                // Antall LED på ringen




Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);


////////////////////
//// VARIABLER /////
////////////////////


// Konstanter som ikke vil endre seg

const int BUTTON_PIN = 7;             // Arduino-pinne koblet til knappens pinne



Servo servo0;
Servo servo1;                         // Opprett servoobjekt for å styre en servo
Servo servo2;
Servo servo3;




// Variabler som vil endre seg:

int lastButtonState = HIGH;           // Forrige tilstand av knapp (start med høy)
int currentButtonState;               // Gjeldende tilstand av knapp
int angle = 0;                        // Gjeldende vinkel på servomotoren
int direction = 1;                    // Retning servo beveger seg i: 1 = fremover, -1 = bakover
int tid_bevegelse = 3000;             // Sekunder på delay
int pos;                              
int sensorValue = A0;
int SENSOR_VAL;
int state = 0;
int randomMove;                       // Variabel som er med på å velge hvilke funksjoner som skal funke i random rekkefølge


////////////////////
////// SETUP ///////
////////////////////


void setup() {
 Serial.begin(9600);                         // Initialiser serial
 Serial.println("Initierer Serial");
 pinMode(BUTTON_PIN, INPUT);                 // Sett arduinopinne til inngang med pull-up motstand
 Serial.println("Initierer knapp");
 servo0.attach(3);                           // Skaut
 Serial.println("Initierer servo skaut");
 servo1.attach(9);                           // Tunge
 Serial.println("Initierer servo tunge");
 servo2.attach(10);                          // Hånd
 Serial.println("Initierer servo hånd");
 servo3.attach(11);                          // Tommel
 Serial.println("Initierer servo tommel");


 WS2812B.begin();                            // Initialiserer kommunikasjonen med LED-ringen
 for(int i=0; i<NUM_PIXELS; i++){
    WS2812B.setPixelColor(i,ring.Color(255,0,255));
    WS2812B.show();
    delay(50);
    }
 Serial.println("Initierer ws2812b");
 ring.begin();                               // Konfigurere LED-ringen
 Serial.println("Initierer ring");
 ring.show();                                // Oppdatere LED-ringen med de siste dataene
 Serial.println("Oppdatere ring");
 ring.setBrightness(50);                     // Setter lysstyrken til LED-ringen
 Serial.println("setter brightness");


}


////////////////////
//// FUNKSJONER ////
////////////////////



void tunge() {                              // Tunge funksjonen som styrer hvordan servoen beveger seg
 servo1.write(180);
 delay(tid_bevegelse);
 servo1.write(0);
 }


 void hand_move(){                          // Hånd funksjonen som styrer hvordan servoen beveger seg
 int count = 5;
 int delayTime = 500;


 for (int i = 0; i < count; i++){
   servo2.write(180);
   delay(delayTime);
   servo2.write(0);
   delay(delayTime);
 }
}



void tommel_opp(){                          // Tommel funksjonen som styrer hvordan servoen beveger seg
 servo3.write(90);
 delay(tid_bevegelse);
 servo3.write(180);
 }


 void led_strip() {                         // Får ledstripen til å lyse    

 int currentButtonState = digitalRead(BUTTON_PIN);


 if (currentButtonState == 0) {

  // Forandrer pikslene til lilla

   for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
     WS2812B.setPixelColor(pixel, WS2812B.Color(0, 0, 150));


     delay(DELAY_INTERVAL); 
     WS2812B.show();
   }


   WS2812B.clear();
   WS2812B.show();

 }
}


void neo_ring(float SENSOR_VAL) {                   // Funksjon for å få Neo Ringen til å lyse i tilkobling til en sensor/trykk
 SENSOR_VAL = analogRead(sensorValue);
 Serial.println(sensorValue);
 while (SENSOR_VAL > 200) {
   for (int i = 0; i < ring.numPixels(); i++) {
     ring.setPixelColor(i, random(255), random(255), random(255), 0);
     ring.show();
     delay(100);
     SENSOR_VAL = analogRead(sensorValue);
   }
 }


 for (int i = ring.numPixels() - 1; i >= 0; i--) {
   ring.setPixelColor(i, 0, 0, 0, 0);
   ring.show();
   delay(100);
 }
}
 

////////////////////
/////// LOOP ///////
////////////////////



void loop() {
 currentButtonState = digitalRead(BUTTON_PIN);          // les ny tilstand av knappen
  int randomMove;
  if (currentButtonState != lastButtonState){
   if (currentButtonState == LOW){
     randomMove = random(3);
   }
 }



 if (currentButtonState == HIGH) {
   Serial.println("Knappen er trykket");
   servo0.write(90);
   delay(1000);
   servo0.write(135);
 
   switch(randomMove){
     case 0:                                   // Funksjon: Damen rekker ut tungen, "vet ikke"
       tunge();
       Serial.println("Tunge");
       break;
     case 1:                                   // Funksjon: Damen beveger på hånden, "nei"
       hand_move();
       Serial.println("hand");
       break;
     case 2:                                   // Funksjon: Damen viser tommel opp, "ja"
       tommel_opp();
       Serial.println("tommel");
       break;
   
   }
 }


 SENSOR_VAL = analogRead(sensorValue);
 Serial.println(SENSOR_VAL);
 currentButtonState = digitalRead(BUTTON_PIN);


  if(SENSOR_VAL>=500){
    Serial.print("LED_statement");
    for(int i=0; i<LED_COUNT; i++){
    ring.clear();
    ring.show();
    ring.setPixelColor(i,ring.Color(150,255,0));
    ring.show();
    delay(50);
    }
  }

}
