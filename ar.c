#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#define MAXSIZE 20
void main(void){
int data[MAXSIZE];
int n;
int i;
int pos;
printf(" please size of array<20:");
scanf("%d",&n);
for(i=0;i<n;i++){
    printf("enter the value[%d]",i);
    scanf("%d",&data[i]);
}
printf(" please position:");
scanf("%d",&pos);

for(i=pos;i<n-1;i++){

data[i]=data[i+1];}

n--;



for(i=0;i<n;i++){
    printf("value[%d]=%d\n",i,data[i]);

}


}
