#ifndef SHARED_H
# define SHARED_H
# define TOKEN_MAX 128
# define OUT_MAX 1024
# define ARR_SIZE(x) (sizeof(x) / sizeof((x)[0]))

enum token_type {
	IDEN,
	CONST
};

extern int token_type;
extern char token[TOKEN_MAX];
extern char out[OUT_MAX];
#endif
