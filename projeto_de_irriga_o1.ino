#include <Wire.h>
#include <LiquidCrystal_I2C.h>


/*
  PROJETO DE IRRIGAÇÃO AUTOMÁTICA

  Aluno: Luis Fernando dos Santos Faria
  Professor: Rodrigo Grassi Martins
  Instituição: Instituto Federal de Educação, Ciência e Tecnologia do Triângulo Mineiro - Campus Ituiutaba

  Descrição:
    Este código faz parte de um projeto de um polo de ensino da rede IF.
    Ele roda em um Arduino Uno e automatiza a irrigação de plantas em viveiros,
    jardins e orquidários (plantas cujas raízes ficam embaixo da terra).
    A irrigação é feita com uma bomba e circuitos montados para esse fim.

  Este é o código que será gravado no Arduino Uno.
*/


// RELE
#define PINO_RELE  8
// SENSOR DE UMIDADE
#define ALIMENTACAO_SENSOR 7
#define PINO_SENSOR A0

// CONSTANTES
#define SOLO_SECO 200
#define SOLO_UMIDO 1023
#define LIMITE_UMIDADE 45
#define INTERVALO_LEITURA 1000
#define ATRASO_LETRA 80

LiquidCrystal_I2C lcd(0x27, 16, 2);
bool sistemaLigado = true;
unsigned long ultimaLeitura = 0;

void escreverLento(const char* texto, int coluna, int linha, int atraso) {
  lcd.setCursor(coluna, linha);
  for (int i = 0; texto[i] != '\0'; i++) {
    lcd.print(texto[i]);
    delay(atraso);
  }
}

void setup() {
  Serial.begin(9600);
  // Cofiguração inicial
  pinMode(PINO_RELE, OUTPUT);
  pinMode(ALIMENTACAO_SENSOR, OUTPUT);
  digitalWrite(PINO_RELE, LOW);
  digitalWrite(ALIMENTACAO_SENSOR, LOW);
  lcd.init();
  lcd.backlight();
  escreverLento("IFTM - CC 2o", 0, 0, ATRASO_LETRA);
  escreverLento("P.I.E II", 0, 1, ATRASO_LETRA);
  delay(2000);
  lcd.clear();
  escreverLento("l/L p/ Ligar", 0, 0, ATRASO_LETRA);
  escreverLento("d/D p/ Desligar", 0, 1, ATRASO_LETRA);
  delay(2000);
  lcd.clear();
}

int lerSensorUmidade() {
  digitalWrite(ALIMENTACAO_SENSOR, HIGH);// Ligo o sensor
  delay(150);
  int valorLeitura = analogRead(PINO_SENSOR);
  digitalWrite(ALIMENTACAO_SENSOR, LOW); // Posso desligar o sensor já, pois a leitura ja foi feita
  valorLeitura = map(valorLeitura, SOLO_SECO, SOLO_UMIDO, 0, 100);
  valorLeitura = constrain(valorLeitura, 0, 100);
  return valorLeitura;
}

void mostrarLeitura(int umidadeLoc) {
  lcd.setCursor(0, 1);
  lcd.print("Umidade: ");
  lcd.print(umidadeLoc);
  lcd.print("%   ");
}

void lerComandoSerial() {
  while (Serial.available() > 0) {
    char comando = Serial.read();
    if (comando == 'l' || comando == 'L') {
      sistemaLigado = true;
      ultimaLeitura = millis() - INTERVALO_LEITURA;
      Serial.println("Sistema LIGADO");
    } else if (comando == 'd' || comando == 'D') {
      sistemaLigado = false;
      digitalWrite(PINO_RELE, LOW);
      lcd.setCursor(0, 0);
      lcd.print("Sistema         ");
      lcd.setCursor(0, 1);
      lcd.print("Desligado      ");
      Serial.println("Sistema DESLIGADO");
    }
  }
}

void loop() {
  lerComandoSerial();

  if (!sistemaLigado) {
    return;
  }

  unsigned long agora = millis();
  if (agora - ultimaLeitura >= INTERVALO_LEITURA) {
    ultimaLeitura = agora;

    int umidadeLoc = lerSensorUmidade();
    lcd.clear();
    mostrarLeitura(umidadeLoc);

    if (umidadeLoc <= LIMITE_UMIDADE) {
      digitalWrite(PINO_RELE, HIGH);
    } else {
      digitalWrite(PINO_RELE, LOW);
    }
  }
}