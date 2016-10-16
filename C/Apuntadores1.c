#include<stdio.h>
#include<stdlib.h>

int main(){
  int *ptr;
  int x=100;

  ptr=&x;

  printf("%d\n",*ptr);
  printf("%p\n",ptr);

  ptr++;

  printf("%p\n",ptr);

  return 0;
}
