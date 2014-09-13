StringWriter
============

I have written this class to solve a problem with old c-style c++ code like this:
```
void g(char *s) {
  if (!strncmp(s,"texta\n",6))
    s+=6;
  if ( *s == 0 )
    return;
  char *xs=strstr(s,"\n\n");
  if (!xs)
    return;
  char xxs=*xs;
  *xs=0;
  char ccs[1000];
  strcpy(ccs,s);
  *xs=xxs;
  s=xs+2;
  xs=strstr(s,"\n\n");
  if (!xs)
    return;
  s=xs+2;
  while (y<YMax && !end) {
    char *sb=s,*se=s;
    while (*se && *se!='\n' && *se!='\f')
      se++;
    if (*se=='\f' || !(*se))
      end=-1;
    int i=se-sb;
    if (i) {
      char xs=s[i];
      s[i]=0;
  ... // continues this way
}
```
What does this code? I have now clue. But I have to reduce the use of `char*` and replace
it by `std::string`. The first and best idea is of course to find out, how this code works and 
clean it up. But you know, in a commercial environment nobody pays for this and if this code is not 
mission critical and runs since ages... why care? 
So the basic idea is to refactor such code in two simple steps:
1. replace most occurences of `char *` with auto
2. replace the basic `char *` (in the above case it is the function param s) with the StringWriter
The StringWriter behaves like a `char *` (with some additional features like range checks), in 
addition I have written replacements for functions like strstr to work on StringWriter. 

Lets look at a simpler example (or just check the teststringwriter.cpp):
```
void g(char *s) 
{
  char *sc = s+3;
  *sc = 'a';
  while (char *scc = strstr(sc, "b"))
    *scc = 'c';
}
```
Now we take step 1:
```
void g(char *s) 
{
  auto sc = s+3;
  *sc = 'a';
  while (auto scc = strstr(sc, "b"))
    *scc = 'c';
}
```
That was easy and changed nothing, now step 2:
```
void g(string& str) 
{
  StringWriter s{str};
  auto *sc = s+3;
  *sc = 'a';
  while (auto *scc = strstr(sc, "b"))
    *scc = 'c';
}
```
Now ```g()``` takes a std::string and works as before. Except the range checking in StringWriter of course. 
For the given examples it may look like overkill. But I have got cases where I cannot wrap the call of g()
into a string version, because the additional copy was too expensive. So I first transformed it this way and 
later started the real refactoring. 
