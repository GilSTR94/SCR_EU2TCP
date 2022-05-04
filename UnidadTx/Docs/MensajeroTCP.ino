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

const IPAddress serverIP(189,202,79,700); // La dirección que desea visitar
uint16_t serverPort = 20064;         // Número de puerto del servidor
WiFiClient client; // Declarar un objeto cliente para conectarse al servidor

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
    Serial.println("Intenta acceder al servidor");
    if (client.connect(serverIP, serverPort)) // Intenta acceder a la dirección de destino
    {
        Serial.println("Visita exitosa");

        client.print("Hello world!");                    // Enviar datos al servidor
        while (client.connected() || client.available()) // Si está conectado
        {
            if (client.connected()) // Si estamos conectados
            {
                last_button_state = button_state; 
                button_state = digitalRead(BUTTON_PIN);
                if (last_button_state == HIGH && button_state == LOW)
                {
                    Serial.println("Si jala el boton"); 
                    led_state = !led_state;
                    digitalWrite(LED_PIN, led_state);
                    client.print("1");
                } 
            }
        }
        Serial.println("Cerrar la conexión actual");
        client.stop(); // Cerrar el cliente
    }
    else
    {
        Serial.println("Acceso fallido");
        client.stop(); // Cerrar el cliente
    }
    delay(5000);
}
