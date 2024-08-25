#include <cstdlib>
#include <cstdio>
#include <cstdio>
#include <iostream>

#include "tbits.h"

int main (int argc, char * argv[])
{
  tbits a,b,c ;  
  double x=1.23 ; 
  
  std::cout << "Initial value: a=" << (int)a << "\n" ; 
  a-- ; 
  std::cout << "Decrement: " << (int)a << "\n" ; 
  b=-a ; 
  a=25 ; 
  std::cout << "a=25 - Any assignment not -1,0 or 1 is set to zero: " << (int)a << "\n" ; 
  int i = -a ;  
}


