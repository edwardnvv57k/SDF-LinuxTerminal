#include "headers.h"

void mygrep (char *pattern, char *filename, int opt_i, int opt_n, int opt_c, int opt_l){
    
    FILE *fp = fopen(filename, "r");

    if (!fp){
        printf ("ERROR!\n");
        return;
    }

    char fileline[2048];
    int num = 0, count = 0;
    
    while (fgets(fileline, 2048, fp)){
        
        num++;
        if (opt_l){
            if (strcasestr(fileline, pattern)){
                printf ("%s\n", filename);
                break;
            }
        }
        if (opt_c){
            if (strcasestr(fileline, pattern)) count++;
            continue;
        }
        if (opt_i){
            if (strcasestr(fileline, pattern)){

                printf ("%s: ", filename);
                if (opt_n)
                    printf ("%d: ", num);

                if (fileline[strlen(fileline) - 1] != '\n'){
                    printf ("%s\n", fileline);
                }
                else
                    printf ("%s", fileline);
            }
        }
        
        else{
            if (strstr(fileline, pattern)){

                printf ("%s: ", filename);
                if (opt_n)
                    printf ("%d: ", num);

                if (fileline[strlen(fileline) - 1] != '\n')
                    printf ("%s\n", fileline);
                else
                    printf ("%s", fileline);
            }
        }
    }

    if (!opt_l && opt_c)  printf ("%s: %d\n", filename, count);

    fclose(fp);
}