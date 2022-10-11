/**
//node=1
#include<SPI.h>
#include <nRF24L01.h>
#include<RF24.h>

RF24 radio(7,8); //CE,CSN
const uint64_t pipe1 = 0xF0F0F0F066;
//max size of struct is 32 bytes 
struct sensor_data{
float temp;
float moisture;
int device_id;
};
sensor_data data; //struct variable

void setup(){
radio.begin();
radio.openWritingPipe(pipe1);
radio.setPALevel(RF24_PA_MAX);
radio.stopListening();
}
void loop(){
//send the whole data
data.temp=40.0;
data.moisture=30;
data.device_id=1;
radio.write(&data,sizeof(data));
delay(5000);
}**/
/**
//node 02
#include<SPI.h>
#include <nRF24L01.h>
#include<RF24.h>

RF24 radio(7,8); //CE,CSN
const uint64_t pipe2 = 0xF0F0F0F0A1;
//max size of struct is 32 bytes 
struct sensor_data{
float temp;
float moisture;
int device_id;
};
sensor_data data; //struct variable

void setup(){
radio.begin();
radio.openWritingPipe(pipe2);
radio.setPALevel(RF24_PA_MAX);
radio.stopListening();
}
void loop(){
//send the whole data
data.temp=20.0;
data.moisture=40;
data.device_id=2;
radio.write(&data,sizeof(data));
delay(4000);
}**/
/**
//node 03
#include<SPI.h>
#include <nRF24L01.h>
#include<RF24.h>

RF24 radio(7,8); //CE,CSN
const uint64_t pipe3 = 0xF0F0F0F0AA;
//max size of struct is 32 bytes 
struct sensor_data{
float temp;
float moisture;
int device_id;
};
sensor_data data; //struct variable

void setup(){
radio.begin();
radio.openWritingPipe(pipe3);
radio.setPALevel(RF24_PA_MAX);
radio.stopListening();
}
void loop(){
//send the whole data
data.temp=30.0;
data.moisture=50;
data.device_id=3;
radio.write(&data,sizeof(data));
delay(2000);
}**/

//sinknode
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8); //CE,CSN
const uint64_t pipe1 = 0xF0F0F0F066;
const uint64_t pipe2 = 0xF0F0F0F0A1;
const uint64_t pipe3 = 0xF0F0F0F0AA;
const uint64_t gateway=0xF0F0F0F0A2;

struct sensor_data{
float temp;
float moisture;
int device_id;
};
sensor_data data; //struct variable


void setup(){
Serial.begin(9600);
radio.begin();
radio.openWritingPipe(gateway);
radio.openReadingPipe(1,pipe1);
radio.openReadingPipe(2,pipe2);
radio.openReadingPipe(3,pipe3);
radio.setPALevel(RF24_PA_MAX);// " min range setting" - increase if you want more range AND have a good power supply

}
void loop(){
	delay(5);
	radio.startListening(); // Start listening for messages
 	// Check whether there is data to be received
if (radio.available()) {
	radio.read(&data,sizeof(data));//Read the whole data and store in 'data' structure.
		Serial.print("Node N0. :");
		Serial.println(data.device_id);
		Serial.print("Soil Moisture: ");
		Serial.print(data.moisture);
		Serial.println("%");
		Serial.print("Soil Temperature: ");
		Serial.print(data.temp);
		Serial.println("°C");
	delay(5);
	radio.stopListening();// Start Writing for messages
	radio.write(&data, sizeof(data));
		}
	}
	
/**
code for esp
#include <ESP8266WiFi.h>
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiManager.h>
WiFiManager wifiManager;

RF24 radio(4,2); //CE,CSN
const uint64_t gateway=0xF0F0F0F0A2;
struct sensor_data{
float temp;
float moisture;
int device_id;
};
sensor_data data; //struct variable
void setup() {
	 Serial.begin(115200);
	 //----------------------------------------------------------------------
					//WiFi block goes here!!!!!
	 //---------------------------------------------------------------------
	
	 radio.begin();
	 radio.openReadingPipe(0,gateway);
	 radio.setPALevel(RF24_PA_MAX);
	 radio.startListening();
	 if(radio.isChipConnected()){
        	Serial.print("Chip is connected!");
      		}
	 else{
        	Serial.print("Chip is not connected!");
      		}
}
void loop(){
	  if(radio.isChipConnected()){
        	Serial.print("Chip is connected!");
      		}
	 else{
        	Serial.print("Chip is not connected!");
      		}
	if (radio.available()){
		radio.read(&data, sizeof(sensor_data));
		Serial.print("Node N0. :");
		Serial.println(data.device_id);
		Serial.print("Soil Moisture: ");
		Serial.print(data.moisture);
		Serial.println("%");
		Serial.print("Soil Temperature: ");
		Serial.print(data.temp);
		Serial.println("°C");
		//send();
	}
	delay(500);
}**/
/**void send() {
	if(WiFi.status()==WL_CONNECTED)
	{
		const char* server = "http://api.thingspeak.com/update";
		String my_Api_key = "1QK63KXC70LIR6VM";
		WiFiClient wifiClient;
		HTTPClient http;
		http.begin(wifiClient,server);
		// Specify content-type header
		http.addHeader("Content-Type", "application/x-www-form-urlencoded");
		String httpRequestData = "api_key=" + my_Api_key + "&field1=" + String(data.device_id)+"&field2=" + String(data.moisture)+"&field3=" + String(data.temp);
		int httpResponseCode = http.POST(httpRequestData);
		
	}
}**/

