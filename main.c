#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TOKEN_MAX 128
#define OUT_MAX 1024
#define ARR_SIZE(x) (sizeof(x) / sizeof((x)[0]))

enum token_type {
	IDEN,
	CONST
};

int lastgetc;
int token_type;
char token[TOKEN_MAX];
char out[OUT_MAX];
int isparam = 0;

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

int met_aster(void)
{
	int dcl(void);

	get_token();
	if (!dcl())
		return (0);
	strcat(out, "pointer to ");
	return (1);
}

int  met_paren(void)
{
	int dcl(void);

	get_token();
	if (!dcl())
		return (0);
	if (token_type != ')') {
		printf("')' needed instead of '%s'\n", token);
		return (0);
	}
	get_token();
	return (1);
}

int met_iden(void)
{
	int dcl(void);

	if (istype(token)) {
		printf("'%s' cannot be used as a name\n", token);
		return (0);
	}
	strcat(out, token);
	strcat(out, " is a ");
	get_token();
	return (1);
}

int function_params(void)
{
	get_token();
	if (token_type != ')') {
		printf("')' needed instead of '%s'\n", token);
		return (0);
	}
	strcat(out, "function returning ");
	get_token();
	return (1);
}

int met_bracket(void)
{
	get_token();
	if (token_type != CONST) {
		printf("constant needed instead of '%s'\n", token);
		return (0);
	}
	get_token();
	if (token_type != ']') {
		printf("']' needed instead of '%s'\n", token);
		return (0);
	}
	strcat(out, "array of ");
	get_token();
	return (1);
}

int dcl(void)
{
	if (token_type == '*')
		return (met_aster());
	if (token_type == '(') {
		if (!met_paren())
			return (0);
	} else if (token_type == IDEN) {
		if (!met_iden())
			return (0);
	} else if (isparam && (token_type == ',' || token_type == ')')) {
		return (1);
	} else {
		printf("'*' or '(' or name needed instead of '%s'\n", token);
		return (0);
	}
	if (token_type == '(')
		return (function_params());
	while (token_type == '[') {
		if (!met_bracket())
			return (0);
	}
	return (1);
}

int type_dcl(void)
{
	char type[TOKEN_MAX];

	if (!istype(token)) {
		printf("invalid type '%s'\n", token);
		return (0);
	}
	strcpy(type, token);
	get_token();
	if (!dcl())
		return (0);
	strcat(out, type);
	return (1);
}

int main(void)
{
	lastgetc = getc(stdin);
	get_token();
	if (!type_dcl())
		return (0);
	if (token_type != '\n') {
		printf("'newline' character needed instead of '%s'\n", token);
		return (0);
	}
	printf("%s\n", out);
	return (0);
}
