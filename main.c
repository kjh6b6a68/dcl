#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define UNIT_MAX 128
#define OUT_MAX 1024
#define ARR_SIZE(x) (sizeof(x) / sizeof((x)[0]))

enum unit_type {
	TYPE,
	NAME,
	CONST
};

char *valid_type[] = {
	"char",
	"int",
	"float",
	"double"
};

int lastgetc;
int unit_type;
char unit[UNIT_MAX];
char type[UNIT_MAX];
char out[OUT_MAX];

int istype(char *str)
{
	int i = 0;

	while (i < (int)ARR_SIZE(valid_type)) {
		if (strcmp(str, valid_type[i]) == 0)
			break;
		i++;
	}
	return (i != ARR_SIZE(valid_type));
}

void get_unit(void)
{
	char *p;

	while (lastgetc == ' ')
		lastgetc = getc(stdin);
	p = unit;
	if (isalpha(lastgetc)) {
		while (isalnum(lastgetc)) {
			*p++ = (char)lastgetc;
			lastgetc = getc(stdin);
		}
		*p = 0;
		unit_type = istype(unit) ? TYPE : NAME;
	} else if (isdigit(lastgetc)) {	
		while (isdigit(lastgetc)) {
			*p++ = (char)lastgetc;
			lastgetc = getc(stdin);
		}
		*p = 0;
		unit_type = CONST;
	} else {
		*p++ = (char)lastgetc;
		*p = 0;
		if (lastgetc != '\n')
			lastgetc = getc(stdin);
		unit_type =  *--p;
	}
}

int dcl(void)
{
	strcat(out, "pointer to pointer to function returning array of ");
	return (1);
}

int main(void)
{
	char type[UNIT_MAX];

	lastgetc = getc(stdin);
	get_unit();
	if (unit_type != TYPE) {
		printf("invalid type '%s'\n", unit);
		return (0);
	}
	strcpy(type, unit);
	if (!dcl()) return (0);
	strcat(out, type);
	printf("%s\n", out);
	return (0);
}
