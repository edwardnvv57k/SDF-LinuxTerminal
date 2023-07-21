#include "headers1.h"

// Question 1 of SDF Assignment 1
// author : Edward Nathan Varghese
// roll no : CS22BTECH11020

int dirExists (char *dname){
    struct stat dirdata;
    stat (dname, &dirdata);
    if (S_ISDIR(dirdata.st_mode)){
        return 1;
    }
    else{
        return 0;
    }
}

int main(void)
{
    while (1){

        char *username = "";
        username = getlogin();
        char hostname[256];
        char* command;
        gethostname(hostname, 253);

        char cwd[PATH_MAX], prompt[256];
            
        memset(prompt, 0, strlen(prompt));
        getcwd(cwd, sizeof(cwd));
        command = readline(strcat(strcat(strcat(prompt, 
        BOLDGRN), strcat(strcat(strcat(username, "@"), 
        strcat(strcat(strcat(hostname, BOLDBLU), ":~"), 
        strcat(cwd, DEFAULT))), "$")), " "));

        memset(cwd, 0, strlen(cwd));
        getcwd(cwd, sizeof(cwd));
        memset(username, 0, strlen(username));
        memset(hostname, 0, strlen(hostname));
        command[strlen(command)] = '\0';


        if(strlen(command) > 0){ 
            add_history(command);
        }

        if (!strcmp(command, "exit")){
            printf ("Exiting...\n");
            break;
        }

        else if (command[0] == 'c' && command[1] == 'd' && command[2] == ' '){
            
            char subc[256];
            memset(subc, '\0', sizeof(subc));
            subc[0] = '/';
            strncpy(subc + 1, command + 3, strlen(command) - 3);

            if (strlen(subc) == 3 && subc[1] == '.' && subc[2] == '.')
                chdir("..");
            else if (strlen(subc) == 2 && subc[1] == '.')
                chdir(".");
            else if (dirExists(subc)){
                chdir(subc);
            }
            else if (dirExists(strcat(cwd, subc))){
                chdir(cwd);
            }
            else{
                printf ("cd: ERROR! Directory does not exist\n");
            }
            continue;
            
        }

        else if (!strcmp(command, "help")){
            printf ("Type \"help command-name\" for more information on a command\n");
        }

        else if (command[0] == 'h' && command[1] == 'e' && command[2] == 'l'
        && command[3] == 'p' && command[4] == ' '){

            command[1] = 'm';
            command[2] = 'a';
            command[3] = 'n';
            command = command + 1;
            system (command);

        }

        else{
            system (command);
        }
    }
    return 0;
}