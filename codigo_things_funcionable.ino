#include <WiFi.h>
#include <HTTPClient.h>

// Configuraciones de WiFi
const char* ssid = "Sarita17";
const char* password = "333759777492";

// Configuración de ThingSpeak
const char* apiKey = "G06J83ZW275QM4HS";  // Copia aquí tu API Key
const char* server = "https://api.thingspeak.com/update?api_key=G06J83ZW275QM4HS&field1=0";

// Pines de los sensores
const int pirPin = 32;       // Sensor PIR en GPIO 32
const int lm35Pin = 33;      // Sensor LM35 en GPIO 33 (entrada analógica)
const int hallPin = 34;      // Sensor de efecto Hall en GPIO 34 (entrada analógica)

// Variables para los datos
int pirState = 0;            // Estado del sensor PIR (movimiento detectado o no)
float temperatura = 0.0;     // Temperatura leída del sensor LM35
int hallValue = 0;           // Valor del sensor de efecto Hall

void setup() {
  Serial.begin(115200);

  // Configuración de los pines
  pinMode(pirPin, INPUT);
  pinMode(lm35Pin, INPUT);
  pinMode(hallPin, INPUT);

  // Conectar al WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando al WiFi...");
  }
  Serial.println("Conectado al WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {  // Verifica si está conectado a WiFi

    // Leer el estado del sensor PIR (movimiento)
    pirState = digitalRead(pirPin);  // El valor es HIGH (1) si detecta movimiento, LOW (0) si no detecta

    // Leer los datos del sensor LM35 (temperatura)
    int lm35Value = analogRead(lm35Pin);  // Lee el valor analógico del sensor
    temperatura = (lm35Value * 3.3 / 4095) * 100;  // Convierte el valor leído en grados Celsius

    // Leer el valor del sensor de efecto Hall
    hallValue = analogRead(hallPin);  // Lee el valor analógico del sensor

    // Mostrar valores en el puerto serial
    Serial.println("Lectura de sensores:");
    Serial.println("Sensor PIR (movimiento): " + String(pirState));
    Serial.println("Temperatura (LM35): " + String(temperatura) + " °C");
    Serial.println("Valor del sensor de efecto Hall: " + String(hallValue));
    Serial.println("-----------------------------");

    // Crear la URL para enviar los datos a ThingSpeak
    HTTPClient http;
    String url = String(server) + "&field1=" + String(pirState) +        // Estado del sensor PIR
                 "&field2=" + String(temperatura) +                      // Temperatura del LM35
                 "&field3=" + String(hallValue);                         // Valor del sensor de efecto Hall
    
    http.begin(url);  // Inicia la conexión a ThingSpeak
    int httpResponseCode = http.GET();  // Realiza la solicitud GET
    
    if (httpResponseCode > 0) {
      String response = http.getString();  // Lee la respuesta del servidor
      Serial.println("Datos enviados a ThingSpeak: " + String(httpResponseCode));
      Serial.println("Respuesta: " + response);
    } else {
      Serial.println("Error enviando los datos: " + String(httpResponseCode));
    }
    
    http.end();  // Termina la conexión
  }
  
  delay(20000);  // Espera 20 segundos antes de enviar el próximo dato
}
