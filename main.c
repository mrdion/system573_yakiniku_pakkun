#include "main.h"

#include "tim/title_tim.h"
; 
unsigned char data_buffer[0x40000]; // 256 kilobytes
unsigned int prim_list[0x4000];
int  dbuf=0, hx=0, hy=0;
int *wachdog;
void prog_vblank_handler() {
	display_is_old = 1;
	time_counter++;
	if(time_counter==999)
	{
		time_counter=0;
	}
}
void ClearScreen(){
	GsRectangle gs_rect;
	gs_rect.x = 0;
	gs_rect.y = 0;
	gs_rect.w = 320;
	gs_rect.h = 240;
	gs_rect.r = 0;
	gs_rect.g = 0;
	gs_rect.b = 0;
	gs_rect.attribute = 0;   
	GsSortRectangle(&gs_rect);

}

void DoubleBuffering(){
if(game_dispenv.y == 0)
      {
         game_dispenv.y = 256;
         game_drawenv.y = 0;
      }
      else
      {
         game_dispenv.y = 0;
         game_drawenv.y = 256;
      }
      *wachdog=0x0;
      GsSetDispEnv(&game_dispenv);
      GsSetDrawEnv(&game_drawenv);
        
}

void api_test(){
	int title_end=1;
	struct DIRENTRY	*dir,dirbuf[1];
	int ata_step=0;
	int	fsize,rsize,wsize;
	int fd;
	unsigned short *ata0;
	unsigned short  *ata1;
	unsigned short  *ata2;
	unsigned short  *ata3;
	unsigned short *ata4;
	unsigned short  *ata5;
	unsigned short  *ata6;
	unsigned short  *ata7;
	int *ata_reset;
	int ata_status=0;
	char buf[2048*2];
	ClearScreen();
	GsPrintFont(10, 10, "API_TEST");
	
	ata_reset=(int*)0x1f560000;
	ata0=(unsigned short*)0x1f480000; //0
	ata1=(unsigned short*)0x1f480002; //1  
	ata2=(unsigned short*)0x1f480004; //2
	ata3=(unsigned short*)0x1f480006; //3
	ata4=(unsigned short*)0x1f480008; //4
	ata5=(unsigned short*)0x1f48000A; //5  
	ata6=(unsigned short*)0x1f48000C; //6
	ata7=(unsigned short*)0x1f48000E; //7
	while(title_end) {
		if(display_is_old)	{
			DoubleBuffering();
			ClearScreen();
			//
			if(pad_read(PAD_1P_BUTTON1)==PAD_ON){
				if(ata_step==0){
					ata_step=1;
				}
				
			}else{
				
				//*ata0=0x0000;
			}
			
			if(pad_read(PAD_1P_BUTTON2)==PAD_ON){
				/**ata1=0x0001;
				*ata4=0x0800;
				*ata5=0x0008;
				*ata6=0x00a0;
				*ata7=0x00a1;*/
			}else{
				
			}
			if(pad_read(PAD_1P_BUTTON3)==PAD_ON){
				//*ata3=0xa1;
			}else{
				
				//*ata2=0x0000;
			}
			if(pad_read(PAD_1P_BUTTON4)==PAD_ON){
				//*ata3=0x0007;
			}else{
				
			}
			if(pad_read(PAD_1P_BUTTON5)==PAD_ON){
				//*ata3=0x80000;
			}else{
				
			}
			switch(ata_step){
				case 1:
					*ata_reset=0x1;
					ata_step++;
					break;
				case 2:
					ata_status=(int)*ata7;
					ata_step++;
					break;
				case 3:
					ata_status=(int)*ata7;
					ata_step++;
					break;
				case 4:
					ata_status=(int)*ata1;
					ata_step++;
					break;
				case 5:
					ata_status=(int)*ata4;
					ata_step++;
					break;
				/*case 6:
					ata_status=(int)*ata5;
					ata_step++;
					break;
				case 3:
					*ata6=0x00a0;
					ata_status=(int)*ata7;
					ata_step++;
					break;
				case 4:
					*ata6=0x00a0;
					*ata1=0x0000;
					*ata5=0x0008;
					*ata4=0x0800;
					*ata7=0x00a1;
					ata_step++;
					break;
				case 5:
					ata_status=(int)*ata7;
					ata_status=(int)*ata1;
					ata_status=(int)*ata2;
					ata_status=(int)*ata4;
					ata_status=(int)*ata5;
					ata_status=(int)*ata0;
					ata_status=(int)*ata0;
					ata_step++;
					break;*/
				default:
					break;
					
			}
			//GsPrintFont(10, 10, "API_TEST");
			GsDrawList();
			while(GsIsDrawing());
			display_is_old=0;
		}
	}
}
void title()
{
	
	int title_end=1;
	int push_start_on=0;
	int push_start_count=0;
	GsSprite sprite;
	GsImageFromTim(&game_image,title_tim);
	GsUploadImage(&game_image);
	GsSpriteFromImage(&sprite, &game_image, 1);
	sprite.x = 0; sprite.y = 0;
	sprite.w = 320; sprite.h = 200;
	sprite.u = 0; sprite.v = 0;
	GsSortSprite(&sprite);
	*wachdog=0x1f5c0000;
	while(title_end) {
		if(display_is_old)	{
			DoubleBuffering();
			ClearScreen();

			GsSortSprite(&sprite);
			if(push_start_on==1){
				if(time_counter%5==0){
					GsPrintFont(80, 180, "GAME PUSH:START");
					push_start_count++;
				}
				if(push_start_count==20){
					title_end=0;
					game_mode=1;
				}
			}else{
				GsPrintFont(80, 180, "GAME PUSH:START");
				GsPrintFont(80, 190, "API TEST PUSH:TEST");
				GsPrintFont(80, 200, "Ver:%d",game_version);
				GsPrintFont(80, 210, "1f5c0000:%d",*wachdog);
			}
			if(pad_read(PAD_1P_START)==PAD_ON){
				push_start_on=1;
			}
			if(pad_read(PAD_SERVICE)==PAD_ON){
				game_mode=2;
				title_end=0;
			}
			//GsPrintFont(0,0, "%d",time_counter);
			GsDrawList();
			while(GsIsDrawing());
			display_is_old=0;
		}
	}
}

int main() {


	GsInit();
	GsClearMem();
	GsSetVideoMode(320, 240, EXAMPLES_VMODE);
	game_dispenv.x=0;
   	game_dispenv.y=0;
  	GsSetDispEnv(&game_dispenv);
  	game_drawenv.x=0;
   	game_drawenv.y=0;
  	game_drawenv.w=320;
   	game_drawenv.h=240;
  	game_drawenv.draw_on_display=1;
  	game_drawenv.ignore_mask=0;
 	game_drawenv.dither=0;
  	game_drawenv.set_mask=0;
   	GsSetDrawEnv(&game_drawenv);
	GsSetList(prim_list);
	SetVBlankHandler(prog_vblank_handler);
	GsLoadFont(768, 0, 768, 256);
	time_counter=0;
	display_is_old=1;
	game_version=2014123001;
   	game_mode=0;
	GsDrawList();
	while(GsIsDrawing());
	
	while(1){
	switch(game_mode)
	{
			case 0:
				title();
				break;
			case 1:
				pakkun_main();
				break;
			case 2:
				api_test();
				break;
			default:
				title();
				break;
		}
	}
}
