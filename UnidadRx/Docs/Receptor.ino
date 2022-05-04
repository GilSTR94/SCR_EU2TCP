#include <WiFi.h>

const char *ssid = "INFINITUM144F_2.4";
const char *password = "yfCtu7MuHT";

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

const IPAddress serverIP(127,0,0,1); // La dirección que desea visitar
uint16_t serverPort = 20064;         // Número de puerto del servidor

WiFiClient client; // Declarar un objeto cliente para conectarse al servidor

void setup()
{
    Serial.begin(115200);
    Serial.println();

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); // Desactiva la suspensión de wifi en modo STA para mejorar la velocidad de respuesta
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());
}

void loop()
{
    Serial.println("Intenta acceder al servidor");
    if (client.connect(serverIP, serverPort)) // Intenta acceder a la dirección de destino
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
