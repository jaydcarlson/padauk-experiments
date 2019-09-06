
#include	"extern.h"

WORD in[55];
WORD out[55];

WORD z1, z2;

WORD pOut, pIn; // these are pointers, but aren't typed as such

int i;

WORD x;
WORD y;
WORD mulOut;

#ifdef MULOP
void mul16(void) {
	// L x L
	MULOP = x$0;
	A = y$0;
	mul
	mulOut = A + (MULRH << 8);

	// L x H
	MULOP = x$0;
	A = y$1;
	mul
	mulOut += (A << 8);

	// H x L
	MULOP = x$1;
	A = y$0;
	mul
	mulOut += (A << 8);

	// H x H
	MULOP = x$1;
	A = y$1;
	mul
	mulOut += (A << 8);
}
#endif

void	FPPA0 (void)
{
	.ADJUST_IC	SYSCLK=ILRC		//	SYSCLK=IHRC/2

	PAC.6 = 1; // make PA6 an output
	while(1) {
		pOut = out;
		pIn = in;
		i = 0;
		do {
			// out = in * 16384 + z1;
			*pOut = (*pIn << 14) + z1;

			 // z1 = inTemp * -32768 + z2 
			z1 = -(*pIn << 15) + z2;

			// z1 += 25576 * out;
#ifdef MULOP
			x = *pOut;
			y = 25576;
			mul16();
			z1 += mulOut;
#else
			z1 += (*pOut << 14)
				+ (*pOut << 13)
				+ (*pOut << 9)
				+ (*pOut << 8)
				+ (*pOut << 7)
				+ (*pOut << 6)
				+ (*pOut << 5)
				+ (*pOut << 3);
#endif
			// z2 = in * 16384
			z2 = (*pIn << 14);

			// z2 -= 10508 * out;
#ifdef MULOP
			x = *pOut;
			y = 10508;
			mul16();
			z2 -= mulOut;
#else
			z2 -= (*pOut << 13)
				- (*pOut << 11)
				- (*pOut << 8)
				- (*pOut << 3)
				- (*pOut << 2);
#endif

			i++;
			pOut++;
			pIn++;
		} while(i < 55);

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

