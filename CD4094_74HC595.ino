//controlling 74HC595/CD4094

#define SELECTED_CHIP 0 //0 = 74HC595, 1 = CD4094

#ifdef SELECTED_CHIP
	#if SELECTED_CHIP != 0 && SELECTED_CHIP != 1
	#error "Invalid Value Entered For SELECTED_CHIP"
	#elif SELECTED_CHIP == 0
	// ONLY for 74HC595
	// const uint8_t MR_Pin = 8; MR(pin 10), MR LOW, Q0-Q7 cleared. Connect to Vcc if unused.	
	#endif
	// Define Connections to 		 74HC595		|	  CD4094
	const uint8_t enablePin = 9; //	OE(pin 13)		|	OE(pin 15)
	const uint8_t latchPin = 10; // ST_CP(pin 12)	|	ST_CP(pin 1)
	const uint8_t clockPin = 11; // SH_CP(pin 11)	|	SH_CP(pin 3)
	const uint8_t dataPin = 12;  // DS(pin 14)		|	DS(pin 2)
	//74HC595: OE HIGH, output is Hi-Z
	//CD4094: OE LOW, output is Hi-Z
#else
#error "SELECTED_CHIP Not Defined!"
#endif

void setup ()
{
  // Setup pins as Outputs
  pinMode(enablePin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  //enable chip output
  #if SELECTED_CHIP == 0
  digitalWrite(enablePin, LOW);
  #else
  digitalWrite(enablePin, HIGH);
  #endif
}

void loop() {
  // Count from 0 to 255 and output on register (LEDs used to display binary value on output)

  for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {

    //Set ST_CP to keep LEDs from changing while writing serial data to register
	digitalWrite(latchPin, LOW);

    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);

    //Reset ST_CP to update the register output
	digitalWrite(latchPin, HIGH);

    delay(500);
  }
}
