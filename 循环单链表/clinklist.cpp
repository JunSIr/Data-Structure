
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

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char ElemType;/* ElemType类型根据实际情况而定，这里假设为int */



typedef struct Node
{
	ElemType data;
	struct Node *next;
}Node;
typedef struct Node *LinkList; /* 定义LinkList */

							   /* 初始化顺序线性表 */
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
	if (!(*L)) /* 存储分配失败 */
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
	while (p && j < i)     /* 寻找第i个结点 */
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;   /* 第i个元素不存在 */
	s = (LinkList)malloc(sizeof(Node));  /*  生成新结点(C语言标准函数) */
	s->data = e;
	s->next = p->next;      /* 将p的后继结点赋值给s的后继  */
	p->next = s;          /* 将s赋值给p的后继 */
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
	LinkList p = L->next; /* p指向第一个结点 */
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
	LinkList p;		/* 声明一结点p */
	p = L->next;		/* 让p指向链表L的第一个结点 */
	j = 1;		/*  j为计数器 */
	while (p!=L && j<i)  /* p不为空或者计数器j还没有等于i时，循环继续 */
	{
		p = p->next;  /* 让p指向下一个结点 */
		++j;
	}
	if (j>i)
		return ERROR;  /*  第i个元素不存在 */
	*e = char(p->data);   /*  取第i个元素的数据 */
	return OK;
}

int LocateElem(LinkList L, ElemType e)
{
	int i = 0;
	LinkList p = L->next;
	while (p->next!=L)
	{
		i++;
		if (p->data == e) /* 找到这样的数据元素 */
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
	while (j < i)	/* 遍历寻找第i个元素 */
	{
		p = p->next;
		++j;
	}
	if (j > i)
		return ERROR;           /* 第i个元素不存在 */
	q = p->next;
	p->next = q->next;			/* 将q的后继赋值给p的后继 */
	*e = q->data;               /* 将q结点中的数据给e */
	free(q);                    /* 让系统回收此结点，释放内存 */
	return OK;
}

Status ClearList(LinkList *L)
{
	LinkList p, q;
	p = (*L)->next;           /*  p指向第一个结点 */
	while (p->next!=*L)                /*  没到表尾 */
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;        /* 头结点指针域为空 */
	return OK;
}


int main()
{
	LinkList L;
	ElemType e;
	Status i;
	
	/*1.初始化单链表*/
	i = InitList(&L);
	printf("1.循环单链表初始化完毕\n");

	/*2.依次采用尾插法插入abcde元素*/

	ListInsert(&L, 1, 'a');
	ListInsert(&L, 2, 'b');
	ListInsert(&L, 3, 'c');
	ListInsert(&L, 4, 'd');
	ListInsert(&L, 5, 'e');
	printf("2.依次采用尾插法插入abcde元素执行完毕\n");


	/*3.输出循环单链表*/
	printf("3.输出单链表\n");
	ListTraverse(L);

	/*4.输出单链表h的长度*/
	printf("4.ListLength(L)=%d \n", ListLength(L));

	/*5.判断单链表h是否为空*/
	i = ListEmpty(L);
	printf("5.L是否空：i=%d(1:是 0:否)\n", i);

	/*6.输出单链表h的第三个元素*/
	GetElem(L, 3, &e);
	printf("6.第3个元素的值为：%c\n", e);

	/*7. 输出元素a的位置*/
	printf("7.元素a的位置：%d\n", LocateElem(L, 'a'));


	
	/*8.在第4个元素位置上插入f元素*/
	i = ListInsert(&L, 4, 'f');
	printf("8.在第4个元素位置上插入f元素执行完毕\n");

	/*9.输出循环单链表*/
	printf("9.输出循环单链表");
	ListTraverse(L);

	/*10.删除单链表h的第3个元素*/
	i = ListDelete(&L, 3, &e); /* 删除第j个数据 */
	printf("10.删除单链表h的第3个元素执行完毕\n");

	/*11.输出单链表*/
	printf("11.输出循环单链表");
	ListTraverse(L);

	/*12.释放单链表*/
	i = ClearList(&L);
	printf("12.释放单链表执行完毕");
	system("pause");

	//printf("1.初始化L后：ListLength(L)=%d\n", ListLength(L));
}



