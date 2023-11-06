// Código para jogo no estilo "Simon Says"
// O jogo irá piscar determinados leds em uma determina ordem
// O jogador/player deverá acompanhar o jogo apertando os botões que correspondem aos determinados leds e suas respectivas ordens

// Diretivas de portas do ESP32 para leds e botões
#define LED_VERM 16
#define LED_AMAR 17
#define LED_VERD 21
#define LED_AZUL 22

#define BOTAO_VERM 33
#define BOTAO_AMAR 32
#define BOTAO_VERD 35
#define BOTAO_AZUL 34
#define BOTAO_RESET 27

// Listas para salvar as portas dos leds e dos botões
int leds[4] = {LED_VERM, LED_AMAR, LED_VERD, LED_AZUL};
int botoes[4] = {BOTAO_VERM, BOTAO_AMAR, BOTAO_VERD, BOTAO_AZUL};

int numeroDeNiveis = 4; // Numero de níveis contidos no jogo (cada nível acrescenta um led à sequência)
int nivel = 0; // Definição do nível inicial como 0
int i = 0; // Variável para ser usada em loops "for"

int sequenciaLeds[4]; // Lista para salvar sequência de leds definida pelo programa
int sequenciaBotoes[4]; // Lista para salvar sequência de botões definido pelo programa
int sequenciaPlayer[4]; // Lista para salvar sequência definida pelo player



void criaSequencia(){ // Define sequência de leds criada pelo programa

  nivel = 1; // Definição de nível 1 para indicar início do jogo

  for(i = 0; i < 4; i++){ //Gera ordem de leds aleatória
    sequenciaLeds[i] = leds[random(4)];
  };

  for(i = 0; i < 4; i++){ //Converte ordem de leds para ordem de botões
    if (sequenciaLeds[i] == LED_VERM){
      sequenciaBotoes[i] = BOTAO_VERM;
    } else if(sequenciaLeds[i] == LED_AMAR){
      sequenciaBotoes[i] = BOTAO_AMAR;
    } else if(sequenciaLeds[i] == LED_VERD){
      sequenciaBotoes[i] = BOTAO_VERD;
    } else {
      sequenciaBotoes[i] = BOTAO_AZUL;
    }
  };

  delay(1000); // Tempo de espera em ms antes da sequência ser exibida
}



void exibeSequencia(){ //Acende led(s) na sequência defiida pelo programa

  for(i=0; i < nivel; i++){ 
    digitalWrite(sequenciaLeds[i], HIGH);
    delay(500);
    digitalWrite(sequenciaLeds[i], LOW);
    delay(500);
  }

  delay(200); // Tempo de espera em ms antes de captar a sequência definida pelo player
}



void captaSequenciaPlayer() { // Capta a sequência de botões definida pelo player

  int index_player = 0; // Variável para manter o loop funcionando de acordo com o nível

  while (index_player < nivel) {
    for (i = 0; i < 4; i++) {
      if (digitalRead(botoes[i]) == LOW) {

        sequenciaPlayer[index_player] = botoes[i]; // Salva o botão que o player pressionou na respectiva ordem dentro da lista

        digitalWrite(leds[i], HIGH); // Acende o led referente ao botão pressionado
        delay(200);
        digitalWrite(leds[i], LOW); // Apaga o led referente ao botão pressionado

        index_player++; // Aumenta o valor do index_player para indicar avanço na sequência
        delay(200);
      }
    }
  }

  verificacao();
}



void verificacao() { // Verifica se a sequência definida pelo jogador está correta
  for (i = 0; i < nivel; i++) {
    if (sequenciaPlayer[i] != sequenciaBotoes[i]) { // Se um valor da sequência do player for diferente da sequência definida pelo programa,
      fimDeJogo(); // é fim de jogo
      return;
    }
  }

  nivel++; // Se o(s) valor(es) da sequência do player for(em) igual(is) ao(s) da sequência, ele avança de nível
  delay(500); // Tempo de espera em ms para avançar para o próximo nível ou sequência
}



void fimDeJogo() { // Para o jogo até que o jogador aperte o botão de reset
  while (digitalRead(BOTAO_RESET) == HIGH) {
  criaSequencia();
  }
}


void setup() { // Definição dos tipos de porta para cada led e cada botão
  pinMode(LED_VERM, OUTPUT);
  pinMode(LED_AMAR, OUTPUT);
  pinMode(LED_VERD, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);

  pinMode(BOTAO_VERM, INPUT_PULLUP);
  pinMode(BOTAO_AMAR, INPUT_PULLUP);
  pinMode(BOTAO_VERD, INPUT_PULLUP);
  pinMode(BOTAO_AZUL, INPUT_PULLUP);
}



void loop() {

  if (nivel == 0) { 
    if (digitalRead(BOTAO_RESET) == LOW) {
      criaSequencia(); // Inicia o jogo após o player apertar o botão de reset
    }
  } else {
    if (nivel <= numeroDeNiveis) { // Começa o jogo caso o nível atual seja menor ou igual ao nível máximo
      exibeSequencia();
      captaSequenciaPlayer();
    } else {
      criaSequencia(); // Reinicia o jogo (e a sequência de leds)
    }
  }
}