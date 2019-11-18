#include <ctype.h>

char search(char *string, char *pattern) {
	char *pat = pattern;
	char *str = string;
	do {
	start:
		if (*pat != tolower(*str)) {
			if (!*str)
				return 0;
			str = ++string;
			pat = pattern;
			goto start;
		}
		str++;
		pat++;
	} while (*pat);
  return 1;
}

int countcs(char *string, char *find){
	int count = 0;
	char *c;
	
	while (*string) {
		c = find;
		while (*c) {
			if (*c==*string) {
				count++;
				break;
			}
			c++;
		}
		string++;
	}
	//if (*string++ == c)
		//		count++;
	return count;
}

int countc(char *string, char c){
	int count = 0;
	while (*string)
		if (*string++ == c)
			count++;
	return count;
}
