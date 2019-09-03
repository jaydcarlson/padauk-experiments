
#include	"extern.h"



void	FPPA0 (void)
{
	.ADJUST_IC	SYSCLK=ILRC		//	SYSCLK=IHRC/2

	//	Insert Initial Code
	PAC = 0xDF; // make everything an output except PA5
	PAPH = 0x20; // make PA5 pull-up

	while (1)
	{
		PA = 0xFF;
		STOPSYS;
		.wait0 PA.5;
		.wait1 PA.5;

		while(PA.5) {
			PA = 0x00;
			.delay 3000;
			PA = 0xFF;
			.delay 3000;
		}
		.wait1 PA.5;
		.delay 1000;

//		...
//		wdreset;

	}
}


void	Interrupt (void)
{
	pushaf;

	if (Intrq.T16)
	{	//	T16 Trig
		//	User can add code
		Intrq.T16	=	0;
		//...
	}

	popaf;
}

