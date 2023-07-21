#include "headers.h"

// Question 2 of SDF Assignment 1
// author : Edward Nathan Varghese
// roll no : CS22BTECH11020

bool fileExists (char *fname){
    FILE *fp = fopen (fname, "r");
    if (fp != NULL){
        return true;
    }
    else{
        return false;
    }
}

bool dirExists (char *dname){
    struct stat dirdata;
    stat (dname, &dirdata);
    if (S_ISDIR(dirdata.st_mode)){
        return true;
    }
    else{
        return false;
    }
}

int main(void)
{

    char helpaddress[PATH_MAX];
    getcwd(helpaddress, sizeof(helpaddress));
    strcat (helpaddress, "/HelpFiles/");

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

        if (command[0] == 'c' && command[1] == 'd' && command[2] == ' '){
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

        else if (command[0] == 'm' && command[1] == 'y' && 
        command[2] == 'l' && command[3] == 's' && 
        (strlen(command) == 4 || command[4] == ' ' || command[4] == '\n')){
            if (strlen(command) == 4 || command[4] == '\n' || command[4] == '\0'){
                //printf ("a");
                myls(0, 0, 0, 0);
            }
            else{
                int start = 5, k = strlen(command);
                char *add;
                add = malloc(sizeof(char) * (256));
                memset (add, 0, strlen(add));
                int opt_a = 0, opt_l = 0, opt_T = 0, opt_r = 0, err = 0;
                if (command[start] != '-'){
                    add = command + start;
                    for (int i = start; i <= k; i++){
                        if (command[i] == ' ' || command[i] == '\n' ||
                            command[i] == '\0'){
                                command[i] = '\0';
                                //printf ("%d", strlen(add));
                                start = i + 1;
                                break;
                            }
                    }
                }
                else{
                    add[0] = '.';
                    add[1] = '\0';
                    //printf ("%d\n", strlen(add));
                }
                while (command[start] == '-'){
                    for (int j = start + 1; j <= k; j++){
                        if (command[j] == ' ' || command[j] == '\n' || command[j] == '\0'){
                            start = j + 1;
                            break;
                        }
                        else if (command[j] == 'a'){
                            opt_a = 1;
                        }
                        else if (command[j] == 'l'){
                            opt_l = 1;
                        }
                        else if (command[j] == 't'){
                            opt_T = 1;
                        }
                        else if (command[j] == 'r'){
                            opt_r = 1;
                        }
                        else{
                            err = 1;
                            printf ("myls: ERROR! Invalid Option\n");
                            break;
                        }
                    }
                    if (err) break;
                }
                if (err) continue;
                char *subc;
                subc = malloc(sizeof(char) * (256));
                memset (subc, 0, strlen(subc));
                if (add[0] != '.')
                    strcat (subc , "/");
                strcat (subc, add);
                char newcwd[PATH_MAX];
                getcwd(newcwd, sizeof(newcwd));
                if (strlen(subc) == 2 && subc[1] == '.' && subc[0] == '.')
                    chdir("..");
                else if (strlen(subc) == 1 && subc[0] == '.')
                    chdir(".");
                else if (dirExists(subc)){
                    chdir(subc);
                }
                else if (dirExists(strcat(cwd, subc))){
                    chdir(cwd);
                }
                else{
                    printf ("myls: ERROR! Directory does not exist\n");
                    chdir(newcwd);
                    continue;
                }
                myls(opt_a, opt_l, opt_T, opt_r);
                chdir(newcwd);
            }
        }


        else if (command[0] == 'm' && command[1] == 'y' && 
        command[2] == 'c' && command[3] == 'p' && command[4] == ' '){

            char* inputs[256];
            int start = 5;
            int track = 0, pos = start, k = strlen(command), flag = 1;
            int opt_v = 0, opt_f = 0, opt_i = 0, opt_n = 0, err = 0;

            while (command[start] == '-'){

                for (int j = start + 1; j <= k; j++){

                    if (command[j] == ' ' || command[j] == '\n' || command[j] == '\0'){
                        start = j + 1;
                        pos = j + 1;
                        break;
                    }
                    else if (command[j] == 'v'){
                        opt_v = 1;
                    }
                    else if (command[j] == 'f'){
                        opt_f = 1;
                        opt_n = 0;
                    }
                    else if (command[j] == 'i'){
                        opt_i = 1;
                        opt_n = 0;
                    }
                    else if (command[j] == 'n'){
                        opt_n = 1;
                        opt_i = 0;
                        opt_f = 0;
                    }
                    else{
                        err = 1;
                        break;
                    }
                }

                if (err) break;
            }

            if (err) printf ("mycp: ERROR! Invalid option.\n");
          
            for (int i = start; i <= k; i++){

                if (flag && command[i] == ' ' || command[i] == '\n' || command[i] == '\0'){
                    command[i] = '\0';
                    inputs[track] = command + pos;
                    pos = i + 1;
                    track++;
                    flag = 0;
                }

                else if (!(command[i] == ' ' || command[i] == '\n' || command[i] == '\0')){
                    flag = 1;
                }
                
            }

            if (inputs[track - 1][0] == ' ' || inputs[track - 1][0] == '\0' || inputs[track - 1][0] == '\n'){
                track--;
            }
        
            if (track == 2){
                if (fileExists(inputs[0])){
                    if (dirExists(inputs[1])){
                        mycp(inputs[0], inputs[track - 1], 1, opt_v, opt_f, opt_i, opt_n);
                    }
                    else{
                        mycp(inputs[0], inputs[track - 1], 0, opt_v, opt_f, opt_i, opt_n);
                    }
                }
                else{
                    printf ("mycp: %s: ERROR! No such file or directory\n", inputs[0]);
                }
                continue;
            }
            
            int flag2 = 0;

            for (int i = 0; i < track - 1; i++){
                if (!fileExists(inputs[i])){
                    printf ("mycp: %s: ERROR! No such file or directory\n", inputs[i]);
                    flag2 = 1;
                    break;
                }
            }
            if (flag2 == 1){
                continue;
            }

            if (!dirExists(inputs[track - 1])){
                printf ("mycp: ERROR! %s is not a directory\n", inputs[track - 1]);
                flag2 = 1;
            }
            if (flag2 == 1){ 
                continue;
            }

            for (int i = 0; i < track - 1; i++){
                mycp(inputs[i], inputs[track - 1], 1, opt_v, opt_f, opt_i, opt_n);
            }    

        }


        else if (command[0] == 'm' && command[1] == 'y' && 
        command[2] == 'm' && command[3] == 'v' && command[4] == ' '){

            char* inputs[256];
            int start = 5;
            int track = 0, pos = start, k = strlen(command), flag = 1;
            int opt_v = 0, opt_f = 0, opt_i = 0, opt_n = 0, err = 0;

            while (command[start] == '-'){

                for (int j = start + 1; j <= k; j++){

                    if (command[j] == ' ' || command[j] == '\n' || command[j] == '\0'){
                        start = j + 1;
                        pos = j + 1;
                        break;
                    }
                    else if (command[j] == 'v'){
                        opt_v = 1;
                    }
                    else if (command[j] == 'f'){
                        opt_f = 1;
                        opt_n = 0;
                        opt_i = 0;
                    }
                    else if (command[j] == 'i'){
                        opt_i = 1;
                        opt_n = 0;
                        opt_f = 0;
                    }
                    else if (command[j] == 'n'){
                        opt_n = 1;
                        opt_i = 0;
                        opt_f = 0;
                    }
                    else{
                        err = 1;
                        break;
                    }

                    }

                if (err) break;
            }

            if (err) printf ("mymv: ERROR! Invalid option.\n");

            for (int i = start; i <= k; i++){

                if (flag && command[i] == ' ' || command[i] == '\n' || command[i] == '\0'){
                    command[i] = '\0';
                    inputs[track] = command + pos;
                    pos = i + 1;
                    track++;
                    flag = 0;
                }
                else if (!(command[i] == ' ' || command[i] == '\n' || command[i] == '\0')){
                    flag = 1;
                }
                
            }
            if (inputs[track - 1][0] == ' ' || inputs[track - 1][0] == '\0' || inputs[track - 1][0] == '\n'){
                track--;
            }

            int flag2 = 0;
            for (int i = 0; i < track - 1; i++){
                if (!fileExists(inputs[i])){
                    printf ("mymv: %s: ERROR! No such file or directory\n", inputs[i]);
                    flag2 = 1;
                    break;
                }
            }

            if (!dirExists(inputs[track - 1])){
                printf ("mymv: ERROR! %s is not a directory\n", inputs[track - 1]);
                flag2 = 1;
            }
            if (flag2 == 1){ 
                continue;
            }

            for (int i = 0; i < track - 1; i++){
                mymv(inputs[i], inputs[track - 1], opt_v, opt_f, opt_i, opt_n);
            }    
        }
        

        else if (command[0] == 'm' && command[1] == 'y' && 
        command[2] == 'g' && command[3] == 'r' && command[4] == 'e' 
        && command[5] == 'p' && command[6] == ' '){

            char *pattern;
            char* inputs[256];
            int start = 7;
            int track = 0, pos = start, k = strlen(command), flag = 1;
            int opt_i = 0, opt_n = 0, opt_c = 0, opt_l = 0;

            if (command[start] == '\"'){

                pattern = command + start + 1;
                int check = 0;

                for (int i = start + 1; i < k; i++){
                    if (command[i] == '\"' && command[i + 1] == ' '){
                        check = 1;
                        start = i + 2;
                        command[i] = '\0';
                        break;
                    }
                }
                
                if (check == 0){
                    printf ("mygrep: ERROR!\n");
                    continue;
                }

            }

            else{

                pattern = command + start;
                int check = 0;
                for (int i = start + 1; i < k; i++){
                    if (command[i] == ' '){
                        check = 1;
                        start = i + 1;
                        command[i] = '\0';
                        break;
                    }
                }

                if (check == 0){
                    printf ("mygrep: ERROR!\n");
                    continue;
                }

            }
            
            pos = start;
            int err = 0;

            for (int i = start; i <= k; i++){

                if (command[i] == '-'){
                    for (int j = i + 1; j <= k; j++){
                        if (command[j] == ' ' || command[j] == '\n' || command[j] == '\0'){
                            i = j;
                            pos = i + 1;
                            break;
                        }
                        else if (command[j] == 'i'){
                            opt_i = 1;
                        }
                        else if (command[j] == 'c'){
                            opt_c = 1;
                        }
                        else if (command[j] == 'n'){
                            opt_n = 1;
                        }
                        else if (command[j] == 'l'){
                            opt_l = 1;
                        }
                        else{
                            err = 1;
                            break;
                        }
                    }
                }

                else if (flag && command[i] == ' ' || command[i] == '\n' || command[i] == '\0'){

                    command[i] = '\0';

                    if (i < k - 1 && command[i + 1] == '-'){

                        for (int j = i + 2; j <= k; j++){
                            if (command[j] == ' ' || command[j] == '\n' || command[j] == '\0'){
                                i = j - 1;
                                break;
                            }
                            else if (command[j] == 'i'){
                                opt_i = 1;
                            }
                            else if (command[j] == 'c'){
                                opt_c = 1;
                            }
                            else if (command[j] == 'n'){
                                opt_n = 1;
                            }
                            else if (command[j] == 'l'){
                                opt_l = 1;
                            }
                            else{
                                err = 1;
                                break;
                            }
                        }
                        continue;

                    }

                    inputs[track] = command + pos;
                    pos = i + 1;
                    track++;
                    flag = 0;
                }

                else if (!(command[i] == ' ' || command[i] == '\n' || command[i] == '\0')){
                    flag = 1;
                }

                if (err) break;
            }

            if (err){
                printf ("mygrep: ERROR! Invalid option\n");
                continue;
            }

            if (inputs[track - 1][0] == ' ' || inputs[track - 1][0] == '\0' || inputs[track - 1][0] == '\n'){
                track--;
            }

            int token = 0;
            for (int i = 0; i < track; i++){

                if (!fileExists(inputs[i]) && !dirExists(inputs[i])){
                    printf ("mygrep: ERROR! %s is not a file or directory\n", inputs[i]);
                    token = 1;
                    break;
                }
            }

            if (token) continue;

            for (int i = 0; i < track; i++){

                if (dirExists(inputs[i])){
                    printf ("mygrep: %s is a directory\n", inputs[i]);
                    continue;
                }

                mygrep (pattern, inputs[i], opt_i, opt_n, opt_c, opt_l);
            }
        } 


        else if (command[0] == 'm' && command[1] == 'y' && 
        command[2] == 'p' && command[3] == 's' 
        && (command[4] == ' ' || strlen(command) == 4)){    

            if (strlen(command) == 4){
                myps(0, 0, 0, 0);
                continue;
            }

            int start = 5, k = strlen(command);
            int err = 0, opt_a = 0, opt_d = 0, opt_e = 0, opt_j = 0;

            while (command[start] == '-'){

                    for (int j = start + 1; j <= k; j++){
                        
                        if (command[j] == ' ' || command[j] == '\n' || command[j] == '\0'){
                            start = j + 1;
                            break;
                        }
                        else if (command[j] == 'a'){
                            opt_a = 1;
                        }
                        else if (command[j] == 'd'){
                            opt_d = 1;
                        }
                        else if (command[j] == 'e'){
                            opt_e = 1;
                        }
                        else if (command[j] == 'j'){
                            opt_j = 1;
                        }
                        else{
                            err = 1;
                            printf ("myls: ERROR! Invalid Option\n");
                            break;
                        }

                    }

                    if (err) break;
                }

                if (err) continue; 

            myps (opt_a, opt_d, opt_e, opt_j);
        }

        else if (!strcmp(command, "exit")){
            printf ("Exiting...\n");
            break;
        }

        else if (!strcmp(command, "help") || !strcmp(command, "man")){
            printf ("Type 'help/ man command-name' for man page of implemented commands\n");
            printf ("The existing commands are: myls, myps, mygrep, mycp and mymv\n");
            continue;
        }

        else if (command[0] == 'h' && command[1] == 'e' && command[2] == 'l'
        && command[3] == 'p' && command[4] == ' ' && strlen(command) > 5){

            command = command + 5;
            char temp[PATH_MAX];
            strcpy (temp, helpaddress);
            strcat(temp, command);
            strcat(temp, ".txt");
            //printf ("%s\n", temp);
            if (!fileExists(temp)){
                printf ("Invalid Command Name!\n");
            }
            else{
                FILE *hfp = fopen(temp, "r");
                char ch;
                while ((ch = fgetc(hfp)) != EOF){
                    printf ("%c", ch);
                }
                printf ("\n");
            }
        }

        else if (command[0] == 'm' && command[1] == 'a' && command[2] == 'n'
        && command[3] == ' ' && strlen(command) > 4){

            command = command + 4;
            char temp[PATH_MAX];
            strcpy (temp, helpaddress);
            strcat(temp, command);
            strcat(temp, ".txt");
            if (!fileExists(temp)){
                printf ("Invalid Command Name!\n");
            }
            else{
                FILE *hfp = fopen(temp, "r");
                char ch;
                while ((ch = fgetc(hfp)) != EOF){
                    printf ("%c", ch);
                }
                printf ("\n");
            }

        }

        /* If questions 1 and 2 are combined
        else{
            system (command);
        }
        */
        
        else{
            printf ("ERROR! Invalid Command.\n");
        }
    }
}
