/*
dp[i][j] = dp[i-1][j-1] + s1[i]~s2[j]
dp[i][j] = dp[i-1][j] + s1[i]~'-'
dp[i][j] = dp[i][j-1] + '-'~s2[j]
*/

#include <iostream>

using namespace std;

#define MAXN 101

int matches[5][5] = 
{
	{5, -1, -2, -1, -3},
	{-1, 5, -3, -2, -4},
	{-2, -3, 5, -2, -2},
	{-1, -2, -2, 5, -1},
	{-3, -4, -2, -1, 0}
};

int tr(char ch)
{
	if(ch == 'A') return 0;
	else if(ch == 'C') return 1;
	else if(ch == 'G') return 2;
	else if(ch == 'T') return 3;
	else return 4;
}

int score(int len1, int len2, char *s1, char *s2)
{
	int dp[MAXN][MAXN];

	dp[0][0] = 0;
	for(int i=1; i<=len1; i++)
		dp[i][0] = dp[i-1][0] + matches[tr(s1[i])][tr('-')];
	for(int j=1; j<=len2; j++)
		dp[0][j] = dp[0][j-1] + matches[tr('-')][tr(s2[j])];

	for(int i=1; i<=len1; i++)
	{
		for(int j=1; j<=len2; j++)
		{
			dp[i][j] = dp[i-1][j-1] + matches[tr(s1[i])][tr(s2[j])];
			dp[i][j] = max(dp[i][j], dp[i-1][j]+matches[tr(s1[i])][tr('-')]);
			dp[i][j] = max(dp[i][j], dp[i][j-1]+matches[tr('-')][tr(s2[j])]);
		}
	}

	return dp[len1][len2];
}

int main(void)
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		int len1, len2;
		char str1[MAXN], str2[MAXN];

		scanf("%d %s", &len1, str1+1);
		scanf("%d %s", &len2, str2+1);

		printf("%d\n", score(len1,len2,str1,str2));
	}

	system("PAUSE");
	return 0;
}
