#include "stringwriter.h"
#include <cstring>
#include <sstream>

StringWriter strstr(const StringWriter& haystack, const char *needle)
{
  auto idx = haystack.str.find(needle, haystack.offset);
  return StringWriter(haystack.str, idx);
}


StringWriter &strcpy(StringWriter &to, const StringWriter &from)
{
  unsigned i;
  while (1) {
    to[i] = from[i];
    if (to[i] == '\0') break;
    ++i;
  }
  return to;
}


StringWriter &strcpy(StringWriter &to, const char *from)
{
  if (from) {
    unsigned i=0;
    while (1) {
      to[i] = from[i];
      if (to[i] == '\0') break;
      ++i;
    }
  }
  return to;
}


size_t strlen(const StringWriter &s)
{
  return strlen(s.str.c_str()+s.offset);
}
