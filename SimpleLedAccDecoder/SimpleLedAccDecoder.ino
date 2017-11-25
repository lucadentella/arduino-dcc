// Simple DCC Led Accessory Decoder
// Luca Dentella, 25.11.2017

// include NmraDcc library
#include <NmraDcc.h>
NmraDcc Dcc;

// definitions
#define DCC_PIN         2
#define BOARD_ADDRESS   5
#define PAIR_ADDRESS    1
#define GREEN_LED_PIN   3
#define RED_LED_PIN     4


void notifyDccAccState(uint16_t Addr, uint16_t BoardAddr, uint8_t OutputAddr, uint8_t State) {
 
  int pairAddress = (OutputAddr >> 1) + 1;
  int outputInPair = OutputAddr & 0x01;
  
  Serial.print("* new accessory decoder packet received (BoardAddr=");
  Serial.print(BoardAddr, DEC);
  Serial.print(", pairAddress=");
  Serial.print(pairAddress, DEC);
  Serial.print(", outputInPair=");
  Serial.println(outputInPair, DEC);

  // check if the command is for our address and output
  if((BoardAddr == BOARD_ADDRESS) && (pairAddress == PAIR_ADDRESS)) {
    if(outputInPair == 0) {
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      Serial.println("! RED led activated");
    } else {
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, HIGH);
      Serial.println("! GREEN led activated");      
    }
  }
}


void setup() {

  // Serial output for debugging
  Serial.begin(115200);
  Serial.println("DCC Led Accessory Decoder");
  Serial.println();

  // init NmraDcc library (PIN, manufacturer, version...) 
  Dcc.pin(digitalPinToInterrupt(DCC_PIN), DCC_PIN, 1);
  Dcc.init(MAN_ID_DIY, 1, FLAGS_DCC_ACCESSORY_DECODER, 0);

  // configure pins
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  Serial.println("- decoder ready");
}


void loop() {

   Dcc.process();
}
