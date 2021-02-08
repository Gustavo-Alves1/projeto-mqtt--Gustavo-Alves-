#include <PubSubClient.h>

#include <UIPEthernet.h>
#include <utility/logging.h>

#include <SPI.h>
int pino2 = 2;
bool estado_sensor;


//Define o endereço MAC que será utilizado
byte mac[] = {0x48, 0xF9, 0x61, 0xC8, 0xE5, 0x81};
bool mensagem;
//Inicia o cliente Ethernet
EthernetClient client;
PubSubClient  mqttClient(client);

void setup() {
  pinMode(pino2,INPUT_PULLUP);
    //Inicia o controlador Ethernet e solicita um IP para o servidor de DHCP
    Ethernet.begin(mac);

    //Inicia o monitor Serial
    Serial.begin(9600);
    mqttClient.setServer("54.161.191.80",1883);

    //Exibe no Monitor Serial as informações sobre o IP do Arduino
    Serial.print("O IP do Arduino e: ");
    Serial.println(Ethernet.localIP());

    //Exibe no Monitor Serial as informações sobre a Máscara de Rede do Arduino
    Serial.print("A Mascara de Rede do Arduino e: ");
    Serial.println(Ethernet.subnetMask());

    //Exibe no Monitor Serial as informações sobre o Gateway do Arduino
    Serial.print("O Gateway do Arduino e: ");
    Serial.println(Ethernet.gatewayIP());

    //Exibe uma linha em branco
    Serial.println("");

}

void loop() {
mqttClient.connect("gustavoalves");
    estado_sensor=digitalRead(pino2);
    
    if (estado_sensor==1){
 mensagem = mqttClient.publish("gustavoalves-s","aberto");
 Serial.println("o rack esta aberto");
    Serial.println(mensagem);
    delay (500);
    }
    else { 
      mensagem = mqttClient.publish("gustavoalves-s","fechado");
    Serial.println("o rack esta fechado");
    Serial.println(mensagem);

    delay(1000);
    }
    
    mqttClient.loop();
   
}
