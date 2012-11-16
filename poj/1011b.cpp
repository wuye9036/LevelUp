#include <stdio.h>

#include <string.h>

#include <stdlib.h>

int n, sum, len, number;

int sticks[65];

bool visit[65], flag;

int cmp(const void *a, const void *b)

{

	return *(int*)b - *(int*)a;

}

//length为当前木棍组合的长度,num为当前组合木棍的数量

void dfs(int p, int length, int num)

{

	int i, pre;

	if (num == number)   //符合要求

	{

		flag = true;

	}

	else if (length == len) //其中一条组合已经符合要求

	{

		dfs(0, 0, num + 1); //标记当前组合木棍数量+1,再来一次搜索组合

	}

	else

	{

		for (i = p, pre = -1; i < n; i++)

		{

			if (!visit[i] && sticks[i] != pre && sticks[i] + length <= len)

			{

				pre = sticks[i];   //剪枝1

				visit[i] = true;

				dfs(i + 1, length + sticks[i], num);

				visit[i] = false;

				if (flag || p == 0) //剪枝2

				{

					return;

				}

			}

		}

	}

}

int main()

{

	int i;

	while (scanf("%d", &n) && n)

	{

		sum = 0;

		flag = false;

		for (i = 0; i < n; i++)

		{

			scanf("%d", &sticks[i]);

			sum += sticks[i];

		}

		qsort(sticks, n, sizeof(sticks[0]), cmp); //从大到小排列,调整搜索的顺序,搜索范围减少

		for (len = sticks[0]; len < sum; len++)

		{

			if (sum % len == 0)

			{

				number = sum / len;

				memset(visit, false, sizeof(visit));

				dfs(0, 0, 0);

				if (flag)

				{

					break;

				}

			}

		}

		printf("%d\n", flag ? len : sum);

	}

	return 0;

}