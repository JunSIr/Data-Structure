#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;
typedef int SElemType; /* SElemType���͸���ʵ������������������Ϊint */

					   /* ˳��ջ�ṹ */

typedef struct
{
	SElemType data[MAXSIZE];
	int top; /* ����ջ��ָ�� */
}SqStack;

int count = 0;



/*���ô˷������ڼ���Ƿ����N�ʺ����*/
int placeQueen(SqStack s, int i, int j) { //���ԣ�i��j���Ƿ���1->i-1�ʺ��г�ͻ��i���У�

		/*aΪ�����ķ���ֵ,0�Ƿ�1����*
		 *kΪ������Ĭ��Ϊ��һ��
		 */								
		int a = 0;  
		int k = 1;



		/*�������ǵ�һ��*/
		if (i == 1) 
		{
			/*����ȷ��-->��һ�е�һ��λ�ÿɷ�*/
			a = 1;		
			return a;
		}


		/*������ǵ�һ�У���i������϶�>=2*/
		while (k <= i - 1)				 //j=1��k-1���Ѿ������˻ʺ����
		{
			/*fabs()�ǶԸ�����ȡ����ֵ
			 *��֤N�ʺ��������㷨,s.data[k] == j-->ͬ��
			 fabs(j - s.data[k] == fabs(i - k��-->ͬ�Խ�
			*/
			if ((s.data[k] == j) || fabs(j - s.data[k] == fabs(i - k)))  
			{
				/*�޺���λ��*/
				a = 0;
				return a;
			}
			else
			k++;
		}
		
		a = 1;
		return a;
}



void queen(int n, SqStack &s) {
	int i, j, k;
	int  find = 0;

	/*��ʼ��ջ��ָ��*/
	s.top = 0;			
	/*����Ϊջ��ָ���ջ����ʼֵΪ1*/
	s.top++;		
	/*����Ϊջ��ָ���ջ����ʼֵΪ1*/     /*--->��1��1����ջ*/
	s.data[s.top] = 1;


	/*������ջ���գ�ѭ������-->����̽Ѱ*/
	while (s.top>0)    
		{
			/*iΪ������־������Ϊ����ʹ�ã�Ҳ�����ж��Ƿ��߾�*/
			i = s.top;    
		
		
			/*��ǰ�ʺ�����s.top == n-->�Ѿ����������һ���ʺ����лʺ���źã����һ����
				*ע�⣺���������������ΪN�ʺ������ж����
			*/
			if (s.top == n) {
				printf("��%d���⣺", ++count);
				for (k = 1; k < s.top; k++)
					printf("(%d,%d)", k, s.data[k]);
				printf("\n");
			}

			find = 0;

			/*��i+1��̽Ѱһ���Żʺ��λ��(i+1,j��*/
			for (j = 1; j <= n; j++)
					/*������ȷ������̽Ѱ��һ�����ʵ�λ��-->������ջ*/
				if (placeQueen(s, i + 1, j)) {
					/*��+1��ջ*/
					s.top++;
					/*����ջ*/
					s.data[s.top] = j;
					/*�ҵ���־,��������forѭ������־δ��������ߵ���һ�δ���*/
					find = 1;
					/*����forѭ��*/
					break; 
				}


			/*��ǰ����Ŀ��-->��ջ*/					
					if (find == 0) {
					while (s.top > 0) {
						/*1-�ѵ�����ĩ����λ�ü������޿ɷ�λ�ã���ջ*/
						if (s.data[s.top] == n) 
							/*������������-1*/
							s.top-- ;

						/*2-δ����ȫλ�ã�����λ�ó���̽Ѱ*/
						for (j = s.data[s.top] + 1; j <= n; j++)
								  /*�ں�������̽Ѱ�����ʵ�λ��*/
							if (placeQueen(s, s.top, j))
							{
									/*����ջ*/
								s.data[s.top] = j;  
								break;
							}


						/*��ǰ�ʺ��ڱ���û�пɷ�λ�ã���ջ
						*/
						if (j > n)
							s.top--;
						else
							break; 
							
				}}

	}}

int main()
{
	
	SqStack s;
	int n; 

		printf("��������Ҫ������ʺ�����...\n");
		scanf("%d", &n); 
	

		printf(" %d�ʺ�����������£�\n", n);
		queen(n,s); 
		printf("\n"); 
		
		system("pause"); 
	return 0;

}
