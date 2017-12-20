//Name:Pengdi Xio
//Eid:px353
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//redunence
int pop(int count){
  count--;
  printf("  popq    %%r10\n");
  printf("  popq    %%r11\n");
  return count;
}

//if it is an operator
int operator(char *token, int count) {
  switch (*token) {
    case '+':
      count=pop(count);
      printf("  addq    %%r10,%%r11\n");
      printf("  pushq   %%r11\n");
      break;
    case '-':
      count=pop(count);
      printf("  subq    %%r10,%%r11\n");
      printf("  pushq   %%r11\n");
      break;
    case 't':
      count=pop(count);
      printf("  imulq   %%r10,%%r11\n");
      printf("  pushq   %%r11\n");
      break;
    case 'n':
      printf("  popq    %%r10\n");
      printf("  negq    %%r10\n");
      printf("  pushq   %%r10\n");
      break;
    }
    return count;
}

int main(int argc, char *argv[]){
  if(argc<2){
    fprintf(stderr, "Must enter at least one argeument\n");
    return 1;
  }
  //the header
  printf("  .globl compute\n");
  printf("compute:\n");
  //track the stake and detemine the illegalization
  int stakecount =0;
  int readnum;
  char s[11];
  long number;
  //token from the input
  for(int i=1; i<argc; i++){
    //copy down the argv
    strcpy(s,argv[i]);
    //the first token
    char *token = argv[i];
    //if it is number
    if(sscanf(s, "%d", &readnum)){
      number=readnum;
      printf("  pushq   $%ld\n", number);
      stakecount++;
    }
    //the token is variable
    else if(*token=='x'||*token =='y'||*token == 'z'){
      stakecount++;
      switch (*token) {
        case 'x':
          printf("  pushq   %%rdi\n");
          break;
        case 'y':
          printf("  pushq   %%rsi\n");
          break;
        case 'z':
          printf("  pushq   %%rdx\n");
          break;
        }
    }
    //the token is operator or negaive number
    else if(*token =='+'||*token =='-'||*token=='t'||*token=='n'){
      stakecount= operator(token, stakecount);
    }
    //the illegal variable
    else{
      fprintf(stderr, "Have illegal character argeument\n");
      return 1;
    }
    //argeument less or equal to operator
    if(stakecount<1){
      fprintf(stderr,"Need more argeument to operate\n");
      return 1;
    }
  }
  //there are more than one argeument still in the stake
  if(stakecount!=1){
    fprintf(stderr, "Left over more than one argeument\n");
    return 1;
  }
  //pop answer to rax
  printf("  popq    %%rax\n");
  printf("  retq\n");

  return 0;
}
