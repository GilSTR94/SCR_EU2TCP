#include <WiFi.h>

const char* ssid = "INFINITUM144F_2.4";
const char* password = "yfCtu7MuHT";

#define LED_PIN 23
int led_state = LOW;

#if defined(LED_BUILTIN)
  const int led =  LED_BUILTIN;
#else
  #if (ESP32)
    // Using pin 13 will crash ESP32_C3
    const int led =  2;
  #else
    const int led =  13;
  #endif
#endif

const char* server = "192.168.1.78"; //Enter server adress
const uint16_t port = 4200; // Enter server portippip 
uint64_t messageTimestamp;      // Número de puerto del servidor

WiFiClient client; // Declarar un objeto cliente para conectarse al servidor

void setup()
{
    Serial.begin(115200);
    Serial.println();

   delay(10);
   Serial.println("");
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   { 
     delay(100);  
     Serial.print('.'); 
   }
   Serial.println("");
   Serial.print("Iniciado STA:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t");
   Serial.println(WiFi.localIP());
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    Serial.println("Intenta acceder al servidor");
    if (client.connect(server, port)) // Intenta acceder a la dirección de destino
    {
        Serial.println("Visita exitosa");

        client.print("Hello world!");                    // Enviar datos al servidor
        while (client.connected() || client.available()) // Si está conectado o se han recibido datos no leídos
        {
            if (client.available()) // Si hay datos para leer
            {
                String line = client.readStringUntil('\n'); // Leer datos a nueva línea
                Serial.print("Leer datos:");
                Serial.println(line);
                digitalWrite(led, 0);
                digitalWrite(led, 1);
                led_state = !led_state;
                digitalWrite(LED_PIN, led_state);
                
                client.write(line.c_str()); // Devuelve los datos recibidos
                
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
