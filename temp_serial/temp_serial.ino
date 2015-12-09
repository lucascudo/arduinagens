const int sensor=5;
float temperatura;

void setup()
{
  analogReference(INTERNAL); // Referencia de 1.1V UNO (1.1/1024=0,913mv) 0,913mv de precisão ou seja 0,09ºC( INTERNAL1V1  Arduino Mega)
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available() > 0 && Serial.read())
  {
    Serial.flush();
    temperatura=0;
    for (int i=0;i<1000;i++)
    {
      temperatura=temperatura+analogRead(sensor);
    }
    temperatura=temperatura/1000; //Media de mil leituras
    temperatura=temperatura*(1.1/1024);//Converte valor lido para tensão
    temperatura=temperatura*100;//Converte para Graus = temperatura/(1/10mv)
    Serial.println(temperatura);
  }
}
