#ifndef LP_H

#define NIL (void *) 0
typedef unsigned int action_t
typedef unsigned int token_t

struct llink {
    token_t val;
    struct llink* next;
};
typedef struct llink lstack;

void init_lstack(lstack**s);
int push(lstack**s, int x);
int pop(lstack**s, int*x);
int peek(lstack**s, int*x);
int parse(int fd, char* file_name, char*buffer);
int lexer(int fd, char* file_name, token_t* tokens);

#endif
