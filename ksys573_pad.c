#include "ksys573_pad.h"
#include <psx.h>


int pad_read(int pad_bit)
{
	int *pad_state;
	int ret=PAD_OFF;
	switch(pad_bit&0x000F0000)
	{

		case 0x00010000:
			
			//GsPrintFont(0, 30, "pad_bit:IN1");
			pad_state=(int*)IN1;
			break;
		case 0x00020000:
			//GsPrintFont(0, 30, "pad_bit:IN2");
			pad_state=(int*)IN2;
			break;
		case 0x00040000:
			//GsPrintFont(0, 30, "pad_bit:IN3");
			pad_state=(int*)IN3;
			break;
		default:
			ret=-1;
			break;
	}
	if(ret==PAD_OFF)
	{
		
		//GsPrintFont(0, 40, "pad_bit:%x",*pad_state);
		ret=(*pad_state&(pad_bit&0xFFF0FFFF));
	}
	return ret;
}
int pad_read_raw_in1()
{
	int *pad_state;
	pad_state=(int*)IN1;
	return *pad_state;
}
int pad_read_raw_in2()
{
	int *pad_state;
	pad_state=(int*)IN2;
	return *pad_state;
}
int pad_read_raw_in3()
{
	int *pad_state;
	pad_state=(int*)IN3;
	return *pad_state;
}
