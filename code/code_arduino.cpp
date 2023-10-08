#define MIC_PIN A0 // Pino do microfone
#define LED_START_PIN 3 // Pino onde começa a barra de LEDs
#define NUM_LEDS 10 // Número de LEDs na barra
#define DECIBELS_PER_LED 4 // Quantidade de decibéis por LED

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_START_PIN + i, OUTPUT);
    digitalWrite(LED_START_PIN + i, LOW); // Desliga todos os LEDs no início
  }
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  int noiseLevel = analogRead(MIC_PIN); // Lê o nível de ruído do microfone
  int mappedLevel = map(noiseLevel, 0, 1023, 0, 100); // Mapeia o valor lido para uma escala de 0 a 100

  // Calcula quantos LEDs devem ser acesos com base no nível de ruído
  int numLedsToLight = mappedLevel / DECIBELS_PER_LED;

  // Limita o número de LEDs acesos para não ultrapassar 10 e o máximo de 40 decibéis
  numLedsToLight = constrain(numLedsToLight, 0, 10); // Limite para não ultrapassar 10 LEDs
  if (numLedsToLight * DECIBELS_PER_LED > 40) {
    numLedsToLight = 40 / DECIBELS_PER_LED; // Limite para não ultrapassar 40 decibéis
  }

  // Atualiza a barra gráfica de LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < numLedsToLight) {
      digitalWrite(LED_START_PIN + i, HIGH); // Acende o LED
    } else {
      digitalWrite(LED_START_PIN + i, LOW); // Apaga o LED
    }
  }

  delay(100); // Aguarda um curto período antes de ler novamente o nível de ruído
}
