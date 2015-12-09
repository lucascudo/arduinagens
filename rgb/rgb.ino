#include <stdio.h>

int r = 9;
int g = 10;
int b = 11;
int rVal[2], gVal[2], bVal[2];
char caracter;
String rgb;

void setup()
{
  Serial.begin(9600);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
}

void loop()
{
  while (Serial.available() > 0)
  {
    if (rgb.length() > 5)
    {
      if (Serial.read() == 'r')
      {
        Serial.println(rgb);
        break;
      }
      else
      {
        rgb = "";
      }
    }
    caracter = Serial.read();
    rgb.concat(caracter);
    //delay(1);
  }
  
  rVal[0] = rgb[0];
  rVal[1] = rgb[1];
  gVal[0] = rgb[2];
  gVal[1] = rgb[3];
  bVal[0] = rgb[4];
  bVal[1] = rgb[5];
  
  analogWrite(r, (int)rVal);
  analogWrite(g, (int)gVal);
  analogWrite(b, (int)bVal);
}
