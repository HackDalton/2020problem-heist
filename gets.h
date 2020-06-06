// Polyfill for gets

#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 255

char *gets(char *str)
{
	if (fgets(str, MAX_BUFFER_SIZE, stdin) != 0)
	{
		str[strcspn(str, "\n")] = '\0';
		return str;
	}
	return 0;
}