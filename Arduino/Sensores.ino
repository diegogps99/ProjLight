#include <DHT.h>

// Pino dosensor de temperatura
#define DHTPIN 2        
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

// pino do sensor de presença
int pirPin = 3;

// inicializa o estado do pino
int pirState = LOW;

// pinos referente a 8 relés
int relays[] = {4, 5, 6, 7, 8, 9, 10, 11}; 

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(pirPin, INPUT);
  
  for (int i = 0; i < 8; i++) {
    pinMode(relays[i], OUTPUT);

    // inicialização das lampadas quando estão apagadas.
    digitalWrite(relays[i], LOW); 
  }
}

void loop() {

    //Verificação do estado do sensor
    pirState = digitalRead(pirPin);
    float temp = dht.readTemperature();
  
    // Enviar os dados dos sensores para o arquivo de ´Automação.py´
    Serial.print("PIR:");
    Serial.print(pirState);
    Serial.print(",TEMP:");
    Serial.println(temp);

    // Verificação do Comando de Automação
    if (Serial.available() > 0) {
        
        String command = Serial.readStringUntil('\n');
        int relayIndex = command.substring(0, 1).toInt();
        String state = command.substring(1);
    
        if (relayIndex >= 0 && relayIndex < 8) {
            if (state == "ON") {
                digitalWrite(relays[relayIndex], HIGH);
            } else if (state == "OFF") {
                digitalWrite(relays[relayIndex], LOW);
            }
        }
    }
    // Intervalo de Leitura
    
  delay(1000);
}