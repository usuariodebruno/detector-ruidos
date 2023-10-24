// Inclui a biblioteca File
#include <SD.h>

// Cria as constantes para os pinos do Arduino
const int microphonePin = A0; //pino analógico MIC - Braco
const int ledPins[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; //pinos digitais conectados aos LEDs

// Cria uma constante para o nome do arquivo
const char *filename = "dados.txt";

// Declara as variáveis
int analogValue;              //leitura analogica
float volts;                  //tensão medida
float dB;                     //valor em decibéis
int ledsOn = 0;               //número de LEDs acesos

// Configura os pinos do Arduino
void setup() {
  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
    pinMode(ledPins[i], OUTPUT); //pinos dos LEDs como saída
  }
  Serial.begin(9600);         //comunicação serial para monitoramento (opcional)
}

// Loop principal
void loop() {
  // Lê o valor do sensor de som pelo MIC
  analogValue = analogRead(microphonePin);

  // Converte o valor analógico em volts (5V)
  volts = analogValue * (5.0 / 1023.0);

  // Calcula o valor em decibéis (verificar calibração sempre)
  // Cálculo aproximado, pode variar dependendo das características do sensor de som
  dB = 20 * log10(volts / 0.0063);

  // Calcula o número de LEDs a serem acesos
  ledsOn = (dB / 4) + 1;

  // Acende os LEDs
  for (int i = 0; i < ledsOn; i++) {
    digitalWrite(ledPins[i], HIGH);
  }

  // Mostra o valor em decibéis no monitor serial
  Serial.print("Valor em dB: ");
  Serial.println(dB);

  /* 
  // Create a File object using the SD class
  File file = SD.open(filename, FILE_WRITE);
  
  if (file) {  // Check if the file was opened successfully
    // Write the value to the file
    file.print(dB);
    file.print("\n");
  
    // Close the file
    file.close();
  } else {
    // Handle error opening the file
    Serial.println("Erro ao abrir o arquivo");
  }

  */
  
  delay(1000);
}
