#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <boost/random.hpp>
#include "tbits.h"
#include "tbits_vector.h"


int main (int argc, char * argv[])
{
  // Tests of tbits
  tbits A, B ;
  
  assert((A==B)) ; 
  A++ ; 
  assert((A==1)) ; 
  A++ ; 
  B=A ; 
  assert((A==-1)) ; 
  assert((B==-1)) ; 
  A++ ; 
  assert((A==0)) ; 
  A-- ; 
  assert((A==-1)) ; 
  B=--A ; 
  assert((A==1)) ; 
  assert((B==1)) ; 
  B=A-- ; 
  assert((B==1)) ; 
  assert((A==0)) ; 
  A-- ; 
  assert((A==-1)) ; 
  A=23 ; 
  assert((A==0)) ; 
  
  printf("All tbits tests successfull\n") ; 

  // Tests of tbits vectors
  int n = sizeof(unsigned int)*4 + 5 ; 
  tbits_vector V(n) ; 
  std::vector<int> V2(n,0) ; 
  
  boost::random::mt19937 rng(std::time(0)); 
  boost::random::uniform_smallint<> rand(-1,1) ; 
  for (int i=0 ; i<n ; i++)
    V2[i] = rand(rng) ; 
  
  V=V2 ; 
  assert((V==V2)) ; 
  boost::random::uniform_smallint<> randrange(0,n) ; 
  int i=randrange(rng) ; 
  assert((V[i]==V2[i])) ; 
  
  for ( ; ! V.overflow() ; V++)
  {
    assert((V==V2)) ; 
    int j=-1 ; 
    do {
      j++ ;
      if (V2[j]==1) V2[j]=-1 ; 
      else if (V2[j]==-1) V2[j]=0 ; 
      else V2[j]=1 ;
    } while (j+1<n && V2[j]==0) ; 
  }
  
  int res = std::count(V2.begin(), V2.end(), 1) ; 
  assert((V.count_positive()==res)) ; 
  res = std::count(V2.begin(), V2.end(), -1) ; 
  assert((V.count_negative()==res)) ; 
  res = std::count(V2.begin(), V2.end(), 0) ; 
  assert((V.count_zero()==res)) ; 
  
  {
  auto vV = V.to_vector<double>() ;
  int i=0 ; 
  for (auto w: vV)
    assert (( w == V[i++])) ;
  }
  
  {
    std::vector<int> vV ; 
    V.to_vector(vV) ;
    assert ((vV == V2)) ;   
  }
  printf("All tbits vector tests successfull\n") ; 
  
  // Test of tbits_ref
  auto V3 = V ;   
  assert((V3==V)) ;
  V3.resize(n/2) ;   
  assert((V3!=V)) ;
  
  do { i= randrange(rng) ; } while (i>n/2-1) ; 
  assert((V3[i]==V[i])) ;
  
  ++V3[i] ;
  assert((V3[i]!=V[i])) ;
  if (V[i] == 0) assert((V3[i]==1)) ; 
  else if (V[i] == 1) assert((V3[i]==-1)) ; 
  else assert((V3[i]==0)) ; 
  
  V3[i] ++ ;
  if (V[i] == 0) assert((V3[i]==-1)) ; 
  else if (V[i] == 1) assert((V3[i]==0)) ; 
  else assert((V3[i]==1)) ; 
   
  V3[i]++ ;
  assert((V3[i]==V[i])) ;
  
  i=n/2-i ; 
  --V3[i] ;
  assert((V3[i]!=V[i])) ;
  if (V[i] == 0) assert((V3[i]==-1)) ; 
  else if (V[i] == 1) assert((V3[i]==0)) ; 
  else assert((V3[i]==1)) ; 
  
  V3[i]-- ;
  if (V[i] == 0) assert((V3[i]==1)) ; 
  else if (V[i] == 1) assert((V3[i]==-1)) ; 
  else assert((V3[i]==0)) ; 
  
  V3[i]-- ;
  assert((V3[i]==V[i])) ;
  
  printf("All tbits ref tests successfull\n") ; 
  
  boost::random::uniform_smallint<> randnan(0,5) ;
  int cnt=0 ; 
  for (int i=0 ; i<V.size() ; i++)
  {
    if (randnan(rng)==0)
    {
      V[i].set_nan() ; 
      cnt++ ; 
    }
  }  
  assert((cnt==V.count_nan())) ; 
  printf("NaN support testing in vector successfull\n") ; 
  
  
}
