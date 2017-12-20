//Name: Pengdi Xia
//Eid: px353

#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

//build upthe cache elements
struct element{
  int valid;
  long long tag;
  long long lru;
};
//initialize variables
int hit=0;
int miss=0;
int evic=0;
//-v command
int v=0;
// b,E,s for the number of line,bites of block and set
int b=0;
int E=0;
int s=0;
//B=2^b, S=2^s
int S=0;
int B=0;
int index_mask;
struct element **cache=NULL;
long long lrucount =0;

// initialize the cache
void initialCache(){
  cache= malloc(S*sizeof(*cache));
  for(int i=0; i<S; i++){
    cache[i]=calloc(E,sizeof(*cache[i]));
  }
  //since the number of set is always 2^s so the S-1 to binary must will be ff..
  index_mask = S-1;
}

//access data
void accessData(long long addr){
  long long indexSet = (addr >> b) & index_mask;
  long long tag = (addr >> (b+s));
  long long minLru = LLONG_MAX;
  int evicLine=0;
  //check the cache for the hit
  for(int i=0; i <E; i++){
    //if it is volid and there is a same tag in set the hit
    if(cache[indexSet][i].tag==tag && cache[indexSet][i].valid!=0){
        hit++;
        cache[indexSet][i].lru = lrucount++;
        return;
    }
    //to save the time we will also look for the min lru for later
    if(cache[indexSet][i].lru<minLru){
      evicLine = i;
      minLru = cache[indexSet][i].lru;
    }
  }
  //then there is no hit
  miss++;
  //check are are nu
  if(cache[indexSet][evicLine].valid ==1){
    evic++;
  }
  cache[indexSet][evicLine].valid=1;
  cache[indexSet][evicLine].tag=tag;
  cache[indexSet][evicLine].lru=lrucount++;
}

// free the cache
void freeCache(){
	for (int i=0; i<S; i++){
    free(cache[i]);
  }
  free(cache);
}

//get the command and run the program
int main(int argc, char**argv){
  int c=0;
  char *tracefile;
  FILE *file;
  //getopt
  while((c=getopt(argc,argv, "s:E:b:t:vh"))!=-1){
    switch (c) {
      case 's':
        s=atoi(optarg);
        break;
      case 'E':
        E=atoi(optarg);
        break;
      case 'b':
        b=atoi(optarg);
        break;
      case 't':
        tracefile=optarg;
        break;
      case 'v':
        exit(0);
      default:
        printf("Wrong input");
        exit(1);
    }
  }
  //B=2^b, S=2^s
  S = 1 << s;
	B = 1 << b;
  //initial cache
  initialCache();
  //read file
  file = fopen(tracefile, "r");
  char instruction;
  unsigned long long addr;
  int size;
  //read the instruction to compute miss,hit, evic
  if(file != NULL){
    while (fscanf(file, " %c %llx,%d", &instruction, &addr, &size) == 3){
			switch(instruction) {
				case 'L':
					accessData(addr);
					break;
				case 'S':
					accessData(addr);
					break;
				case 'M':
					accessData(addr);
					accessData(addr);
					break;
				default:
					break;
			}
    }
  }
  //close file
  fclose(file);
  //freed the cache
  freeCache();
  //print result
  printSummary(hit, miss, evic);
  return 0;
}
