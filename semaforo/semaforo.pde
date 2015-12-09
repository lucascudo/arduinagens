 int car_g = 7; //define o pino 7 como carVerde
 int car_y = 8; //define o pino 8 como carAmarelo
 int car_r = 9; //define o pino 9 como carVermelho
 int ped_r = 10; //define o pino 10 como pedVermelho
 int ped_g = 11; //define o pino 11 como pedVerde
 boolean ligado = 1; //define flag para ligar/desligar
 char input;
 
 void setup(){
  Serial.begin(9600);
  pinMode(car_r,OUTPUT);
  pinMode(car_y,OUTPUT);
  pinMode(car_g,OUTPUT);
  pinMode(ped_r,OUTPUT);
  pinMode(ped_g,OUTPUT);
 }

 void loop(){
  apaga();
  if (ligado) {
    digitalWrite(car_r,HIGH); //ascende o LED verde do carro (PASSE_CARRO)
    digitalWrite(car_r,LOW); //ascende o LED verde do carro (PASSE_CARRO)
    digitalWrite(car_g,HIGH); //ascende o LED verde do carro (PASSE_CARRO)
    digitalWrite(ped_r,HIGH); //ascende o LED vermelho do pedestre (PARE_PEDESTRE)
    delay(15000);//mantem o LED verde do carro acesso por 7 seg
    digitalWrite(car_g,LOW); //apaga o LED verde do carro apos 7 seg
    digitalWrite(car_y,HIGH); //ascende o LED amarelo do carro(ATENÇAO_CARRO)
    delay(5000);  
    digitalWrite(car_y,LOW); //apaga o LED amarelo do carro apos 3 seg
    digitalWrite(car_r,HIGH); //ascende o LED vermelho do carro(PARE_CARRO)
    digitalWrite(ped_r,LOW); //ascende o LED vermelho do carro(PARE_CARRO)
    digitalWrite(ped_g,HIGH); //apaga o LED vermelho do pedestre
    delay(8000); //mantem o LED vermelho do carro acesso por 5 seg
    digitalWrite(ped_g,LOW); //apaga o LED vermelho do pedestre
    for (int i = 0; i < 8; i++) {
      digitalWrite(ped_r,HIGH); //ascende o LED vermelho do carro(PARE_CARRO)
      delay(200);
      digitalWrite(ped_r,LOW); //ascende o LED vermelho do carro(PARE_CARRO)
      delay(200);
    }
  } else {
    //pisca o LED amarelo
    digitalWrite(car_y, HIGH);
    delay(200);
    digitalWrite(car_y, LOW);   
    delay(200);
  }
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input) {
      if (input == 'l') {
        ligado = 1;
      } else if (input == 'd') {
        ligado = 0;
      }
    }
  }
  Serial.println(input);
}

void apaga() {
  digitalWrite(ped_r,LOW);
  digitalWrite(ped_g,LOW);
  digitalWrite(car_r,LOW);
  digitalWrite(car_g,LOW);
  digitalWrite(car_y,LOW);
}

