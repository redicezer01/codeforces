#include <stdio.h>

int main()
{
	int msiz = 5;
	int x, y;
	int found = 0;
	int row, col;	/* row and col where should be 1 */

	row = col = 3;

	for (x = 1; x <= msiz && !found; ++x) {
		for (y = 1; y <= msiz; ++y) {
			if (getchar() == '1') {
				found = 1;
				break;	
			}
			getchar();
		}
	}
	x = (--x>row) ? x-row : row-x;
	y = (y>col) ? y-col : col-y;
	
	printf("%d\n", x+y);
	
	return (0);
}
