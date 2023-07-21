#include "headers.h"

void mymv(char* ad1, char* ad2, int opt_v, int opt_f, int opt_i, int opt_n)
{

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
            remove (ad1);
            fclose(fp2);
        }
        fclose(fp1);
    
}
