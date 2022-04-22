#include <stdio.h>

#define MAX_DAYS 30
#define VALID_D(d) (1 <= d && d <= 30)
#define VALID_TOTAL_TIME(t) (0 <= t && t <= 240)
#define VALID_DAY_TIME(t) (0 <= t && t <= 8)
	
static struct {
	int max;
	int min;
} days[MAX_DAYS];

int sch[MAX_DAYS];

int main()
{	
	int i, h, d, sum;
	int min, max, tmax, tmin;

	min = max =tmin = tmax = 0;

	scanf("%d %d", &d, &sum);
	if (!VALID_D(d) || !VALID_TOTAL_TIME(sum)) {
		printf("NO\n");
		return (0);
	}

	for (i = 0; i < d; ++i) {
		scanf("%d %d", &min, &max);
		if (!VALID_DAY_TIME(min) || !VALID_DAY_TIME(max)) {
			printf("NO\n");
			return (0);
		}
		days[i].max = max;
		days[i].min = min;
		tmax += max;
		tmin += min;
	}

	if (sum < tmin || tmax < sum) {
		printf("NO\n");
		return (0);
	}

	h = sum;
	printf("YES\n");
	for (i = 0; i < d; ++i) {
		max = h - (tmin - days[i].min);
		tmin -= days[i].min;
		if (max > days[i].max) {
			h -= days[i].max;
			sch[i] = days[i].max;
			printf("%d", days[i].max);
		} else if (h <= 0) {
			printf("%d", h);
		} else {
			h -= max;
			sch[i] = max;
			printf("%d", max);
		}
		if (i != d-1)
			printf(" ");
	}

	printf("\n");
	
	return (0);
}
