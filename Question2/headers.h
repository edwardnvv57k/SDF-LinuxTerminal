#define _GNU_SOURCE
#define BOLDGRN "\001\033[1;32m\002"
#define BOLDRED "\001\033[1;31m\002"
#define BOLDBLU "\001\033[1;34m\002"
#define BOLDBLK "\001\033[1;30m\002"
#define DEFAULT "\001\033[0m\002"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <netdb.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <ctype.h>

// Question 2 of SDF Assignment 1
// author : Edward Nathan Varghese
// roll no : CS22BTECH11020

bool fileExists (char *fname);


// mycp command
void mycp(char* ad1, char* ad2, int operation, int opt_v, 
          int opt_f, int opt_i, int opt_n);

// mymv command
void mymv(char* ad1, char* ad2, int opt_v, int opt_f, 
          int opt_i, int opt_n);

// mygrep command
void mygrep (char *pattern, char *filename, int opt_i, 
             int opt_n, int opt_c, int opt_l);

// myls command
void myls(int opt_a, int opt_l, int opt_t, int opt_r);

// myls functions

char* getUsername(uid_t user_id);

char* getGroupname(gid_t group_id);

int compare_function(const void *x, const void *y);

int time_compare_function(const void *x, const void *y);

// myps command
void myps(int opt_a, int opt_d, int opt_e, int opt_j);