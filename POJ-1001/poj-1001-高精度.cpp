#include <cstdio>
#include <iostream>
#include <iostream>

using namespace std;

char num[10];
char res_mul[1000];
char add_dot[1000];
int n;

int multiply(char *num, int mul, int len)
{
	int a, b;
	__int64 cin=0;

	for(int i=0; i<len; i++)
	{
		a = num[i] - '0';
		b = a*mul + cin;
		num[i] = b%10 + '0';
		cin = b/10;
	}
	while(cin>0)
	{
		num[len++] = cin%10 + '0';
		cin /= 10;
	}

	return len;
}

int pow(char *num, int mul, int len, int &dots, int pow)
{
	int total_dots=dots;

	for(int i=1; i<pow; i++)
	{
		total_dots += dots;
		len = multiply(num, mul, len);
	}
	dots = total_dots;

	return len;
}

int insert_dot(char *dst, int &s_pos, char *src, int len, int dots)
{
	int cnt = 0;
	if(len<=dots)
	{
		for(int i=len; i<dots; i++)
			src[i] = '0';

		len = dots;
		dst[cnt++] = '0';
		dst[cnt++] = '.';
		for(int i=len-1; i>=0; i--)
			dst[cnt++] = src[i];
		len += 1;
	}
	else
	{
		dots = len - dots + 1;
		for(int i=len-1; i>=0; i--)
		{
			if(cnt == dots-1)
				dst[cnt++] = '.';
			dst[cnt++] = src[i];
		}
	}

	len += 1;

	int fdot=true;
	for(int i=len-1; i>=0; i--)
	{
		if(dst[i]=='.')
		{
			fdot = false;
			len--;
			break;
		}
		if(dst[i]=='0')
			len--;
		else
			break;
	}

	if(fdot && dst[0]=='0')
		s_pos = 1;
	else
		s_pos = 0;

	return len;
}

int remove_dot(char *dst, char *src, int &len, int &dots)
{
	bool fdot=false;
	for(int i=0; i<len; i++)
	{
		if(src[i] == '.')
		{
			fdot = true;
			break;
		}
	}

	if(!fdot)
	{
		src[len++] = '.';
		src[len++] = '0';
	}

	dots=-1;
	int cnt = len-1;
	dst[cnt--] = '\0';
	for(int i=0; i<len; i++)
	{
		if(dots!=-1) src[i-1] = src[i];

		if(src[i]!='.')
			dst[cnt--] = src[i];
		else
			dots = i;
	}
	src[len-1] = '\0';
	dots = len - dots - 1;

	return atoi(src);
}

int main()
{
	while (scanf("%s %d", num, &n)==2)
	{
		int dots;
		int len = strlen(num);

		int mul = remove_dot(res_mul, num, len, dots);
		len = pow(res_mul, mul, len-1, dots, n);

		int s_pos;
		len = insert_dot(add_dot, s_pos, res_mul, len, dots);

		for(int i=s_pos; i<len; i++)
		{
			cout << add_dot[i];
		}
		cout << endl;
	}
}

