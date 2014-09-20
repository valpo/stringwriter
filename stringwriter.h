#ifndef STRCLASS_H
#define STRCLASS_H

#include <string>
#include <string.h>
#include <iosfwd>
#include <cassert>

/** StringWriter wraps a std::string into an object which looks like a c-string char*
 * note that c++ strings may contain 0 bytes. This may cause unexpected effects:
 *   string s{"This is a text."};
 *   StringWriter sw{s};
 *   strpcy(sw, "hallo"); // now s == "hallo\0s a text."
 *   strlen(sw) == 5;
 *   s.size() == 15;
*/
class StringWriter
{
public:
  using size_type = std::string::size_type;
  static const size_type npos = std::string::npos;
  friend StringWriter strstr(const StringWriter& haystack, const char *needle);
  friend StringWriter& strcpy(StringWriter&, const StringWriter&);
  friend StringWriter& strcpy(StringWriter&, const char*);
  friend size_t strlen(const StringWriter& s);
private:
  std::string& str; //< the string we working on
  size_type offset; //< the current offset in this string
public:
  StringWriter(std::string& s, size_type i =0)
    : str(s), offset(i)
  {}
  StringWriter(const StringWriter& o)
    : str(o.str), offset(o.offset)
  {}
  char& operator[](size_type i)
  {
    assert(i <= str.size());
    //return StringWriter(this->str, offset+i);
    return str[offset+i];
  }
  const char& operator[](size_type i) const
  {
    assert(i <= str.size());
    //return StringWriter(this->str, offset+i);
    return str[offset+i];
  }

  const char* c_str() const
  {
    return str.c_str() + offset;
  }

  StringWriter& operator+=(size_type i)
  {
    offset += i;
    return *this;
  }

  StringWriter operator+(size_type i) const
  {
    return StringWriter(this->str, offset+i);
  }

  char& operator*()
  {
    return str[offset];
  }

  StringWriter& operator=(char c)
  {
    assert(offset < str.size());
    str[offset] = c;
    return *this;
  }
  StringWriter operator++(int)
  {
    assert(offset < str.size()); // we can go one behind
    StringWriter old{*this};
    offset++;
    return old;
  }

  bool operator==(char c) const
  {
    if (offset == str.size()) return c == 0;
    else return str[offset] == c;
  }

  explicit operator bool() const
  {
    return !operator==(0);
  }
};

StringWriter strstr(const StringWriter& haystack, const char *needle);
StringWriter& strcpy(StringWriter&, const StringWriter&);
StringWriter& strcpy(StringWriter&, const char*);
size_t strlen(const StringWriter& s); //< returns strlen(s.str.c_str())


#endif /* STRCLASS_H */
