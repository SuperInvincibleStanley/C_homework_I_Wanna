/**************************************************************************************************************************************************************************

***************************************************************************************************************************************************************************
*  -这个是一个i wanna游戏，取名为：i wanna fight with C                                                                                                                   *
*  -此项目为 20 级生工班 王焕钧，冯铭俊，吕辰越，韦庆波，张昊天共同完成的C语言作业,代码均为手打，无任何复制或照抄。                                                       *
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


IMAGE img_start;
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
IMAGE img_ej;                     //表情包第一关
IMAGE GAMEOVER  ;                  //GAMEOVER图片

int fps = 20;               //帧数
float jump1 = 12;         //一段跳速度
float jump2 = 9;          //二段跳速度
float gravity = 1;      //重力加速度

int level = 6;           // 存档点编号
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
int judgemaps[Weight][High];     //判定像素


int ch_x = bian;                         //人物横坐标（左上角像素点）
int ch_x1 = ch_x ;                               //上一帧人物横坐标
int judge_ch_x_behind = ch_x + 7   ;                       //人物后方判定点横坐标（左朝向：judge_ch_x_behind = ch_x + 5 + weight_ch）                           
int judge_ch_x_front = ch_x + weight_ch + 7 ;             //人物前方判定点横坐标 (左朝向：judge_ch_x_front = ch_x + 5) 
int ch_y = High - (bian + high_ch) ;                       //人物纵坐标（左上角像素点）
int ch_y1 = ch_y;                                                //上一帧人物纵坐标
int judge_ch_y_foot = ch_y + high_ch;                            //人物脚部判定
int judge_ch_y_head = ch_y;                                      //人物头部判定                            

char input;                                       //获取键盘输入

void start();                                      //开始界面
void background();                                //游戏背景(不包括方块)
void Mapcolor();                                  //游戏背景颜色（包括方块）
void levels();                                    //关卡
void level1();
void level2();
void level3();
void level4();
void level5();
void level6();
void level7();
int judgestate();                       //碰撞状态
int istouch();                           //判定是否碰撞     0：空中  1:往右撞到砖块左侧  2：往左撞到砖块右侧   3：往上撞到砖块下侧    4：往下撞到砖块上方   5：撞到有杀伤力的物品
int istouchzhuankuai();                  //判定碰撞类型是否为砖块
/*int istouchci();                          //判定碰撞类型是否为刺
int judgeci();                            //刺的判定轮廓*/
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
void map3();
void map4();
void map5();
void map6();    
void map7(); 
void dead();                                     //死亡动画

void start()
{
	loadimage(&img_start,"start.png");
	putimage(0,0,Weight,High,&img_start,0,0);
	while(1)
	{
		if((GetAsyncKeyState(VK_LSHIFT)&0x8000))
			break;
		if((GetAsyncKeyState(VK_ESCAPE)&0x8000))
			exit(0);
	}
}
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
	{
		loadimage(&img_ci,"ci.png");
		for(i = 1; i <= 15; i ++)
		{
			for(j = 30; j >= 31 - 2 * i; j--)
			{
				judgemaps[a*bian+i][b*bian+j] = 1;
			}
		}
		for(i = 16; i <= 30; i ++)
		{
			for(j = 30; j >= 2*(i-15)-1; j--)
			{
				judgemaps[a*bian+i][b*bian+j] = 1;
			}
		}
		
	}
	else if (maps[a][b] == 3)
	{
		loadimage(&img_ci,"ci2.png");
		for(i = 1; i <= 15; i ++)
		{
			for(j = 1; j <= 2 * i ;j++)
			{
				judgemaps[a*bian+i][b*bian+j] = 1;
			}
		}
		for(i = 16; i <= 30; i ++)
		{
			for(j = 1; j <= 2*(31-i); j++)
			{
				judgemaps[a*bian+i][b*bian+j] = 1;
			}
		}
		
	}
	else if (maps[a][b] == 4)
	{
		loadimage(&img_ci,"ci3.png");
		for(j = 1; j <= 15; j++)
		{
			for(i = 30; i >= 31 - 2*j; i--)
			{
				judgemaps[a*bian+i][b*bian+j] = 1;
			}
		}
		for(j = 16; j <= 30; j++)
		{
			for(i = 30; i >=2*(j-15)-1;i--)
			{
				judgemaps[a*bian+i][b*bian+j] = 1;
			}
		}
		
	}
	else if (maps[a][b] == 5)
	{
		loadimage(&img_ci,"ci4.png");
		for(j = 1; j <= 15; j++)
		{
			for(i = 1; i <= 2*j; i++)
			{
				judgemaps[a*bian+i][b*bian+j] = 1;
			}
		}
		for(j = 16; j<= 30; j++)
		{
			for(i = 1; i <=2*(31-j);i++)
			{
				judgemaps[a*bian+i][b*bian+j] = 1;
			}
		}
	}
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
	for(int i = 0; i < Weight; i++)
		for(int j =0; j < High; j++)
			judgemaps[i][j] = 0; //初始化判定
	background();
	towards = 1;
	if (level == 1)
	{
		level1();
	}
	else if(level == 2)
	{
		level2();
	}
	else if(level == 3)
	{
		level3();
	}
	else if(level == 4)
	{
		level4();
	}
	else if(level == 5)
	{
		level5();
	}
	else if(level == 6)
	{
		level6();
	}
	else
	{
		level7();
	}
}

void level1()
{
	ch_x = bian;
	ch_y = High - (bian + high_ch) ;
	ch_x1 = ch_x;
	ch_y1 = ch_y;
	judgepoint();
	map1();
	Mapcolor();
}

void level2()
{
	ch_x = bian;
	ch_y = High - (bian + high_ch) ;
	ch_x1 = ch_x;
	ch_y1 = ch_y;
	judgepoint();
	map2();
	Mapcolor();
}

void level3()
{
	ch_x = bian;
	ch_y = High - (bian + high_ch) ;
	ch_x1 = ch_x;
	ch_y1 = ch_y;
	judgepoint();
	map3();
	Mapcolor();
}

void level4()
{
	ch_x = bian;
	ch_y = High - (bian + high_ch) ;
	ch_x1 = ch_x;
	ch_y1 = ch_y;
	judgepoint();
	map4();
	Mapcolor();
}

void level5()
{
	ch_x = bian;
	ch_y = High - (bian + high_ch) ;
	ch_x1 = ch_x;
	ch_y1 = ch_y;
	judgepoint();
	map5();
	Mapcolor();
}

void level6()
{
	ch_x = bian;
	ch_y =  (3*bian - high_ch) ;
	ch_x1 = ch_x;
	ch_y1 = ch_y;
	judgepoint();
	map6();
	Mapcolor();
}

void level7()
{
	ch_x = 23*bian;
	ch_y =  (7*bian - high_ch) ;
	ch_x1 = ch_x;
	ch_y1 = ch_y;
	judgepoint();
	map7();
	Mapcolor();
}

void map1()
{
	loadimage(&img_ej,"ej.png");
	putimage(505,260,358,328,&img_ej,0,0);
	int i,j;
	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			maps[i][j] = 0;
	int a;
	for(a = 0; a < 25; a ++)
    {
		maps[a][18] = 1;
		maps[a][0] = 1;
	}
	maps[10][17] = 1;
	maps[11][17] = 1;
	maps[12][17] = 1;
	maps[4][11] = 2;
	maps[10][10] = 1;
	maps[10][11] = 1;
	maps[9][10] = 4;
	maps[10][5] = 3;
	maps[1][6] = 5;
	for(a = 2; a < 11; a ++)
	{
		maps[a][4] = 1;
		maps[a][3] = 1;
		maps[a][2] = 1;
	}
	for(a = 12; a < 23; a++)
	{
		maps[a][2] =1;
	}
	maps[2][3] = 0;
	for(a = 13; a < 24; a++)
	{
		maps[a][7] = 1;
	}
	maps[21][6] = 2;
	maps[21][4] = 3;
	maps[21][3] = 1;
	maps[17][6] = 1;
	maps[17][5] = 2;
	maps[17][3] = 3;
	maps[13][6] = 1;
	maps[13][5] = 1;
	maps[13][4] = 2;
	maps[12][10] = 5;
	maps[13][14] = 4;
	maps[13][17] = 2;
	for(a = 8;a < 18; a++)
	{
		maps[14][a] = 1;
	}
	maps[14][16] = 0;
	for(a = 0; a < 10; a ++)
	{
		maps[a][7] = 1;
	}
	for(a = 0 ; a < 19; a++)
	{
		maps[0][a] = 1;
		maps[11][a] = 1;
		maps[24][a] = 1;
	}
	maps[11][1] = 0;
	maps[11][2] = 2;
	for(a = 2 ; a < 12; a ++)
	{
		maps[a][12] = 1;
	}
	for(a = 0; a < 10; a ++)
	{
		maps[a][15] = 1;
	}
	for(a = 15; a < 24; a++)
	{
		maps[a][15] = 1;
	}
	maps[24][17] = 0;
	maps[24][16] = 0;
	maps[23][16] = 3;
	maps[24][17] = 6;
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
loadimage(&img_ej,"ej2.jpg");
putimage(288,64,96,96,&img_ej,0,0);
maps[k][18]=1;
maps[k][14]=1;
maps[k][13]=1;
maps[k][0]=1;
maps[k][1]=1;
}
for(k=2;k<19;k = k+2)
{
	maps[k][17]=2;
}
for(k=3;k<20;k = k+2)
{
	maps[k][15]=3;
}
for(k=9;k<18;k=k+4)
{
	maps[k][12]=2;
	maps[k+1][12]=2;
}
for(k=12;k<23;k++)
{
	maps[k][2]=3;
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
for(l=2;l<11;l++)
{
	maps[7][l]=4;
}
for(l=5;l<12;l++)
{
	maps[23][l]=4;
}
maps[23][17]=1;maps[23][16]=1;maps[23][15]=1;maps[23][14]=0;maps[23][13]=0;maps[23][1]=0;maps[23][0]=0;maps[23][4]=1;
maps[22][17]=1;maps[22][16]=1;maps[22][14]=0;maps[22][13]=0;maps[22][1]=0;maps[22][0]=0;maps[22][1]=1;
maps[21][17]=1;maps[21][14]=0;maps[21][12]=2;maps[21][5]=1;
maps[1][10]=1;maps[1][2]=5;maps[1][3]=5;maps[1][4]=0;maps[1][5]=5;maps[1][11]=1;maps[1][12]=1;
maps[2][8]=1;maps[2][5]=1;maps[2][7]=2;maps[2][11]=5;maps[2][12]=5;
maps[3][8]=1;
maps[6][12]=2;
maps[7][12]=2;maps[7][5]=0;maps[7][6]=0;
maps[8][6]=0;maps[8][5]=3;
maps[11][9]=1;maps[11][8]=2;maps[11][10]=3;
maps[12][9]=1;maps[12][10]=3;
maps[15][7]=1;
maps[16][7]=1;maps[16][6]=2;
maps[19][5]=1;
maps[20][5]=1;maps[20][4]=2;
for(a = 0;a<25;a++)
		for(b = 0; b<19; b++)
			if(maps[a][b] == 1)
				zhuankuai(a,b);
			else if(maps[a][b] == 2 || maps[a][b] == 3 || maps[a][b] == 4 || maps[a][b] == 5)        //2：刺往上；3：刺往下；4：刺往左；5：刺往右
				ci(a,b);
}

void map3()
{
	int i,j;
	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			maps[i][j] = 0;
	for(i=1;i<25;i++) 
	{maps[i][0]=1;
	maps[i][18]=1;}
	for(j=0;j<19;j++){
	maps[0][j]=1;}
   for(j=1;j<16;j++){
	maps[24][j]=1;}
for(j=1;j<16;j++){
	maps[1][j]=5;}

maps[3][17]=1;maps[3][16]=1;maps[3][15]=1;maps[3][13]=1;maps[3][11]=1;maps[3][9]=1;maps[3][7]=1;maps[3][5]=1;maps[3][3]=1;
for(j=3;j<18;j++){
	maps[4][j]=1;}
for(i=3;i<24;i++) 
maps[i][1]=3;
for(i=4;i<23;i++) 
maps[i][4]=1;
maps[5][3]=1;maps[7][3]=2;maps[9][3]=2;maps[11][3]=2;maps[13][3]=2;maps[15][3]=2;maps[17][3]=2;maps[19][3]=2;maps[21][3]=2;
for(i=5;i<23;i++) 
maps[i][5]=3;
for(i=23;i>5;i--){ 
maps[i][8]=1;
maps[i][9]=3;}
maps[23][7]=2;maps[21][7]=2;maps[19][7]=2;maps[17][7]=2;maps[15][7]=2;maps[13][7]=2;maps[11][7]=2;maps[9][7]=2;maps[7][7]=2;
for(i=5;i<23;i++) {
maps[i][12]=1;
maps[i][13]=3;}
maps[21][11]=2;maps[19][11]=2;maps[17][11]=2;maps[15][11]=2;maps[13][11]=2;maps[11][11]=2;maps[9][11]=2;maps[7][11]=2;maps[5][11]=2;
for(i=24;i>5;i--)
maps[i][16]=1;
maps[23][15]=2;maps[21][15]=2;maps[19][15]=2;maps[17][15]=2;maps[15][15]=2;maps[13][15]=2;maps[11][15]=2;maps[9][15]=2;maps[7][15]=2;



	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			if(maps[i][j] == 1)
				zhuankuai(i,j);
		else if(maps[i][j] == 2 || maps[i][j] == 3 || maps[i][j] == 4 || maps[i][j] == 5)
				ci(i,j);
}


void map4()
{
    int i,j;
	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			maps[i][j] = 0;
    maps[0][18] = 1;maps[1][18] = 1;maps[2][18] = 1;maps[3][17] = 1;maps[0][15] = 1;maps[1][15] = 1;maps[5][13] = 1;maps[5][14] = 1;
	maps[5][15] = 1;maps[5][16] = 1;maps[5][17] = 1;maps[5][18] = 1;maps[2][11] = 1;maps[3][11] = 1;
	maps[4][11] = 1;maps[0][6] = 1;maps[2][6] = 1;maps[2][9] = 1;maps[3][4] = 1;maps[4][4] = 1;
	maps[5][4] = 1;maps[4][5] = 1;maps[4][6] = 1;maps[4][7] = 1;maps[4][8] = 1;
	maps[4][9] = 1;maps[5][8] = 1;maps[8][2] = 1;maps[8][6] = 1;maps[11][3] = 1;
	maps[11][5] = 1;maps[11][7] = 1;maps[11][9] = 1;maps[8][15] = 1;maps[9][14] = 1;
	maps[7][18] = 1;maps[8][18] = 1;maps[9][18] = 1;maps[11][13] = 1;maps[12][13] = 1;
	maps[14][3] = 1;maps[14][6] = 1;maps[14][9] = 1;maps[14][12] = 1;maps[6][10] = 1;
	maps[8][11] = 1;maps[16][2] = 1;maps[16][5] = 1;maps[16][8] = 1;maps[16][11] = 1;
	maps[16][13] = 1;maps[17][13] = 1;maps[19][13] = 1;maps[19][4] = 1;maps[20][4] = 1;
	maps[18][7] = 1;maps[18][10] = 1;maps[20][9] = 1;maps[22][3] = 1;maps[22][7] = 1;
	maps[22][11] = 1;maps[24][9] = 1;maps[24][16] = 1;maps[23][14] = 1;maps[11][16] = 1;
	maps[24][5] = 1;maps[13][16] = 1;maps[15][16] = 1;maps[17][16] = 1;maps[19][16] = 1;
	maps[21][16] = 1;
	    for(j = 1;j<10;j++)
		{
			maps[9][j] = 1;
		}
		for(j=3;j<14;j++)
		{
			maps[13][j] = 1;
		}
		for(j=1;j<12;j++)
		{
			maps[17][j] = 1;
		}
		for(j=3;j<14;j++)
		{
			maps[21][j] = 1;
		}
		for(i=0;i<25;i++)
		{
			maps[i][0] = 1;
		}

	//正常砖块位置

	maps[0][14] = 2;maps[0][11] = 2;maps[1][11] = 2;maps[6][18] = 2;maps[8][17] = 2;
	maps[21][2] = 2;maps[4][3] = 2;maps[1][6] = 5;maps[1][3] = 2;maps[2][3] = 2;
	maps[3][8] = 2;maps[10][5] = 2;maps[12][7] = 2;maps[10][9] = 2;
	maps[18][6] = 2;maps[5][10] = 2;maps[7][10] = 2;maps[20][3] = 2;

	for (i=10;i<25;i++)
	{
		maps[i][18] = 2;
	}
	                                                                                         //↑尖刺位置

	maps[2][12] = 3;maps[0][12] = 3;maps[1][12] = 3;maps[5][11] = 3;maps[7][11] = 3; 
	maps[0][1] = 3;maps[1][4] = 3;maps[2][4] = 3;maps[1][7] = 4;maps[3][9] = 3; 
	maps[3][1] = 3;maps[4][1] = 3;maps[8][3] = 3;maps[5][5] = 3;maps[6][2] = 3;
	maps[7][2] = 3;maps[10][1] = 3;maps[12][1] = 0;maps[13][1] = 3;maps[14][1] = 3;
	maps[15][1] = 3;maps[11][1] = 3;maps[16][3] = 3;maps[14][4] = 3;maps[16][6] = 3;
	maps[14][7] = 3;maps[16][9] = 3;maps[14][10] = 3;maps[18][1] = 3;maps[19][1] = 3;
	maps[20][5] = 3;maps[22][4] = 3;maps[22][8] = 3;maps[24][6] = 3;maps[9][15] = 3;
	maps[18][11] = 3;maps[10][10] = 3;maps[10][11] = 3;
	
	for(i=10;i<23;i++)
	{
		maps[i][14] = 3;
	}

		//↓尖刺位置

	maps[4][13] = 4;maps[4][14] = 4;maps[4][15] = 4;maps[8][12] = 4;maps[8][13] = 4;
	maps[8][14] = 4;maps[7][15] = 4;maps[8][7] = 4;maps[7][6] = 4;maps[8][8] = 4;
	maps[12][11] = 4;maps[12][12] = 4;maps[24][1] = 4;maps[24][2] = 4;maps[24][3] = 4;
	maps[24][10] = 4;maps[24][11] = 4;maps[24][12] = 4;maps[23][16] = 4;maps[12][3] = 4;
	//←尖刺位置

	maps[2][15] = 5;maps[6][13] = 5;maps[0][9] = 5;maps[6][4] = 5;maps[18][8] = 5;
	maps[18][9] = 5;maps[19][7] = 5;maps[19][11] = 5;
	//→尖刺位置


	for(i = 0;i<25;i++)
	for(j = 0; j<19; j++)
	if(maps[i][j] == 1)
			zhuankuai(i,j);
			else if(maps[i][j] == 2 || maps[i][j] == 3 || maps[i][j] == 4 || maps[i][j] == 5)        //2：刺往上；3：刺往下；4：刺往左；5：刺往右
				ci(i,j);
}

void map5()
{
	int i,j;
	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			maps[i][j] = 0;
	int a;
	for(a = 0; a < 25; a ++)
    {
		maps[a][0] = 1;
	}
    maps[1][18]=1;          //2：刺往上；3：刺往下；4：刺往左；5：刺往右
	for(a = 0; a < 25; a ++)
	{
		maps[a][4] = 1;
		maps[a][3] = 1;
     	maps[a][2] = 2;
	}
	for(a=2;a<23;a++)
	{
	    maps[a][18]=2;
		maps[a][17]=1;
	}
	for(a=11;a<23;a++)
	{
		maps[a][17]=0;
	}

    maps[4][17] = 0; 
	maps[7][17] = 0; 
	maps[8][17] = 0; 
	maps[12][17] = 0; 
	maps[13][17] = 0; 
	maps[10][15] = 1;  
	for(a = 13; a < 24; a++)
	{
		maps[a][7] = 1;
	}
    	maps[13][7] = 0;
	for(a=7;a<19;a++)
	{
	   maps[16][a]=1;
       maps[18][a]=1;
       maps[20][a]=1;
	}
	for(a = 8;a < 18; a++)
	{
		maps[14][a] = 1;
	}
	maps[14][16] = 0;
	for(a = 0; a < 10; a ++)
	{
		maps[a][11] = 1;
	}
   	maps[2][11] = 0;
	maps[3][11] = 0; 
    maps[10][11] = 3; 
	for(a = 1 ; a < 19; a++)
	{
		maps[0][a] = 1;
		maps[11][a] = 1;
		maps[24][a] = 1;
	}
	maps[11][5] = 0;
	maps[11][6] = 0;
	maps[11][1] = 0;
	maps[11][2] = 2;
	for(a = 2 ; a < 12; a ++)
	{
		maps[a][13] = 1;
		maps[a][14] = 3;
	}
	maps[10][13] = 0;
	maps[9][14] = 0; 
	maps[10][14] = 0;
	maps[11][14] = 4;
	maps[24][17] = 0;
	maps[24][16] = 0;
	maps[23][16] = 0;
    maps[15][7]=0;
    maps[17][7]=0;
    maps[19][7]=0;
    maps[21][7]=0;
    maps[22][7]=0;
    maps[23][7]=0;
    maps[23][18]=1;
    maps[10][8]=1;
    maps[1][13]=1;
	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			if(maps[i][j] == 1)
				zhuankuai(i,j);
			else if(maps[i][j] == 2 || maps[i][j] == 3 || maps[i][j] == 4 || maps[i][j] == 5)        //2：刺往上；3：刺往下；4：刺往左；5：刺往右
				ci(i,j);
}


void map6()
{
	int i,j,k,l;
	int a,b;
	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			maps[i][j] = 0;
for(k=0;k<24;k++)
{
	maps[k][0]=3;
}
for(k=0;k<21;k++)
{
	maps[k][3]=1;
	maps[k][4]=1;
}
for(k=3;k<19;k++)
{
	maps[k][7]=1;
}
for(k=6;k<21;k++)
{
	maps[k][11]=1;
}
for(k=4;k<22;k++)
{
	maps[k][18]=1;
}
for(k=15;k<20;k++)
{
	maps[k][16]=1;
}
for(l=5;l<19;l++)
{
	maps[0][l]=1;
}
for(l=8;l<19;l++)
{
	maps[3][l]=1;
}
for(l=8;l<13;l++)
{
	maps[4][l]=1;
}
for(l=12;l<15;l++)
{
	maps[7][l]=1;
	maps[8][l]=1;
}
for(l=12;l<17;l++)
{
	maps[15][l]=1;
	maps[16][l]=1;
}
for(l=14;l<18;l++)
{
	maps[11][l]=1;
	maps[12][l]=1;
}
for(l=3;l<16;l++)
{
	maps[21][l]=1;
}
for(l=0;l<19;l++)
{
	maps[24][l]=1;
}
maps[7][0]=1;maps[11][0]=0;
maps[7][1]=3;
maps[3][2]=2;maps[6][2]=2;maps[11][2]=2;maps[13][2]=2;maps[14][2]=2;maps[17][2]=2;maps[19][2]=2;
maps[4][3]=2;maps[9][3]=2;maps[10][3]=2;
maps[5][5]=3;maps[8][5]=3;maps[12][5]=3;maps[16][5]=3;maps[22][5]=5;
maps[3][6]=2;maps[7][6]=2;maps[9][6]=2;maps[11][6]=2;maps[13][6]=2;maps[15][6]=2;maps[18][6]=2;
maps[2][7]=4;
maps[9][8]=3;maps[11][8]=3;maps[12][8]=3;maps[20][8]=1;
maps[7][9]=1;maps[18][9]=2;
maps[7][10]=1;maps[8][10]=2;maps[9][10]=2;maps[11][10]=2;maps[12][10]=2;maps[14][10]=2;maps[15][10]=2;maps[16][10]=2;maps[18][10]=1;maps[23][10]=4;
maps[1][11]=5;maps[6][11]=1;
maps[6][12]=1;
maps[12][13]=2;
maps[6][14]=1;maps[9][14]=5;
maps[2][15]=4;maps[13][15]=1;
maps[4][16]=1;maps[20][16]=5;
maps[5][17]=2;maps[7][17]=2;maps[8][17]=2;maps[9][17]=2;
maps[18][18]=2;maps[22][18]=2;maps[23][18]=2;
		for(a = 0;a<25;a++)
		for(b = 0; b<19; b++)
			if(maps[a][b] == 1)
				zhuankuai(a,b);
			else if(maps[a][b] == 2 || maps[a][b] == 3 || maps[a][b] == 4 || maps[a][b] == 5)        //2：刺往上；3：刺往下；4：刺往左；5：刺往右
				ci(a,b);
}

void map7()
{
	int i,j;
		for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			maps[i][j] = 0;
	for(i=0;i<19;i++)
	{
		maps[24][i] = 1;
		maps[0][i] = 1;
	}
	maps[23][7] = 1;
	for(i = 0; i < 25; i++)
	{
		maps[i][18] = 1;
		maps[i][0] = 1;
	}
	maps[24][17] = 0;

	for(i = 0; i<25; i++)
		for(j = 0; j < 19; j++)
		{
			if(maps[i][j] == 1)
				zhuankuai(i,j);
			else if(maps[i][j] == 2 || maps[i][j] == 3 || maps[i][j] == 4 || maps[i][j] == 5)        //2：刺往上；3：刺往下；4：刺往左；5：刺往右
				ci(i,j);
		}
}











//判定是否碰撞     0：空中       1:往右撞到砖块左侧        2：往左撞到砖块右侧       3：往上撞到砖块下侧           4：往下撞到砖块上方        5：撞到有杀伤力的物品

int istouch()
{
	float vy = ch_vy;
	if(ch_vy <= - bian)
		vy = - bian + 1;
	judgepoint();
	/*if(istouchci() == 1)
	{
		if((maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_foot-1 - vy))/ bian] == 2 || 
		maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_head-1 - vy))/ bian] == 2 || 
		maps[(judge_ch_x_behind + ch_vx * towards)/ bian][((int)(judge_ch_y_head-1 - vy))/ bian ] == 2 || 
		maps[(judge_ch_x_behind + ch_vx * towards) / bian][((int)(judge_ch_y_foot-1 - vy))/ bian] == 2) && (judgeci() == 1))
		{
			return 5;
		}
	}*/
	if(istouchzhuankuai() == 1)
		if((maps[(judge_ch_x_front + ch_vx * towards)/ bian][(judge_ch_y_foot -1 )/ bian ] == 1 || 
			(maps[(judge_ch_x_front + ch_vx * towards)/ bian][(judge_ch_y_head )/ bian ] == 1 && maps[(judge_ch_x_behind)/ bian][(judge_ch_y_head )/ bian ] == 0))&& towards == 1 )
		{
			return 1;
		}
		if((maps[(judge_ch_x_front + ch_vx * towards )/ bian ][(judge_ch_y_foot -1 )/ bian ] == 1 ||
			(maps[(judge_ch_x_front + ch_vx * towards)/ bian][(judge_ch_y_head )/ bian ] == 1 && maps[(judge_ch_x_front)/ bian][(judge_ch_y_head )/ bian ] == 0))&& towards == -1 )
		{
			return 2;
		}
		if(maps[(judge_ch_x_front - towards)/ bian][((int)(judge_ch_y_head - vy))/ bian] == 1 ||
			maps[(judge_ch_x_behind - towards)/ bian][((int)(judge_ch_y_head - vy))/ bian] == 1)
		{
			return 3;
		}
		if(maps[(judge_ch_x_front - towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1 || 
			maps[(judge_ch_x_behind - towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1)
			return 4;
	return 0;

}

//碰撞状态判定
int judgestate()
{
	int i;
	if(maps[ch_x/bian][ch_y/bian] == 6 )
	{
		isdie =0;
		return 6;
	}
	for(i = (int)judge_ch_y_head; i <= (int)judge_ch_y_foot; i++)
		if (judgemaps[judge_ch_x_front][i]==1 || judgemaps[judge_ch_x_behind][i] == 1)
			return 5;
	if(towards == 1)
	{
	    for(i = judge_ch_x_behind;i <= judge_ch_x_front;i ++)
	    	if (judgemaps[i][(int)judge_ch_y_foot]==1||judgemaps[i][(int)judge_ch_y_head]==1)
		    	return 5;
	}
	else
	{
		for(i = judge_ch_x_front;i <= judge_ch_x_behind;i ++)
	    	if (judgemaps[i][(int)judge_ch_y_foot]==1||judgemaps[i][(int)judge_ch_y_head]==1)
		    	return 5;
	}
	if (istouch() == 1)
	{
		/*judge_ch_x_front = ((judge_ch_x_front + ch_vx * towards)/ bian ) * bian;
		ch_vx = 0;
		ch_x = judge_ch_x_front - weight_ch - 7;*/
		return 1;
	}
	if (istouch() == 2)
	{
		/*judge_ch_x_front = ((judge_ch_x_front  + ch_vx * towards)/ bian + 1) * bian - 1 ;
		ch_vx = 0;
		ch_x = judge_ch_x_front - 5 ;*/
		return 2;
	}
	if (istouch() == 3)
	{
		/*judge_ch_y_head = ((judge_ch_y_head - ch_vy)/ bian ) * bian;
		ch_vy = -1;
		ch_y = judge_ch_y_head;*/
		return 3;
	}
	if (istouch() == 4 )
	{
		/*judge_ch_y_foot = (((int)(judge_ch_y_foot - ch_vy))/ bian ) * bian;
		ch_vy = 0;
		ch_y = judge_ch_y_foot - high_ch;*/
		return 4;
	}
	else
		return 0;

}

int istouchzhuankuai()
{
	float vy = ch_vy;
	if(ch_vy <= - bian + 1)
		vy =  - bian + 1;
	if(maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1 || 
		maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_head - vy))/ bian] == 1 || 
		maps[(judge_ch_x_behind + ch_vx * towards)/ bian][((int)(judge_ch_y_head - vy))/ bian ] == 1 || 
		maps[(judge_ch_x_behind  + ch_vx * towards) / bian][((int)(judge_ch_y_foot - vy))/ bian] == 1)
		return 1;
	else
		return 0;
}

/*int istouchci()
{
	float vy = ch_vy;
	if(ch_vy <= -bian + 1)
		vy = - bian + 1;
	if(maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_foot - 1 - vy))/ bian] == 2 || 
		maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_head - 1 - vy))/ bian] == 2 || 
		maps[(judge_ch_x_behind + ch_vx * towards)/ bian][((int)(judge_ch_y_head - 1 - vy))/ bian ] == 2 || 
		maps[(judge_ch_x_behind + ch_vx * towards) / bian][((int)(judge_ch_y_foot - 1 - vy))/ bian] == 2 ||
		maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_foot-1 - vy))/ bian] == 3 || 
		maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_head-1 - vy))/ bian] == 3 || 
		maps[(judge_ch_x_behind + ch_vx * towards)/ bian][((int)(judge_ch_y_head-1 - vy))/ bian ] == 3 || 
		maps[(judge_ch_x_behind + ch_vx * towards) / bian][((int)(judge_ch_y_foot-1 - vy))/ bian] == 3 ||
		maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_foot-1 - vy))/ bian] == 4 || 
		maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_head-1 - vy))/ bian] == 4 || 
		maps[(judge_ch_x_behind + ch_vx * towards)/ bian][((int)(judge_ch_y_head-1 - vy))/ bian ] == 4 || 
		maps[(judge_ch_x_behind + ch_vx * towards) / bian][((int)(judge_ch_y_foot-1 - vy))/ bian] == 4 ||
		maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_foot-1 - vy))/ bian] == 5 || 
		maps[(judge_ch_x_front + ch_vx * towards)/ bian][((int)(judge_ch_y_head-1 - vy))/ bian] == 5 || 
		maps[(judge_ch_x_behind + ch_vx * towards)/ bian][((int)(judge_ch_y_head-1 - vy))/ bian ] == 5 || 
		maps[(judge_ch_x_behind + ch_vx * towards) / bian][((int)(judge_ch_y_foot-1 - vy))/ bian] == 5 )
		return 1;
	else
		return 0;
}

//刺的判定轮廓
int judgeci()
{
	int y,x;
	    if(towards == 1)
	    {
		if((judge_ch_x_front % bian) <= 15)
			x = judge_ch_x_front;
		else if(judge_ch_x_front % bian > 15 && judge_ch_x_behind % bian <= 15)
			x = 32;
		else
			x = judge_ch_x_behind;
	}
	if(x <= 15 && x >= 0)
	{
		y = bian - 1 - 2 * x;
	}
	else if ( x <= 31 && x >= 16)
	{
		y = 2*(x - 15) - 1;
	}
	else
		y = 1;
	if(((int)judge_ch_y_foot) % bian <= y)
	    return 1;
	else
	    return 0;
}
*/
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
	ch_vx = 0;
	loadimage(&img_kid_right, "img_kid.png");
	loadimage(&img_kid_left,"img_kid1.png");
	int k,m,n;
	BeginBatchDraw();
	if(towards > 0)               //往右朝向
	{
    	for(k=0; k <= 12 && isdie == 0;)
		{   
	    	 for(m = ch_x1; m <= ch_x1 + 24; m ++)
			 {
		        for(n = ch_y1 ; n <= ch_y1 + 21 ; n ++)
				{
		         putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
				}
			 }
			 ch_x1 = ch_x;
			 ch_y1 = ch_y;
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
		for(k=0; k <= 12 && isdie == 0;)
		{   
	    	 for(m = ch_x1; m <= ch_x1  + 24; m ++)
			 {
		        for(n = ch_y1 ; n <= ch_y1 + 21 ; n ++)
				{
		         putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
				}
			 }
			 ch_x1 = ch_x;
			 ch_y1 = ch_y;
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
	else kidrun();
}

//kid跑步动画
void kidrun()
{
	int m,n,i,j;
	BeginBatchDraw();
	right_i = 0;
	left_i = 0;
	while(isdie == 0)
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
				{
					judge_ch_x_front = ((judge_ch_x_front + ch_vx * towards)/ bian ) * bian;
	            	ch_vx = 0;
	            	ch_x = judge_ch_x_front - weight_ch - 7;
				}
				else
					ch_vx = 6;
				ch_x1 = ch_x;
				ch_y1 = ch_y;
				ch_x = ch_vx * towards + ch_x ;

		        for(m = ch_x1 ; m <= ch_x + 24; m ++)
				{
		            for(n = ch_y1; n <= ch_y + 21 ; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
				if(judgestate() == 5)
				{
					goto end;
				}
				if(judgestate() == 6)
					goto final;
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
				{
					judge_ch_x_front = ((judge_ch_x_front  + ch_vx * towards)/ bian + 1) * bian - 1 ;
	            	ch_vx = 0;
	            	ch_x = judge_ch_x_front - 5 ;
				}
				else
					ch_vx = 6;
				ch_x1 = ch_x;
				ch_y1 = ch_y;
				ch_x = ch_vx * towards + ch_x ;
		        for(m = ch_x - 2*6 -24; m <= ch_x + 2*6 + 24; m ++)
				{
		            for(n = ch_y - 21 + ch_vy; n <= ch_y + 21 - ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
				if(judgestate() == 5)
				{
					goto end;
				}
				if(judgestate() == 6)
					goto final;
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
	else if(judgestate() == 0)
	{
		leftjump = 1;
		songtimes = 1;
		kidfall();
	}
	else kidwait();
final: isdie = 0;
	;

end: if(isdie == 0)
     	isdie = 1; 

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
	while(isdie == 0)
    {
		if(songtimes == 1&&(GetAsyncKeyState(VK_LSHIFT)&0x8000))
		{
			break;
		}
		if((GetAsyncKeyState(VK_LEFT)&0x8000))
		{
			towards = -1;
			if(judgestate() == 2)
			{
				judge_ch_x_front = ((judge_ch_x_front  + ch_vx * towards)/ bian + 1) * bian - 1 ;
	        	ch_vx = 0;
	        	ch_x = judge_ch_x_front - 5 ;
			}
			else
				ch_vx = 6;
			ch_x1 = ch_x;
			ch_x = ch_x - ch_vx;
			
		}
		else if((GetAsyncKeyState(VK_RIGHT)&0x8000))
		{
			towards = 1;
			if(judgestate() == 1)
			{
				judge_ch_x_front = ((judge_ch_x_front + ch_vx * towards)/ bian ) * bian;
	        	ch_vx = 0;
	         	ch_x = judge_ch_x_front - weight_ch - 7;
			}
			else
				ch_vx = 6;
			ch_x1 = ch_x;
			ch_x = ch_x + ch_vx;
			
		}
		else
		{
			ch_vx = 0;
			ch_x1 = ch_x;
		}
		ch_y1 = ch_y;
		
		if(!(GetAsyncKeyState(VK_LSHIFT)&0x8000) && songtimes == 0)
		{
			ch_vy = 0.45 * ch_vy;
			songtimes++;
		}
			ch_y = ch_y - ch_vy;
		if(judgestate() == 3)
		{
			judge_ch_y_head = ((judge_ch_y_head - ch_vy)/ bian ) * bian;
	    	ch_vy = -1;
	    	ch_y = judge_ch_y_head;
			for(m = ch_x - 2*6 -24; m <= ch_x + 2*6+ 24; m ++)
			{
	            for(n = 0; n <= judge_ch_y_foot; n ++)
				{
		            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
				}
			}
			break;
		}

		if((judgestate() == 2 || judgestate() == 1 ) && (maps[(judge_ch_x_front - towards)/ bian][((int)(judge_ch_y_head - ch_vy))/ bian] == 1 || 
					maps[(judge_ch_x_behind - towards)/ bian][((int)(judge_ch_y_head - ch_vy))/ bian] == 1))
				{
					{
						if(towards == 1)
						{
							judge_ch_x_front = ((judge_ch_x_front + ch_vx * towards)/ bian ) * bian;
		                    ch_vx = 0;
	                    	ch_x = judge_ch_x_front - weight_ch - 7;
						}
						else
						{
							judge_ch_x_front = ((judge_ch_x_front  + ch_vx * towards)/ bian + 1) * bian - 1 ;
	                    	ch_vx = 0;
	                    	ch_x = judge_ch_x_front - 5 ;
						}
					}
					judge_ch_y_head = (((int)(judge_ch_y_head - ch_vy))/ bian ) * bian;
	            	ch_vy = -1;
					for(m = ch_x - 2*6 -24; m <= ch_x + 2*ch_vx + 24; m ++)
					{
		                for(n = 0; n <= judge_ch_y_foot; n ++)
						{
			                putpixel(m, n, mapcolor[m][n]);          
						}
					}
					break;
				}

		
		
		if(towards == 1)
		{
            for(m = ch_x1; m <= ch_x1 + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y1 ; n <= ch_y1 + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
			if(judgestate() == 5)
				{
					goto end;
				}
			if(judgestate()==6)
				goto final;
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
		    for (m = ch_x1 ; m <= ch_x1 + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y1 ; n <= ch_y1 + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
			if(judgestate() == 5)
				{
					goto end;
				}
			if(judgestate()==6)
				goto final;
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
				if(judgestate() == 3)
			{
					judge_ch_y_head = ((judge_ch_y_head - ch_vy)/ bian ) * bian;
	            	ch_vy = -1;
		            ch_y = judge_ch_y_head;
					for(m = ch_x - 2*6 -24; m <= ch_x + 2*6+ 24; m ++)
				{
		            for(n = 0; n <= judge_ch_y_foot; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
				break;
			}
				ch_vy = ch_vy - gravity;
		}
		if(ch_vy <=0 )
			break;
	}
	if(songtimes == 1 && (GetAsyncKeyState(VK_LSHIFT)&0x8000))
		kidjump2();
	else
    	kidfall();
final: isdie = 0;
	;

end: if(isdie == 0)
     	isdie = 1; 
}

void kidjump2()
{ 
	leftjump --;
	int m,n,i,j;
	ch_vy = jump2;
	right_i = 0;
	left_i = 0;
	BeginBatchDraw();
	while(isdie == 0)
    {
		ch_x1 = ch_x;
		ch_y1 = ch_y;
		if((GetAsyncKeyState(VK_LEFT)&0x8000))
		{
			if(judgestate() == 2)
			{
				judge_ch_x_front = ((judge_ch_x_front  + ch_vx * towards)/ bian + 1) * bian - 1 ;
	        	ch_vx = 0;
	        	ch_x = judge_ch_x_front - 5 ;
			}
			else
				ch_vx = 6;
			ch_x = ch_x - ch_vx;
			towards = -1;
		}
		else if((GetAsyncKeyState(VK_RIGHT)&0x8000))
		{
			if(judgestate() == 1)
			{
				judge_ch_x_front = ((judge_ch_x_front + ch_vx * towards)/ bian ) * bian;
	         	ch_vx = 0;
        		ch_x = judge_ch_x_front - weight_ch - 7;
			}
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

		if(judgestate() == 3)
		{
			judge_ch_y_head = ((judge_ch_y_head - ch_vy)/ bian ) * bian;
	    	ch_vy = -1;
	    	ch_y = judge_ch_y_head;
			for(m = ch_x - 2*6 -24; m <= ch_x + 2*6+ 24; m ++)
			{
	            for(n = 0; n <= judge_ch_y_foot; n ++)
				{
		            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
				}
			}
			break;
		}
		if((judgestate() == 2 || judgestate() == 1 ) && (maps[(judge_ch_x_front - towards)/ bian][((int)(judge_ch_y_head - ch_vy))/ bian] == 1 || 
					maps[(judge_ch_x_behind - towards)/ bian][((int)(judge_ch_y_head - ch_vy))/ bian] == 1))
				{
			if(towards == 1)
			{
				judge_ch_x_front = ((judge_ch_x_front + ch_vx * towards)/ bian ) * bian;
	        	ch_vx = 0;
    	    	ch_x = judge_ch_x_front - weight_ch - 7;
			}
			else
			{
				judge_ch_x_front = ((judge_ch_x_front  + ch_vx * towards)/ bian + 1) * bian - 1 ;
        		ch_vx = 0;
	        	ch_x = judge_ch_x_front - 5 ;
			}
					judge_ch_y_head = (((int)(judge_ch_y_head - ch_vy))/ bian ) * bian;
	            	ch_vy = -1;
					for(m = ch_x - 2*6 -24; m <= ch_x + 2*ch_vx + 24; m ++)
					{
		                for(n = 0; n <= judge_ch_y_foot; n ++)
						{
			                putpixel(m, n, mapcolor[m][n]);          
						}
					}
					break;
				}

		
		if(towards == 1)
		{
            for(m = ch_x1 ; m <= ch_x1 + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y1; n <= ch_y1 + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
			if(judgestate() == 5)
				{
					goto end;
				}
			if(judgestate()==6)
				goto final;
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
		    for (m = ch_x1 ; m <= ch_x  + 24; m ++)
				{
		            for(n = ch_y1 ; n <= ch_y + 42 ; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
			if(judgestate() == 5)
				{
					goto end;
				}
			if(judgestate()==6)
				goto final;
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
final: isdie = 0;
	;

end: if(isdie == 0)
     	isdie = 1; 
}

//下降动画
void kidfall()
{ 
	int m,n,i,j;
	right_i = 0;
	left_i = 0;
	BeginBatchDraw();
	while(isdie == 0)
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
			{
				judge_ch_x_front = ((judge_ch_x_front  + ch_vx * towards)/ bian + 1) * bian - 1 ;
	        	ch_vx = 0;
	         	ch_x = judge_ch_x_front - 5 ;
			}
			else
				ch_vx = 6;
			towards = -1;
		}
		else if((GetAsyncKeyState(VK_RIGHT)&0x8000))
		{
			if(judgestate() == 1)
			{
				judge_ch_x_front = ((judge_ch_x_front + ch_vx * towards)/ bian ) * bian;
	        	ch_vx = 0;
	        	ch_x = judge_ch_x_front - weight_ch - 7;
			}
			else
				ch_vx = 6;
			towards = 1;
		}
		else 
			ch_vx = 0;
		ch_x1 = ch_x;
		ch_y1 = ch_y;
		
		float vy = ch_vy;
	    if(ch_vy <= - bian)
	        vy = - bian + 1;
		if(judgestate() == 4)
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
		if((judgestate() == 2 || judgestate() == 1 )&& (maps[(judge_ch_x_front - towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1 || 
			maps[(judge_ch_x_behind - towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1))
		{
			if(towards == 1)
			{
	 			judge_ch_x_front = ((judge_ch_x_front + ch_vx * towards)/ bian ) * bian;
	        	ch_vx = 0;
	        	ch_x = judge_ch_x_front - weight_ch - 7;
			}
			else
			{
				judge_ch_x_front = ((judge_ch_x_front  + ch_vx * towards)/ bian + 1) * bian - 1 ;
	        	ch_vx = 0;
	        	ch_x = judge_ch_x_front - 5 ;
			}
			judge_ch_y_foot = (((int)(judge_ch_y_foot - ch_vy))/ bian ) * bian;
	      	ch_vy = 0;
       		ch_y = judge_ch_y_foot - high_ch;
			for(m = ch_x - 2*6 -24; m <= ch_x + 2*ch_vx + 24; m ++)
			{
	            for(n = 0; n <= judge_ch_y_foot; n ++)
				{
	                putpixel(m, n, mapcolor[m][n]);          
				}
			}
			break;
		}
		ch_x = ch_x + towards * ch_vx;
		ch_y = ch_y - ch_vy;
		if(towards == 1)
		{
            for(m = ch_x1; m <= ch_x1  + 24; m ++)
				{
		            for(n = ch_y1; n <= ch_y1 + 42 ; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
			if(judgestate() == 5)
				{
					goto end;
				}
			if(judgestate()==6)
				goto final;
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
		}
		else if(towards == -1)
		{ 
		    for(m = ch_x1; m <= ch_x1 + 24; m ++)
				{
		            for(n = ch_y1; n <= ch_y1 + 42 ; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //去除kid上一帧动画
					}
				}
	            loadimage(&img_kid_fall_left, "img_kid1.png");
				if(judgestate() == 5)
				{
					goto end;
				}
				if(judgestate()==6)
				goto final;
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
			
		}
		ch_vy = ch_vy - gravity;
	}
	if(songtimes == 1 && leftjump == 1 && (GetAsyncKeyState(VK_LSHIFT)&0x8000) && isdie != 1)
		kidjump2();
	else
	{
	leftjump = 2;
	songtimes = 0;
	if(isdie == 0)
	    kidrun();
	}
final: isdie = 0;
	;

end: if(isdie == 0)
     	isdie = 1; 
}

void dead()
{
	int i,j,c;
	    loadimage(&GAMEOVER,"gameover.png");
	    putimage(20,220,758,160,&GAMEOVER,0,0);
		for (i = 20; i <= 778 ; i ++)
		{
			for(j = 220; j <= 380; j ++)
			{
			c = getpixel(i, j);
            if(c == 0xffffff)
	            putpixel(i, j, mapcolor[i][j]); 
			}
		}
		FlushBatchDraw();
}


void main()
{
    initgraph(Weight,High);
	start();
start:
	levels();
	kidwait();
	if(isdie == 1)
	{
		dead();
     	while(1)
		{
		if((GetAsyncKeyState(VK_ESCAPE)&0x8000))
			exit(0);
		if((GetAsyncKeyState(82)&0x8000))
		{

			isdie = 0;
			ch_vx =0;
			ch_vy =0;
			songtimes = 0;
			goto start;
		}
		if((GetAsyncKeyState(49)&0x8000))
		{
			level = 1;
			isdie = 0;
			ch_vx =0;
			ch_vy =0;
			songtimes = 0;
			goto start;
		}
		if((GetAsyncKeyState(50)&0x8000))
		{
			level = 2;
			isdie = 0;
			ch_vx =0;
			ch_vy =0;
			songtimes = 0;
			goto start;
		}
		if((GetAsyncKeyState(51)&0x8000))
		{
			level = 3;
			isdie = 0;
			ch_vx =0;
			ch_vy =0;
			songtimes = 0;
			goto start;
		}
		if((GetAsyncKeyState(52)&0x8000))
		{
			level = 4;
			isdie = 0;
			ch_vx =0;
			ch_vy =0;
			songtimes = 0;
			goto start;
		}
		if((GetAsyncKeyState(53)&0x8000))
		{
			level = 5;
			isdie = 0;
			ch_vx =0;
			ch_vy =0;
			songtimes = 0;
			goto start;
		}
		if((GetAsyncKeyState(54)&0x8000))
		{
			level = 6;
			isdie = 0;
			ch_vx =0;
			ch_vy =0;
			songtimes = 0;
			goto start;
		}
		if((GetAsyncKeyState(55)&0x8000))
		{
			level = 7;
			isdie = 0;
			ch_vx =0;
			ch_vy =0;
			songtimes = 0;
			goto start;
		}
		
		}
		
	}
	level ++;
	goto start;
	EndBatchDraw();
	getch();
	closegraph();
}

