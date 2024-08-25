

class tbits
{
public:
  
  //========================================
  /*tbits& operator=(const tbits& o)
  {
    a=o.a ; b=o.b ; 
    return *this ; 
  }*/
  tbits& operator=(const int & o)
  {
    if (o==1) {a=true ; b=false ; }
    else if (o==-1) {a=true ; b=true ; }
    else {a=false ; b=false ; }
    return *this ; 
  }
  //========================================
  operator int() 
  {
    if (a)
    {
      if (b)
        return -1 ; 
      else 
        return +1 ; 
    }
    return 0 ; 
  }
  operator bool() 
  {
    return a ; 
  } 
  //========================================
  tbits& operator++()
  {
    if (a)
    {
      if(b) {a=false ; b=false ;}
      else {a=true; b=true ; }
    }
    else 
    {
      a=true ; b=false ; 
    }
    return *this; // return new value by reference
  }
  
  tbits operator++(int)  // postfix increment
  {
      tbits old = *this; // copy old value
      operator++();  // prefix increment
      return old;    // return old value
  }

  tbits& operator--()
  {
    if (a)
    {
      if(b) {a=true ; b=false ;}
      else {a=false; b=false ; }
    }
    else 
    {
      a=true ; b=true ; 
    }
      return *this; // return new value by reference
  }

  tbits operator--(int)  // postfix decrement
  {
      tbits old = *this; // copy old value
      operator--();  // prefix decrement
      return old;    // return old value
  }

  //===========================================
  template <typename T>
  void sign(T v)
  {
    if (v>0) {a=true; b=false ; }
    else if (v<0) {a=true; b=true ; }
    else {a=false ; b=false ;}
  }
  //-------------------------------------------
  bool is_nan () {return (a==false && b==true) ; }
  void set_nan() {a=false ; b=true ; }
  void clear_nan(){a=false ; b=false ; }
  
private:
  bool a=false, b=false ; 
  
} ; 








