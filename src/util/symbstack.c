#define NIL (void *) 0
struct llink {
unsigned int val;
struct llink* next;
};
typedef struct llink lstack;


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
extern void init_lstack(lstack**s)
{
(*s) = NULL
}
static int is_empty(lstack**s)
{
return (*s);
}
extern int push(lstack**s, int x)
{
return newlist( x, s );
}
extern int pop(lstack**s, int x)
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
extern int peek(lstack**s, int x)
{
int res = 0;
if (*s)
{
*x = (*s)->val;
res = 1;
}
return res;
}


