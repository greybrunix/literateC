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
void parse(int fd, char* file_name);


int
main(int argc,
     char**argv)
{
    int fd_c;
    char* file_path;
    char* file_name;
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
        execv();
        execv();
     */
        ;
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
            write(2, "Not a .ltc file\n", 17);
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
        res = !strcmp(file_path, ".ltc");
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
    return 0;
}

