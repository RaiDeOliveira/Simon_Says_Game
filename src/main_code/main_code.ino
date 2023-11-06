#define LED_VERM 16
#define LED_AMAR 17
#define LED_VERD 21
#define LED_AZUL 22

#define BOTAO_VERM 33
#define BOTAO_AMAR 32
#define BOTAO_VERD 35
#define BOTAO_AZUL 34

int leds[] = {LED_VERM, LED_AMAR, LED_VERD, LED_AZUL};

void ledsAcendem(){
  int i = 0;
  int sequencia[] = {0, 0, 0, 0};

  for(i = 0; i < 4; i++){

    sequencia[i] = leds[random(4)];
  
  };

  digitalWrite(sequencia[3], HIGH);
  delay(500);
  digitalWrite(sequencia[3], LOW);

}

int botoesAcendemLeds(){
    if(digitalRead(BOTAO_VERM) == LOW){
    digitalWrite(LED_VERM, HIGH);
  } else {
    digitalWrite(LED_VERM, LOW);}

    if(digitalRead(BOTAO_AMAR) == LOW){
    digitalWrite(LED_AMAR, HIGH);
  } else {
    digitalWrite(LED_AMAR, LOW);}
  
    if(digitalRead(BOTAO_AZUL) == LOW){
    digitalWrite(LED_AZUL, HIGH);
  } else {
    digitalWrite(LED_AZUL, LOW);}
  
    if(digitalRead(BOTAO_VERD) == LOW){
    digitalWrite(LED_VERD, HIGH);
  } else {
    digitalWrite(LED_VERD, LOW);}
  
  return 0;
  }




void setup() {
  pinMode(LED_VERM, OUTPUT);
  pinMode(LED_AMAR, OUTPUT);
  pinMode(LED_VERD, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);

  pinMode(BOTAO_VERM, INPUT_PULLUP);
  pinMode(BOTAO_AMAR, INPUT);
  pinMode(BOTAO_VERD, INPUT);
  pinMode(BOTAO_AZUL, INPUT_PULLUP);
}



void loop() {
  ledsAcendem();
  botoesAcendemLeds();
}