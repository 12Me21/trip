#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char *trip(char *, size_t);
char search(char *, char *);
int countc(char *string, char c);
int countcs(char *string, char *c);

#define CODE_LEN 8

#define rand_char() ('"'+rand()%93)

void corrupt(char *str, size_t len){
	str[rand()%len] = rand_char();
}

int main(int argc, char **argv){
	if (argc == 2) {
		puts(trip(argv[1], strlen(argv[1])));
	} else if (argc >= 3) {
		srand(time(0));
		char tripcode[CODE_LEN+1];
		int i;
		for(i=0;i<CODE_LEN;i++)
			tripcode[i] = rand_char();
		tripcode[i]=0;
		if (argv[1][1] == 'i') {
			
			if (argc > 3) {
				printf("i searchs:");
				char **av = argv+2;
				while (*av)
					printf(" %s", *av++);
				printf("\n");
				while (1) {
					char *t = trip(tripcode, CODE_LEN);
					av = argv+2;
					while (*av) {
						if (!search(t, *av))
							goto fail;
						av++;
					}
					printf("%s : %s\n", tripcode, t);
				fail:
					corrupt(tripcode, CODE_LEN);
				}
			} else {
				printf("i search: %s\n", argv[2]);
				while (1) {
					char *t = trip(tripcode, CODE_LEN);
					if (search(t, argv[2]))
						printf("%s : %s\n", tripcode, t);
					corrupt(tripcode, CODE_LEN);
				}
			}
		} else if (argv[1][1] == 'c') {
			printf("c Search: %s\n", argv[2]);
			//printf("%d\n", countc("test",'t'));
			//return 0;
			//char c = argv[2][0];
			int max = 1;
			if (argc == 4)
				max = atoi(argv[3]);
			char c = argv[2][0];
			if (c && argv[2][1] == '\0') {
				while (1) {
					char *t = trip(tripcode, CODE_LEN);
					int count = countc(t, c);
					if (count >= max) {
						printf("%s : %s | %d\n", tripcode, t, count);
						max = count;
					}
					corrupt(tripcode, CODE_LEN);
				}
			}
			while (1) {
				char *t = trip(tripcode, CODE_LEN);
				int count = countcs(t, argv[2]);
				if (count >= max) {
					printf("%s : %s | %d\n", tripcode, t, count);
					max = count;
				}
				corrupt(tripcode, CODE_LEN);
			}
		} else {
			printf("Search: %s\n", argv[2]);
			while (1) {
				char *t = trip(tripcode, CODE_LEN);
				if (strstr(t, argv[2]))
					printf("%s : %s\n", tripcode, t);
				corrupt(tripcode, CODE_LEN);
			}
		}
	} else {
		fprintf(stderr, "%s <trip>\n", argv[0]);
		fprintf(stderr, "%s - <search> (case sensitive)\n", argv[0]);
		fprintf(stderr, "%s -i <search>\n", argv[0]);
		fprintf(stderr, "%s -c <chars>\n", argv[0]);
		return 1;
	}
	return 0;
}
