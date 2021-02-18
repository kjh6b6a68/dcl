#include "shared.h"
#include "dcl.h"
#include "dcl_utils.h"
#include <stdio.h>
#include <string.h>

int isparam = 0;

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

int dcl(void)
{
	switch (token_type) {
	case '*':
		get_token();
		return (met_aster());
	case '(':
		get_token();
		return (met_paren());
	case IDEN:
		return (met_iden());
	default :
		printf("valid declaration needed instead of '%s'\n", token);
		return (0);
	}
}

int param_dcl(void)
{
	switch (token_type) {
	case '*':
		get_token();
		return (met_aster());
	case '(':
		get_token();
		return (met_paren());
	case IDEN:
		return (met_iden());
	case '[':
		return (arrays());
	case ',':
		return (1);
	case ')':
		return (1);
	default :
		printf("valid declaration needed instead of '%s'\n", token);
		return (0);
	}
}

int met_aster(void)
{
	if (!dcl())
		return (0);
	strcat(out, "pointer to ");
	return (1);
}

int met_paren(void)
{
	if (token_type == ')' || istype(token)) {
		return (met_func_paren());
	} else {
		return (met_just_paren());
	}
}

int met_iden(void)
{
	if (istype(token)) {
		printf("'%s' cannot be used as a name\n", token);
		return (0);
	}
	strcat(out, token);
	strcat(out, " is a ");
	get_token();
	return (check_func_and_arrs());
}

int arrays(void)
{
	while (token_type == '[') {
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
	}
	return (1);
}

int met_func_paren(void)
{
	while (1) {
		if (!type_dcl())
			return (0);
		if (token_type != ',')
			break ;
		get_token();
	}
	if (token_type != ')') {
		printf("')' needed instead of '%s'\n", token);
		return (0);
	}
	strcat(out, "function returning ");
	get_token();
	return (1);
}

int met_just_paren(void)
{
	if (!dcl())
		return (0);
	if (token_type != ')') {
		printf("')' needed instead of '%s'\n", token);
		return (0);
	}
	get_token();
	return (check_func_and_arrs());
}

int check_func_and_arrs(void)
{
	if (token_type == '(') {
		get_token();
		return (met_func_paren());
	}
	if (token_type == '[')
		return (arrays());
	return (1);
}
