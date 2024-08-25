#include <cstdlib>
#include <cstdio>
#include <cstdio>
#include <iostream>

#include "tbits_vector.h"

int main (int argc, char * argv[])
{
  tbits_vector A({-1,1,0,2,1,5,-1,0}) ; // A contains {-1,1,0,0,1,0,-1,0}
  
  std::vector V = {1,1,0,0,-1,-1} ; 
  std::array arr = {-1,-1,0,0,1,1} ; 
  
  A=arr ; 
  
  A.print() ;
  A.to_vector(V) ; // Overwrites V
  
  A={0,0,0,0,0,0,0,0} ; 
  for (int i=0 ; i<10 ; i++)
  {
    (A++).print() ; printf("\n"); // array incrementing
  }
  
  std::cout << "The second element is " << A[1] << "\n" ;
  
}


