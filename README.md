# repositorio-entregavel-sprint8
repositorio para conectar o sensor de um rack com arduino em um celular com o MQTT
# objetivo

o objetivo desse projeto é usar o arduino com um sensor magnetico para monitorar um rack verificando se o RACK está ABERTO oun FECHADO e usando a internet mandar a informação para o celular usando o #MQTT(Message Queuing Telemetry Transport) para um servidor hospedado pela Amazon Web Service(AWS) e exibir a informação em um cliente MQTT [MQTT DASH] (https://play.google.com/store/apps/details?id=net.routix.mqttdash&hl=pt_BR&gl=US) instalado no smarthphone,exemplo abaixo

![](https://camo.githubusercontent.com/7beef2d4780d87a603d7de49b2da0467c8537dff96575b628a04bd4010ebb1cc/68747470733a2f2f692e696d6775722e636f6d2f4d576870586b562e706e67)
foram utilizados as seguintes bibliotecas
* [UIPEthernet](https://github.com/UIPEthernet/UIPEthernet) (conexão do ENC28J60 com o Arduino) 
* [PubSubClient](https://pubsubclient.knolleary.net/) (client MQTT para o Arduino)

## Materias

* Arduino Uno
* Modulo Ethernet (ENC28J60)
* Sensor Magnético (MC-38)
* Jumpers

## Circuito


![](https://camo.githubusercontent.com/ad1da211b35b60b23fb095a64e76dc6504d0c3229e853bd82a69a4d5d27bbb88/68747470733a2f2f692e696d6775722e636f6d2f594947477453472e706e67)


[![](https://camo.githubusercontent.com/a80d00f23720d0bc9f55481cfcd77ab79e141606829cf16ec43f8cacc7741e46/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f4c696e6b6564496e2d3030373742353f7374796c653d666f722d7468652d6261646765266c6f676f3d6c696e6b6564696e266c6f676f436f6c6f723d7768697465)](https://www.linkedin.com/in/gustavo-alves-de-siqueira-9611b8206/)

[![](https://camo.githubusercontent.com/be08f7a1c998ec3e477fd0d3cc0e7fa39255cce4e77daf537e80c0f33e4d87d0/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f4d6963726f736f66745f4f75746c6f6f6b2d3030373844343f7374796c653d666f722d7468652d6261646765266c6f676f3d6d6963726f736f66742d6f75746c6f6f6b266c6f676f436f6c6f723d7768697465)](https://gustavoaclion@gmail.com)

## codigos utilizados

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
    mqttClient.setServer("54.174.235.157",1883);

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

## autor:Gustavo Alves
