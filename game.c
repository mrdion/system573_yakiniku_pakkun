#include <psx.h>
#include <stdio.h>
#include <stdlib.h>
#include "ksys573_pad.h"
#include "tim/game_tim.h"
#include "tim/title_tim.h"

#define MODE_TITLE = 0
#define MODE_GAME = 1

GsDispEnv game_dispenv;
GsDrawEnv game_drawenv;
unsigned char data_buffer[0x40000]; // 256 kilobytes
unsigned int prim_list[0x4000];
int game_mode;
volatile int display_is_old = 1;
volatile int time_counter = 0;
int  dbuf=0, hx=0, hy=0;
int game_version;
GsImage game_image;
GsSprite oniku_sprite;
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
	int	fsize,rsize,wsize;
	int fd;
	int *ata0;
	int *ata1;
	int *ata2;
	int *ata3;
	char buf[2048*2];
	ClearScreen();
	GsPrintFont(10, 10, "API_TEST");
	
	
	//sio_init
	ata0=(int*)0x1f480000;
	ata1=(int*)0x1f480004;
	ata2=(int*)0x1f480008;
	ata3=(int*)0x1f48000C;
	while(title_end) {
		if(display_is_old)	{
			DoubleBuffering();
			ClearScreen();
			//
			if(pad_read(PAD_1P_BUTTON1)==PAD_ON){
				*ata0=0x00000001;
			}else{
				
				*ata0=0x00000000;
			}
			if(pad_read(PAD_1P_BUTTON2)==PAD_ON){
				*ata1=0x00000001;
			}else{
				
				*ata1=0x00000000;
			}
			if(pad_read(PAD_1P_BUTTON3)==PAD_ON){
				*ata1=0x00000001;
			}else{
				
				*ata1=0x00000000;
			}
			if(pad_read(PAD_1P_BUTTON4)==PAD_ON){
				*ata1=0x00000001;
			}else{
				
				*ata1=0x00000000;
			}	
			GsPrintFont(10, 10, "API_TEST");
			GsPrintFont(10, 20, "ata0:%x",ata0);
			GsPrintFont(10, 30, "ata0:%x",ata1);
			GsPrintFont(10, 40, "ata0:%x",ata2);
			GsPrintFont(10, 50, "ata0:%x",ata3);
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
	game_version=2014123002;
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
