#include "string.h"
#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 40 /* 存储空间初始分配量 */

typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;	/* ElemType类型根据实际情况而定，这里假设为int */

typedef char String[MAXSIZE + 1]; /*  0号单元存放串的长度 */

 /* 生成一个其值等于chars的串T */
Status StrAssign(String T, char *chars)
{

													/*strlen-->检测字符串长度*/
	int i;
	if (strlen(chars)>MAXSIZE)
		return ERROR;
	else
	{	
		/*T[0]存放串的长度*/
		T[0] = strlen(chars);


		for (i = 1; i <= T[0]; i++)
			T[i] = *(chars + i - 1);
		return OK;
	}
}

/* 由串S复制得串T */
Status StrCopy(String T, String S)
{
	int i;
	for (i = 0; i <= S[0]; i++)
		T[i] = S[i];
	return OK;
}

/* 若S为空串,则返回TRUE,否则返回FALSE */
Status StrEmpty(String S)
{
	if (S[0] == 0)
		return TRUE;
	else
		return FALSE;
}

/*  初始条件: 串S和T存在 */
/*  操作结果: 若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0 */
int StrCompare(String S, String T)
{
	int i;
	for (i = 1; i <= S[0] && i <= T[0]; ++i)
		if (S[i] != T[i])
			return S[i] - T[i];
	return S[0] - T[0];
}

/* 返回串的元素个数 */
int StrLength(String S)
{
	return S[0];
}

/* 初始条件:串S存在。操作结果:将S清为空串 */
Status ClearString(String S)
{
	S[0] = 0;/*  令串长为零 */
	return OK;
}

/* 用T返回S1和S2联接而成的新串。若未截断，则返回TRUE，否则FALSE */
Status Concat(String T, String S1, String S2)
{
	int i;
	if (S1[0] + S2[0] <= MAXSIZE)
	{ /*  未截断 */
		for (i = 1; i <= S1[0]; i++)
			T[i] = S1[i];
		for (i = 1; i <= S2[0]; i++)
			T[S1[0] + i] = S2[i];
		T[0] = S1[0] + S2[0];
		return TRUE;
	}
	else
	{ /*  截断S2 */
		for (i = 1; i <= S1[0]; i++)
			T[i] = S1[i];
		for (i = 1; i <= MAXSIZE - S1[0]; i++)
			T[S1[0] + i] = S2[i];
		T[0] = MAXSIZE;
		return FALSE;
	}
}

/* 用Sub返回串S的第pos个字符起长度为len的子串。 */
Status SubString(String Sub, String S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S[0] || len<0 || len>S[0] - pos + 1)
		return ERROR;
	for (i = 1; i <= len; i++)
		Sub[i] = S[pos + i - 1];
	Sub[0] = len;
	return OK;
}

/* 返回子串T在主串S中第pos个字符之后的位置。若不存在,则函数返回值为0。 */
/* 其中,T非空,1≤pos≤StrLength(S)。 */
int Index(String S, String T, int pos)
{
	int i = pos;	/* i用于主串S中当前位置下标值，若pos不为1，则从pos位置开始匹配 */
	int j = 1;				/* j用于子串T中当前位置下标值 */
	while (i <= S[0] && j <= T[0]) /* 若i小于S的长度并且j小于T的长度时，循环继续 */
	{
		if (S[i] == T[j]) 	/* 两字母相等则继续 */
		{
			++i;
			++j;
		}
		else 				/* 指针后退重新开始匹配 */
		{
			i = i - j + 2;		/* i退回到上次匹配首位的下一位 */
			j = 1; 			/* j退回到子串T的首位 */
		}
	}
	if (j > T[0])
		return i - T[0];
	else
		return 0;
}


/*  T为非空串。若主串S中第pos个字符之后存在与T相等的子串， */
/*  则返回第一个这样的子串在S中的位置，否则返回0 */
int Index2(String S, String T, int pos)
{
	int n, m, i;
	String sub;
	if (pos > 0)
	{
		n = StrLength(S);	/* 得到主串S的长度 */
		m = StrLength(T);	/* 得到子串T的长度 */
		i = pos;
		while (i <= n - m + 1)
		{
			SubString(sub, S, i, m);	/* 取主串中第i个位置长度与T相等的子串给sub */
			if (StrCompare(sub, T) != 0)    /* 如果两串不相等 */
				++i;
			else 				/* 如果两串相等 */
				return i;		/* 则返回i值 */
		}
	}
	return 0;	/* 若无子串与T相等，返回0 */
}


/*  初始条件: 串S和T存在,1≤pos≤StrLength(S)+1 */
/*  操作结果: 在串S的第pos个字符之前插入串T。完全插入返回TRUE,部分插入返回FALSE */
Status StrInsert(String S, int pos, String T)
{
	int i;
	if (pos<1 || pos>S[0] + 1)
		return ERROR;
	if (S[0] + T[0] <= MAXSIZE)
	{ /*  完全插入 */
		for (i = S[0]; i >= pos; i--)
			S[i + T[0]] = S[i];
		for (i = pos; i<pos + T[0]; i++)
			S[i] = T[i - pos + 1];
		S[0] = S[0] + T[0];
		return TRUE;
	}
	else
	{ /*  部分插入 */
		for (i = MAXSIZE; i <= pos; i--)
			S[i] = S[i - T[0]];
		for (i = pos; i<pos + T[0]; i++)
			S[i] = T[i - pos + 1];
		S[0] = MAXSIZE;
		return FALSE;
	}
}

/*  初始条件: 串S存在,1≤pos≤StrLength(S)-len+1 */
/*  操作结果: 从串S中删除第pos个字符起长度为len的子串 */
Status StrDelete(String S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S[0] - len + 1 || len<0)
		return ERROR;
	for (i = pos + len; i <= S[0]; i++)
		S[i - len] = S[i];
	S[0] -= len;
	return OK;
}

/*  初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
/*  操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */
Status Replace(String S, String T, String V)
{
	int i = 1; /*  从串S的第一个字符起查找串T */
	if (StrEmpty(T)) /*  T是空串 */
		return ERROR;
	do
	{
		i = Index(S, T, i); /*  结果i为从上一个i之后找到的子串T的位置 */
		if (i) /*  串S中存在串T */
		{
			StrDelete(S, i, StrLength(T)); /*  删除该串T */
			StrInsert(S, i, V); /*  在原串T的位置插入串V */
			i += StrLength(V); /*  在插入的串V后面继续查找串T */
		}
	} while (i);
	return OK;
}

/*  输出字符串T */
void StrPrint(String T)
{
	int i;
	for (i = 1; i <= T[0]; i++)
		printf("%c", T[i]);
	printf("\n");
}

/*子串的替换*/
Status RepStr1(String T, int i, int j, String V) {

	int k;
	/*定义结果串*/
	
	String str;

	/*将结果串设为空串*/
	str[0] = 0;

	/*位序参数不正确时返回空串*/
	if (i <= 0 || i > T[0] || i + j - 1 > T[0])
		return FALSE; 

	/*i前替换给结果串*/
	for (k = 1; k <= i-1; k++) 
		str[k] = T[k]; 
	printf("i前替换给结果串结果：");
	str[0] = i - 1; 
	StrPrint(str);
	
	/*将替换串赋给结果串*/
	for (k = 1; k <= V[0]; k++) 
		str[i + k -1] = V[k]; 		
		str[0] = i - 1+V[0];
	printf("\n将替换串赋给结果串：");
	StrPrint(str);
	
	/*将前串的后续赋值给结果串*/
		
	for (int m = i  ; m <= T[0]; m++)
		str[i-1+V[0]+1] = T[m];
		printf("\n将原串后续接给结果串：");
		str[0] = i - 1 + V[0] + T[0] - j; 
		StrPrint(str);

	printf("8.将串s的第2个字符开始的第5个字符替换成串s1而产生串s2-->执行完毕\n");
	printf("******************************************************");
	/*输出串s2*/
	printf("\n9.输出串s2--->");
	StrPrint(str);


}

int main()
{

	int i, j ,h;
	Status k;
	//char ss;
	String t, s, s1;
	String s2; 
	String s3;
	String s4;


	/*测试
	String s3, s4; 
	StrAssign(s3 ,"abcd");
	StrAssign(s4 ,"efg");
	RepStr1(s3, 2, 3, s4); 
	*/

	/*建立串s*/
	k = StrAssign(s, "abcdefghijklnm");
	if (!k)
	{
		printf("串长超过MAXSIZE(=%d)\n", MAXSIZE);
		exit(0);
	}
	printf("1.1串s创建成功\n"); 
	

	/*建立串s1*/

	h = StrAssign(s1, "abcdefghijklnm");
	if (!h)
	{
		printf("串长超过MAXSIZE(=%d)\n", MAXSIZE);
		exit(0);
	}
	printf("1.2串s1创建成功\n");


	/*输出串s*/
	printf("2.输出串s--->"); 
	StrPrint(s);

	/*输出串s的长度*/	
	int l = StrLength(s); 
	printf("3.输出串s的长度:-->%d",l);

	/*在串s的第9个字符位插入串s1而产生串s2*/

		/* 由串s复制得s2 */
		StrCopy(s2, s); 	

	StrInsert(s2, 9, s1);
	printf("\n4.在串s的第9个字符位插入串s1而产生串s2--->插入成功\n"); 

	/*输出串s*/
	printf("5.输出串s2--->");
	StrPrint(s);

	/*删除串s的第2个字符开始的5个字符而产生串s2*/
	StrDelete(s, 2,5);
	printf("6.已执行：删除串s的第2个字符开始的5个字符而产生串s2\n"); 
	
	/*输出串s*/
	printf("7.输出串s--->");
	StrPrint(s);

	/*将串s的第2个字符开始的第5个字符替换成串s1而产生串s2*/
	printf("******************************************************\n");
	printf("\n8.将串s的第2个字符开始的第5个字符替换成串s1而产生串s2开始执行\n");
		RepStr1(s,2,5,s1);
	
	/*提取串s的第2个字符开始的10个字符而产生串s3*/
		printf("10.提取串s的第2个字符开始的10个字符而产生串s3开始执行\n");

		
		int le = StrLength(s);
		printf("串s的长度：%d\n", le); 

		StrAssign(s3, "");
		SubString(s3, s, 2, 7); 
		printf("10.提取串s的第2个字符开始的10个字符而产生串s3执行完毕\n");

		/*输出串s3*/
		printf("11.输出串s3--->");
		StrPrint(s3);


		/*将串s1和串s2连接起来而产生串s4*/
		printf("12.将串s1和串s2连接起来而产生串s4\n");
		StrAssign(s4, "");
		Concat(s4, s1, s2); 
		printf("12.将串s1和串s2连接起来而产生串s4执行完毕\n");


		/*输出串s4*/
		printf("13.输出串s4--->");
		StrPrint(s4);


		system("pause"); 

		return 0;

	

}


