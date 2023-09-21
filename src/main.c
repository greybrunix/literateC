#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#define NIL (void *) 0

static int cfile(char* file_path);
static void path_to_name(char** file_name, char* file_path);
extern void lexer();
extern int parse(int fd, char* file_name);

static int
main(int argc,
     char**argv)
{
    auto int fd_c, res;
    auto char* file_path, file_name,
    tmpc = "./tmp.c",
    tmpt = "./tmp.tex",
    arg1[] = { tmpc , NIL },
    arg2[] = { tmpt , NIL };
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
        /* if (flag)
        unlink(tmpc);
        unlink(tmpt);
        */
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
    auto int res = 0;
    while (*file_path && *file_path != '.')
        file_path++;
    if (*file_path == '.')
        res = !strcmp(file_path, ".lrc");
    return res;
}

void
path_to_name(char** file_name, char* file_path)
{
    auto int i, dir_nest = 0;
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

