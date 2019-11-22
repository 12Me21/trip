#include <ctype.h>

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
