#include <Arduino.h>
#include <ACAN2517FD.h>
#include <SPI.h>


//——————————————————————————————————————————————————————————————————————————————
//  Test setup
//——————————————————————————————————————————————————————————————————————————————

const uint8_t btn_pin = 3; // D3
//const uint8_t led_pin = 5; // Intern lys
const uint8_t exled_pin = 17; // A3

uint8_t led_state = LOW;

unsigned long time; // For interrupt timing
unsigned long elapsed_time; // For interrupt timing
volatile int count = 0;

unsigned long sendingTime; // For SDS sending timing
float analogVoltage = 0;
int wheelspeed = 0;


//——————————————————————————————————————————————————————————————————————————————
//  CANBUS setup
//——————————————————————————————————————————————————————————————————————————————

static const byte MCP2517_CS  = 7; // CS input of MCP2517
static const byte MCP2517_INT =  2; // INT output of MCP2517

ACAN2517FD can(MCP2517_CS, SPI, MCP2517_INT);
CANFDMessage FDsuspentionValue, FDwheelspeed;

void sendFDData(CANFDMessage FDmessage) {
  can.tryToSend(FDmessage);
}

void toggle();

//——————————————————————————————————————————————————————————————————————————————
//  Generell setup
//——————————————————————————————————————————————————————————————————————————————

void setup() {
	/* --------------------------- Interrupt setup --------------------------- */
	pinMode(btn_pin, INPUT); // D3
	//pinMode(led_pin, OUTPUT); // Internt lys
	pinMode(exled_pin, OUTPUT); // A3

	attachInterrupt(digitalPinToInterrupt(btn_pin), toggle, RISING);


	time = millis(); 
    sendingTime = millis(); 

	/* --------------------------- CANbus setup --------------------------- */
	SPI.begin();

  	ACAN2517FDSettings settings(ACAN2517FDSettings::OSC_20MHz, 500UL * 1000UL, DataBitRateFactor::x8);
	settings.mRequestedMode = ACAN2517FDSettings::NormalFD;
 	settings.mDriverTransmitFIFOSize = 1;
  	settings.mDriverReceiveFIFOSize = 1;
	
	const uint32_t errorCode = can.begin(settings, [] { can.isr () ; });
	if (errorCode != 0) {

  	}

  	/* -------------------------------------------------------------------------- */
  	/*                               Sending frames                               */
  	/* -------------------------------------------------------------------------- */

  	// Verdien til suspension displacement value
  	FDsuspentionValue.id = 0x420;
  	FDsuspentionValue.len = 1; // Valid lengths are: 0, 1, ..., 8, 12, 16, 20, 24, 32, 48, 64
  	FDsuspentionValue.type = CANFDMessage::CANFD_WITH_BIT_RATE_SWITCH;

	FDwheelspeed.id = 0x424;
  	FDwheelspeed.len = 1; // Valid lengths are: 0, 1, ..., 8, 12, 16, 20, 24, 32, 48, 64
  	FDwheelspeed.type = CANFDMessage::CANFD_WITH_BIT_RATE_SWITCH;

	//Serial.begin(9600);
}

void loop() {
	if(count == 12) {
		elapsed_time = millis() - time;
		time = millis();

		wheelspeed = 123;
		//led_state = !(led_state);
		//digitalWrite(led_pin, led_state);
		count = 0;


	}

	// Når det har gått 10ms, gjør følgende:
	if (millis() - sendingTime > 1000) {
		analogVoltage = analogRead(14); // Leser fra A0 på breakoutboardet til ACMen
		analogVoltage = (int)(analogVoltage * (5 / 1023.0) * 10); // Konverterer til spenning i millivolt

		FDsuspentionValue.data[0] = analogVoltage;
		FDwheelspeed.data[0] = wheelspeed;

		sendFDData(FDsuspentionValue);
		sendFDData(FDwheelspeed);
		//Serial.println(analogVoltage);

	    sendingTime = millis();
	}

}

// Skrur LED av/på ved knappetrykk
void toggle() {
 	// Koblet til ekstern LED
	count++;
	led_state = !(led_state);
	digitalWrite(exled_pin, led_state);
}

