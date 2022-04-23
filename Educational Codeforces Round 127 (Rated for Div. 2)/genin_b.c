#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	fp = fopen("test_b2_4K.txt", "w");

	fwrite("1\n", 1, 2, fp);
	fwrite("40000\n", 1, 6, fp);
	int i;
	for (i = 0; i < 40000; ++i) {
		fprintf(fp, "%d ", i);
	}	
	fwrite("\n", 1, 1, fp);

	fclose(fp);	
	return(0);
}
