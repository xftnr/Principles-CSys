#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

extern int64_t compute(int64_t x, int64_t y, int64_t z);
  int main(){
    int64_t x = 1;
    int64_t y = 2;
    int64_t z = 3;
    int64_t computeResult = compute(x, y, z);
    printf("Result: %" PRId64 "\n", computeResult);
return 0;
}
