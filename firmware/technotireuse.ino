#include <SoftwareSerial.h>
#include <Servo.h> 

Servo myServo;
int mot=7;
int interuptOpen=2;//open
int interuptClose=3;
int servoPin=6;
int tempoOpen=6300; //time needed to fill the glass
int tempoDrops=1000; //for the last drops -> faut pas gacher
SoftwareSerial mySerial(10, 11); // RX, TX

unsigned char req_command = 29;
int last_coin = 0;
int total_value = 0;

void setup() 
{
   pinMode(mot,OUTPUT);
   digitalWrite(mot, LOW);
   myServo.attach(servoPin);
   myServo.write(10);
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
      digitalWrite(mot,HIGH);
    while(digitalRead(interuptOpen)==HIGH){
    //delay(20); ?
    }
    delay(tempoOpen);
    digitalWrite(mot,LOW);
    while(digitalRead(interuptClose)==HIGH){
      //delay(20); ?
    }
    delay(tempoDrops);
    int i;
    for(i=40;i<=120;i=i+20){
      myServo.write(i);
      delay(100);
    }
    delay(50);
    myServo.write(20);
    total_value = 0;
} 
