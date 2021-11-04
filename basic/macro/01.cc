#include <iostream>

#define unpack(i, n) 

#include <stdio.h>

#define REP0(X)
#define REP1(X) X
#define REP2(X) REP1(X) X
#define REP3(X) REP2(X) X
#define REP4(X) REP3(X) X
#define REP5(X) REP4(X) X
#define REP6(X) REP5(X) X
#define REP7(X) REP6(X) X
#define REP8(X) REP7(X) X
#define REP9(X) REP8(X) X
#define REP10(X) REP9(X) X

#define REP(HUNDREDS,TENS,ONES,X) \
  REP##HUNDREDS(REP10(REP10(X))) \
  REP##TENS(REP10(X)) \
  REP##ONES(X)

int main(void)
{
  printf(REP(1,0,7, "*")); // "*" repeated 907 times
  printf(REP(0,9,2, "#")); // "#" repeated 92 times
  printf(REP(0,0,1, "@")); // "@" repeated 1 times
  return 0;
}