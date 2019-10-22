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

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

typedef struct Node
{
	ElemType data;
	struct Node *next;
	struct Node *prior;
}Node;
typedef struct Node *LinkList;


Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
	if (!(*L)) /* 存储分配失败 */
		return ERROR;
	(*L)->next = NULL; /* 指针域为空 */
	(*L)->prior = NULL; 
	return OK;
}
/*尾插法建立双向链表*/
void CreateListR(Node *&L, ElemType a[], int n) {

	Node *s, *r;
	L = (Node *)malloc(sizeof(Node));   /*创建头结点*/
	r = L;								/*r始终指向尾结点，开始时指向头结点*/
	for (int i = 0; i < n; i++)			/*循环建立数据结点*/
	{
		s = (Node *)malloc(sizeof(Node));
		s->data = a[i];                 /*创建数据结点s*/
		r->next = s;					/*将s结点插入到r结点之后*/
		s->prior = r;					
		r = s;							/*r指向尾结点*/
	}
	r->next = NULL; 
}

/*访问链表结点并打印*/
Status visit(ElemType c)
{
	printf("%c ", c);
	return OK;
}

/*正向遍历双链表*/
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

/* 初始条件：顺序线性表L已存在。
操作结果：返回L中数据元素个数 */
int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next; /* p指向第一个结点 */
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


/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
Status GetElem(LinkList L, int i, ElemType *e)
{
	int j;
	LinkList p;		/* 声明一结点p */
	p = L->next;		/* 让p指向链表L的第一个结点 */
	j = 1;		/*  j为计数器 */
	while (p && j<i)  /* p不为空或者计数器j还没有等于i时，循环继续 */
	{
		p = p->next;  /* 让p指向下一个结点 */
		++j;
	}
	if (!p || j>i)
		return ERROR;  /*  第i个元素不存在 */
	*e = char(p->data);   /*  取第i个元素的数据 */
	return OK;
}

int LocateElem(LinkList L, ElemType e)
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		i++;
		if (p->data == e) /* 找到这样的数据元素 */
			return i;
		p = p->next;
	}

	return 0;
}

Status ListInsert(LinkList *L, int i, ElemType e)
{
	int j = 0;
	LinkList p = *L, s;  /*p指向头结点，j设置为0*/

	if (i <= 0) return false; /*i错误返回false*/

	while (j < i - 1 && p != NULL) /*查找第i-1个结点*/
	{
		j++;
		p = p->next;
	}
	if (p == NULL)
	{
		return FALSE;  /*未找到第i-1个结点，返回false*/
	}
	else {
		s = (LinkList)malloc(sizeof(LinkList)); /*创建新结点s*/
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

/*初始条件：顺序线性表L已存在，1≤i≤ListLength(L) * /
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p->next && j < i)	/* 遍历寻找第i个元素 */
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i)
		return ERROR;           /* 第i个元素不存在 */
	q = p->next;
	p->next = q->next;			/* 将q的后继赋值给p的后继 */
	*e = q->data;               /* 将q结点中的数据给e */
	free(q);                    /* 让系统回收此结点，释放内存 */
	return OK;
}

/* （异常中断）初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(LinkList *L)
{
	LinkList p, q;
	p = (*L)->next;           /*  p指向第一个结点 */
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}         
	
		
	
	(*L)->next = NULL;        /* 头结点指针域为空 */
	return OK;
}



int main() {
	LinkList L;
	ElemType e;
	Status i;
	/*1.初始化双链表*/
	i = InitList(&L);
	printf("1.双向链表初始化完毕\n");

	/*2.依次采用尾插法插入abcde元素*/
	char a[] = { 'a','b','c','d','e' }; 
	CreateListR(*&L, a, 5); 
	printf("2.尾插法建立双向链表执行完毕\n");
	
	/*3.输出双链表*/
	ListTraverse(L); 
	printf("3.双向链表输出完毕\n");

	/*4.输出双链表h的长度*/
	printf("4.输出双向链表的元素个数（长度）"); 
	int j  = ListLength(L); 
	cout << j;
	printf("\n"); 
	
	/*5.判断双链表h是否为空*/
	i = ListEmpty(L); 
	printf("5.L是否空：i=%d(1:是 0:否)\n", i);

	/*6.输出双链表h的第三个元素*/
	GetElem(L, 3, &e);
	printf("6.输出双链表h的第三个元素%c\n",e);
	
	/*7. 输出元素a的位置*/
	printf("7.元素a的位置：%d\n", LocateElem(L, 'a'));

	/*8.在第4个元素位置上插入f元素*/
	ListInsert(&L, 4, 'f'); 
	printf("8.在第4个元素位置上插入f元素执行完毕\n");

	/*9.输出双链表*/
	ListTraverse(L);
	printf("9.双向链表输出完毕\n");

	/*10.删除双链表h的第3个元素*/
	i = ListDelete(&L, 3, &e); /* 删除第j个数据 */
	printf("10.删除双链表h的第3个元素执行完毕\n");

	/*11.输出双链表*/
	ListTraverse(L);
	printf("11.双向链表输出完毕\n");

	/*11.释放双链表*/
	//异常中断i = ClearList(&L);
	printf("12.释放双链表执行完毕");

	


	
	system("pause"); 
}

