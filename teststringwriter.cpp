#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <iostream>
#include <cstring>
#include "stringwriter.h"

using namespace std;

template<typename T, typename FromString, typename ToString, typename ToCharPtr>
T& strtransform(const std::string& ref, T& str, FromString fs, ToString ts, ToCharPtr ptr)
{
  cout << "transform" << endl;
  fs(str,ref);
  BOOST_CHECK(ts(str) == ref);
  auto c1 = ptr(str);
  c1 += 4;
  auto c1x = c1 + 3;
  *c1 = 'x';
  *c1x = 'y';
  for(unsigned i=0; c1[i]; ++i)
    if (c1[i] == 'i') {
      c1[i] = 'a';
      //cout << i << endl;
    }
  while (auto c = strstr(c1, "\n")) {
    *c = '_';
  }
  //c1x[100] = 'z'; <-- will crash with char*, will checked with StringWriter
  BOOST_CHECK(ts(str) != ref);
  return str;
}

BOOST_AUTO_TEST_SUITE( StringWriter )

BOOST_AUTO_TEST_CASE(testStringWriter)
{
  std::string s{"This a text\nwith several line\nbreaks and some longer lines\n and shorter ones."};

  std::string s2;
  std::string s2x = strtransform(s, s2,
      [](std::string& str, const std::string& s){ str = s; },
      [](const std::string& s){ return s; },
      [](std::string& s){ return StringWriter(s,0); }
      );
  cout << s2 << endl;

  char *s3 = new char[s.size()+1];
  strtransform(s, s3,
      [](char *str, const std::string& s){ strcpy(str,s.c_str()); },
      [](char *s){ return std::string(s); },
      [](char *s){ return s; }
      );
  cout << s3 << endl;

  BOOST_CHECK(std::string(s3) == s2);
  BOOST_CHECK(s2 == s2x);
}

BOOST_AUTO_TEST_SUITE_END()

