#include <REGX52.H>
#include <INTRINS.H>
void Delay1ms(unsigned int XMS)	//@11.0592MHz
{
	while(XMS)
	{
		unsigned char data i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
		XMS--;
	}	
	
}
void main()
{
	P2 = 0xFE;
	Delay1ms(200);
	P2 = 0xFD;
	Delay1ms(200);
	P2 = 0xFB;
	Delay1ms(200);
	P2 = 0xF7;
	Delay1ms(200);
	P2 = 0XEF;
	Delay1ms(200);
	P2 = 0xDF;
	Delay1ms(200);
	P2 = 0xBF;
	Delay1ms(200);
	P2 = 0x7F;
	Delay1ms(200);

}
