/**************************************************************************************************************************************************************************

***************************************************************************************************************************************************************************
*  -这个是一个i wanna游戏，取名为：i wanna fight with C                                                                                                                   *
*  -此项目为我们共同完成的C语言作业,代码均为手打，无任何复制或照抄。                                                       *
*  -此外用到了Easyx自带的头文件<graphics.h>，目前只兼容VC++，因此请下载安装Easyx并用VC++运行此程序（Codeblocks貌似运行不起来）                                            *
*  -科普：i wanna 为一款变态像素小游戏系列，以坑人和高难度操作出名，本家作品为 “i wanna be the guy”。感兴趣的伙伴可以上百度搜索 “delicious fruit” 即可下载此系列游戏  *
*  -代码量真的特别大，难度也较高，从hithub,CSDN，Bilibili等地方自学写的作品，求求老师多给点分吧来弥补损耗掉的头发吧 （＞人＜；）                                          *
*  -祝大家游戏愉快！！（可能游戏里有一些小bug会影响游戏体验，希望大家不要太介意）                                                                                         *
***************************************************************************************************************************************************************************

***************************************************************************************************************************************************************************/

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>

#define Weight 800        //游戏画面长
#define High 608          //游戏画面宽

#define bian 32           //砖块边长
#define high_ch 21        //人物长
#define weight_ch 11      //人物宽


 
IMAGE img_kid_right;              //往右朝向kid
IMAGE img_kid_left;               //往左朝向kid
IMAGE img_kid_run_right;          //往右运动kid图片
IMAGE img_kid_run_left;           //往左运动kid图片
IMAGE img_kid_jump_right;         //往右朝向跳起kid图片
IMAGE img_kid_jump_left;          //往左朝向跳起kid图片
IMAGE img_kid_fall_right;
IMAGE img_kid_fall_left;
IMAGE img_zhuankuai;              //砖块图片
IMAGE img_ci;                     //刺图片
IMAGE GAMEOVER  ;                  //GAMEOVER图片

int fps = 20;               //帧数
float jump1 = 12;         //一段跳速度
float jump2 = 9;          //二段跳速度
float gravity = 1;      //重力加速度

int level = 1;           // 存档点编号
int isdie = 0;           //人物是否死亡 0存活 1死亡 2换关
int ischange = 0;        //地图转换
int gamestatus = 0;      //游戏状态，0为初始菜单界面，1为正常游戏，2为结束游戏状态，3为游戏暂停

int towards = 1;        //判断方向
int ch_vx = 6 ;         //人物运动水平速度
float ch_vy = 0;       //任务运动竖直速度
int left_i = 0;        //向左行走动画序号
int right_i = 0;       //向右行走动画序号
int isOnFloor = 0;     //判断是否在地面上
int leftjump = 2;      //剩余跳跃次数
int songtimes = 0;     //空中松开shift次数
int maps[25][19];      //地图格子
int mapcolor[Weight][High]; //地图像素点颜色

int ch_x = bian;                         //人物横坐标（左上角像素点）
int judge_ch_x_behind = ch_x + 7   ;                       //人物后方判定点横坐标（左朝向：judge_ch_x_behind = ch_x + 5 + weight_ch）                           
int judge_ch_x_front = ch_x + weight_ch + 7 ;             //人物前方判定点横坐标 (左朝向：judge_ch_x_front = ch_x + 5) 
int ch_y = High - (bian + high_ch) ;                       //人物纵坐标（左上角像素点）
int judge_ch_y_foot = ch_y + high_ch;                            //人物脚部判定
int judge_ch_y_head = ch_y;                                      //人物头部判定                            

char input;                                       //获取键盘输入


void background();                                //游戏背景(不包括方块)
void Mapcolor();                                  //游戏背景颜色（包括方块）
void levels();                                    //关卡
void level1();
int judgestate();                       //碰撞状态
int istouch();                           //判定是否碰撞     0：空中  1:往右撞到砖块左侧  2：往左撞到砖块右侧   3：往上撞到砖块下侧    4：往下撞到砖块上方   5：撞到有杀伤力的物品
int istouchzhuankuai();                  //判定碰撞类型是否为砖块
void judgepoint();                                //碰撞点函数
void kidwait();                                   //无操作下的kid动画
void kidrun();                                    //kid普通跑的动画
void kidjump1();                                  //kid一段跳
void kidjump2();                                  //kid二段跳
void kidfall();                                   //kid自由落体
void zhuankuai(int a,int b);                      //砖块图片
void ci(int a,int b);                             //刺图片
void map1();                                      //第一关地图绘画
void map2();                                      //第二关地图绘画

void background()
{
	int i,j;
	for (i = 0; i <= Weight; i++)
	{
		for (j = 0; j <= High; j++)
		{
			putpixel(i,j, 0xE0F0E6);
		}
	}
}

void zhuankuai(int a, int b)
{

	loadimage(&img_zhuankuai,"zhuankuai.png");
	putimage(a*bian,b*bian,bian,bian,&img_zhuankuai,0,0);
}

void ci(int a,int b)
{
	int i,j,c;
	if (maps[a][b] == 2)
	    loadimage(&img_ci,"ci.png");
	else if (maps[a][b] == 3)
		loadimage(&img_ci,"ci2.png");
	else if (maps[a][b] == 4)
		loadimage(&img_ci,"ci3.png");
	else if (maps[a][b] == 5)
		loadimage(&img_ci,"ci4.png");
	putimage(a*bian,b*bian,bian,bian,&img_ci,0,0);
	for(i = a*bian; i < a*bian + bian ; i++)
	{
		for(j = b*bian; j < b *bian + bian; j ++)
		{
			c = getpixel(i, j);
            if(c == 0xffffff)
	        putpixel(i, j, 0xE0F0E6);
		}
	}
}

//得到背景每个像素点的颜色
void Mapcolor()
{
	for (int i = 0; i < Weight; i ++)
	{
		for (int j = 0; j < High; j ++)
		{
			mapcolor[i][j] = getpixel(i, j);
		}
	}
}

//关卡选择器

void levels()
{
	if (level == 1)
	{
		level1();
	}
}

void level1()
{
	background();
	map2();
	Mapcolor();
}

void map1()
{
	int i,j;
	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			maps[i][j] = 0;
	maps[0][18] = 1; maps[1][18] = 1; maps[2][18] = 1;
	maps[3][16] = 1; maps[4][16] = 1; maps[5][17] = 1;
	maps[2][2] = 2;
	maps[2][3] = 3;
	maps[2][4] = 4;
	maps[2][5] = 5;
	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			if(maps[i][j] == 1)
				zhuankuai(i,j);
			else if(maps[i][j] == 2 || maps[i][j] == 3 || maps[i][j] == 4 || maps[i][j] == 5)        //2：刺往上；3：刺往下；4：刺往左；5：刺往右
				ci(i,j);
}
void map2()
{
	int i,j,k,l;
	int a,b;
	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			maps[i][j] = 0;
for(k=0;k<25;k++)
{
maps[k][18]=1;
maps[k][14]=1;
maps[k][13]=1;
maps[k][0]=1;
maps[k][1]=1;
}
for(k=2;k<19;k = k+2)
{
	maps[k][18]=2;
}
for(k=3;k<20;k = k+2)
{
	maps[k][16]=2;
}
for (l=0;l<19;l++)
{
maps[24][l]=1;
}
for(l=0;l<14;l++)
{
maps[0][l]=1;
}
for(l=3;l<11;l++)
{
	maps[4][l]=1;
	maps[5][l]=1;
}
for(l=2;l<11;l++)
{
	maps[8][l]=1;
}
maps[23][17]=1;maps[23][16]=1;maps[23][15]=1;maps[23][14]=0;maps[23][13]=0;maps[23][1]=0;maps[23][0]=0;maps[23][4]=1;
maps[22][17]=1;maps[22][16]=1;maps[22][14]=0;maps[22][13]=0;maps[22][1]=0;maps[22][0]=0;maps[22][1]=1;
maps[21][17]=1;maps[21][14]=0;
maps[1][10]=1;
maps[2][8]=1;maps[2][5]=1;maps[2][7]=2;
maps[3][8]=1;
maps[8][6]=0;maps[8][5]=0;
maps[11][9]=1;
maps[12][9]=1;
maps[15][7]=1;
maps[16][7]=1;
maps[19][5]=1;
maps[20][5]=1;
for(a = 0;a<25;a++)
		for(b = 0; b<19; b++)
			if(maps[a][b] == 1)
				zhuankuai(a,b);
			else if(maps[a][b] == 2 || maps[a][b] == 3 || maps[a][b] == 4 || maps[a][b] == 5)        //2：刺往上；3：刺往下；4：刺往左；5：刺往右
				ci(a,b);
}


//判定是否碰撞     0：空中       1:往右撞到砖块左侧        2：往左撞到砖块右侧       3：往上撞到砖块下侧           4：往下撞到砖块上方        5：撞到有杀伤力的物品

int istouch()
{
	float vy = ch_vy;
	if(ch_vy <= - bian)
		vy = - bian + 1;
	judgepoint();
	if(istouchzhuankuai() == 1)
		if(maps[(judge_ch_x_front + ch_vx * towards)/ bian][(judge_ch_y_foot - 1)/ bian ] == 1 && towards == 1 )
		{
			return 1;
		}
		if(maps[(judge_ch_x_front + ch_vx * towards )/ bian ][(judge_ch_y_foot - 1)/ bian ] == 1 && towards == -1)
		{
			return 2;
		}
		if(maps[(judge_ch_x_front - towards)/ bian][((int)(judge_ch_y_head - vy))/ bian] == 1)
		{
			return 3;
		}
		if(maps[(judge_ch_x_front - towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1 || maps[(judge_ch_x_behind - towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1)
			return 4;
	return 0;

}

//碰撞状态判定
int judgestate()
{
	if (istouch() == 1)
	{
		judge_ch_x_front = ((judge_ch_x_front + ch_vx * towards)/ bian ) * bian;
		ch_vx = 0;
		ch_x = judge_ch_x_front - weight_ch - 7;
		return 1;
	}
	if (istouch() == 2)
	{
		judge_ch_x_front = ((judge_ch_x_front  + ch_vx * towards)/ bian + 1) * bian - 1 ;
		ch_vx = 0;
		ch_x = judge_ch_x_front - 5 ;
		return 2;
	}
	if (istouch() == 3)
	{
		judge_ch_y_head = ((judge_ch_y_head - ch_vy)/ bian ) * bian;
		ch_vy = 0;
		ch_y = judge_ch_y_head;
		return 3;
	}
	if (istouch() == 4 )
	{
		judge_ch_y_foot = (((int)(judge_ch_y_foot - ch_vy))/ bian ) * bian;
		ch_vy = 0;
		ch_y = judge_ch_y_foot - high_ch;
		return 4;
	}
	if (istouch() == 0)
	{
		return 0;
	}
	else 
		return 7;
}

int istouchzhuankuai()
{
	float vy = ch_vy;
	if(ch_vy <= - bian + 1)
		vy =  - bian + 1;
	if(maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1 || 
		maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_head - vy))/ bian] == 1 || 
		maps[(judge_ch_x_behind)/ bian][((int)(judge_ch_y_head - vy))/ bian ] == 1 || 
		maps[judge_ch_x_behind  / bian][((int)(judge_ch_y_foot - vy))/ bian] == 1)
		return 1;
	else
		return 0;
}

void judgepoint()
{
	if(towards == 1)
	{
		judge_ch_x_behind = ch_x + 7   ; 
		judge_ch_x_front = ch_x + weight_ch + 7 ; 
	}
	else
	{
		judge_ch_x_behind = ch_x + 5 + weight_ch;
		judge_ch_x_front = ch_x + 5;
	}
	judge_ch_y_foot = ch_y + high_ch;
	judge_ch_y_head = ch_y; 
}


//kid不动的时候动画

void kidwait()                          
{
	ch_vx = 5;

	loadimage(&img_kid_right, "img_kid.png");
	loadimage(&img_kid_left,"img_kid1.png");
	int k,m,n;
	BeginBatchDraw();
	if(towards > 0)               //往右朝向
	{
    	for(k=0; k <= 12;)
		{   
	    	 for(m = ch_x - ch_vx - 24; m <= ch_x + ch_vx + 24; m ++)
			 {
		        for(n = ch_y - 21 + ch_vy; n <= ch_y + 21 - ch_vy; n ++)
				{
		         putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
				}
			 }
	    	 switch (k)
			 {
		         case 0:
			         putimage(ch_x,ch_y,24,21,&img_kid_right,28*k+1,3);
				     break;
			     case 1:
				     putimage(ch_x,ch_y,24,21,&img_kid_right,28*(k-1)+1,3);
				     break;
			     case 2:
				     putimage(ch_x,ch_y,24,21,&img_kid_right,28*(k-2)+1,3);
				     break;
		         case 3:
				     putimage(ch_x,ch_y,24,21,&img_kid_right,28*(k-2),3);
                     break;
			     case 4:
				     putimage(ch_x,ch_y,24,21,&img_kid_right,28*(k-3),3);
                     break;
			     case 5:
				     putimage(ch_x,ch_y,24,21,&img_kid_right,28*(k-4),3);
                     break;
			     case 6:
				     putimage(ch_x,ch_y,24,21,&img_kid_right,28*(k-4),3);
				     break;
			     case 7:
				     putimage(ch_x,ch_y,24,21,&img_kid_right,28*(k-5),3);
				     break;
			     case 8:
				     putimage(ch_x,ch_y,24,21,&img_kid_right,28*(k-6),3);
				     break;
		         case 9:
				     putimage(ch_x,ch_y,24,21,&img_kid_right,28*(k-6)-1,3);
			     	 break;
			     case 10:
				     putimage(ch_x,ch_y,24,21,&img_kid_right,28*(k-7)-1,3);
			    	 break;
			     case 11:
				     putimage(ch_x,ch_y,24,21,&img_kid_right,28*(k-8)-1,3);
			    	 break;
			 }                                                             //导入kid图片
	          int c;
	          for(int i = ch_x; i <= ch_x + 24; i ++)
			  {
		          for(int j = ch_y - 21; j <= ch_y + 20; j ++)
				  {
		           c = getpixel(i, j);
                   if(c == 0xffffff)
			           putpixel(i, j, mapcolor[i][j]);          //去除kid之外的颜色
				  }
			  }
	 	      FlushBatchDraw();
	     	  Sleep(fps);
		      k++;
		      if(k == 12)
			      k = 0;
	          if(kbhit())
			  {
			      if((GetAsyncKeyState(VK_LEFT)&0x8000)||(GetAsyncKeyState(VK_RIGHT)&0x8000)||(GetAsyncKeyState(VK_LSHIFT)&0x8000))
				      break;
			  }
		}
	}
	else 
	{
		for(k=0; k <= 12;)
		{   
	    	 for(m = ch_x - ch_vx -24; m <= ch_x + ch_vx + 24; m ++)
			 {
		        for(n = ch_y - 21 + ch_vy; n <= ch_y + 21 - ch_vy; n ++)
				{
		         putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
				}
			 }
	    	 switch (k)
			 {
		         case 0:
			         putimage(ch_x,ch_y,24,21,&img_kid_left,174-(28*(k)+1+24),3);
				     break;
			     case 1:
				     putimage(ch_x,ch_y,24,21,&img_kid_left,174-(28*(k-1)+1+24),3);
				     break;
			     case 2:
				     putimage(ch_x,ch_y,24,21,&img_kid_left,174-(28*(k-2)+1+24),3);
				     break;
		         case 3:
				     putimage(ch_x,ch_y,24,21,&img_kid_left,174-(28*(k-2)+24),3);
                     break;
			     case 4:
				     putimage(ch_x,ch_y,24,21,&img_kid_left,174-(28*(k-3)+24),3);
                     break;
			     case 5:
				     putimage(ch_x,ch_y,24,21,&img_kid_left,174-(28*(k-4)+24),3);
                     break;
			     case 6:
				     putimage(ch_x,ch_y,24,21,&img_kid_left,174-(28*(k-4)+24),3);
				     break;
			     case 7:
				     putimage(ch_x,ch_y,24,21,&img_kid_left,174-(28*(k-5)+24),3);
				     break;
			     case 8:
				     putimage(ch_x,ch_y,24,21,&img_kid_left,174-(28*(k-6)+24),3);
				     break;
		         case 9:
				     putimage(ch_x,ch_y,24,21,&img_kid_left,174-(28*(k-6)-1+24),3);
			     	 break;
			     case 10:
				     putimage(ch_x,ch_y,24,21,&img_kid_left,174-(28*(k-7)-1+24),3);
			    	 break;
			     case 11:
				     putimage(ch_x,ch_y,24,21,&img_kid_left,174-(28*(k-8)-1+24),3);
			    	 break;
			 }                                                             //导入kid图片
	          int c;
	          for(int i = ch_x; i <= ch_x + 24; i ++)
			  {
		          for(int j = ch_y - 21; j <= ch_y + 20; j ++)
				  {
		           c = getpixel(i, j);
                   if(c == 0xffffff)
			           putpixel(i, j, mapcolor[i][j]);          //去除kid之外的颜色
				  }
			  }
	 	      FlushBatchDraw();
	     	  Sleep(fps);
		      k++;
		      if(k == 12)
			      k = 0;
	          if(kbhit())
			  {
			      if((GetAsyncKeyState(VK_LEFT)&0x8000)||(GetAsyncKeyState(VK_RIGHT)&0x8000)||(GetAsyncKeyState(VK_LSHIFT)&0x8000))
				      break;
			  }
		}
	}
	if((GetAsyncKeyState(VK_LSHIFT)&0x8000))
		kidjump1();
	 kidrun();
	getch();
	EndBatchDraw();
}

//kid跑步动画
void kidrun()
{
	int m,n,i,j;
	BeginBatchDraw();
	right_i = 0;
	left_i = 0;
	while(1)
	{
		if((GetAsyncKeyState(VK_LSHIFT)&0x8000))
			break;
		if(judgestate() == 0)
		{
			break;
		}

		if(kbhit())
		{
	        if((GetAsyncKeyState(VK_RIGHT)&0x8000))                             //往右运动
			{
				towards = 1;
				if(judgestate() == 1)
					ch_vx = 0;
				else
					ch_vx = 6;
				ch_x = ch_vx * towards + ch_x ;

		        for(m = ch_x - 2*6 -24; m <= ch_x + 2*6 + 24; m ++)
				{
		            for(n = ch_y - 21 + ch_vy; n <= ch_y + 21 - ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
	            loadimage(&img_kid_run_right, "img_kid.png");
		        switch (right_i)
				{

			        case 0:
			 	      	putimage(ch_x,ch_y,24,21,&img_kid_run_right,28*right_i+1,29);
			   	       	break;
			        case 1:
			 	       	putimage(ch_x,ch_y,24,21,&img_kid_run_right,28*right_i+3,29);
                        break;
                    case 2:
			   	       	putimage(ch_x,ch_y,24,21,&img_kid_run_right,28*right_i+3,29);
			   	       	break;
			        case 3:
			   	       	putimage(ch_x,ch_y,24,21,&img_kid_run_right,28*right_i+3,29);
			           	break;
			      	case 4:
			           	putimage(ch_x,ch_y,24,21,&img_kid_run_right,28*right_i+6,29);
			           	break;
				}                                                             //导入kid图片
	            int c;
	            for(i = ch_x; i <= ch_x + 24; i ++)
				{
		            for(j = ch_y; j <= ch_y + 20; j ++)
					{
			            c = getpixel(i, j);
                        if(c == 0xffffff)
				            putpixel(i, j, mapcolor[i][j]);          //去除kid之外的颜色
					}
				}
		        FlushBatchDraw();
			    Sleep(fps);
				right_i ++;
		        if(right_i == 4)
			        right_i = 0;
			}
			else if((GetAsyncKeyState(VK_LEFT)&0x8000))                                      //往左运动动画
			{
				towards = -1;
				if(judgestate() == 2)
					ch_vx = 0;
				else
					ch_vx = 6;
				ch_x = ch_vx * towards + ch_x ;
		        for(m = ch_x - 2*6 -24; m <= ch_x + 2*6 + 24; m ++)
				{
		            for(n = ch_y - 21 + ch_vy; n <= ch_y + 21 - ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
	            loadimage(&img_kid_run_left, "img_kid1.png");
		        switch (left_i)
				{
			        case 0:
			 	       	putimage(ch_x,ch_y,26,21,&img_kid_run_left,174-(28*(left_i+1)),29);
                        break;
                    case 1:
			   	       	putimage(ch_x,ch_y,26,21,&img_kid_run_left,174-(28*(left_i+1)+3),29);
			   	       	break;
			        case 2:
			   	       	putimage(ch_x,ch_y,26,21,&img_kid_run_left,174-(28*(left_i+1)+3),29);
			           	break;
			      	case 3:
			           	putimage(ch_x,ch_y,26,21,&img_kid_run_left,174-(28*(left_i+1)+3),29);
			           	break;
				}                                                             //导入kid图片
	            int c;
	            for(i = ch_x; i <= ch_x + 26; i ++)
				{
		            for(j = ch_y; j <= ch_y + 20; j ++)
					{
			            c = getpixel(i, j);
                        if(c == 0xffffff)
				            putpixel(i, j, mapcolor[i][j]);          //去除kid之外的颜色
					}
				}
		        FlushBatchDraw();
			    Sleep(fps);
				left_i ++;
		        if(left_i == 4)
			        left_i = 0;
			}
			else
				break;
			
		}
		else
			break;
	}
	if((GetAsyncKeyState(VK_LSHIFT)&0x8000))
		kidjump1();
	if(judgestate() == 0)
	{
		leftjump = 1;
		songtimes = 1;
		kidfall();
	}
	kidwait();
	getch();
	EndBatchDraw();
}

//跳跃动画
void kidjump1()
{ 
	leftjump --;
	int m,n,i,j;
	ch_vy = jump1;
	right_i = 0;
	left_i = 0;
	BeginBatchDraw();
	while(1)
    {
		if(songtimes == 1&&(GetAsyncKeyState(VK_LSHIFT)&0x8000))
		{
			break;
		}
		if((GetAsyncKeyState(VK_LEFT)&0x8000))
		{
			if(judgestate() == 2)
				ch_vx = 0;
			else
				ch_vx = 6;
			ch_vx = 6;
			ch_x = ch_x - ch_vx;
			towards = -1;
		}
		else if((GetAsyncKeyState(VK_RIGHT)&0x8000))
		{
			if(judgestate() == 1)
				ch_vx = 0;
			else
				ch_vx = 6;
			ch_x = ch_x + ch_vx;
			towards = 1;
		}
		else 
			ch_vx = 0;
		ch_y = ch_y - ch_vy;
		
		if(!(GetAsyncKeyState(VK_LSHIFT)&0x8000) && songtimes == 0)
		{
			ch_vy = 0.45 * ch_vy;
			songtimes++;
		}

		
		
		if(towards == 1)
		{
            for(m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 2 * ch_vy - 42; n <= ch_y + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
	        loadimage(&img_kid_jump_right, "img_kid.png");
			switch (right_i)
			 {
		         case 0:
			         putimage(ch_x,ch_y ,24,23,&img_kid_jump_right,28*(right_i) + 1,70);
				     break;
			     case 1:
				     putimage(ch_x,ch_y,24,23,&img_kid_jump_right,28*(right_i - 1)+1,70);
				     break;
				 case 2:
				     putimage(ch_x,ch_y ,24,23,&img_kid_jump_right,28*(right_i - 1)-3,70);
				     break;
				 case 3:
				     putimage(ch_x,ch_y ,24,23,&img_kid_jump_right,28*(right_i - 2)-3,70);
				     break;
			 } 
			 int c;
	            for(i = ch_x; i <= ch_x + 26; i ++)
				{
		            for(j = ch_y; j <= ch_y + 23 + ch_vy; j ++)
					{
			            c = getpixel(i, j);
                        if(c == 0xffffff)
				            putpixel(i, j, mapcolor[i][j]);          //去除kid之外的颜色
					}
				}
				FlushBatchDraw();
				Sleep(fps);
				right_i++;
				if(right_i == 4)
					right_i = 0;
				ch_vy = ch_vy - gravity;
				
		}
		else if(towards == -1)
		{ 
		    for (m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 2 * ch_vy - 42; n <= ch_y + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
	            loadimage(&img_kid_jump_left, "img_kid1.png");
		switch (left_i)
			 {
		         case 0:
			         putimage(ch_x,ch_y ,26,23,&img_kid_jump_left,174-(28*(left_i)+1+24),70);
				     break;
			     case 1:
				     putimage(ch_x,ch_y ,26,23,&img_kid_jump_left,174-(28*(left_i - 1)+1+24),70);
				     break;
			 	 case 2:
				     putimage(ch_x,ch_y ,26,23,&img_kid_jump_left,174-(28*(left_i - 1)-3+24),70);
				     break;
				 case 3:
				     putimage(ch_x,ch_y ,26,23,&img_kid_jump_left,174-(28*(left_i - 2)-3+24),70);
				     break;
			 } 
			 int c;
	            for(i = ch_x; i <= ch_x + 26; i ++)
				{
		            for(j = ch_y; j <= ch_y + 23 + ch_vy; j ++)
					{
			            c = getpixel(i, j);
                        if(c == 0xffffff)
				            putpixel(i, j, mapcolor[i][j]);          //去除kid之外的颜色
					}
				}
				FlushBatchDraw();
				Sleep(fps);
				left_i++;
				if(left_i == 4)
					left_i = 0;
				ch_vy = ch_vy - gravity;
		}
		if(ch_vy <=0 )
			break;
	}
	if(songtimes == 1 && (GetAsyncKeyState(VK_LSHIFT)&0x8000))
		kidjump2();
	
	kidfall();

}

void kidjump2()
{ 
	leftjump --;
	int m,n,i,j;
	ch_vy = jump2;
	right_i = 0;
	left_i = 0;
	BeginBatchDraw();
	while(1)
    {
		if((GetAsyncKeyState(VK_LEFT)&0x8000))
		{
			if(judgestate() == 2)
				ch_vx = 0;
			else
				ch_vx = 6;
			ch_x = ch_x - ch_vx;
			towards = -1;
		}
		else if((GetAsyncKeyState(VK_RIGHT)&0x8000))
		{
			if(judgestate() == 1)
				ch_vx = 0;
			else
				ch_vx = 6;
			ch_x = ch_x + ch_vx;
			towards = 1;
		}
		else 
			ch_vx = 0;
		ch_y = ch_y - ch_vy;
		
		if(!(GetAsyncKeyState(VK_LSHIFT)&0x8000))
		{
			ch_vy = 0.45 * ch_vy;
			songtimes ++;
		}

		
		if(towards == 1)
		{
            for(m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 2 * ch_vy - 42; n <= ch_y + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
	        loadimage(&img_kid_jump_right, "img_kid.png");
			switch (right_i)
			 {
		         case 0:
			         putimage(ch_x,ch_y ,24,23,&img_kid_jump_right,28*(right_i) + 1,70);
				     break;
			     case 1:
				     putimage(ch_x,ch_y,24,23,&img_kid_jump_right,28*(right_i - 1)+1,70);
				     break;
				 case 2:
				     putimage(ch_x,ch_y ,24,23,&img_kid_jump_right,28*(right_i - 1)-3,70);
				     break;
				 case 3:
				     putimage(ch_x,ch_y ,24,23,&img_kid_jump_right,28*(right_i - 2)-3,70);
				     break;
			 } 
			 int c;
	            for(i = ch_x; i <= ch_x + 26; i ++)
				{
		            for(j = ch_y; j <= ch_y + 23 + ch_vy; j ++)
					{
			            c = getpixel(i, j);
                        if(c == 0xffffff)
				            putpixel(i, j, mapcolor[i][j]);          //去除kid之外的颜色
					}
				}
				FlushBatchDraw();
				Sleep(fps);
				right_i++;
				if(right_i == 4)
					right_i = 0;
				ch_vy = ch_vy - gravity;
				
		}
		else if(towards == -1)
		{ 
		    for (m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 2 * ch_vy - 42; n <= ch_y + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
	            loadimage(&img_kid_jump_left, "img_kid1.png");
		switch (left_i)
			 {
		         case 0:
			         putimage(ch_x,ch_y ,26,23,&img_kid_jump_left,174-(28*(left_i)+1+24),70);
				     break;
			     case 1:
				     putimage(ch_x,ch_y ,26,23,&img_kid_jump_left,174-(28*(left_i - 1)+1+24),70);
				     break;
			 	 case 2:
				     putimage(ch_x,ch_y ,26,23,&img_kid_jump_left,174-(28*(left_i - 1)-3+24),70);
				     break;
				 case 3:
				     putimage(ch_x,ch_y ,26,23,&img_kid_jump_left,174-(28*(left_i - 2)-3+24),70);
				     break;
			 } 
			 int c;
	            for(i = ch_x; i <= ch_x + 26; i ++)
				{
		            for(j = ch_y; j <= ch_y + 23 + ch_vy; j ++)
					{
			            c = getpixel(i, j);
                        if(c == 0xffffff)
				            putpixel(i, j, mapcolor[i][j]);          //去除kid之外的颜色
					}
				}
				FlushBatchDraw();
				Sleep(fps);
				left_i++;
				if(left_i == 4)
					left_i = 0;
				ch_vy = ch_vy - gravity;
		}
		if(ch_vy <=0 )
			break;
	}
	kidfall();

}

//下降动画
void kidfall()
{ 
	int m,n,i,j;
	right_i = 0;
	left_i = 0;
	BeginBatchDraw();
	while(1)
    {
		if(!(GetAsyncKeyState(VK_LSHIFT)&0x8000) && songtimes ==0 )
		{
			songtimes ++;
		}
		if(songtimes == 1 && leftjump == 1 && (GetAsyncKeyState(VK_LSHIFT)&0x8000))
			break;
		if((GetAsyncKeyState(VK_LEFT)&0x8000))
		{
			if(judgestate() == 2)
				ch_vx = 0;
			else
				ch_vx = 6;
			ch_x = ch_x - ch_vx;
			towards = -1;
		}
		else if((GetAsyncKeyState(VK_RIGHT)&0x8000))
		{
			if(judgestate() == 1)
				ch_vx = 0;
			else
				ch_vx = 6;
			ch_x = ch_x + ch_vx;
			towards = 1;
		}
		else 
			ch_vx = 0;
		ch_y = ch_y - ch_vy;
		float vy = ch_vy;
	        if(ch_vy <= - bian)
		        vy = - bian + 1;
		if(towards == 1)
		{
            for(m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 2 * ch_vy - 42; n <= ch_y + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
	        loadimage(&img_kid_fall_right, "img_kid.png");
			switch (right_i)
			 {
		         case 0:
			         putimage(ch_x,ch_y,24,23,&img_kid_fall_right,28*(right_i) + 4,100);
				     break;
			     case 1:
				     putimage(ch_x,ch_y,24,23,&img_kid_fall_right,28*(right_i - 1)+4,100);
				     break;
				 case 2:
				     putimage(ch_x,ch_y,24,23,&img_kid_fall_right,28*(right_i - 1)+5,100);
				     break;
				 case 3:
				     putimage(ch_x,ch_y,24,23,&img_kid_fall_right,28*(right_i - 2)+5,100);
				     break;
			 } 
			 int c;
	         for(i = ch_x; i <= ch_x + 26; i ++)
			{
		        for(j = ch_y; j <= ch_y + 23; j ++)
				{
			         c = getpixel(i, j);
                     if(c == 0xffffff)
				         putpixel(i, j, mapcolor[i][j]);          //去除kid之外的颜色
				}
			}
		    FlushBatchDraw();
			Sleep(fps);
			right_i++;
			if(right_i == 4)
				right_i = 0;
			if(judgestate() == 4)
			{
					for(m = ch_x - 2*6 -24; m <= ch_x + 2*6+ 24; m ++)
				{
		            for(n = 0; n <= judge_ch_y_foot; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
				break;
			}
			if(judgestate() == 1 && (maps[(judge_ch_x_front - towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1 || 
					maps[(judge_ch_x_behind - towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1))
				{
					judge_ch_y_foot = (((int)(judge_ch_y_foot - ch_vy))/ bian ) * bian;
	            	ch_vy = 0;
            		ch_y = judge_ch_y_foot - high_ch;
					for(m = ch_x - 2*6 -24; m <= ch_x + 2*ch_vx + 24; m ++)
					{
		                for(n = 0; n <= judge_ch_y_foot; n ++)
						{
			                putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
						}
					}
					break;
				}
		}
		else if(towards == -1)
		{ 
		    for(m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 2 * ch_vy - 42; n <= ch_y + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
	            loadimage(&img_kid_fall_left, "img_kid1.png");
		switch (left_i)
			 {
		         case 0:
			         putimage(ch_x,ch_y,26,23,&img_kid_fall_left,174-(28*(left_i)+4+24),100);
				     break;
			     case 1:
				     putimage(ch_x,ch_y,26,23,&img_kid_fall_left,174-(28*(left_i - 1)+4+24),100);
				     break;
			 	 case 2:
				     putimage(ch_x,ch_y,26,23,&img_kid_fall_left,174-(28*(left_i - 1)+5+24),100);
				     break;
				 case 3:
				     putimage(ch_x,ch_y,26,23,&img_kid_fall_left,174-(28*(left_i - 2)+5+24),100);
				     break;
			 } 
			 int c;
	            for(i = ch_x; i <= ch_x + 26; i ++)
				{
		            for(j = ch_y; j <= ch_y + 23; j ++)
					{
			            c = getpixel(i, j);
                        if(c == 0xffffff)
				            putpixel(i, j, mapcolor[i][j]);          //去除kid之外的颜色
					}
				}
				FlushBatchDraw();
				Sleep(fps);
				left_i++;
				if(left_i == 4)
					left_i = 0;
				if(judgestate() == 4)
				{
					for(m = ch_x - 2*6 -24; m <= ch_x + 2*ch_vx + 24; m ++)
					{
		                for(n = 0; n <= judge_ch_y_foot; n ++)
						{
			                putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
						}
					}
				break;
				}
				if(judgestate() == 2 && (maps[(judge_ch_x_front - towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1 || 
					maps[(judge_ch_x_behind - towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1))
				{
					judge_ch_y_foot = (((int)(judge_ch_y_foot - ch_vy))/ bian ) * bian;
	            	ch_vy = 0;
            		ch_y = judge_ch_y_foot - high_ch;
					for(m = ch_x - 2*6 -24; m <= ch_x + 2*ch_vx + 24; m ++)
					{
		                for(n = 0; n <= judge_ch_y_foot; n ++)
						{
			                putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
						}
					}
					break;
				}
		}
		ch_vy = ch_vy - gravity;
	}
	if(songtimes == 1 && leftjump == 1 && (GetAsyncKeyState(VK_LSHIFT)&0x8000))
		kidjump2();
	leftjump = 2;
	songtimes = 0;
	kidrun();
}

void dead()
{
	int i,j,c;
	{
	    loadimage(&GAMEOVER,"gameover.png");
	    putimage(20,220,758,160,&GAMEOVER,0,0);
		for (1 == 20; i <= 778 ; i ++)
		{
			for(j = 220; j <= 380; j ++)
			{
			c = getpixel(i, j);
            if(c == 0xffffff)
	            putpixel(i, j, mapcolor[i][j]); 
			}
		}

	}
}


void main()
{
    initgraph(Weight,High);
	levels();
	//dead();
	kidwait();
	closegraph();
}

