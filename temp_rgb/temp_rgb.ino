const int sensor=5;
int rPin = 9;
int bPin = 11;
int rVal, bVal;
float temperatura;

void setup()
{
  analogReference(INTERNAL); // Referencia de 1.1V UNO (1.1/1024=0,913mv) 0,913mv de precisão ou seja 0,09ºC( INTERNAL1V1  Arduino Mega)
  pinMode(rPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}
void loop()
{
  temperatura=0;
  for(int i=0;i<1000;i++)
  {
  temperatura=temperatura+analogRead(sensor);
  }
  temperatura=temperatura/1000; //Media de mil leituras
  temperatura=temperatura*(1.1/1024);//Converte valor lido para tensão
  temperatura=temperatura*100;//Converte para Graus = temperatura/(1/10mv)
  if (temperatura < 21)
    bVal = 255;
  else if (temperatura < 22)
    bVal = 230;
  else if (temperatura < 23)
    bVal = 205;
  else if (temperatura < 24)
    bVal = 180;
  else if (temperatura < 25)
    bVal = 155;
  else if (temperatura < 26)
    bVal = 130;
  else if (temperatura < 27)
    bVal = 105;
  else if (temperatura < 28)
    bVal = 80;
  else if (temperatura < 29)
    bVal = 55;
  else if (temperatura < 30)
    bVal = 30;
  else
    bVal = 0;
  rVal = 255 - bVal;
  analogWrite(rPin, rVal);
  analogWrite(bPin, bVal);
  //Serial.println(temperatura);
}
