#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char *trip(char *, size_t);
char *trip_lower(char *, size_t);
int countc(char *string, char c);
int countcs(char *string, char *c);

#define CODE_LEN 16

const char charset[] = "1234567890-=abcdefghijklmnopqrstuvwxyz;',./"; //lower
//const char charset[] = "!@#$%&*()_+ABCDEFGHIJKLMNOPQRSTUVWXYZ:\",.?"; //upper

#define rand_char(r) (charset[(r) % (sizeof(charset)-1)])

void corrupt(char *str, size_t len){
	unsigned int r = rand();
	str[r % len] = rand_char(r / len);
}

void print_trip(char *key, char *trip) {
	printf("%s %s\n", key, trip);
}

int main(int argc, char **argv){
	if (argc == 2) {
		puts(trip(argv[1], strlen(argv[1])));
	} else if (argc >= 3) {
		srand(time(0));
		char tripcode[CODE_LEN+1];
		int i;
		for(i=0;i<CODE_LEN;i++)
			tripcode[i] = rand_char(rand());
		tripcode[i]=0;
		if (argv[1][1] == 'i') {
			// case insensitive, multiple words (&)
			if (argc > 3) {
				printf("i searchs:");
				char **av = argv+2;
				while (*av)
					printf(" %s", *av++);
				printf("\n");
				while (1) {
					char *t = trip_lower(tripcode, CODE_LEN);
					av = argv+2;
					while (*av) {
						if (!strstr(t, *av))
							goto fail;
						av++;
					}
					print_trip(tripcode, trip(tripcode, CODE_LEN));
				fail:
					corrupt(tripcode, CODE_LEN);
				}
			// case insensitive, 1 word
			} else {
				printf("i search: %s\n", argv[2]);
				while (1) {
					char *t = trip_lower(tripcode, CODE_LEN);
					if (strstr(t, argv[2]))
						print_trip(tripcode, trip(tripcode, CODE_LEN));
					corrupt(tripcode, CODE_LEN);
				}
			}
			// chars
		} else if (argv[1][1] == 'c') {
			printf("c Search: %s\n", argv[2]);
			//printf("%d\n", countc("test",'t'));
			//return 0;
			//char c = argv[2][0];
			int max = 1;
			if (argc == 4)
				max = atoi(argv[3]);
			char c = argv[2][0];
			//multiple chars counts
			if (c && argv[2][1] == '\0') {
				while (1) {
					char *t = trip(tripcode, CODE_LEN);
					int count = countc(t, c);
					if (count >= max) {
						print_trip(tripcode, t);
						//printf("%s : %s | %d\n", tripcode, t, count);
						max = count;
					}
					corrupt(tripcode, CODE_LEN);
				}
			}
			// single char count
			while (1) {
				char *t = trip(tripcode, CODE_LEN);
				int count = countcs(t, argv[2]);
				if (count >= max) {
					print_trip(tripcode, t);
					//printf("%s : %s | %d\n", tripcode, t, count);
					max = count;
				}
				corrupt(tripcode, CODE_LEN);
			}
			//case sensitive search (1 word)
		} else {
			printf("Search: %s\n", argv[2]);
			while (1) {
				char *t = trip(tripcode, CODE_LEN);
				if (strstr(t, argv[2]))
					print_trip(tripcode, t);
				//printf("%s : %s\n", tripcode, t);
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
