
#include "stdio.h"    
#include "string.h"
#include "ctype.h"      
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"


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
}Node;
typedef struct Node *LinkList; /* ����LinkList */

							   /* ��ʼ��˳�����Ա� */
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(Node)); /* ����ͷ���,��ʹLָ���ͷ��� */
	if (!(*L)) /* �洢����ʧ�� */
		return ERROR;
	(*L)->next = *L; 

	return OK;
}

Status ListInsert(LinkList *L, int i, ElemType e)
{
	int j;
	LinkList p, s;
	p = *L;
	j = 1;
	while (p && j < i)     /* Ѱ�ҵ�i����� */
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;   /* ��i��Ԫ�ز����� */
	s = (LinkList)malloc(sizeof(Node));  /*  �����½��(C���Ա�׼����) */
	s->data = e;
	s->next = p->next;      /* ��p�ĺ�̽�㸳ֵ��s�ĺ��  */
	p->next = s;          /* ��s��ֵ��p�ĺ�� */
	return OK;
}

Status visit(ElemType c)
{
	printf("%c ", c);
	return OK;
}

Status ListTraverse(LinkList L)
{
	LinkList p = L->next;
	while (p->next != L)
	{
		visit(p->data);
		p = p->next;
	}
	visit(p->data);
	

	
	printf("\n");
	return OK;
}

int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next; /* pָ���һ����� */
	while (p->next != L)
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


Status GetElem(LinkList L, int i, ElemType *e)
{
	int j;
	LinkList p;		/* ����һ���p */
	p = L->next;		/* ��pָ������L�ĵ�һ����� */
	j = 1;		/*  jΪ������ */
	while (p!=L && j<i)  /* p��Ϊ�ջ��߼�����j��û�е���iʱ��ѭ������ */
	{
		p = p->next;  /* ��pָ����һ����� */
		++j;
	}
	if (j>i)
		return ERROR;  /*  ��i��Ԫ�ز����� */
	*e = char(p->data);   /*  ȡ��i��Ԫ�ص����� */
	return OK;
}

int LocateElem(LinkList L, ElemType e)
{
	int i = 0;
	LinkList p = L->next;
	while (p->next!=L)
	{
		i++;
		if (p->data == e) /* �ҵ�����������Ԫ�� */
			return i;
		p = p->next;
	}

	return 0;
}

Status ListDelete(LinkList *L, int i, ElemType *e)
{
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (j < i)	/* ����Ѱ�ҵ�i��Ԫ�� */
	{
		p = p->next;
		++j;
	}
	if (j > i)
		return ERROR;           /* ��i��Ԫ�ز����� */
	q = p->next;
	p->next = q->next;			/* ��q�ĺ�̸�ֵ��p�ĺ�� */
	*e = q->data;               /* ��q����е����ݸ�e */
	free(q);                    /* ��ϵͳ���մ˽�㣬�ͷ��ڴ� */
	return OK;
}

Status ClearList(LinkList *L)
{
	LinkList p, q;
	p = (*L)->next;           /*  pָ���һ����� */
	while (p->next!=*L)                /*  û����β */
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;        /* ͷ���ָ����Ϊ�� */
	return OK;
}


int main()
{
	LinkList L;
	ElemType e;
	Status i;
	
	/*1.��ʼ��������*/
	i = InitList(&L);
	printf("1.ѭ���������ʼ�����\n");

	/*2.���β���β�巨����abcdeԪ��*/

	ListInsert(&L, 1, 'a');
	ListInsert(&L, 2, 'b');
	ListInsert(&L, 3, 'c');
	ListInsert(&L, 4, 'd');
	ListInsert(&L, 5, 'e');
	printf("2.���β���β�巨����abcdeԪ��ִ�����\n");


	/*3.���ѭ��������*/
	printf("3.���������\n");
	ListTraverse(L);

	/*4.���������h�ĳ���*/
	printf("4.ListLength(L)=%d \n", ListLength(L));

	/*5.�жϵ�����h�Ƿ�Ϊ��*/
	i = ListEmpty(L);
	printf("5.L�Ƿ�գ�i=%d(1:�� 0:��)\n", i);

	/*6.���������h�ĵ�����Ԫ��*/
	GetElem(L, 3, &e);
	printf("6.��3��Ԫ�ص�ֵΪ��%c\n", e);

	/*7. ���Ԫ��a��λ��*/
	printf("7.Ԫ��a��λ�ã�%d\n", LocateElem(L, 'a'));


	
	/*8.�ڵ�4��Ԫ��λ���ϲ���fԪ��*/
	i = ListInsert(&L, 4, 'f');
	printf("8.�ڵ�4��Ԫ��λ���ϲ���fԪ��ִ�����\n");

	/*9.���ѭ��������*/
	printf("9.���ѭ��������");
	ListTraverse(L);

	/*10.ɾ��������h�ĵ�3��Ԫ��*/
	i = ListDelete(&L, 3, &e); /* ɾ����j������ */
	printf("10.ɾ��������h�ĵ�3��Ԫ��ִ�����\n");

	/*11.���������*/
	printf("11.���ѭ��������");
	ListTraverse(L);

	/*12.�ͷŵ�����*/
	i = ClearList(&L);
	printf("12.�ͷŵ�����ִ�����");
	system("pause");

	//printf("1.��ʼ��L��ListLength(L)=%d\n", ListLength(L));
}



