#include<stdio.h>

int a,b;//自变量。不区分非终结符，n代表etf，E::=E+T|T，T::=T*F|F，F::=(E)|i

int f[6]={0,0,2,4,5,5};//栈顶
int g[6]={0,5,1,3,0,5};//读入

//6a+b
int error[7]={0,4,6,25,29,31,35};

//# ( + * ) i 
int reserver(char i)
{
	switch(i)
	{
		case '\0'://字符串的结尾，书上为sharp，C语言为0 
		{
			return 0;
		}
		case '(':
		{
			return 1;
		}
		case '+':
		{
			return 2;
		}
		case '*':
		{
			return 3;
		}
		case ')': 
		{
			return 4;
		}
		case 'i':
		{
			return 5;
		}
		default://非法读入报错 
		{
			return -1;
		}
	}
}

int stack[2048];
int stacktop;//stacktop总指向栈顶元素的下一个位置，即stacktop-1才是栈顶元素 

char cc[2048];
int cctop;//cctop总指向下一个要读的字符 

int getsym()//返回stacktop应该减去的值 
{
	if(stacktop==0)//栈为空 
	{
		return -1;
	}
	if(stack[stacktop-1]==5)//i，5
	{
		return 1;
	}
	if(stacktop<3)//后面的规则要求栈里至少有3个字符，即012的位置必须有字符，stacktop至少是3，避免下溢出错误 
	{
		return -1;
	}
	if(stack[stacktop-1]==6&&stack[stacktop-2]==2&&stack[stacktop-3]==6)//E+T，626
	{
		return 3;
	}
	if(stack[stacktop-1]==6&&stack[stacktop-2]==3&&stack[stacktop-3]==6)//T*F，636
	{
		return 3;
	}
	if(stack[stacktop-1]==4&&stack[stacktop-2]==6&&stack[stacktop-3]==1)//(E)，164
	{
		return 3;
	}
	return -1;
}

FILE *in;

int main(__attribute__((unused)) int argc,char *argv[])
{
	in=fopen(argv[1],"r");
	fscanf(in,"%s",cc);
	cctop=0;
	stacktop=0;
	while(1)//减少用else，每个分支末尾尽可能continue或者break
	{
		if(cctop==-1)//已经读过文件尾了
		{
			printf("E\n");//读入出错时输出E 
			break;
		}
		reserver(cc[cctop]);//读入不一定合法
		if(b==-1)
		{
			printf("E\n");//读入出错时输出E 
			break;
		}
		if(stacktop!=0)//栈非空
		{
			a=stack[stacktop-1];//此时栈顶一定是合法字符的整数 
			if(a==6)//栈顶是非终结符
			{
				if(stacktop==1)
				{
					a=0;//表示前一个位置应该是sharp 
				}
				else
				{
					a=stack[stacktop-2];
					if(a==6)//每一步非终结符都不能相邻，再前面一个应该是终结符才对 
					{
						printf("E\n");//违反规则时输出E  
						break;
					}
				}
				
			}
			if(a==0&&b==0&&stack[stacktop-1]==6&&stacktop==1)//整个程序顺利结束 
			{
				break;
			}
			int count=6*a+b;//查错误表 
			int flag=0;//暂存
			int i;
			for(i=0;i<7;i++)
			{
				if(count==error[i])
				{
					printf("E\n");//无法判断优先级关系时输出E
					flag=1;
					break;//这个break没有跳出while
				}
			}
			if(flag==1)
			{
				break;//这里break才能跳出while
			}
			if(f[a]>g[b])//仅大于的时候才规约，其他时候读入 
			{
				int rr=getsym();
				if(rr==-1)
				{
					printf("RE\n");//规约失败时输出RE 
					break;
				}
				printf("R\n");//规约成功时输出R
				stacktop-=rr;
				stack[stacktop]=6;//非终结符号 
				stacktop++;
				continue;
			}
		}
        stacktop++;
		if(cc[cctop]!='\0')//没读入文件尾字符的时候才要报读入 
		{
			printf("I%c\n",cc[cctop]);
			cctop++;
		}
		else
		{
			cctop=-1;//已经读过文件尾了 
		}
	}
	fclose(in);
	return 0; 
}
