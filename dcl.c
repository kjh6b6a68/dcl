#include "shared.h"
#include "dcl.h"
#include "dcl_utils.h"
#include <stdio.h>
#include <string.h>

int param_depth = 0;

int type_dcl(void)
{
	char type[TOKEN_MAX];

	if (!istype(token)) {
		printf("valid type needed instead of '%s'\n", token);
		return (0);
	}
	strcpy(type, token);
	get_token();
	if (!dcl())
		return (0);
	strcat(out, param_depth ? "" : type);
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
	default:
		if (param_depth)
			return (check_funcs_and_arrs());
		else {
			printf("valid declaration needed instead of '%s'\n", token);
			return (0);
		}
	}
}

int met_aster(void)
{
	if (!dcl())
		return (0);
	strcat(out, param_depth ? "" : "pointer to ");
	return (1);
}

int met_paren(void)
{
	if (param_depth == 0
		|| token_type =='*'
		|| token_type == '('
		|| (token_type == IDEN && !istype(token))) {
		if (!just_paren())
			return (0);
	} else {
		if (!func_paren())
			return (0);
	}
	return (check_funcs_and_arrs());
}

int met_iden(void)
{
	if (param_depth == 0 && istype(token)) {
		printf("valid declaration needed instead of '%s'\n", token);
		return (0);
	} else if (istype(token))
		return (1);
	param_depth ? 0 : (strcat(out, token), strcat(out, " is "));
	get_token();
	return (check_funcs_and_arrs());
}

int func_paren(void)
{
	param_depth++;
	if (!istype(token))
		goto after_valid_params;
	while (1) {
		if (!type_dcl())
			return (0);
		if (token_type != ',')
			goto after_valid_params;
		get_token();
	}
after_valid_params:
	if (token_type != ')') {
		printf("')' needed instead of '%s'\n", token);
		return (0);
	}
	param_depth--;
	strcat(out, param_depth ? "" : "function returning ");
	get_token();
	return (1);
}

int just_paren(void)
{
	if (!dcl())
		return (0);
	if (token_type != ')') {
		printf("')' needed instead of '%s'\n", token);
		return (0);
	}
	get_token();
	return (1);
}

int check_funcs_and_arrs(void)
{
	while (1) {
		if (token_type == '(') {
			get_token();
			if (!func_paren())
				return (0);
		} else if (token_type == '[') {
			get_token();
			if (!bracket())
				return (0);
		} else
			return (1);
	}
}

int bracket(void)
{
	if (token_type != CONST) {
		printf("constant needed instead of '%s'\n", token);
		return (0);
	}
	get_token();
	if (token_type != ']') {
		printf("']' needed instead of '%s'\n", token);
		return (0);
	}
	strcat(out, param_depth ? "" : "array of ");
	get_token();
	return (1);
}
