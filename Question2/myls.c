#include "headers.h"

struct lsdata{
    char fmode[100];
    int links;
    char owner[256];
    char group[256];
    long long int size;
    time_t time;
    char timechar[256];
    char name[256];
};

char* getUsername(uid_t user_id){
    struct passwd *pws;
    pws = getpwuid(user_id);
    return pws->pw_name;
}

char* getGroupname(gid_t group_id){
    struct group *gr;
    gr = getgrgid(group_id);
    return gr->gr_name;
}

int compare_function(const void *x, const void *y)
{
    const struct lsdata *l1 = x;
    const struct lsdata *l2 = y;
    return strcmp(l1->name, l2->name);
}

int time_compare_function(const void *x, const void *y)
{
    const struct lsdata *l1 = x;
    const struct lsdata *l2 = y;
    return -1 * (l1->time - l2->time);
}


void myls(int opt_a, int opt_l, int opt_t, int opt_r)
{
    struct dirent *dstruct;
    struct lsdata details[1024];
    DIR *directory = opendir(".");
    if (directory == NULL){
        printf ("Directory couldn't be opened. Aborting...\n");
        return;
        //exit(EXIT_FAILURE);
    }
    else{
    int count = 0;
    while ((dstruct = readdir(directory)) != NULL){
        if (opt_a == 0 && dstruct->d_name[0] == '.')
            continue;
        struct stat metadata;
        if (stat(dstruct->d_name, &metadata) < 0){
            printf ("Metadata retrieval failed. Aborting...\n");
            return;
            //exit(EXIT_FAILURE);
        }
        uid_t user_id = metadata.st_uid;
        gid_t group_id = metadata.st_gid;
        mode_t fmode = metadata.st_mode;
        
        char m[11] = "----------";
        if (S_ISREG(fmode)){
            m[0] = '-';
        }
        else if (S_ISREG(fmode)){
            m[0] = 'd';
        }
        if(fmode & S_IRUSR )
            m[1] = 'r';
        if(fmode & S_IWUSR )
            m[2] = 'w';
        if(fmode & S_IXUSR )
            m[3] = 'x';
        if(fmode & S_IRGRP )
            m[4] = 'r';
        if(fmode & S_IWGRP )
            m[5] = 'w';
        if(fmode & S_IXGRP )
            m[6] = 'x';
        if(fmode & S_IROTH )
            m[7] = 'r';
        if(fmode & S_IWOTH )
            m[8] = 'w';
        if(fmode & S_IXOTH )
            m[9] = 'x';
        m[10] = '\0';

        strcpy(details[count].fmode, m);
        //strcpy(details[count].fmode, getFmode(metadata.st_mode));
        details[count].links = metadata.st_nlink;
        details[count].size = metadata.st_size;
        strcpy(details[count].owner, getUsername(user_id));
        strcpy(details[count].group, getGroupname(group_id));
        details[count].time = metadata.st_mtime;
        strcpy(details[count].name, dstruct->d_name);

        struct tm ts;
        ts = *localtime(&details[count].time);
        strftime(details[count].timechar, sizeof(details[count].timechar),\
        "%b %d %H:%M", &ts);

        count++;
    }

    qsort(details, count, sizeof(*details), compare_function);

    if (opt_t == 1){
        qsort(details, count, sizeof(*details), time_compare_function);
    }

    if (opt_r == 1){
        for (int i = 0; i < count/2; i++){
            struct lsdata temp = details[i];
            details[i] = details[count - 1 - i];
            details[count - 1 - i] = temp;
        }
        
    }

    if (opt_l == 0){
        for (int i = 0; i < count; i++){
            printf ("%s\n", details[i].name);
        }
    }
    else{
        for (int i = 0; i < count; i++){
            printf ("%s %d %s %s %-7lld %s %s\n", details[i].fmode, details[i].links, \
            details[i].owner, details[i].group, details[i].size, \
            details[i].timechar, details[i].name);
        }
    }
    }
    closedir (directory);
}


// -a 	list all files including hidden file starting with '.'.
// -l   list with long format - show permissions.
// -t    sort by time & date.
// -r    list in reverse order.
// -d    list directories - with ' */'.

/*
If the -l option is given, the following information is displayed for each file: file mode,
     number of links, owner name, group name, number of bytes in the file, abbreviated month, day-of-
     month file was last modified, hour file last modified, minute file last modified, and the
     pathname.  If the file or directory has extended attributes, the permissions field printed by the
     -l option is followed by a '@' character.  Otherwise, if the file or directory has extended
     security information (such as an access control list), the permissions field printed by the -l
     option is followed by a '+' character.  If the -% option is given, a '%' character follows the
     permissions field for dataless files and directories, possibly replacing the '@' or '+'
     character.
*/