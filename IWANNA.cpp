/**************************************************************************************************************************************************************************

***************************************************************************************************************************************************************************
*  -�����һ��i wanna��Ϸ��ȡ��Ϊ��i wanna fight with C                                                                                                                   *
*  -����ĿΪ 20 �������� ��������������������Խ��Τ�첨������칲ͬ��ɵ�C������ҵ,�����Ϊ�ִ����κθ��ƻ��ճ���                                                       *
*  -�����õ���Easyx�Դ���ͷ�ļ�<graphics.h>��Ŀǰֻ����VC++����������ذ�װEasyx����VC++���д˳���Codeblocksò�����в�������                                            *
*  -���գ�i wanna Ϊһ���̬����С��Ϸϵ�У��Կ��˺͸��ѶȲ���������������ƷΪ ��i wanna be the guy��������Ȥ�Ļ������ϰٶ����� ��delicious fruit�� �������ش�ϵ����Ϸ  *
*  -����������ر���Ѷ�Ҳ�ϸߣ���hithub,CSDN��Bilibili�ȵط���ѧд����Ʒ��������ʦ�����ְ����ֲ���ĵ���ͷ���� �����ˣ�����                                          *
*  -ף�����Ϸ��죡����������Ϸ����һЩСbug��Ӱ����Ϸ���飬ϣ����Ҳ�Ҫ̫���⣩                                                                                         *
***************************************************************************************************************************************************************************

***************************************************************************************************************************************************************************/

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>

#define Weight 800        //��Ϸ���泤
#define High 608          //��Ϸ�����

#define bian 32           //ש��߳�
#define high_ch 21        //���ﳤ
#define weight_ch 11      //�����


 
IMAGE img_kid_right;              //���ҳ���kid
IMAGE img_kid_left;               //������kid
IMAGE img_kid_run_right;          //�����˶�kidͼƬ
IMAGE img_kid_run_left;           //�����˶�kidͼƬ
IMAGE img_kid_jump_right;         //���ҳ�������kidͼƬ
IMAGE img_kid_jump_left;          //����������kidͼƬ
IMAGE img_kid_fall_right;
IMAGE img_kid_fall_left;
IMAGE img_zhuankuai;              //ש��ͼƬ
IMAGE img_ci;                     //��ͼƬ
IMAGE img_ej;                     //�������һ��
IMAGE GAMEOVER  ;                  //GAMEOVERͼƬ

int fps = 20;               //֡��
float jump1 = 12;         //һ�����ٶ�
float jump2 = 9;          //�������ٶ�
float gravity = 1;      //�������ٶ�

int level = 1;           // �浵����
int isdie = 0;           //�����Ƿ����� 0��� 1���� 2����
int ischange = 0;        //��ͼת��
int gamestatus = 0;      //��Ϸ״̬��0Ϊ��ʼ�˵����棬1Ϊ������Ϸ��2Ϊ������Ϸ״̬��3Ϊ��Ϸ��ͣ

int towards = 1;        //�жϷ���
int ch_vx = 6 ;         //�����˶�ˮƽ�ٶ�
float ch_vy = 0;       //�����˶���ֱ�ٶ�
int left_i = 0;        //�������߶������
int right_i = 0;       //�������߶������
int isOnFloor = 0;     //�ж��Ƿ��ڵ�����
int leftjump = 2;      //ʣ����Ծ����
int songtimes = 0;     //�����ɿ�shift����
int maps[25][19];      //��ͼ����
int mapcolor[Weight][High]; //��ͼ���ص���ɫ
int judgemaps[Weight][High];     //�ж�����

int ch_x = bian;                         //��������꣨���Ͻ����ص㣩
int ch_x1 = ch_x ;                               //��һ֡���������
int judge_ch_x_behind = ch_x + 7   ;                       //������ж�������꣨����judge_ch_x_behind = ch_x + 5 + weight_ch��                           
int judge_ch_x_front = ch_x + weight_ch + 7 ;             //����ǰ���ж�������� (����judge_ch_x_front = ch_x + 5) 
int ch_y = High - (bian + high_ch) ;                       //���������꣨���Ͻ����ص㣩
int ch_y1 = ch_y;                                                //��һ֡����������
int judge_ch_y_foot = ch_y + high_ch;                            //����Ų��ж�
int judge_ch_y_head = ch_y;                                      //����ͷ���ж�                            

char input;                                       //��ȡ��������


void background();                                //��Ϸ����(����������)
void Mapcolor();                                  //��Ϸ������ɫ���������飩
void levels();                                    //�ؿ�
void level1();
int judgestate();                       //��ײ״̬
int istouch();                           //�ж��Ƿ���ײ     0������  1:����ײ��ש�����  2������ײ��ש���Ҳ�   3������ײ��ש���²�    4������ײ��ש���Ϸ�   5��ײ����ɱ��������Ʒ
int istouchzhuankuai();                  //�ж���ײ�����Ƿ�Ϊש��
/*int istouchci();                          //�ж���ײ�����Ƿ�Ϊ��
int judgeci();                            //�̵��ж�����*/
void judgepoint();                                //��ײ�㺯��
void kidwait();                                   //�޲����µ�kid����
void kidrun();                                    //kid��ͨ�ܵĶ���
void kidjump1();                                  //kidһ����
void kidjump2();                                  //kid������
void kidfall();                                   //kid��������
void zhuankuai(int a,int b);                      //ש��ͼƬ
void ci(int a,int b);                             //��ͼƬ
void map1();                                      //��һ�ص�ͼ�滭
void map2();                                      //�ڶ��ص�ͼ�滭
void dead();                                     //��������

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

//�õ�����ÿ�����ص����ɫ
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

//�ؿ�ѡ����

void levels()
{
	if (level == 1)
	{
		level1();
	}
}

void level1()
{
	for(int i = 0; i < Weight; i++)
		for(int j =0; j < High; j++)
			judgemaps[i][j] = 0; //��ʼ���ж�
	background();
	map1();
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
	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			if(maps[i][j] == 1)
				zhuankuai(i,j);
			else if(maps[i][j] == 2 || maps[i][j] == 3 || maps[i][j] == 4 || maps[i][j] == 5)        //2�������ϣ�3�������£�4��������5��������
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
maps[1][10]=1;maps[1][2]=5;maps[1][3]=5;maps[1][4]=5;maps[1][5]=5;maps[1][11]=1;maps[1][12]=1;
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
			else if(maps[a][b] == 2 || maps[a][b] == 3 || maps[a][b] == 4 || maps[a][b] == 5)        //2�������ϣ�3�������£�4��������5��������
				ci(a,b);
}


//�ж��Ƿ���ײ     0������       1:����ײ��ש�����        2������ײ��ש���Ҳ�       3������ײ��ש���²�           4������ײ��ש���Ϸ�        5��ײ����ɱ��������Ʒ

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

//��ײ״̬�ж�
int judgestate()
{
	int i;
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
		ch_vy = -1;
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

//�̵��ж�����
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


//kid������ʱ�򶯻�

void kidwait()                          
{
	ch_vx = 0;
	loadimage(&img_kid_right, "img_kid.png");
	loadimage(&img_kid_left,"img_kid1.png");
	int k,m,n;
	BeginBatchDraw();
	if(towards > 0)               //���ҳ���
	{
    	for(k=0; k <= 12 && isdie == 0;)
		{   
	    	 for(m = ch_x1; m <= ch_x1 + 24; m ++)
			 {
		        for(n = ch_y1 ; n <= ch_y1 + 21 ; n ++)
				{
		         putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
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
			 }                                                             //����kidͼƬ
	          int c;
	          for(int i = ch_x; i <= ch_x + 24; i ++)
			  {
		          for(int j = ch_y - 21; j <= ch_y + 20; j ++)
				  {
		           c = getpixel(i, j);
                   if(c == 0xffffff)
			           putpixel(i, j, mapcolor[i][j]);          //ȥ��kid֮�����ɫ
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
		         putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
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
			 }                                                             //����kidͼƬ
	          int c;
	          for(int i = ch_x; i <= ch_x + 24; i ++)
			  {
		          for(int j = ch_y - 21; j <= ch_y + 20; j ++)
				  {
		           c = getpixel(i, j);
                   if(c == 0xffffff)
			           putpixel(i, j, mapcolor[i][j]);          //ȥ��kid֮�����ɫ
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
	if(isdie == 1)
		dead();
	if((GetAsyncKeyState(VK_LSHIFT)&0x8000))
		kidjump1();
	kidrun();
	getch();
	EndBatchDraw();
}

//kid�ܲ�����
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
	        if((GetAsyncKeyState(VK_RIGHT)&0x8000))                             //�����˶�
			{
				towards = 1;
				if(judgestate() == 1)
					ch_vx = 0;
				else
					ch_vx = 6;
				ch_x1 = ch_x;
				ch_y1 = ch_y;
				ch_x = ch_vx * towards + ch_x ;

		        for(m = ch_x1 ; m <= ch_x + 24; m ++)
				{
		            for(n = ch_y1; n <= ch_y + 21 ; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
					}
				}
				if(judgestate() == 5)
				{
					isdie = 1;
					break;
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
				}                                                             //����kidͼƬ
	            int c;
	            for(i = ch_x; i <= ch_x + 24; i ++)
				{
		            for(j = ch_y; j <= ch_y + 20; j ++)
					{
			            c = getpixel(i, j);
                        if(c == 0xffffff)
				            putpixel(i, j, mapcolor[i][j]);          //ȥ��kid֮�����ɫ
					}
				}
		        FlushBatchDraw();
			    Sleep(fps);
				right_i ++;
		        if(right_i == 4)
			        right_i = 0;
			}
			else if((GetAsyncKeyState(VK_LEFT)&0x8000))                                      //�����˶�����
			{
				towards = -1;
				if(judgestate() == 2)
					ch_vx = 0;
				else
					ch_vx = 6;
				ch_x1 = ch_x;
				ch_y1 = ch_y;
				ch_x = ch_vx * towards + ch_x ;
		        for(m = ch_x - 2*6 -24; m <= ch_x + 2*6 + 24; m ++)
				{
		            for(n = ch_y - 21 + ch_vy; n <= ch_y + 21 - ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
					}
				}
				if(judgestate() == 5)
				{
					isdie = 1;
					break;
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
				}                                                             //����kidͼƬ
	            int c;
	            for(i = ch_x; i <= ch_x + 26; i ++)
				{
		            for(j = ch_y; j <= ch_y + 20; j ++)
					{
			            c = getpixel(i, j);
                        if(c == 0xffffff)
				            putpixel(i, j, mapcolor[i][j]);          //ȥ��kid֮�����ɫ
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
	if(isdie == 1)
		dead();
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

//��Ծ����
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
				ch_vx = 0;
			else
				ch_vx = 6;
			ch_x1 = ch_x;
			ch_x = ch_x - ch_vx;
			
		}
		else if((GetAsyncKeyState(VK_RIGHT)&0x8000))
		{
			towards = 1;
			if(judgestate() == 1)
				ch_vx = 0;
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
			for(m = ch_x - 2*6 -24; m <= ch_x + 2*6+ 24; m ++)
			{
	            for(n = 0; n <= judge_ch_y_foot; n ++)
				{
		            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
				}
			}
			break;
		}

		if((judgestate() == 2 || judgestate() == 1 ) && (maps[(judge_ch_x_front - towards)/ bian][((int)(judge_ch_y_head - ch_vy))/ bian] == 1 || 
					maps[(judge_ch_x_behind - towards)/ bian][((int)(judge_ch_y_head - ch_vy))/ bian] == 1))
				{
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
            for(m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 2 * ch_vy - 42; n <= ch_y + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
					}
				}
			if(judgestate() == 5)
				{
					isdie = 1;
					break;
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
				            putpixel(i, j, mapcolor[i][j]);          //ȥ��kid֮�����ɫ
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
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
					}
				}
			if(judgestate() == 5)
				{
					isdie = 1;
					break;
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
				            putpixel(i, j, mapcolor[i][j]);          //ȥ��kid֮�����ɫ
					}
				}
				FlushBatchDraw();
				Sleep(fps);
				left_i++;
				if(left_i == 4)
					left_i = 0;
				if(judgestate() == 3)
			{
					for(m = ch_x - 2*6 -24; m <= ch_x + 2*6+ 24; m ++)
				{
		            for(n = 0; n <= judge_ch_y_foot; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
					}
				}
				break;
			}
				ch_vy = ch_vy - gravity;
		}
		if(ch_vy <=0 )
			break;
	}
	if(isdie == 1)
		dead();
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
	while(isdie == 0)
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

		if(judgestate() == 3)
		{
			for(m = ch_x - 2*6 -24; m <= ch_x + 2*6+ 24; m ++)
			{
	            for(n = 0; n <= judge_ch_y_foot; n ++)
				{
		            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
				}
			}
			break;
		}
		if((judgestate() == 2 || judgestate() == 1 ) && (maps[(judge_ch_x_front - towards)/ bian][((int)(judge_ch_y_head - ch_vy))/ bian] == 1 || 
					maps[(judge_ch_x_behind - towards)/ bian][((int)(judge_ch_y_head - ch_vy))/ bian] == 1))
				{
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
            for(m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 2 * ch_vy - 42; n <= ch_y + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
					}
				}
			if(judgestate() == 5)
				{
					isdie = 1;
					break;
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
				            putpixel(i, j, mapcolor[i][j]);          //ȥ��kid֮�����ɫ
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
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
					}
				}
			if(judgestate() == 5)
				{
					isdie = 1;
					break;
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
		            putpixel(i, j, mapcolor[i][j]);          //ȥ��kid֮�����ɫ
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
	if(isdie == 1)
		dead();
	kidfall();

}

//�½�����
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
				ch_vx = 0;
			else
				ch_vx = 6;
			towards = -1;
		}
		else if((GetAsyncKeyState(VK_RIGHT)&0x8000))
		{
			if(judgestate() == 1)
				ch_vx = 0;
			else
				ch_vx = 6;
			towards = 1;
		}
		else 
			ch_vx = 0;
		ch_y = ch_y - ch_vy;
		float vy = ch_vy;
	    if(ch_vy <= - bian)
	        vy = - bian + 1;
		if(judgestate() == 4)
		{
			for(m = ch_x - 2*6 -24; m <= ch_x + 2*ch_vx + 24; m ++)
			{
	            for(n = 0; n <= judge_ch_y_foot; n ++)
				{
	                putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
				}
			}
			break;
		}
		if((judgestate() == 2 || judgestate() == 1 )&& (maps[(judge_ch_x_front - towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1 || 
			maps[(judge_ch_x_behind - towards)/ bian][((int)(judge_ch_y_foot - vy))/ bian] == 1))
		{
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
		if(towards == 1)
		{
            for(m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 2 * ch_vy - 42; n <= ch_y + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
					}
				}
			if(judgestate() == 5)
				{
					isdie = 1;
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
				         putpixel(i, j, mapcolor[i][j]);          //ȥ��kid֮�����ɫ
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
		    for(m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 2 * ch_vy - 42; n <= ch_y + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
					}
				}
	            loadimage(&img_kid_fall_left, "img_kid1.png");
				if(judgestate() == 5)
				{
					isdie = 1;
				}
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
				            putpixel(i, j, mapcolor[i][j]);          //ȥ��kid֮�����ɫ
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
	leftjump = 2;
	songtimes = 0;
	if(isdie == 0)
	    kidrun();
}

void dead()
{
	int i,j,c;
	{
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

	}
	while(1)
	{
	}
}


void main()
{
    initgraph(Weight,High);
	levels();
	kidwait();
	dead();
	closegraph();
}

