#include <REGX52.H>
#include <INTRINS.H>
void Delay500ms(void)	//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void main()
{
	P2 = 0xFE;
	Delay500ms();
	P2 = 0xFD;
	Delay500ms();
	P2 = 0xFB;
	Delay500ms();
	P2 = 0xF7;
	Delay500ms();
	P2 = 0XEF;
	Delay500ms();
	P2 = 0xDF;
	Delay500ms();
	P2 = 0xBF;
	Delay500ms();
	P2 = 0x7F;
	Delay500ms();
}