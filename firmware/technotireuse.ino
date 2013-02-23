#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

unsigned char req_command = 29;
int last_coin = 0;
int total_value = 0;

void setup() 
{ 
   mySerial.begin(9600);
   mySerial.listen();
   Serial.begin(9600);
} 

void loop() {
	while (total_value < 250) {
		mySerial.write((byte)0); //INIT
		mySerial.write(req_command); //0x1D Request
		delay(15);

		//Throw away these two bytes:
		mySerial.read();
		mySerial.read();

		while (!mySerial.available()) {}
		delay(10);
		last_coin = mySerial.read() << 8;
		last_coin += mySerial.read() & 0xFF;

		switch (last_coin) {
			case 16434:
				total_value += 50;
				break;
			case 16584:
				total_value += 200;
				break;
			case 16484:
				total_value += 100;
				break;
		}

		Serial.println(total_value);
	    delay(1000);
    }
    //
    Serial.println("Purchase OK!");
    
    total_value = 0;
} 
