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

int fps = 20;               //֡��
float jump1 = 12;         //һ�����ٶ�
float jump2 = 10;          //�������ٶ�
float gravity = 1;      //�������ٶ�

int level = 1;           // �浵����
int isdie = 0;           //�����Ƿ����� 0��� 1���� 2����
int ischange = 0;        //��ͼת��
int gamestatus = 0;      //��Ϸ״̬��0Ϊ��ʼ�˵����棬1Ϊ������Ϸ��2Ϊ������Ϸ״̬��3Ϊ��Ϸ��ͣ

int towards = 1;        //�жϷ���
int ch_vx = 5 ;         //�����˶�ˮƽ�ٶ�
float ch_vy = 0;       //�����˶���ֱ�ٶ�
int left_i = 0;        //�������߶������
int right_i = 0;       //�������߶������
int isOnFloor = 0;     //�ж��Ƿ��ڵ�����
int leftjump = 2;
int songtimes = 0;     //�����ɿ�shift����
int maps[25][19];      //��ͼ����
int mapcolor[Weight][High]; //��ͼ���ص���ɫ

int ch_x = bian;                                //��������꣨���Ͻ����ص㣩
int ch_y = High - (bian + high_ch);          //���������꣨���Ͻ����ص㣩


char input;                                       //��ȡ��������


void background();                                //��Ϸ����(����������)
void Mapcolor();                                  //��Ϸ������ɫ���������飩
void levels();                                    //�ؿ�
void level1();
void kidwait();                                   //�޲����µ�kid����
void kidrun();                                    //kid��ͨ�ܵĶ���
void putin();
void kidjump1();
void kidjump2();
void kidfall();
int istouch();                                    //�ж��Ƿ���ש
void zhuankuai(int a,int b);                      //ש��ͼƬ��
void map1();                                      //��һ�ص�ͼ�滭

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
	background();
	map1();
	Mapcolor();
}

void map1()
{
	int i,j;
	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			maps[i][j] = 0;
	maps[0][18] = 1; maps[1][18] = 1; maps[2][18] = 1;
	maps[3][16] = 1; maps[4][16] = 1; maps[5][16] = 1;
	for(i = 0;i<25;i++)
		for(j = 0; j<19; j++)
			if(maps[i][j] == 1)
				zhuankuai(i,j);
}


//�ж��Ƿ���ש��
/*
int istouch()
{
	if 
*/



//kid������ʱ�򶯻�


void kidwait()                          
{
	ch_vx = 6;

	loadimage(&img_kid_right, "img_kid.png");
	loadimage(&img_kid_left,"img_kid1.png");
	int k,m,n;
	BeginBatchDraw();
	if(towards > 0)               //���ҳ���
	{
    	for(k=0; k <= 12;)
		{   
	    	 for(m = ch_x - ch_vx - 24; m <= ch_x + ch_vx + 24; m ++)
			 {
		        for(n = ch_y - 21 + ch_vy; n <= ch_y + 21 - ch_vy; n ++)
				{
		         putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
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
		for(k=0; k <= 12;)
		{   
	    	 for(m = ch_x - ch_vx -24; m <= ch_x + ch_vx + 24; m ++)
			 {
		        for(n = ch_y - 21 + ch_vy; n <= ch_y + 21 - ch_vy; n ++)
				{
		         putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
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
	if((GetAsyncKeyState(VK_LSHIFT)&0x8000))
		kidjump1();
	 kidrun();
	getch();
	EndBatchDraw();
}

//kid�ܲ�����
void kidrun()
{
	ch_vx = 6;
	int m,n,i,j;
	BeginBatchDraw();
	right_i = 0;
	left_i = 0;
	while(1)
	{
		if((GetAsyncKeyState(VK_LSHIFT)&0x8000))
			break;
		if(kbhit())
		{
	        if((GetAsyncKeyState(VK_RIGHT)&0x8000))                             //�����˶�
			{
				towards = 1;
				ch_x = ch_vx * towards + ch_x ;

		        for(m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 21 + ch_vy; n <= ch_y + 21 - ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
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
				ch_x = ch_vx * towards + ch_x ;
		        for(m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 21 + ch_vy; n <= ch_y + 21 - ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
					}
				}
	            loadimage(&img_kid_run_left, "img_kid1.png");
		        switch (left_i)
				{
			        case 0:
			 	       	putimage(ch_x,ch_y,26,21,&img_kid_run_left,174-(28*(left_i+1)),29);
                        break;
                    case 1:
			   	       	putimage(ch_x,ch_y,26,21,&img_kid_run_left,174-(28*(left_i+1)+2),29);
			   	       	break;
			        case 2:
			   	       	putimage(ch_x,ch_y,26,21,&img_kid_run_left,174-(28*(left_i+1)+2),29);
			           	break;
			      	case 3:
			           	putimage(ch_x,ch_y,26,21,&img_kid_run_left,174-(28*(left_i+1)+2),29);
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
	if((GetAsyncKeyState(VK_LSHIFT)&0x8000))
		kidjump1();
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
	while(1)
    {
		if((GetAsyncKeyState(VK_LEFT)&0x8000))
		{
			ch_vx = 6;
			ch_x = ch_x - ch_vx;
			towards = -1;
		}
		else if((GetAsyncKeyState(VK_RIGHT)&0x8000))
		{
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

		if(songtimes == 1&&(GetAsyncKeyState(VK_LSHIFT)&0x8000))
		{
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
			ch_vx = 6;
			ch_x = ch_x - ch_vx;
			towards = -1;
		}
		else if((GetAsyncKeyState(VK_RIGHT)&0x8000))
		{
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
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
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
	kidfall();

}

//�½�����
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
			ch_vx = 6;
			ch_x = ch_x - ch_vx;
			towards = -1;
		}
		else if((GetAsyncKeyState(VK_RIGHT)&0x8000))
		{
			ch_vx = 6;
			ch_x = ch_x + ch_vx;
			towards = 1;
		}
		else 
			ch_vx = 0;
		ch_y = ch_y - ch_vy;
		if(towards == 1)
		{
            for(m = ch_x - 2*ch_vx -24; m <= ch_x + 2*ch_vx + 24; m ++)
				{
		            for(n = ch_y - 2 * ch_vy - 42; n <= ch_y + 42 + 2 * ch_vy; n ++)
					{
			            putpixel(m, n, mapcolor[m][n]);          //ȥ��kid��һ֡����
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
				         putpixel(i, j, mapcolor[i][j]);          //ȥ��kid֮�����ɫ
				}
			}
		    FlushBatchDraw();
			Sleep(fps);
			right_i++;
			if(right_i == 4)
				right_i = 0;
			if(ch_y - ch_vy >= High - (bian + high_ch))
			{
				ch_y = High - (bian + high_ch);
				break;
			}
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
				if(ch_y - ch_vy >= High - (bian + high_ch))
			{
				ch_y = High - (bian + high_ch);
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



//��ü�������

void putin()
{
	while(1)
	{
	    input = getch();
	    if (::GetAsyncKeyState(VK_RIGHT)& 0x8000)
		{
			right_i ++; 
			kidrun();
		}
	}
}



void main()
{
    initgraph(Weight,High);
	levels();
	kidwait();
	closegraph();
}
