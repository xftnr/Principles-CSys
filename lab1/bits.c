/*
* CS:APP Data Lab
*
* <Pengdi Xia px353>
*
* bits.c - Source file with your solutions to the Lab.
*          This is the file you will hand in to your instructor.
*
* WARNING: Do not include the <stdio.h> header; it confuses the dlc
* compiler. You can still use printf for debugging without including
* <stdio.h>, although you might get a compiler warning. In general,
* it's not good practice to ignore compiler warnings, but in this
* case it's OK.
*/

#if 0
/*
* Instructions to Students:
*
* STEP 1: Read the following instructions carefully.
*/

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

Replace the "return" statement in each function with one
or more lines of C code that implements the function. Your code
must conform to the following style:

int Funct(arg1, arg2, ...) {
/* brief description of how your implementation works */
int var1 = Expr1;
...
int varM = ExprM;

varJ = ExprJ;
...
varN = ExprN;
return ExprR;
}

Each "Expr" is an expression using ONLY the following:
1. Integer constants 0 through 255 (0xFF), inclusive. You are
not allowed to use big constants such as 0xffffffff.
2. Function arguments and local variables (no global variables).
3. Unary integer operations ! ~
4. Binary integer operations & ^ | + << >>

Some of the problems restrict the set of allowed operators even further.
Each "Expr" may consist of multiple operators. You are not restricted to
one operator per line.

You are expressly forbidden to:
1. Use any control constructs such as if, do, while, for, switch, etc.
2. Define or use any macros.
3. Define any additional functions in this file.
4. Call any functions.
5. Use any other operations, such as &&, ||, -, or ?:
6. Use any form of casting.
7. Use any data type other than int.  This implies that you
cannot use arrays, structs, or unions.


You may assume that your machine:
1. Uses 2s complement, 32-bit representations of integers.
2. Performs right shifts arithmetically.
3. Has unpredictable behavior when shifting an integer by more
than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
/*
* pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
*/
int pow2plus1(int x) {
/* exploit ability of shifts to compute powers of 2 */
return (1 << x) + 1;
}

/*
* pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
*/
int pow2plus4(int x) {
/* exploit ability of shifts to compute powers of 2 */
int result = (1 << x);
result += 4;
return result;
}

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
1. Define or use any macros.
2. Define any additional functions in this file.
3. Call any functions.
4. Use any form of casting.
5. Use any data type other than int or unsigned.  This means that you
cannot use arrays, structs, or unions.
6. Use any floating point data types, operations, or constants.


NOTES:
1. Use the dlc (data lab checker) compiler (described in the handout) to
check the legality of your solutions.
2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
that you are allowed to use for your implementation of the function.
The max operator count is checked by dlc. Note that '=' is not
counted; you may use as many of these as you want without penalty.
3. Use the btest test harness to check your functions for correctness.
4. Use the BDD checker to formally verify your functions
5. The maximum number of ops for each function is given in the
header comment for each function. If there are any inconsistencies
between the maximum ops in the writeup and in this file, consider
this file the authoritative source.

/*
* STEP 2: Modify the following functions according the coding rules.
*
*   IMPORTANT. TO AVOID GRADING SURPRISES:
*   1. Use the dlc compiler to check that your solutions conform
*      to the coding rules.
*   2. Use the BDD checker to formally verify that your solutions produce
*      the correct answers.
*/


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
This file is part of the GNU C Library.
linter
The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with the GNU C Library; if not, see
<http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
include it implicitly at the start of every compilation.  It must
not itself include <features.h> or any other header that includes
<features.h> because the implicit include comes before any feature
test macros that may be defined in a source file before it first
explicitly includes a system header.  GCC knows the name of this
header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
and complex.  If the GCC (4.9 and later) predefined macros
specifying compiler intent are available, use them to determine
whether the overall intent is to support these features; otherwise,
presume an older compiler has intent to support these features and
define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/*
* bitAnd - x&y using only ~ and |
*   Example: bitAnd(6, 5) = 4
*   Legal ops: ~ |
*   Max ops: 8
*   Rating: 1
*/
int bitAnd(int x, int y) {
  return ~(~x|~y);
}
/*
* getByte - Extract byte n from word x
*   Bytes numbered from 0 (LSB) to 3 (MSB)
*   Examples: getByte(0x12345678,1) = 0x56
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 6
*   Rating: 2
*/
int getByte(int x, int n) {
  //set 1 byte as a group, there are 4 groups in a int
  //shift to get the target group and only show the lS byte
  return (x>>(n<<3))&0xFF;
}
/*
* logicalShift - shift x to the right by n, using a logical shift
*   Can assume that 0 <= n <= 31
*   Examples: logicalShift(0x87654321,4) = 0x08765432
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 20
*   Rating: 3
*/
int logicalShift(int x, int n) {
  //to get the 0x7fffffff from 1<<(32-n)-1
  //careful the special case which 1<<32 is still 1 since the overflow
  int mask = ((1<<(32+(~n+1)))^(!n))+~0;
  return (x>>n)&mask;
}
/*
* bitCount - returns count of number of 1's in word
*   Examples: bitCount(5) = 2, bitCount(7) = 3
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 40
*   Rating: 4
*/
int bitCount(int x) {
  //build the mask 0x1111111111
  int mask1 = 0x11;
  mask1 = (mask1 << 8) + 0x55;
	mask1 = (mask1 << 8) + 0x55;
	mask1 = (mask1 << 8) + 0x55;
  //add each 4 bit togather
  x=(x&mask1)+((x>>1)&mask1)+((x>>2)&mask1)+((x>>3)&mask1);
  //build mask2 to add each 8 bit
  int mask2 = 0x0F;
  mask2 = (mask2 << 8) + 0x0F;
  mask2 = (mask2 << 8) + 0x0F;
  mask2 = (mask2 << 8) + 0x0F;
  x=((x>>4)+x)&mask2;
  //no mask needed,since total wont beyond the 32
  x=((x>>8)+x);
  //add each side 16 bits
  x=((x>>16)+x);
  //only need the last 6 bit for count int
  return x&0x3f;
}
/*
* bang - Compute !x without using !
*   Examples: bang(3) = 0, bang(0) = 1
*   Legal ops: ~ & ^ | + << >>
*   Max ops: 12
*   Rating: 4
*/
int bang(int x) {
  //get the x negative
  int x_neg = ~x+1;
  //only the 0 where positive and negative will have same sign with 0
  return (~((x|x_neg)>>31))&0x01;
}
/*
* tmin - return minimum two's complement integer
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 4
*   Rating: 1
*/
int tmin(void) {
  //min is 0x80000000
  int x = 0x80;
  return x<<24;
}
/*
* fitsBits - return 1 if x can be represented as an
*  n-bit, two's complement integer.
*   1 <= n <= 32
*   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 15
*   Rating: 2
*/
int fitsBits(int x, int n) {
  //need to shift left by (n-1)
  //compare with shift to right
  int shift = (~n+33);
  return !(((x<<shift)>>shift)^x);
}
/*
* divpwr2 - Compute x/(2^n), for 0 <= n <= 30
*  Round toward zero
*   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 15
*   Rating: 2
*/
int divpwr2(int x, int n) {
  int sign = x>>31;
  //if positive then shift to right n
  //if negative then we need round up to the nearest multiple
  return (x+(sign&((1<<n)+(~0))))>>n;
}
/*
* negate - return -x
*   Example: negate(1) = -1.
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 5
*   Rating: 2
*/
int negate(int x) {
  return ((~x)+1);
}
/*
* isPositive - return 1 if x > 0, return 0 otherwise
*   Example: isPositive(-1) = 0.
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 8
*   Rating: 3
*/
int isPositive(int x) {
  //the sign is 1 and the number is not 0
  return (!((x>>31)&0x01))&(!!x);
}
/*
* isLessOrEqual - if x <= y  then return 1, else return 0
*   Example: isLessOrEqual(4,5) = 1.
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 24
*   Rating: 3
*/
int isLessOrEqual(int x, int y) {
  //need x and y be the two side of 0
  int mask = 0x80<<24;
  int shift = ~((x >> 1) + (y >> 1) + 1) + 1;
  //condider the two special case
  //when x==y return 1
  int equal = !(x^y);
  //when x==minimum return 1
  int x_min = !(x^mask);
  x += shift;
  y += shift;
  return x_min|(!!(x & mask) & !(y & mask))|equal;
}
/*
* ilog2 - return floor(log base 2 of x), where x > 0
*   Example: ilog2(16) = 4
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 90
*   Rating: 4
*/
int ilog2(int x) {
  //using the binary to solve the question
  //define the MS 1 at left or right side of 16
  int mask1 = (~0)<<16;
  int index1 = (!!(x&mask1))<<4;
  x=x>>index1;
  //define the MS 1 at left or right side of 24 or 8
  int mask2 = 0xff<<8;
  int index2 = (!!(x&mask2))<<3;
  x=x>>index2;
  //keep dividing
  int index3 = (!!(x&0xf0))<<2;
  x=x>>index3;
  int index4 = (!!(x&12))<<1;
  x=x>>index4;
  int index5 = (!!(x&2));
  //sum all the index
  int sum = index1+index2+index3+index4+index5;
  return sum;
}
/*
* float_neg - Return bit-level equivalent of expression -f for
*   floating point argument f.
*   Both the argument and result are passed as unsigned int's, but
*   they are to be interpreted as the bit-level representations of
*   single-precision floating point values.
*   When argument is NaN, return argument.
*   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
*   Max ops: 10
*   Rating: 2
*/
unsigned float_neg(unsigned uf) {
  unsigned mask = 0x80000000;
  //the two exceptions
  unsigned NaN = 0x7fc00000;
  unsigned infinate = 0xffc00000;
  if(uf==NaN|| uf==infinate){
    return uf;
  }
  //not exceptions, the give negative
  return uf^mask;
}
/*
* float_i2f - Return bit-level equivalent of expression (float) x
*   Result is returned as unsigned int, but
*   it is to be interpreted as the bit-level representation of a
*   single-precision floating point values.
*   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
*   Max ops: 30
*   Rating: 4
*/
unsigned float_i2f(int x) {
  //special case 0
  if(x==0){
    return 0;
  }
  if(x==0x80000000){
    return 0xcf000000;
  }
  unsigned sign = x&0x80000000;
  unsigned man;
  //to get the mantissa for absolute value
  if(sign){
    man = ~x+1;
  }
  else{
    man = x;
  }
  //find the first vaild bit
  unsigned temp;
  unsigned count = 0;
  unsigned rod = 0;
  while(1){
    temp = man;
    man=man<<1;
    count++;
    if(temp&0x80000000){
      break;
    }
  }
  //if shifted less than 9 bit we need round the number
  if((man & 0x1ff)>0x0100){
    rod = 1;
  }
  else if ((man&0x3ff)==0x300){
    rod = 1;
  }
  return (sign|((127+32-count)<<23)|man>>9)+rod;
}
/*
* float_twice - Return bit-level equivalent of expression 2*f for
*   floating point argument f.
*   Both the argument and result are passed as unsigned int's, but
*   they are to be interpreted as the bit-level representation of
*   single-precision floating point values.
*   When argument is NaN, return argument
*   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
*   Max ops: 30
*   Rating: 4
*/
unsigned float_twice(unsigned uf) {
  //take out the exponent
  unsigned ex = (uf>>23)&0xFF;
  //take out the sign
  unsigned sign = uf&0x80000000;
  //take out the mantissa
  unsigned man = uf&0x007fffff;
  //exceptions
  if(ex == 0xFF ||(ex==0 && man == 0)){
    return uf;
  }
  //exponent is 0
  if(ex){
    ex++;
  }
  //exponent become the 1 from 0 and mantissa round even
  else if(man == 0x007fffff){
    man--;
    ex++;
  }
  //shift the mantissa
  else {
    man= man<<1;
  }
  return sign|(ex<<23)|man;
}
