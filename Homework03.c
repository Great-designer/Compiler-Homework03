#include<stdio.h>

//# ( + * ) i 
const int sharp=0;
const int left=1;
const int plus=2;
const int star=3;
const int right=4;
const int ii=5;

const int nn=6;//�����ַ��ս����n����etf��E::=E+T|T��T::=T*F|F��F::=(E)|i

int a,b;//�Ա��� 

int f[6]={0,0,2,4,5,5};//ջ��
int g[6]={0,5,1,3,0,5};//����

//6a+b
int error[7]={0,4,6,25,29,31,35};

int reserver(char b)
{
	switch(b)
	{
		case '\0'://�ַ����Ľ�β������Ϊsharp��C����Ϊ0 
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
		default://�Ƿ����뱨�� 
		{
			return -1;
		}
	}
}

int stack[2048];
int stacktop;//stacktop��ָ��ջ��Ԫ�ص���һ��λ�ã���stacktop-1����ջ��Ԫ�� 

char cc[2048];
int cctop;//cctop��ָ����һ��Ҫ�����ַ� 

int getsym()//����stacktopӦ�ü�ȥ��ֵ 
{
	if(stacktop==0)//ջΪ�� 
	{
		return -1;
	}
	if(stack[stacktop-1]==5)//i��5
	{
		return 1;
	}
	if(stacktop<3)//����Ĺ���Ҫ��ջ��������3���ַ�����012��λ�ñ������ַ���stacktop������3��������������� 
	{
		return -1;
	}
	if(stack[stacktop-1]==6&&stack[stacktop-2]==2&&stack[stacktop-3]==6)//E+T��626
	{
		return 3;
	}
	if(stack[stacktop-1]==6&&stack[stacktop-2]==3&&stack[stacktop-3]==6)//T*F��636
	{
		return 3;
	}
	if(stack[stacktop-1]==4&&stack[stacktop-2]==6&&stack[stacktop-3]==1)//(E)��164
	{
		return 3;
	}
	return -1;
}

FILE *in;

int main(int argc,char *argv[])
{
	in=fopen(argv[1],"r");
	fscanf(in,"%s",cc);
	cctop=0;
	stacktop=0;
	while(1)//������else��ÿ����֧ĩβ������continue����break
	{
		if(cctop==-1)//�Ѿ������ļ�β��
		{
			printf("E\n");//�������ʱ���E 
			break;
		}
		b=reserver(cc[cctop]);//���벻һ���Ϸ�
		if(b==-1)
		{
			printf("E\n");//�������ʱ���E 
			break;
		}
		if(stacktop!=0)//ջ�ǿ�
		{
			a=stack[stacktop-1];//��ʱջ��һ���ǺϷ��ַ������� 
			if(a==6)//ջ���Ƿ��ս��
			{
				if(stacktop!=1)
				{
					a=f[stack[stacktop-2]];
					if(a==6)//ÿһ�����ս�����������ڣ���ǰ��һ��Ӧ�����ս���Ŷ� 
					{
						printf("E\n");//Υ������ʱ���E  
						break;
					}
				}
				else
				{
					a=0;//��ʾǰһ��λ��Ӧ����sharp 
				}
			}
			if(a==0&&b==0&&stack[stacktop-1]==6&&stacktop==1)//��������˳������ 
			{
				break;
			}
			int count=6*a+b;//������ 
			int i;//����ǰ�����д��ii����д��i�ķ��� 
			for(i=0;i<7;i++)
			{
				if(count==error[i])
				{
					printf("E\n");//�޷��ж����ȼ���ϵʱ���E
					break;
				}
			}
			if(f[a]>g[b])//�����ڵ�ʱ��Ź�Լ������ʱ����� 
			{
				int rr=getsym();
				if(rr==-1)
				{
					printf("RE\n");//��Լʧ��ʱ���RE 
					break;
				}
				printf("R\n");//��Լ�ɹ�ʱ���R
				stacktop-=rr;
				stack[stacktop]=6;//���ս���� 
				stacktop++;
				continue;
			}
		}
		stack[stacktop]=b;
		stacktop++;
		if(cc[cctop]!='\0')//û�����ļ�β�ַ���ʱ���Ҫ������ 
		{
			printf("I%c\n",cc[cctop]);
			cctop++;
		}
		else
		{
			cctop=-1;//�Ѿ������ļ�β�� 
		}
	}
	fclose(in);
	return 0; 
}
