#ifndef _LOFTILI_LIB_STREAM_H
#define _LOFTILI_LIB_STREAM_H

#include <iostream>
#include <sstream>
#include <string>

namespace loftili {

namespace lib {

template <class TT_DataType>
class T_Stream {
  public:
    virtual T_Stream& operator <<(const char *data) { 
      printf("%s", data); return *this;
    }

  private:
    typedef TT_DataType Data;
    Data m_data;
};

typedef T_Stream< std::basic_stringstream<char> > Stream;

}

}

#endif
