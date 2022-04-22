#include <stdio.h>
#include <stdlib.h>


#define MAX 100000
#define RAND_L (rand() % 33)
#define RAND_C (rand() % 26 + 'a')

char word[32];

int main()
{
	int i, j, len;
	FILE *fp;

	fp = fopen("large_in.txt", "w");
	fprintf(fp, "%d\n", MAX);

	for (i = 0; i < MAX; ++i) {
		len = RAND_L;
		for (j = 0; j < len; ++j)
			word[j] = RAND_C;
		word[j] = '\0';
			
		fprintf(fp, "%s\n", word);
	}

	fclose(fp);

	return (0);
}
