#include <stdio.h>
#define swap(a, b){int t;t = a;a = b;b = t;}
int N=16;

void fake_ordering(int *vec, int iL, int iR)
{
    int tmp;
    int iM = (iR - iL) / 2;
    if (vec[iL] > vec[iM])swap(vec[iL], vec[iM]);
        
    if (vec[iM] > vec[iR])swap(vec[iM], vec[iR]);
        
    if (vec[iL] > vec[iM])swap(vec[iL], vec[iM]);
        
    
    
    for(int i=0;i<N-1;i++)printf("%d,",vec[i]);

    printf("\n");
    
    fake_ordering(vec, iL, iM);
    fake_ordering(vec, iM + 1, iR);
    return;
}
int main(){
    int vec[16]={788,2,3,1,22,47,48,0,5,99,11,9,1010,10,6,88};
    //int N=16;
    fake_ordering(vec,0,N-1);
}
