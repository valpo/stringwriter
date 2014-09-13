#include "stringwriter.h"
#include <sstream>

StringWriter strstr(StringWriter& haystack, const char *needle)
{
  auto idx = haystack.str.find(needle, haystack.offset);
  return StringWriter(haystack.str, idx);
}
