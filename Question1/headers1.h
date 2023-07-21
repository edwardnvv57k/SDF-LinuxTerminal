#define _GNU_SOURCE
#define BOLDGRN "\001\033[1;32m\002"
#define BOLDRED "\001\033[1;31m\002"
#define BOLDBLU "\001\033[1;34m\002"
#define BOLDBLK "\001\033[1;30m\002"
#define DEFAULT "\001\033[0m\002"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <dirent.h>

// Question 1 of SDF Assignment 1
// author : Edward Nathan Varghese
// roll no : CS22BTECH11020

int dirExists (char *dname);

