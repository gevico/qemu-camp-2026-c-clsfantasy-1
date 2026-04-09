#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

static int maze[MAX_ROW][MAX_COL] = {
	{0, 1, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 1, 0},
};

static int visited[MAX_ROW][MAX_COL];

static int dfs(int row, int col)
{
	static const int directions[4][2] = {
		{1, 0},
		{-1, 0},
		{0, 1},
		{0, -1},
	};

	if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL) {
		return 0;
	}

	if (maze[row][col] == 1 || visited[row][col]) {
		return 0;
	}

	visited[row][col] = 1;

	if (row == MAX_ROW - 1 && col == MAX_COL - 1) {
		printf("(%d, %d)\n", row, col);
		return 1;
	}

	for (int i = 0; i < 4; i++) {
		if (dfs(row + directions[i][0], col + directions[i][1])) {
			printf("(%d, %d)\n", row, col);
			return 1;
		}
	}

	return 0;
}

int main(void)
{
	if (!dfs(0, 0)) {
		printf("No path!\n");
	}

	return 0;
}