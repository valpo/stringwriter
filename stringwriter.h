#ifndef STRCLASS_H
#define STRCLASS_H

#include <string>
#include <string.h>
#include <iosfwd>
#include <cassert>

/** StringWriter wraps a std::string into an object which looks like a c-string char* */
class StringWriter
{
public:
  using size_type = std::string::size_type;
  static const size_type npos = std::string::npos;
  friend StringWriter strstr(StringWriter& haystack, const char *needle);
private:
  std::string& str; //< the string we working on
  size_type offset; //< the current offset in this string
public:
  StringWriter(std::string& s, size_type i =0)
    : str(s), offset(i)
  {}
  StringWriter operator[](size_type i)
  {
    assert(i <= str.size());
    return StringWriter(this->str, offset+i);
  }

  StringWriter operator+=(size_type i)
  {
    offset += i;
    return *this;
  }

  StringWriter operator+(size_type i)
  {
    return StringWriter(this->str, offset+i);
  }

  StringWriter& operator*()
  {
    return *this;
  }

  StringWriter& operator=(char c)
  {
    assert(offset < str.size());
    str[offset] = c;
    return *this;
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

StringWriter strstr(StringWriter& haystack, const char *needle);

#endif /* STRCLASS_H */
