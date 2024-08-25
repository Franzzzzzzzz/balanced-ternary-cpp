#include <vector>
#include <array>
#include <cmath>




class tbits_vector
{  
  class tbits_ref 
  {
  public:
    tbits_ref(std::vector<unsigned int> *d, int id ) 
    {
      data = d ; 
      idx_l = (id*2)%((sizeof(unsigned int))*8); 
      idx_h = (id*2)/((sizeof(unsigned int))*8); 
    }
    //------------------------------------------
    void set_plusone(void) 
    {
      (*data)[idx_h] &= ~(0b11U<<(idx_l)) ; 
      (*data)[idx_h] |=  (0b10U<<(idx_l)) ;
    }
    void set_minusone(void) { (*data)[idx_h] |= (0b11U<<(idx_l)) ; }
    void set_zero (void) {(*data)[idx_h] &= ~(0b11U<<(idx_l)) ; }
    void set_nan(void) 
    {
      (*data)[idx_h] &= ~(0b11U<<(idx_l)) ; 
      (*data)[idx_h] |=  (0b01U<<(idx_l)) ;
    }
    void clear_nan(void) {set_zero() ; }
    void skip_nan() 
    {
      if ((((*data)[idx_h] >> idx_l)&0b11)==1) set_plusone() ;       
    }
    bool is_nan()
    {
      return ((((*data)[idx_h] >> idx_l)&0b11)==1) ; 
    }
    bool is_zero()
    {
      return ((((*data)[idx_h] >> idx_l)&0b11)==0) ; 
    }
    //------------------------------------------
    tbits_ref& operator=(const int v)
    {
      if (v==1) set_plusone() ;
      else if (v==-1) set_minusone() ; 
      else set_zero() ; 
      return *this ; 
    }
    //------------------------------------------
    tbits_ref & operator++()
    {
      char v = ((*data)[idx_h]>>idx_l) & 0b11 ;
      if (v==2) set_minusone() ; 
      else if (v==0) set_plusone() ; 
      else set_zero() ; 
      return *this; // return new value by reference
    }    
    tbits_ref operator++(int)  // postfix increment
    {
        tbits_ref old = *this; // copy old value
        operator++();  // prefix increment
        return old;    // return old value
    }
    //------------------------------------------
    tbits_ref& operator--()
    {
      char v = ((*data)[idx_h]>>idx_l) & 0b11 ;
      if (v==3) set_plusone() ; 
      else if (v==0) set_minusone() ; 
      else set_zero() ; 
      return *this; // return new value by reference
    }
    tbits_ref operator--(int)  // postfix decrement
    {
        tbits_ref old = *this; // copy old value
        operator--();  // prefix decrement
        return old;    // return old value
    }
    //------------------------------------------
    operator int() 
    {
      char v = (((*data)[idx_h]>>idx_l) & 0b11)  ; 
      if (v==2) return 1 ; 
      if (v==3) return -1 ;
      return 0 ; 
    }
  private: 
    std::vector<unsigned int> * data;
    size_t idx_h; 
    char idx_l ; 
  } ; 
  
public: 
  void resize (size_t n) 
  { 
    data.resize(int(ceil(n*2/(double)((sizeof(unsigned int)*8))))) ;  
    sz = n ; 
  }
  size_t size(void) {return sz; }
  //------------------------------------------
  tbits_vector & operator++()
  {
    data[0] ++ ;
    size_t i ; 
    for (i=0 ; data[i]==0 && i<sz-1 ; i++)
      data[i+1]++ ; 
    
    size_t j=0 ; 
    for (j=0 ; (*this)[j].is_zero() && j<sz ; j++);
    (*this)[j].skip_nan() ; 
    
    if (j==sz) ovflow = true ; 
    else ovflow = false ; 
    
    return *this; // return new value by reference
  }    
  tbits_vector operator++(int)  // postfix increment
  {
      tbits_vector old = *this; // copy old value
      operator++();  // prefix increment
      return old;    // return old value
  }
    //---------------------------------------------  
  tbits_ref operator[] (int n) {
    tbits_ref res(&data,n) ; 
    return res ; 
  }
  //--------------------------------------------------
  template <typename T>
  bool operator== (std::vector<T> const &v)
  {
    for ( size_t i=0 ; i<sz; i++)
      if ((*this)[i] != v[i])
        return false ; 
    return true ; 
  }
  template <typename T>
  bool operator!= (std::vector<T> const &v)
  { 
    return !((*this)==v); 
  }
  bool operator== (tbits_vector const & v )
  {
    if (v.sz != sz) return false ; 
    for (size_t i=0 ; i<data.size()  ; i++)
      if (data[i] != v.data[i])
        return false ; 
    return true ; 
  }
  bool operator!= (tbits_vector const & v)
  { 
    return !((*this)==v); 
  }
  
  //---------------------------------------------  
  template <typename T> 
  std::vector<T> to_vector ()
  {
    std::vector<T> res(sz,0) ; 
    for (size_t i=0, lo=0, hi=0 ; i<sz ; i++, lo+=2)
    {
      if (lo>=sizeof(unsigned int)*8) {hi++; lo=0 ; }
      if (((data[hi]>>lo) & 0b11)==3) res[i]=-1 ;
      else if (((data[hi]>>lo) & 0b11)==2) res[i]=1 ;
      else res[i] = 0 ; 
    }
    return res ; 
  }
  template <typename T> void to_vector (std::vector<T> & v) {v = to_vector<T>() ; }
  //---------------------------------------------
  void print() 
  {
    for (size_t i=0, lo=0, hi=0 ; i<sz ; i++, lo+=2)
    {
      if (lo>=sizeof(unsigned int)*8) {hi++; lo=0 ; }
      if (((data[hi]>>lo) & 0b11)==3) printf("-") ;
      else if (((data[hi]>>lo) & 0b11)==2) printf("+") ;
      else if (((data[hi]>>lo) & 0b11)==1) printf("N") ;
      else printf("0") ; 
      
    }
    printf("\n") ; 
  }
  //-----------------------------------------------
  tbits_vector() {}
  tbits_vector(size_t n) 
  {
    data.resize(int(ceil(n*2/(double)((sizeof(unsigned int)*8))))) ;  
    sz = n ; 
  }
  tbits_vector(std::vector<int> v) 
  {
    size_t n=v.size() ;     
    data.resize(int(ceil(n*2/(double)((sizeof(unsigned int)*8))))) ;  
    sz = n ; 
    for (size_t i=0 ; i<n ; i++)
      (*this)[i]=v[i] ; 
  }
  template <typename T, size_t N>
  tbits_vector(std::array<T,N> v) 
  {
    size_t n=v.size() ; 
    data.resize(int(ceil(n*2/(double)((sizeof(unsigned int)*8))))) ;  
    sz = n ; 
    for (size_t i=0 ; i<n ; i++)
      (*this)[i]=v[i] ; 
  }
  //------------------------------------------------
  size_t count_nan() {return count_val(1) ; }
  size_t count_zero() {return count_val(0) ; }
  size_t count_positive() {return count_val(2) ; }
  size_t count_negative() {return count_val(3) ; }  
  
  bool overflow() {return ovflow ; }
  
private:
  size_t count_val (int c)
  {
    size_t count = 0;
    for (size_t i=0, lo=0, hi=0 ; i<sz ; i++, lo+=2)
    {
      if (lo>=sizeof(unsigned int)*8) {hi++; lo=0 ; }
      if (((data[hi]>>lo) & 0b11)==c) count ++;
    }
    return count ; 
  }
  
  std::vector<unsigned int> data ;
  size_t sz = 0 ; 
  bool ovflow=false ;   
} ; 








