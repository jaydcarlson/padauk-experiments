
extern bit dataReady : pa.0;
BYTE	SPI_Data_In;
BYTE	cnt;

BIT SPI_In			:	PA.6;
BIT SPI_InMode		:	PAC.6;
BIT SPI_Clk			:	PA.7;
BIT SPI_ClkMode		:	PAC.7;


// This FPPA is responsible for receiving SPI bytes and alerting FFPPA0 whenever a new byte is received.
void	FPPA1 (void)
{
	set0	SPI_ClkMode;
	set0	SPI_InMode;

	while (1)
	{
		cnt	=	8;

		do
		{
			.wait0	SPI_Clk;
			.wait1	SPI_Clk;
			swapc	SPI_In;     // swap the data pin with carry
			slc		SPI_Data_In; // left-shift the carry
		} while (--cnt);
		dataReady = 1;
	}
}

