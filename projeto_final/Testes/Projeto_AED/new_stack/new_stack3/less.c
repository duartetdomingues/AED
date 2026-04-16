#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int less(int x,int y){
    return x<y ? true : false;
}

int main(){
    int a=2;
    int b=1;
    printf("%d",less(b,a)) ;
}
