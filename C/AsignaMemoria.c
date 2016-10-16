#include<stdio.h>
#include<stdlib.h>

int asignaMem(int **ptr);

int main(){


  return 0;
}

int asignaMem(int **ptr){
  int res=0;
  //NULL
  *ptr=(int *)malloc(sizeof(int));
  if(*ptr)
    res=1;
  return(res);
}
