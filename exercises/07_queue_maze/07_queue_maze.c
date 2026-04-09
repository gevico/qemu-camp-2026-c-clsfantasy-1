#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

typedef struct {
	int row;
	int col;
} Point;

static int maze[MAX_ROW][MAX_COL] = {
	{0, 1, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 1, 0},
};

static int visited[MAX_ROW][MAX_COL];
static Point parent[MAX_ROW][MAX_COL];

static int bfs(Point start, Point end)
{
	Point queue[MAX_ROW * MAX_COL];
	int front = 0;
	int rear = 0;
	static const int directions[4][2] = {
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0},
	};

	queue[rear++] = start;
	visited[start.row][start.col] = 1;
	parent[start.row][start.col].row = -1;
	parent[start.row][start.col].col = -1;

	while (front < rear) {
		Point current = queue[front++];

		if (current.row == end.row && current.col == end.col) {
			return 1;
		}

		for (int i = 0; i < 4; i++) {
			int next_row = current.row + directions[i][0];
			int next_col = current.col + directions[i][1];

			if (next_row < 0 || next_row >= MAX_ROW || next_col < 0 || next_col >= MAX_COL) {
				continue;
			}

			if (maze[next_row][next_col] == 1 || visited[next_row][next_col]) {
				continue;
			}

			visited[next_row][next_col] = 1;
			parent[next_row][next_col] = current;
			queue[rear++] = (Point){next_row, next_col};
		}
	}

	return 0;
}

static void print_path(Point end)
{
	Point current = end;

	while (current.row != -1 && current.col != -1) {
		printf("(%d, %d)\n", current.row, current.col);
		current = parent[current.row][current.col];
	}
}

int main(void)
{
	Point start = {0, 0};
	Point end = {MAX_ROW - 1, MAX_COL - 1};

	if (maze[start.row][start.col] == 1 || maze[end.row][end.col] == 1) {
		printf("No path!\n");
		return 0;
	}

	if (bfs(start, end)) {
		print_path(end);
	} else {
		printf("No path!\n");
	}

	return 0;
}