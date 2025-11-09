#include <Arduino.h>



//declaração de variáveis
const int botao = 3;
const int led_verde = 2;
const int led_amarelo = 4;
const int led_vermelho = 5;

//variavel auxiliar
bool sistema = false;

void setup()
{

  //configuração das entrada e saídas
  pinMode(botao,INPUT_PULLUP);
  pinMode(led_verde,OUTPUT);
  pinMode(led_amarelo,OUTPUT);
  pinMode(led_vermelho,OUTPUT);

}

void loop()
{

  //se o botao estiver pressionado (digitalRead(botao) = 0) liga o sistema
  if(!digitalRead(botao)){
  	sistema = !sistema;
  }

  //se o sistema estiver ligado (sistema = 1), executa a logica do semaforo
  if(sistema){
    //liga o led verde
  	digitalWrite(led_verde,HIGH);

    //espera 2000 milisegundo (2s)
    delay(2000);

    //desliga o led verde
    digitalWrite(led_verde,LOW);
    
    digitalWrite(led_amarelo,HIGH);
    delay(1000);
    digitalWrite(led_amarelo,LOW);
    
    digitalWrite(led_vermelho,HIGH);
    delay(3000);
    digitalWrite(led_vermelho,LOW);
  }
}