#include	"extern.h"

// attach the WS2812B LED(s) to this pin
bit	LED 		: pa.3;
bit	LEDC 		: pac.3;

// this pin is used for debugging; it asserts whenever a byte is received
bit dataReady 	: pa.0;
bit dataReadyC 	: pac.0;

extern BYTE	SPI_Data_In;
BYTE spiTemp;

// Main CPU context is responsible for initalizing the pins and
// managing the WS2812B LEDs
void	FPPA0 (void)
{
	// we're running the CPU a bit hot --- 18 MHz --- but otherwise the timing doesn't work out.
	.ADJUST_IC	SYSCLK=IHRC/2, IHRC=18MHz, VDD=5V, Bandgap=On;
	fppen	=	0xFF; // enable the other FPPAs (only two total in our case)
	DISGINT; // disable global interrupt
	LEDC = 1; // set pin to output
	dataReadyC = 1; // debug pin as an output

	while (1)
	{
		// TODO: we need some sort of watchdog that we feed whenever we get a byte
		// otherwise, the SPI state machine might get out of sync
		.wait1 dataReady;
		spiTemp = SPI_Data_In;
		dataReady = 0;

		.FOR bitno, <7,6,5,4,3,2,1,0>
			if (spiTemp.bitno == 0) {
				SET1 LED;
				SET0 LED;
				.DELAY 2;
			} else {
				SET1 LED;
				.DELAY 2;
				SET0 LED;
			}
		.ENDM
	}
}


void	Interrupt (void)
{
	pushaf;

	if (Intrq.T16)
		Intrq.T16	=	0;
	}
	popaf;
}

