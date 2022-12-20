//Vidur Goel Question Number 2.b

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> //linux specific library
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h> //Used for handling directory files
#include <errno.h> //For EXIT codes and error handling
#include <stddef.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <signal.h>
#include <semaphore.h>
#include <stdio.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/un.h>

# define ll int

ll line;
ll sector;
struct sockaddr_un address;

struct Data_Packet{
    char arr_of_string[5][10];
    ll arr_of_index[5];
    ll high_index;
};

int timediff;
#define BILLION 1000000000L;

struct Data_Packet packet_generator(char arr[5][10],ll indexarr[5],ll high_index){
    struct Data_Packet pack;
    memcpy(pack.arr_of_index, indexarr, sizeof(int) * 5);
    memcpy(pack.arr_of_string, arr, sizeof(char) * 5*10);
    pack.high_index=high_index;
    return pack;
}

char * String_Generator(ll length){
    char * string_generated=malloc(sizeof(char)*10);
    for(ll i=0;i<length;i++){
        char * m;
        ll k=rand();
        if(k%62>=0 && k%62<=9){
            string_generated[i]='0'+k%62;
        }
        else if(k%62>=10 && k%62<=35){
            string_generated[i]='a'+(k%62)-10;
        }
        else{
            string_generated[i]='A'+k%62-36;
        }
    }
    return string_generated;
}

void string_printing(char a[10]){
    for(ll i=0;i<10;i++){
        printf("%c",a[i]);
    }
    printf("%c",'\n');
    return;
}

void copy_arr(char ** a,char ** b,ll i1,ll length){
    for(ll i=0;i<length;i++){
        char * m=malloc((sizeof(char)*10));
        for(ll j=0;j<10;j++){
            m[j]=b[5*i1+i][j];
            printf("%c",b[5*i1+i][j]);
        }
        a[i]=m;
        printf("\n");
    }
}

void copy_arr2(ll * a,ll i1,ll length){
    for(ll i=0;i<length;i++){
        a[i]=i1+i;
    }
    return;
}

int main(int argc,char * argv[]){
    if((sector = socket(AF_UNIX, SOCK_STREAM, 0))<0){
        printf("Error while opening a socket");
        exit(1);
    }
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "MYSOCKETFILE");

    connect(sector, (struct sockaddr *)&address, sizeof(struct sockaddr_un));

    ll i=0;
    while(i<=49){
        struct Data_Packet data;
        read(sector,(void*)&data,sizeof(data));
        // printf("\n%s ",data.arr_of_string[0]);
        // printf("%s\n ",data.arr_of_string[1]);
        // printf("%s ",data.arr_of_string[2]);
        // printf("%s ",data.arr_of_string[3]);
        // printf("%s\n",data.arr_of_string[4]);
        printf("\n%d ",data.arr_of_index[0]);
        printf("%d ",data.arr_of_index[1]);
        printf("%d ",data.arr_of_index[2]);
        printf("%d ",data.arr_of_index[3]);
        printf("%d\n",data.arr_of_index[4]);
        ll high = data.high_index;
        write(sector,&high,sizeof(int));
        i=high+1;
    }
    sleep(1);
    close(sector);
    exit(0);
}
