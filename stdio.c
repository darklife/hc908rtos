/*
  Copyright (c) 2008, Marcelo Samsoniuk
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

      * Neither the name of the copyright holder nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER 'AS IS'' AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>

int gets(char *p, int max)
{
  int i=0;

  while((p[i] = getchar()) != '\r' && i < max - 2)
  {
    if((p[i]==127||p[i]=='\b'))
    {
      if(i)
        i--;
    }
    else
      i++;
  }
  putchar('\n');  
  p[i] = 0;
  
  return i;
}

int putstr(char *s)
{
  int i, j;

  for (i = 0; (j = s[i]); i++)
    putchar(j);
    
  return i;
}

int puts(char *s)
{
  int i = putstr(s);

  putchar('\n');

  return i + 1;
}

char *itostr(unsigned int i, char base)
{
  const char  *hex = "0123456789abcdef";
  static char tmp[sizeof(int)*8+1];
  char   j,k;

  tmp[j = sizeof(int)*8]=0;

  if(i)
  {
    for (k=0; i; i=i/base, k++)
      tmp[--j] = hex[i%base];
  }
  else
  {
    tmp[--j] = '0';
    k=1;
  }
  while(j&1)
  {
    tmp[--j] = '0';
  }

  return tmp + j;
}

int strtoi(char *p,char base)
{
  const char  *hex = "0123456789abcdef";
  int   i,j;
  
  for(i=0;*p;p++)
  {
    i=i*base;
    for(j=0;j!=base;j++)
      if(hex[j]==*p)
        i+=j;
  }    
  return i;  
}

int printf(const char *fmt, ...)
{
  int i, inside=0;
  char **p = (char **) &fmt;

  for (i = 0; fmt[i]; i++)
  {
    if (inside) 
    {
      if (fmt[i] == 's')
        putstr(*++p);
      else if (fmt[i] == 'd')
        putstr(itostr((int) *++p,10));
      else if (fmt[i] == 'x')
        putstr(itostr((int) *++p,16));
      else if (fmt[i] == 'b')
        putstr(itostr((int) *++p,2));
      inside = 0;
    } 
    else 
    {
      if (fmt[i] == '%')
        inside = 1;
      else
        putchar(fmt[i]);
    }
  }
  return i;
}
