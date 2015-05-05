#ifndef _LOFTILI_LIB_JSON_PARSER_H
#define _LOFTILI_LIB_JSON_PARSER_H

namespace loftili {

namespace lib {

class JsonParser {
  public: 
    bool Null() { return true; };
    bool Bool(bool b) { return true; };
    bool Int(int i) { return true; };
    bool Uint(unsigned u) { return true; };
    bool Int64(int64_t i) { return true; };
    bool Uint64(uint64_t u) { return true; };

    virtual bool Double(double) {
      return true; 
    };

    virtual bool String(const char*, size_t, bool) {
      return true;
    };

    virtual bool StartObject() {
      return true; 
    };

    virtual bool Key(const char*, size_t, bool) {
      return true; 
    };

    virtual bool EndObject(size_t) {
      return true; 
    };

    virtual bool StartArray() {
      return true; 
    };

    virtual bool EndArray(size_t) {
      return true; 
    };
};

}

}

#endif
