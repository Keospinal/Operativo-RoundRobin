#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i,j,k;
    for(i = 0;i<2;i++){
        if(fork()==0){
         for(j = 0;j<3;j++){
                if(fork()==0){
                for(k=0;k<4;k++){
                        if(fork()==0){
                        break;
                        }
                }
                break;
                        }
                }
         break;
                }
        }
        while(1);
}