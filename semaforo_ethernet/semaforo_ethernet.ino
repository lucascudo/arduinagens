/*
  Web  Server
 
 A simple web server

 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
String request, result;
int car_g = 5; //define o pino 7 como carVerde
int car_y = 6; //define o pino 8 como carAmarelo
int car_r = 7; //define o pino 9 como carVermelho
int ped_r = 8; //define o pino 10 como pedVermelho
int ped_g = 9; //define o pino 11 como pedVerde
boolean ligado = 0; //define flag para ligar/desligar
char input;
int possivel_velocidade, velocidade = 2;

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

void apaga() {
  digitalWrite(ped_r,LOW);
  digitalWrite(ped_g,LOW);
  digitalWrite(car_r,LOW);
  digitalWrite(car_g,LOW);
  digitalWrite(car_y,LOW);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando servidor na porta 80...");
  pinMode(car_r,OUTPUT);
  pinMode(car_y,OUTPUT);
  pinMode(car_g,OUTPUT);
  pinMode(ped_r,OUTPUT);
  pinMode(ped_g,OUTPUT);
  // start the Ethernet connection and the server:
  byte ip[] = { 10,88,0,77 };
  Ethernet.begin(mac, ip);
  //Ethernet.begin(mac);
  server.begin();
}

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          if (request.substring(6).startsWith("d")) {
            input = 'd';
          } else if (request.substring(6).startsWith("l")) {
            input = 'l';
          }
          possivel_velocidade = request.charAt(7) - 48;
          if (possivel_velocidade > 0 && possivel_velocidade < 10) {
            velocidade = possivel_velocidade;
          }
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          // output the value of the request
          client.print("<!DOCTYPE html>");
          client.print("<html lang=\"pt-BR\">");
          client.print("<head>");
          client.print("<meta charset=\"utf-8\">");
          client.print("</head>");
          client.print("<body>");
          client.print("<p>");
          client.print(result);
          client.print("</p>");
          client.print("<input id=\"v\" type=\"number\" min=\"1\" max=\"9\">");
          client.print("<a id=\"l\" href=\"?l\">");
          client.print("ON");
          client.print("</a>");
          client.print(" <a id=\"d\" href=\"?d\">");
          client.print("OFF");
          client.print("</a>");
          client.print("<script src=\"http://code.jquery.com/jquery-1.9.1.js\"></script>");
          client.print("<script type=\"text/javascript\">");
          client.print("$(\"input#v\").blur(function() {");
          client.print("$(\"a#d\").attr(\"href\", \"?d\" + $(this).val());");
          client.print("$(\"a#l\").attr(\"href\", \"?l\" + $(this).val());");
          client.print("});");
          client.print("</script>");
          client.print("<!-- ");
          client.print(request);
          client.print(" -->");
          client.println("</body>");
          request = "";
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
  
  apaga();
  if (ligado) {
    digitalWrite(car_r,HIGH); //ascende o LED verde do carro (PASSE_CARRO)
    digitalWrite(car_r,LOW); //ascende o LED verde do carro (PASSE_CARRO)
    digitalWrite(car_g,HIGH); //ascende o LED verde do carro (PASSE_CARRO)
    digitalWrite(ped_r,HIGH); //ascende o LED vermelho do pedestre (PARE_PEDESTRE)
    delay(15000/velocidade);//mantem o LED verde do carro acesso por 7 seg
    digitalWrite(car_g,LOW); //apaga o LED verde do carro apos 7 seg
    digitalWrite(car_y,HIGH); //ascende o LED amarelo do carro(ATENÇAO_CARRO)
    delay(5000/velocidade);  
    digitalWrite(car_y,LOW); //apaga o LED amarelo do carro apos 3 seg
    digitalWrite(car_r,HIGH); //ascende o LED vermelho do carro(PARE_CARRO)
    digitalWrite(ped_r,LOW); //ascende o LED vermelho do carro(PARE_CARRO)
    digitalWrite(ped_g,HIGH); //apaga o LED vermelho do pedestre
    delay(8000/velocidade); //mantem o LED vermelho do carro acesso por 5 seg
    digitalWrite(ped_g,LOW); //apaga o LED vermelho do pedestre
    for (int i = 0; i < 8; i++) {
      digitalWrite(ped_r,HIGH); //ascende o LED vermelho do carro(PARE_CARRO)
      delay(200/velocidade);
      digitalWrite(ped_r,LOW); //ascende o LED vermelho do carro(PARE_CARRO)
      delay(200/velocidade);
    }
  } else {
    //pisca o LED amarelo
    digitalWrite(car_y, HIGH);
    delay(200/velocidade);
    digitalWrite(car_y, LOW);   
    delay(200/velocidade);
  }
  if (input == 'l') {
    ligado = 1;
  } else if (input == 'd') {
    ligado = 0;
  }
  result = (ligado) ? "Em funcionamento" : "Em manutenção";
  result += " a ";
  result += velocidade;
  result += "X";
  Serial.println(Ethernet.localIP());
  Serial.println(result);
}
