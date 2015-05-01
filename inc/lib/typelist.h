#ifndef _LOFTILI_LIB_TYPELIST_H
#define _LOFTILI_LIB_TYPELIST_H

namespace loftili {

namespace lib {

namespace generic {

struct T_Null {};

template <class TT_H, class TT_T>
class T_Typelist {
  public:
    typedef TT_H T_Head;
    typedef TT_T T_Tail;
};

template <class TT_A=T_Null, class TT_B=T_Null, class TT_C=T_Null, class TT_D=T_Null>
class T_Seq;

template <class TT_A>
class T_Seq<TT_A, T_Null, T_Null, T_Null> {
  public:
    typedef T_Typelist<TT_A, T_Null> T_Result;
};

template <class TT_A, class TT_B>
class T_Seq<TT_A, TT_B, T_Null, T_Null> {
  public:
    typedef T_Typelist<TT_A, 
            T_Typelist<TT_B, 
            T_Null> > T_Result;
};

template <class TT_A, class TT_B, class TT_C>
class T_Seq<TT_A, TT_B, TT_C, T_Null> {
  public:
    typedef T_Typelist<TT_A, 
            T_Typelist<TT_B, 
            T_Typelist<TT_C, 
            T_Null> > > T_Result;
};

template <class TT_A, class TT_B, class TT_C, class TT_D>
class T_Seq {
  public:
    typedef T_Typelist<TT_A, 
            T_Typelist<TT_B, 
            T_Typelist<TT_C, 
            T_Typelist<TT_D, T_Null
            > > > > T_Result;
};

template <class T_Unit>
class T_BasicHolder {
  public:
    T_Unit m_item;
};

template <class T_ComponentList, template <class> class T_Holder=T_BasicHolder>
struct T_ScatterHierarchy;

template <class T_Head, class T_Tail, template <class> class T_Holder>
struct T_ScatterHierarchy<T_Typelist<T_Head, T_Tail>, T_Holder> : 
  public T_ScatterHierarchy<T_Tail, T_Holder>, 
  public T_ScatterHierarchy<T_Head, T_Holder> {

  template <typename T> 
  struct T_Rebind {
    typedef T_Holder<T> T_Result;
  };

};

template <class T_Head, template <class> class T_Holder>
struct T_ScatterHierarchy : public T_Holder<T_Head> {

  template <typename T> 
  struct T_Rebind {
    typedef T_Holder<T> T_Result;
  };

};

template <template <class> class T_Holder>
struct T_ScatterHierarchy<T_Null, T_Holder> {

  template <typename T> 
  struct T_Rebind {
    typedef T_Holder<T> T_Result;
  };

};


}

}

}

#endif
