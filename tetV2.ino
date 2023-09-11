#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Adafruit_DotStar.h>
#include <EEPROM.h> 
#define DATAPIN    23
#define CLOCKPIN   22
#define led 90
#define WLAN_SSID       "Bbox-A3E72FC8"             // Your SSID
#define WLAN_PASS       "fjnzJ6ANXdFJC7194b"        // Your password


int NUMPIXELS = 90;
int num,nums = 1;
int nb = 1;
int BEGIN = 0;
int wait = 0;
String next,previous;
int Bright = 0;
int r,g,b = 0;
int i = 1;
/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "unknow0441"            // Replace it with your username
#define AIO_KEY         "aio_XWdh309ubEh0qCQbkwxptBfPq5Zp"   // Replace with your Project Auth Key

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe Mode = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/mode");

void setup() {
  Serial.begin(115200);
  EEPROM.commit();
  strip.begin(); // Initialize pins for output
  strip.setBrightness(Bright);
  strip.show();  // Turn all LEDs off AS
  pinMode(5, OUTPUT);
  pinMode(0, OUTPUT);

  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);

    delay( 100 ); // power-up safety delay
  
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  digitalWrite(led,LOW);

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&Mode);

  for (Bright = 0; Bright <= 80; Bright++){
    strip.setBrightness(Bright);
    for (int i = BEGIN; i <= NUMPIXELS; i++){
       strip.setPixelColor(i, 255, 255, 255);
       delay(1);  // Pause for a moment
      }
      strip.show(); // Update strip with new contents

  }
}

void loop() {
 
  MQTT_connect();
 Adafruit_MQTT_Subscribe *subscription;
  
  while ((subscription = mqtt.readSubscription(2))) {
   Serial.print("test");
    if (subscription == &Mode) {
      Serial.print("Mode > ");
      Serial.print(F("Got: "));
      Serial.println((char *)Mode.lastread);
      byte Mode1_state = atoi((char *)Mode.lastread);
      next = ((char *)Mode.lastread);
      ModeChange();
    }
  }
 
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    //Serial.println("Connected");
    return;
  }

  digitalWrite(led,HIGH);
  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      //while (1);
      Serial.println("Wait 10 min to reconnect");
      delay(600000);
    }
  }
  Serial.println("MQTT Connected!");
  digitalWrite(led,LOW);
}



void ModeChange(){
  Serial.println(next);
  if (next == "Off" or next == "off"){
    r = 0;
    g = 0;
    b = 0; 
    wait = 10;
   couleursimple(wait);  
     }
  else if (next == "en arc en ciel" or next == "Arc en ciel" or next == "Arc-en-ciel" or next == "arc - en - ciel"){
   rainbow(10);        
  }
  else if (next == "en rouge" or next == "rouge"){
    r = 255;
    g = 0;
    b = 0; 
    wait = 10;
   couleursimple(wait);        
  }
  else if (next == "en bleu" or next == "bleu" or next == "quatre" or next == "4"){
    r = 0;
    g = 0;
    b = 255; 
    wait = 10;
   couleursimple(wait);        
  }
  else if (next == "en vert" or next == "vert" or next == "cinq" or next == "5" or next == "verre"){
    r = 0;
    g = 255;
    b = 0;  
    wait = 10;
   couleursimple(wait);        
  }
  else if (next == "en blanc" or next == "blanc" or next == "six" or next == "6"){
    r = 255;
    g = 255;
    b = 255; 
    wait = 10;
   couleursimple(wait);        
  }
  else if (next == "en noir" or next == "noir" or next == "sept" or next == "7"){
    r = 0;
    g = 0;
    b = 0; 
    wait = 10;
   couleursimple(wait);        
  }
  else if (next == "en gris" or next == "gris" or next == "huit" or next == "8"){
    r = 128;
    g = 128;
    b = 128;
    wait = 10; 
   couleursimple(wait);        
  }
  else if (next == "magenta" or next == "en magenta" or next == "Fushia" or next == "fushia" or next == "neuf" or next == "9"){
    r = 255;
    g = 0;
    b = 255;
    wait = 10; 
   couleursimple(wait);        
  }
  else if (next == "violet" or next == "en violet" or next == "dix" or next == "10"){
    r = 128;
    g = 0;
    b = 128;
    wait = 10; 
   couleursimple(wait);        
  }
  else if (next == "bordeaux" or next == "en bordeaux" or next == "en Bordeaux" or next == "Bordeaux" or next == "onze" or next == "11"){
    r = 128;
    g = 0;
    b = 0;
    wait = 10; 
   couleursimple(wait);        
  }
  else if (next == "jaune" or next == "en jaune" or next == "douze" or next == "12"){
    r = 255;
    g = 255;
    b = 0;
    wait = 10; 
   couleursimple(wait);        
  }
  else if (next == "cyan" or next == "en cyan" or next == "treize" or next == "13"){
    r = 0;
    g = 255;
    b = 255;
    wait = 10; 
   couleursimple(wait);        
  }
  else if (next == "orange" or next == "en orange" or next == "quatorze" or next == "14"){
    r = 255;
    g = 128;
    b = 0;
    wait = 10; 
   couleursimple(wait); 
          
  }
  else if(next == "défilé" or next == "en défilé" or next == "15"){
    defile();
  }
  else if(next == "en pong" or next == "pong" or next == "kong" or next == "Kong" or next == "en 16" or next == "16"){
    pong();
  }
  else if(next == "fillcenter" or next == "en fillcenter" or next == "en fil Center" or next == "en Fil Center" or next == "dix-sept" or next == "17"){
    fillcenter();
  }
  else if(next == "Aleatoire" or next == "Aléatoire" or next == "aleatoire" or next == "aléatoire"){
    alea(); 
  }
  else if(next == "choix" or next == "Choix" or next == "choi" or next == "Choi"){
    fullalea(); 
  }
  else if(next == "1"){
    nb=1;
  }
  else if(next == "2"){
    nb = 2 ;
  }
  else if(next == "10 %"){
    strip.setBrightness(10);
    strip.show(); 
  }
  else if(next == "20 %"){
    strip.setBrightness(20);
    strip.show();
  }
  else if(next == "30 %"){
    strip.setBrightness(30);
    strip.show();
  }
  else if(next == "40 %"){
    strip.setBrightness(40);
    strip.show();
  }
  else if(next == "50 %"){
    strip.setBrightness(50);
    strip.show();
  }
  else if(next == "60 %"){
    strip.setBrightness(60);
    strip.show();
  }
  else if(next == "70 %"){
    strip.setBrightness(70);
    strip.show();
  }
  else if(next == "80 %"){
    strip.setBrightness(80);
    strip.show();
  }
  else if(next == "90 %"){
    strip.setBrightness(90);
    strip.show();
  }
  else if(next == "100 %"){
    strip.setBrightness(100);
    strip.show();
  }
  

  
  else{
    previous = next ;
    for (int i = 0; i <= 3; i++){
      r = 255;
      g = 255;
      b = 255; 
      delay(200);
      erreur(); 
      strip.show(); 
      r = 0;
      g = 0;
      b = 0; 
      delay(200);
      erreur(); 
      strip.show(); 
  }
   r = 128;
   g = 128;
   b = 128;
   couleursimple(wait); 
}
}
void alea(){
  r = random(0, 255);
  g = random(0, 255);
  b = random(0, 255);
  couleursimple(20); 
}
void fullalea(){
  for(int i =0;i<=NUMPIXELS;i = i +nb){
    r = random(0, 255);
    g = random(0, 255);
    b = random(0, 255);
    strip.setPixelColor(i, g, r, b);
    strip.show(); // Update strip with new contents
    delay(20);  // Pause for a moment
  }
}


void pong(){
  for (int i = BEGIN; i <= NUMPIXELS; i++){
     strip.setPixelColor(i, 255, 255, 0);
     strip.setPixelColor(i-2, 0, 0, 0);
     strip.show(); // Update strip with new contents
     delay(30);  // Pause for a moment

  }
  for (int i = NUMPIXELS; i >= BEGIN; i--){
     strip.setPixelColor(i, 255, 255, 0);
     strip.setPixelColor(i+2, 0, 0, 0);
     strip.show(); // Update strip with new contents
     delay(30);  // Pause for a moment
  }
  
}

void defile(){
      for (int i = 0; i <= 2; i = i +nb){
        r = 0;
        g = 0;
        b = 0;
        r = 255;
        wait = 20;
        couleursimple(wait); 
        delay(NUMPIXELS * wait);  
        r = 0;
        couleursimple(wait);
        delay(NUMPIXELS * wait);  
        g = 255;
        couleursimple(wait);
        delay(NUMPIXELS * wait);
        g = 0;
        couleursimple(wait);
        delay(NUMPIXELS * wait); 
        b = 255;
        couleursimple(wait);
        delay(NUMPIXELS * wait);
        b = 0;
        couleursimple(wait);
        delay(NUMPIXELS * wait);
      }
}


void erreur(){
   for (int i = BEGIN; i <= NUMPIXELS; i = i +nb){
    strip.setPixelColor(i, g, r, b);
    delay(10);  // Pause for a moment
   }
}



void couleursimple(int wait){
  i = 1;
   for (int i = BEGIN; i <= NUMPIXELS; i = i +nb){
    Serial.print(BEGIN);
    strip.setPixelColor(i, g, r, b);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
   }
   
}

void fillcenter(){
  int center = NUMPIXELS/2;
  int imin = center;
  int imax = center;
  strip.setPixelColor(center, 0, 255, 0);
  do{
    imax++;
    imin--;
    strip.setPixelColor(imax, 128, 128, 128);
    strip.setPixelColor(imin, 128, 128, 128);
    strip.show(); // Update strip with new contents
    delay(100);  // Pause for a moment
  }while(imin >=0);
  do{

    strip.setPixelColor(imax, 0, 0, 0);
    strip.show(); // Update strip with new contents
    strip.setPixelColor(imin, 0, 0, 0);
    strip.show(); // Update strip with new contents
    delay(100);  // Pause for a moment
        imax--;
    imin++;
  }while(imin <= NUMPIXELS);

   
}
void rainbow(int wait) {

    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
      for(int i=BEGIN; i<strip.numPixels(); i++) { // For each pixel in strip...     
       int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
     } 
     strip.show(); // Update strip with new contents
     delay(wait);  // Pause for a moment
     
   }
}
