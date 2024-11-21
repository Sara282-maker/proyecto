
const int temperatura = 35;
const int movimiento = 33;
const int magnetico = 32;
const int pinLED =2;

void setup(){
Serial.begin(9600);
pinMode(movimiento,INPUT);
pinMode(magnetico,INPUT);

}

void loop(){
  int valortemperatura= analogRead(temperatura);
  int valormovimiento= digitalRead(movimiento);
  int valormagnetico= digitalRead(magnetico);

float voltage = valortemperatura * (3.3 / 4095.0); // Convertir el valor analógico a voltaje
  
  // El LM35 produce 10 mV por grado Celsius
  float temperature = (voltage * 100); // Convertir voltios a grados Celsius

    // Si detecta movimiento, encender el LED y enviar un mensaje
  if (valormovimiento == HIGH) {
    Serial.println("Movimiento detectado");
    Serial.println(valormovimiento);
    digitalWrite(pinLED, HIGH);  // Encender el LED
  } else {
    Serial.println("No se detecta movimiento");
    digitalWrite(pinLED, LOW);   // Apagar el LED
  }
  // Esperar un poco antes de la siguiente lectura

// Verificar si se detecta un campo magnético
  if (valormagnetico == HIGH) {
    Serial.println("No se detecta campo magnético");
  } else {
    Serial.println("Campo magnético detectado");
  }

  // Pequeña pausa antes de la siguiente lectura
delay(1000);
}



