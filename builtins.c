//
// Created by ioan on 05.04.2022.
//

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "builtins.h"

#define HELP "I will not help you"

void help()
{
    printf("%s", HELP);
}

void cd(char *dir, const char *newDir)
{
    if (!newDir)
    {
        printf("Where's the newDir???\n");
        return;
    }


    struct stat* stat1;

    if (!strcmp(newDir,".."))
    {
        if (strrchr(dir,'/') != strchr(dir,'/'))
            dir[strrchr(dir,'/')-dir] = '\0';
        else printf("Cannot ..\n");

        return;
    }

    // try to find it locally
    DIR* _dir = opendir(dir);



    if (_dir != NULL)
    {
        struct dirent* dirent = readdir(_dir);
        while (dirent != NULL)
        {
            if (!strcmp(dirent->d_name,newDir))
            {
                if (dirent->d_type == DT_DIR)
                {
                    strcat(dir,"/");
                    strcat(dir,newDir);
                    closedir(_dir);
                    return;
                }
                else
                {
                    printf("%s is not a dir\n",newDir);
                    closedir(_dir);
                    return;
                }
            }
            dirent = readdir(_dir);
        }

        closedir(_dir);
    }


    // try to find it globally
    _dir = opendir(newDir);

    if (_dir != NULL)
    {
        strcpy(dir,newDir);
        closedir(_dir);
        return;
    }


    printf("%s not found\n",newDir);


}

void exitSh(int code)
{
    exit(code);
}

void pwd(const char *cd)
{
    DIR* _dir = opendir(cd);

    const static char* types[] = {"File","Directory","Link","Unknown"};

    if (_dir == NULL)
    {
        printf("Permission denied\n");
        return;
    }

    printf("---%s---\n",cd);
    struct dirent* dirent = readdir(_dir);
    while (dirent != NULL)
    {
        int direntType = 4;

        switch (dirent->d_type)
        {
            case DT_DIR:
                direntType = 1;
                break;
            case DT_REG:
                direntType = 0;
                break;
            case DT_LNK:
                direntType = 2;
                break;
            default:
                direntType = 3;
                break;
        }
        
        
        printf("%-40s\t%-20s\n",dirent->d_name,types[direntType]);
        dirent = readdir(_dir);
    }

    closedir(_dir);
}

void type(const char *cd, const char *file)
{
    if (file == NULL)
    {
        printf("File ??\n");
        return;
    }

    struct stat buf;


    int a= lstat(file,&buf);

    if (a== -1)
    {
        printf("File??\n");
        return;
    }

    if (S_ISLNK(buf.st_mode))
    {
        printf("link\n");
    }
    else if (S_ISREG(buf.st_mode))
    {
        printf("file \n");
    }
    else if (S_ISDIR(buf.st_mode))
    {
        printf("dir\n");
    }
    else printf("??\n");
}

void create(const char *cd,const char* type,char *name, char *third, char *fourth)
{
    if (!type || ! name)
    {
        printf("Wrong arguments\n");
        return;
    }


    switch (type[1])
    {
        case 'f':
            // if dir
            if (third)
            {
                strcat(third,"/");
                strcat(third,name);
                strcpy(name,third);
            }

            int fd = open(name,O_WRONLY | O_CREAT | O_TRUNC,S_IRUSR|S_IWUSR|S_IXUSR);
            if (fd == -1)
            {
                printf("Error creating %s\n",name);
                return;
            }
            close(fd);

            break;
        case 'd':
            if (third)
            {
                strcat(third,"/");
                strcat(third,name);
                strcpy(name,third);
            }

            mkdir(name,S_IRUSR|S_IWUSR|S_IXUSR);

            break;
        case 'l':
            if (!third)
            {
                printf("No file to create link to\n");
                return;
            }
            if (fourth)
            {
                strcat(fourth,"/");
                strcat(fourth,name);
                strcpy(name,fourth);
            }
            
            symlink(third,name);
            break;
        default:
            printf("Invalid options");
            return;
            break;
    }


}


