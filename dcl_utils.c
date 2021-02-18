#include "shared.h"
#include "dcl_utils.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

extern int lastgetc;

void get_token(void)
{
	while (lastgetc == ' ')
		lastgetc = getc(stdin);
	if (isalpha(lastgetc)) {
		get_iden();
		token_type = IDEN;
	} else if (isdigit(lastgetc)) {
		get_const();
		token_type = CONST;
	} else {
		token[0] = (char)lastgetc;
		token[1] = 0;
		if (lastgetc != '\n')
			lastgetc = getc(stdin);
		token_type =  token[0];
	}
}

int istype(char *str)
{
	char *valid_type[] = {
		"char",
		"int",
		"float",
		"double"
	};
	int i = 0;

	while (i < (int)ARR_SIZE(valid_type)) {
		if (strcmp(str, valid_type[i]) == 0)
			break;
		i++;
	}
	return (i != ARR_SIZE(valid_type));
}

void get_iden(void)
{
	char *p;

	p = token;
	while (isalnum(lastgetc)) {
		*p++ = (char)lastgetc;
		lastgetc = getc(stdin);
	}
	*p = 0;
}

void get_const(void)
{
	char *p;

	p = token;
	while (isdigit(lastgetc)) {
		*p++ = (char)lastgetc;
		lastgetc = getc(stdin);
	}
	*p = 0;
}
