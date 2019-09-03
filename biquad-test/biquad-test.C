
#include	"extern.h"

WORD in[11];
WORD out[11];

WORD z1, z2;
WORD outTemp;
WORD inTemp;

void filter(void) 
{
	outTemp = (inTemp << 14) + z1; // inTemp * a0 + z1;
	z1 = -(inTemp << 15) + z2
		+ (outTemp << 14)
		+ (outTemp << 13)
		+ (outTemp << 9)
		+ (outTemp << 8)
		+ (outTemp << 7)
		+ (outTemp << 6)
		+ (outTemp << 5)
		+ (outTemp << 3); // inTemp * a1 + z2 - b1 * outTemp;

	z2 = (inTemp << 14)
		- (outTemp << 13)
		- (outTemp << 11)
		- (outTemp << 8)
		- (outTemp << 3)
		- (outTemp << 2);
}

void	FPPA0 (void)
{
	.ADJUST_IC	SYSCLK=IHRC/2		//	SYSCLK=IHRC/2

	PAC.6 = 1; // make PA6 an output
	while(1) {
		PA.6 = 1;
		.FOR i, <0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10>
			inTemp = in[i];
			filter();
			out[i] = outTemp;
		.ENDM
		PA.6 = 0;
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

