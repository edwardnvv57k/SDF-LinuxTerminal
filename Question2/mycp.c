#include "headers.h"

void mycp(char* ad1, char* ad2, int operation, int opt_v, int opt_f, int opt_i, int opt_n)
{
    if (operation == 0){

        FILE *fp1, *fp2;
        fp1 = fopen(ad1, "r");
        fp2 = fopen(ad2, "w");

        if (!fp1 || !fp2){
            printf ("ERROR!\n");
            return;
        }
        if (!strcmp(ad1, ad2)){
            printf ("mycp: %s and %s are identical (not copied)\n", ad1, ad2);
        }
        else{
            int go = 1;
            if (opt_i){
                char response[256];
                printf ("overwrite %s? (y/ n) ", ad2);
                scanf ("%s", response);
                if (response[0] != 'y' && response[0] != 'Y'){
                    go = 0;
                }
            }
            if (go){
                if (opt_f){
                    remove (ad2);
                    fp2 = fopen(ad2, "w");
                }
                char ch;
                while ((ch = fgetc(fp1)) != EOF){
                    fputc(ch, fp2);
                }

                if (opt_v){
                    printf ("%s -> %s\n", ad1, ad2);
                }
            }
            else if (opt_i){
                printf ("not overwritten\n");
            }
        }
        fclose(fp1);
        fclose(fp2);
    }

    else if (operation == 1){
        
        FILE *fp1, *fp2;
        fp1 = fopen(ad1, "r");
        char *temp;
        temp = malloc(sizeof(char) * (strlen(ad2) + 1));
        memset(temp, 0, strlen(temp));
        strcpy(temp, ad2);
        strcat(strcat(temp, "/"), ad1);
        int fe = 0;
        if (fileExists(temp)){
            fe = 1;
        }
        int go = 1;
        if (opt_i){
            char response[256];
            printf ("overwrite %s? (y/ n) ", temp);
            scanf ("%s", response);
            if (response[0] != 'y' && response[0] != 'Y'){
                go = 0;
            }
        }
        if (fe && (opt_n || !go)){
            printf ("%s not overwritten\n", temp);
        }
        else{
            if (fe && opt_f){
                remove (temp);
            }
            fp2 = fopen(temp , "w");
            free(temp);
            if (!fp1 || !fp2){
                printf ("ERROR!\n");
                return;
            }
            char ch;
            while ((ch = fgetc(fp1)) != EOF){
                fputc(ch, fp2);
            }

            if (opt_v){
                printf ("%s -> %s/%s\n", ad1, ad2, ad1);
            }
            fclose(fp2);
        }
        fclose(fp1);
    }
}
