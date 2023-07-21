#include "headers.h"

void myps(int opt_a, int opt_d, int opt_e, int opt_j){
    DIR *proc = opendir("/proc");
    if (!proc){
        printf ("myps: ERROR! proc can't be opened\n");
        return;
    }
    else{
        struct stat meta;
        struct dirent *dirdetails;
        //session id != pid

        if (opt_j) printf ("%6s %6s %6s %8s %8s %s\n", "PID", "PGID", "SID", "TTY", "TIME", "CMD");
        else printf ("%6s %8s %8s %s\n", "PID", "TTY", "TIME", "CMD");
        
        while (dirdetails = readdir(proc)){

            int pid;
            if (isdigit(dirdetails->d_name[0])){

                pid = strtol(dirdetails->d_name, NULL, 10);
                char fd_path[256];
                sprintf(fd_path, "/proc/%d/fd/0", pid);
                
                int fd_file = open(fd_path, O_RDONLY);
                char self[256];
                char *tty = ttyname(fd_file);

                if (tty == NULL){
                    tty = "     ?";
                }

                strcpy(self, tty);
                char stat_path[256];
                sprintf(stat_path, "/proc/%d/stat", pid);

                FILE *stat_file = fopen(stat_path, "r");
                
                char *termtty = ttyname(STDIN_FILENO);
                int ppid, session, psr, pgid;
                long long int utime, stime, cuttime, cstime, STIME;
                unsigned long long int rss;
                int seconds, mins, hrs;
                char cmd[256], status;
                
                fscanf(stat_file , "%*d %s %c %d %d %d %*d %*d %*u %*d %*d %*d %*d %lld %lld %lld %lld %*d %*d %*d %*d %lld %*d %llu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d %d",
                   cmd , &status , &ppid, &pgid, 
                   &session, &utime, &stime  , 
                   &cuttime, &cstime,&STIME
                   , &rss , &psr , &seconds);
                seconds = stime/sysconf(_SC_CLK_TCK);
                mins = seconds/60;
                hrs = mins/60;
                mins %= 60;
                seconds %= 60;
                fclose (stat_file);
                
                if (!opt_j){
                    
                    if (opt_a + opt_d + opt_e == 0 && !strcmp(self, termtty)){
                        printf ("%6d %8s %02d:%02d:%02d %s\n", pid, tty + 5, hrs, mins, seconds, cmd);
                    }
                    else if (opt_e){
                        printf ("%6d %8s %02d:%02d:%02d %s\n", pid, tty + 5, hrs, mins, seconds, cmd);
                    }
                    else if (opt_a && session != pid && tty[5] != '?'){
                        printf ("%6d %8s %02d:%02d:%02d %s\n", pid, tty + 5, hrs, mins, seconds, cmd);
                    }
                    else if (opt_d && session != pid){
                        printf ("%6d %8s %02d:%02d:%02d %s\n", pid, tty + 5, hrs, mins, seconds, cmd);
                    }

                }

                else{
                    
                    if (opt_a + opt_d + opt_e == 0 && !strcmp(self, termtty)){
                        printf ("%6d %6d %6d %8s %02d:%02d:%02d %s\n", pid, pgid, session, tty + 5, hrs, mins, seconds, cmd);
                    }
                    else if (opt_e){
                        printf ("%6d %6d %6d %8s %02d:%02d:%02d %s\n", pid, pgid, session, tty + 5, hrs, mins, seconds, cmd);
                    }
                    else if (opt_a && session != pid && tty[5] != '?'){
                        printf ("%6d %6d %6d %8s %02d:%02d:%02d %s\n", pid, pgid, session, tty + 5, hrs, mins, seconds, cmd);
                    }
                    else if (opt_d && session != pid){
                        printf ("%6d %6d %6d %8s %02d:%02d:%02d %s\n", pid, pgid, session, tty + 5, hrs, mins, seconds, cmd);
                    }

                } 
            }
        }
    }
}