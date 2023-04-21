#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#define NIL (void *) 0

int cfile(char* file_path);
void path_to_name(char** file_name, char* file_path);
void lexer();
int parse(int fd, char* file_name);


int
main(int argc,
     char**argv)
{
    int fd_c;
    char* file_path;
    char* file_name;
    char* tmpc = "./tmp.c";
    char* tmpt = "./tmp.tex";
    char* arg1[] = { tmpc , NIL };
    char* arg2[] = { tmpt , NIL };
    int res;
    /* 0 -> success
       argument error:
        1 -> Number of Args
        2 -> not a ltc file
        3 -> File doesn't exist
       255 -> unknown
    */
    res = 0;
    if (argc != 2)
        res = 1;
    else if (argc == 2)
    {
        file_path = argv[1];
        if (!cfile(argv[1]))
            res = 2;
        else if ((fd_c = open(argv[1],
                              O_RDONLY)) == -1)
            res = 3;
    }
    if (!res)
    {
        path_to_name(&file_name, file_path);
        res = parse(fd_c, file_name);
        close(fd_c);
    }

    if (!res)
    {/* Compile C code and Typeset Document
        execv("gcc", {"./tmp.c", 0});
        execv("latex", {"./tmp.tex", 0});
     */
        /*execv("gcc", arg1);
        execv("latex", arg2);
        */
        unlink(tmpc);
        unlink(tmpt);
    }



    switch (res)
    {
        case 1:
        { 
            write(2, "Not enough arguments\n", 22);
            break;
        }
        case 2:
        {
            write(2, "Not a .lrc file\n", 17);
            break;
        }
        case 3:
        {
            write(2, "Invalid Path\n", 14);
            break;
        }
        case 255:
        {
            write(2, "Undefined\n", 11);
            break;
        }
        ;
    }
    return res;
}


int
cfile(char* file_path)
{
    int res = 0;
    while (*file_path && *file_path != '.')
        file_path++;
    if (*file_path == '.')
        res = !strcmp(file_path, ".lrc");
    return res;
}

void
path_to_name(char** file_name, char* file_path)
{
    int i, dir_nest = 0;
    for (i=0; file_path[i]; i++)
        if (file_path[i] == '/')
            dir_nest++;
    while (dir_nest)
    {
        if (*file_path == '/')
            dir_nest--;
        file_path++;
    }
    *file_name = file_path;
}

int
parse(int fd, char* file_name)
{
    int fd_cfile;
    int fd_tfile;
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
    /* Check if Grammar is LR(1)*/
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
    fd_cfile = creat("./tmp.c", 0600); /* tmp file will be deleted shortly */
    fd_tfile = creat("./tmp.tex", 0600);



    close(fd_cfile);
    close(fd_tfile);
    return 0;
}

