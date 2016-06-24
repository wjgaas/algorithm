/*
----------------------------------------------------------------------------------
	problem : 487-3279
	url : http://poj.org/problem?id=1002
	Author : WJG
	time : 2015.09.28
	comment : 
----------------------------------------------------------------------------------
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <malloc.h>

#define MAXM 10000000

//map 'A'-'Y' to '2'-'9'
int tr(char c)
{
	if(c>'P') c--;
	return (c-'A')/3 + 2 + '0';
}

//trans string to int
int num2int(char *s, int len)
{
	char n[8];
	int cnt = 0;

	for(int i=0; i<len; i++)
		if(s[i] != '-')
			n[cnt++] = s[i]>='A' ? tr(s[i]):s[i];

	return atoi(n);
}

int main()
{
	int T;
	char num[50];

	//malloc array for hash
	int *tab = (int*)malloc(sizeof(int)*MAXM);
	memset(tab, 0, sizeof(int)*MAXM);

	scanf("%d", &T);

	for(int i=0; i<T; i++)
	{
		scanf("%s", num);
		tab[num2int(num, strlen(num))]++;
	}

	bool duplicate_flag=true;
	for(int i=0; i<MAXM; i++)
	{
		if(tab[i]>=2)
		{
			printf("%03d-%04d %d\n", i/10000, i%10000, tab[i]);
			duplicate_flag=false;
		}
	}

	if(duplicate_flag)
		printf("No duplicates.\n");

	free(tab);
}
