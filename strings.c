/*
        Copyright (c) 2005, Infralogic Informatica Ltda
        Copyright (c) 2008, Marcelo Samsoniuk
        All rights reserved.

        Redistribution and use in source and binary forms, with or without
        modification, are permitted provided that the following conditions
        are met:

            * Redistributions of source code must retain the above copyright
              notice, this list of conditions and the following disclaimer.

            * Redistributions in binary form must reproduce the above
              copyright notice, this list of conditions and the following
              disclaimer in the documentation and/or other materials
              provided with the distribution.

            * Neither the name of the Infralogic Informatica Ltda nor the
              names of its contributors may be used to endorse or promote
              products derived from this software without specific prior
              written permission.

        THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
        "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
        LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
        FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
        COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
        INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
        BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
        LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
        CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
        LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
        ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
        POSSIBILITY OF SUCH DAMAGE.
*/

#include <strings.h>

#ifndef _HC908RTOS_STRINGS_
#define _HC908RTOS_STRINGS_

int strcmp(char *p, char *q)
{
  while(*p && *p == *q)
    p++, q++;
        
  return *p - *q;
}

int strcpy(char *p, char *q)
{
  int i;

  for(i=0;p[i]=q[i];i++)
    ;     
  return i;
}

int strlen(char *p)
{
  int i;
  
  for(i=0;p[i];i++)
    ;
  return i;
}

#endif
