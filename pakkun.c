#include "main.h"
#include "tim/game_tim.h"
void pakkun_main()
{
	
	ClearScreen();
	int game_end=1;
	//RLDU
	//0123
	int i;
	unsigned char char_position_x=0x0;
	unsigned char char_position_y=0x0;
	int char_direction=0;
	int char_direction_lr=0;
	int char_sprite_counter=0;
	bool char_position_x_do=false;
	bool char_position_y_do=false;
	bool char_position_do=false;
	GsSprite my_char;
	GsSprite niku;
	GsSprite honou;
	GsLine line;
	int line_color=0;
	int line_color_1=0;
	bool line_color_down=false;
	GsImageFromTim(&game_image,game_tim);
	GsUploadImage(&game_image);
	GsSpriteFromImage(&my_char, &game_image, 1);
	my_char.x = 16; my_char.y = 16;
	my_char.w = 16; my_char.h = 16;
	my_char.u = 0; my_char.v = 0;
	GsSortSprite(&my_char);
	while(game_end) {
		if(display_is_old)	{
			DoubleBuffering();
			ClearScreen();
			
			//パッド
			if(char_position_do==false){
				if(pad_read(PAD_1P_LEFT)==PAD_ON){
					my_char.x--;
					char_direction=1;
					char_direction_lr=0;
					if(my_char.x==15){
						my_char.x=16;	
					}
				}
				if(pad_read(PAD_1P_RIGHT)==PAD_ON){
					my_char.x++;
					char_direction=0;
					char_direction_lr=1;
					if(my_char.x==289){
						my_char.x=288;	
					}
				}
				if(pad_read(PAD_1P_UP)==PAD_ON){
					my_char.y--;
					char_direction=3;
					if(my_char.y==15){
						my_char.y=16;	
					}
				}
				if(pad_read(PAD_1P_DOWN)==PAD_ON){
					my_char.y++;
					char_direction=2;
					if(my_char.y==193){
						my_char.y=192;	
					}
				}
			}
			//升目にあわせて座標変える
			if(my_char.x%16!=0){	
				char_position_x_do=true;
				char_position_do=true;
			
				switch(char_direction){
					case 0:
						my_char.x++;
						if(my_char.x==15){
							my_char.x=16;	
						}
						break;
					case 1:
						my_char.x--;
						if(my_char.x==289){
							my_char.x=288;	
						}
						break;
					default:
						if(char_direction_lr==0){
							my_char.x++;
							if(my_char.x==15){
								my_char.x=16;	
							}
						}else{
							my_char.x--;
							if(my_char.x==289){
								my_char.x=288;	
							}
						}
						break;
				}
			}else{
				if(char_position_x_do==true){
					char_position_x=(19-((320-my_char.x)/16));
					char_position_x_do=false;
				}
			}
			if(my_char.y%16!=0){
				char_position_y_do=true;
				char_position_do=true;
				switch(char_direction){
					case 2:
						my_char.y++;
						if(my_char.y==193){
							my_char.y=192;	
						}
						
						break;
					case 3:
						my_char.y--;
						if(my_char.y==15){
							my_char.y=16;	
						}
						break;
					default:
						break;
				}
					
			}else{
				if(char_position_y_do==true){
					char_position_y=(14-((240-my_char.y)/16));
					char_position_y_do=false;
				}
			}
			if(char_position_y_do==false&&char_position_x_do==false)
			{
				char_position_do=false;
			}
			//アニメーション
			if(time_counter%5==0){
				
				char_sprite_counter++;
				if(char_sprite_counter==8){
					char_sprite_counter=0;
				}
								
			}
			if(time_counter%2==0){
				if(line_color_down==false){
					line_color++;
					if(line_color==128){
						line_color=127;
						line_color_down=true;
					}
				}else{
					line_color--;
					if(line_color==-1){
						line_color_1++;
						if(line_color_1==4){
							line_color_1=0;
						}
						line_color=0;
						line_color_down=false;
					}
				}
			}
			
			for(i=1;i<20;i++){
				switch(line_color_1)
				{
					case 0:
						line.r = 255-line_color; line.g = 255-line_color; line.b = line_color;
						break;
					case 1:
						line.r = 255-line_color; line.g = line_color; line.b = 255-line_color;
						break;
					case 2:
						line.r = line_color; line.g = 255-line_color; line.b = 255-line_color;
						break;
					case 3:
						line.r = 255-line_color; line.g = line_color; line.b = 255-line_color;
						break;
				}
				line.x[0]=i*16;
				line.x[1]=i*16;
				line.y[0]=16;
				line.y[1]=209;
				GsSortLine(&line);
			}
			for(i=1;i<14;i++){
				switch(line_color_1)
				{
					case 0:
						line.r = line_color; line.g = 255-line_color; line.b = 255-line_color;
						break;
					case 1:
						line.r = 255-line_color; line.g = line_color; line.b = 255-line_color;
						break;
					case 2:
						line.r = 255-line_color; line.g = line_color; line.b = 255-line_color;
						break;
					case 3:
						line.r = 255-line_color; line.g = 255-line_color; line.b = line_color;
						break;
				}
				line.x[0]=16;
				line.x[1]=305;
				line.y[0]=i*16;
				line.y[1]=i*16;
				GsSortLine(&line);
			}
			my_char.u = char_sprite_counter*16;
			my_char.v = char_direction*16;
			GsSortSprite(&my_char);
			GsPrintFont(0,0, "%d",time_counter);
			GsPrintFont(30,0, "%d,%d",my_char.x,my_char.y);
			GsPrintFont(100,0, "%d,%d",char_position_x,char_position_y);
			GsPrintFont(130,0, "%d",line_color_1);
			GsPrintFont(180,0, "%d",line_color);
			if(char_sprite_counter==8){
				char_sprite_counter=0;
			}
			GsDrawList();
			while(GsIsDrawing());
			display_is_old=0;
		}
	}
}