/*
 *  This sketch sends a message to a TCP server
 *
 */
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;

#define BUTTON_PIN 4
#define LED_PIN 23
int led_state = LOW;
int button_state;
int last_button_state;

void setup()
{
    pinMode(2,OUTPUT);
    Serial.begin(115200); delay(10);
  
    // We start by connecting to a WiFi network
    WiFiMulti.addAP("Totalplay-FF9F_EXT", "FF9FB2592NZjUNvN");
    Serial.println(); Serial.println(); Serial.print("Waiting for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) 
    {
        Serial.print("."); delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(500);
    
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    button_state = digitalRead(BUTTON_PIN);
}

void loop()
{
    digitalWrite(2,HIGH);
    delay(100);
    digitalWrite(2,LOW);
    delay(100);
    Serial.println("Si jala la pantalla");
//  const uint16_t port = 80;
//  const char * host = "192.168.1.1"; // ip or dns
    const uint16_t port = 20064;
    const char * host = "127.0.0.1"; // ip or dns

    Serial.print("Connecting to "); Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (!client.connect(host, port)) 
    {
        Serial.println("Connection failed.");
        Serial.println("Waiting 5 seconds before retrying...");
        delay(5000); return;
    }

  last_button_state = button_state; 
  button_state = digitalRead(BUTTON_PIN);
  if (last_button_state == HIGH && button_state == LOW)
  {
    Serial.println("Si jala el boton"); 
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state);
    //This will send a request to the server
    client.print("1");
  } 
  int maxloops = 0;
  //wait for the server's reply to become available
  while (!client.available() && maxloops < 1000)
  {
    maxloops++;
    delay(1); //delay 1 msec
  }
  if (client.available() > 0)
  {
    //read back one line from the server
    String line = client.readStringUntil('\r'); Serial.println(line);
  }
  else
  {
    Serial.println("client.available() timed out ");
  }

    Serial.println("Closing connection."); client.stop();

    Serial.println("Waiting 5 seconds before restarting..."); delay(5000);
}
