#include <Arduino.h>

const int botao = 3;
const int led_verde = 2;
const int led_amarelo = 4;
const int led_vermelho = 5;

bool sistema = false; // Indica se o semáforo deve estar funcionando

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(led_verde, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  // Garante que todos os LEDs estejam desligados no início
  digitalWrite(led_verde, LOW);
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_vermelho, LOW);
}

void loop() {
  // Leitura do botão: Se o botão for pressionado, inverte o estado do sistema.
  // Adicionei um pequeno delay aqui para "debouncing" do botão,
  // evitando múltiplas inversões com um único toque rápido.
  if (!digitalRead(botao)) {
    delay(50); // Pequeno atraso para debouncing
    while (!digitalRead(botao)); // Espera o botão ser solto
    sistema = !sistema; // Inverte o estado do sistema
    // Se o sistema for desligado, apaga todos os LEDs imediatamente
    if (!sistema) {
      digitalWrite(led_verde, LOW);
      digitalWrite(led_amarelo, LOW);
      digitalWrite(led_vermelho, LOW);
    }
  }

  // Lógica do semáforo
  if (sistema) {
    // Ciclo Verde
    digitalWrite(led_verde, HIGH);
    // Verifica o botão a cada 100ms durante o tempo do LED verde
    for (int i = 0; i < 20; i++) { // 20 * 100ms = 2000ms (2 segundos)
      delay(100);
      if (!digitalRead(botao)) { // Se o botão for pressionado, desliga e sai
        delay(50); // Debouncing
        while (!digitalRead(botao));
        sistema = false;
        digitalWrite(led_verde, LOW);
        digitalWrite(led_amarelo, LOW);
        digitalWrite(led_vermelho, LOW);
        return; // Sai da função loop para recomeçar
      }
    }
    digitalWrite(led_verde, LOW);

    // Se o sistema foi desligado enquanto o verde estava aceso, não continua para amarelo/vermelho
    if (!sistema) return;

    // Ciclo Amarelo
    digitalWrite(led_amarelo, HIGH);
    // Verifica o botão a cada 100ms durante o tempo do LED amarelo
    for (int i = 0; i < 10; i++) { // 10 * 100ms = 1000ms (1 segundo)
      delay(100);
      if (!digitalRead(botao)) { // Se o botão for pressionado, desliga e sai
        delay(50); // Debouncing
        while (!digitalRead(botao));
        sistema = false;
        digitalWrite(led_verde, LOW);
        digitalWrite(led_amarelo, LOW);
        digitalWrite(led_vermelho, LOW);
        return; // Sai da função loop para recomeçar
      }
    }
    digitalWrite(led_amarelo, LOW);

    // Se o sistema foi desligado enquanto o amarelo estava aceso, não continua para vermelho
    if (!sistema) return;

    // Ciclo Vermelho
    digitalWrite(led_vermelho, HIGH);
    // Verifica o botão a cada 100ms durante o tempo do LED vermelho
    for (int i = 0; i < 30; i++) { // 30 * 100ms = 3000ms (3 segundos)
      delay(100);
      if (!digitalRead(botao)) { // Se o botão for pressionado, desliga e sai
        delay(50); // Debouncing
        while (!digitalRead(botao));
        sistema = false;
        digitalWrite(led_verde, LOW);
        digitalWrite(led_amarelo, LOW);
        digitalWrite(led_vermelho, LOW);
        return; // Sai da função loop para recomeçar
      }
    }
    digitalWrite(led_vermelho, LOW);
  }
}