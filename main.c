#include "shared.h"
#include "dcl.h"
#include "dcl_utils.h"
#include <stdio.h>

int token_type;
char token[TOKEN_MAX];
char out[OUT_MAX];
int lastgetc;

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
