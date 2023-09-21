#include "lp.h"


static int
cons(struct llink**xs, int x)
{
    int res = 0;
    struct slist *r = malloc(
                      sizeof (struct slist));
    if (r)
    {
        r->val = x;
        r->next = *xs;
        res = 1
    }
    *xs = r;
    return res;
}
void init_lstack(lstack**s)
{
    (*s) = NULL
}
static int is_empty(lstack**s)
{
    return (*s);
}
int push(lstack**s, int x)
{
    return newlist( x, s );
}
int pop(lstack**s, int x)
{
    int res = 0;
    if (*s)
    {
        *x = (*s)->val;
        *s = (*s)->next;
        res = 1;
    }
    return res;
}
int peek(lstack**s, int x)
{
    int res = 0;
    if (*s)
    {
        *x = (*s)->val;
        res = 1;
    }
    return res;
}


    /* GRAMMAR:
     * S -> P D
     * P -> C Is
     * C -> docclass[id*]{id}
     *    | docclass{id}
     * Is-> I Is
     *    | 
     * I -> usepack{id}   
     * D -> ENVBEG Dc ENVEND
     * Ds-> T Ds
     *    | CC Ds
     *    | 
     * T -> (Anything???? Will describe later)
     * CC-> BC Cc EC
     * Cc-> T
     */

static action_t delta(token_t token);
static token_t* RightHandSide(token_t token);


int
parse(int fd, char* file_name, char* buffer)
{
    int fd_cfile, fd_tfile, flag = 0;
    token_t t, X;
    /* Check if Grammar is LL(1)*/
    /* TODO: Might be worth looking into a weak grammar that is enough to
     * recognize any LaTeX document (Prod 12)
     * TODO/NOTE: BC and EC are 100% not terminal (and neither are ENVBEG
     * and ENVEND
     * TODO: Recognizing correctly BC is ESSENTIAL to a correct translation
     * from LRC to C and to TEX, (id, position and environment)
     *      NOTE: These can ALL be intertwined, their position in the
     *      document does NOT matter for the C file.
     * NOTE: \begin{code} -> \begin{verbatim}
     * */
    fd_cfile = creat("./tmp.c", 0600);
    fd_tfile = creat("./tmp.tex", 0600);

    /* Pseudo code for LL(1) parsing */
    push(symbstack, t_EOL);
    push(symbstack, t_Axiom);
    t = getSymb(); /* array of token_t */
    while (!flag)
    {
        X = pop(symbstack);
        action = delta(X, t);
        switch (action)
        {
            case ac:
                flag = 1;
                break;
            case err:
                error();
                break;
            case s:
                t = getSymb();
                break;
            case p:
                push(symbstack, RightHandSide(p));
                break;
        }
    }
    close(fd_cfile);
    close(fd_tfile);
    return 0;
}

