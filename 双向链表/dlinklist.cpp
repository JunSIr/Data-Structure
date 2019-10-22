#include "stdio.h"    
#include "string.h"
#include "ctype.h"      
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"
#include "iostream"
using namespace std; 

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef char ElemType;/* ElemType���͸���ʵ������������������Ϊint */

typedef struct Node
{
	ElemType data;
	struct Node *next;
	struct Node *prior;
}Node;
typedef struct Node *LinkList;


Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(Node)); /* ����ͷ���,��ʹLָ���ͷ��� */
	if (!(*L)) /* �洢����ʧ�� */
		return ERROR;
	(*L)->next = NULL; /* ָ����Ϊ�� */
	(*L)->prior = NULL; 
	return OK;
}
/*β�巨����˫������*/
void CreateListR(Node *&L, ElemType a[], int n) {

	Node *s, *r;
	L = (Node *)malloc(sizeof(Node));   /*����ͷ���*/
	r = L;								/*rʼ��ָ��β��㣬��ʼʱָ��ͷ���*/
	for (int i = 0; i < n; i++)			/*ѭ���������ݽ��*/
	{
		s = (Node *)malloc(sizeof(Node));
		s->data = a[i];                 /*�������ݽ��s*/
		r->next = s;					/*��s�����뵽r���֮��*/
		s->prior = r;					
		r = s;							/*rָ��β���*/
	}
	r->next = NULL; 
}

/*���������㲢��ӡ*/
Status visit(ElemType c)
{
	printf("%c ", c);
	return OK;
}

/*�������˫����*/
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;
	for(int i = 0 ; i<5; i++)
	{
		visit(p->data);
		p = p->next;
	}
	
	return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ�
�������������L������Ԫ�ظ��� */
int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next; /* pָ���һ����� */
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}

Status ListEmpty(LinkList L)
{
	if (L->next)
		return FALSE;
	else
		return TRUE;
}


/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* �����������e����L�е�i������Ԫ�ص�ֵ */
Status GetElem(LinkList L, int i, ElemType *e)
{
	int j;
	LinkList p;		/* ����һ���p */
	p = L->next;		/* ��pָ������L�ĵ�һ����� */
	j = 1;		/*  jΪ������ */
	while (p && j<i)  /* p��Ϊ�ջ��߼�����j��û�е���iʱ��ѭ������ */
	{
		p = p->next;  /* ��pָ����һ����� */
		++j;
	}
	if (!p || j>i)
		return ERROR;  /*  ��i��Ԫ�ز����� */
	*e = char(p->data);   /*  ȡ��i��Ԫ�ص����� */
	return OK;
}

int LocateElem(LinkList L, ElemType e)
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		i++;
		if (p->data == e) /* �ҵ�����������Ԫ�� */
			return i;
		p = p->next;
	}

	return 0;
}

Status ListInsert(LinkList *L, int i, ElemType e)
{
	int j = 0;
	LinkList p = *L, s;  /*pָ��ͷ��㣬j����Ϊ0*/

	if (i <= 0) return false; /*i���󷵻�false*/

	while (j < i - 1 && p != NULL) /*���ҵ�i-1�����*/
	{
		j++;
		p = p->next;
	}
	if (p == NULL)
	{
		return FALSE;  /*δ�ҵ���i-1����㣬����false*/
	}
	else {
		s = (LinkList)malloc(sizeof(LinkList)); /*�����½��s*/
		s->data = e;
		s->next = p->next;
		if (p->next != NULL)
		{
			p->next->prior = s;
			s->prior = p;
			p->next = s;
			return TRUE;
		}
	}
}

/*��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) * /
/* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p->next && j < i)	/* ����Ѱ�ҵ�i��Ԫ�� */
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i)
		return ERROR;           /* ��i��Ԫ�ز����� */
	q = p->next;
	p->next = q->next;			/* ��q�ĺ�̸�ֵ��p�ĺ�� */
	*e = q->data;               /* ��q����е����ݸ�e */
	free(q);                    /* ��ϵͳ���մ˽�㣬�ͷ��ڴ� */
	return OK;
}

/* ���쳣�жϣ���ʼ������˳�����Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
Status ClearList(LinkList *L)
{
	LinkList p, q;
	p = (*L)->next;           /*  pָ���һ����� */
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}         
	
		
	
	(*L)->next = NULL;        /* ͷ���ָ����Ϊ�� */
	return OK;
}



int main() {
	LinkList L;
	ElemType e;
	Status i;
	/*1.��ʼ��˫����*/
	i = InitList(&L);
	printf("1.˫�������ʼ�����\n");

	/*2.���β���β�巨����abcdeԪ��*/
	char a[] = { 'a','b','c','d','e' }; 
	CreateListR(*&L, a, 5); 
	printf("2.β�巨����˫������ִ�����\n");
	
	/*3.���˫����*/
	ListTraverse(L); 
	printf("3.˫������������\n");

	/*4.���˫����h�ĳ���*/
	printf("4.���˫�������Ԫ�ظ��������ȣ�"); 
	int j  = ListLength(L); 
	cout << j;
	printf("\n"); 
	
	/*5.�ж�˫����h�Ƿ�Ϊ��*/
	i = ListEmpty(L); 
	printf("5.L�Ƿ�գ�i=%d(1:�� 0:��)\n", i);

	/*6.���˫����h�ĵ�����Ԫ��*/
	GetElem(L, 3, &e);
	printf("6.���˫����h�ĵ�����Ԫ��%c\n",e);
	
	/*7. ���Ԫ��a��λ��*/
	printf("7.Ԫ��a��λ�ã�%d\n", LocateElem(L, 'a'));

	/*8.�ڵ�4��Ԫ��λ���ϲ���fԪ��*/
	ListInsert(&L, 4, 'f'); 
	printf("8.�ڵ�4��Ԫ��λ���ϲ���fԪ��ִ�����\n");

	/*9.���˫����*/
	ListTraverse(L);
	printf("9.˫������������\n");

	/*10.ɾ��˫����h�ĵ�3��Ԫ��*/
	i = ListDelete(&L, 3, &e); /* ɾ����j������ */
	printf("10.ɾ��˫����h�ĵ�3��Ԫ��ִ�����\n");

	/*11.���˫����*/
	ListTraverse(L);
	printf("11.˫������������\n");

	/*11.�ͷ�˫����*/
	//�쳣�ж�i = ClearList(&L);
	printf("12.�ͷ�˫����ִ�����");

	


	
	system("pause"); 
}

