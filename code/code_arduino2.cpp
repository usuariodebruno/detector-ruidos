const int microphonePin = A0; //pino analógico MIC - Braco
const int ledPin = 2;         //pino digital conectado ao LED - Amarelo

int threshold = 40;           //valor limiar em decibeis (NBR 10152 da ABNT)
int analogValue;              //leitura analogica
float volts;                  //tensão medida
float dB;                     //valor em decibéis

void setup() {
  pinMode(ledPin, OUTPUT);    //pino do LED como saída
  Serial.begin(9600);         //comunicação serial para monitoramento (opcional)
}

void loop() {
  analogValue = analogRead(microphonePin);   //lê o valor do sensor de som pelo MIC

  //convertendo o valor analógico em volts (5V)
  volts = analogValue * (5.0 / 1023.0);

  //calculo do valor em decibéis (verificar calibração sempre)
  //calculo aproximado, pode variar dependendo das características do sensor de som
  dB = 20 * log10(volts / 0.0063);

  if (dB > threshold) {
    digitalWrite(ledPin, HIGH);  //acende o LED som acima do permitido
  } else {
    digitalWrite(ledPin, LOW);   //apaga o LED se o som for menor
  }

  //exibe o valor em decibéis no monitor serial para monitoramento
  //para painel degital
  Serial.print("Valor em dB: ");
  Serial.println(dB);

  delay(100);  //pequeno atraso para evitar leituras rápidas demais
}
