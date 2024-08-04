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
#include <strings.h>
#include <ipc.h>
#include <app.h>
#include <con.h>

void con_task()
{
  static char buffer[20],offset,busy;
  static struct ipc_msg request = { con_task, con_task, EVENT_READY };
  struct ipc_msg *reply = ipc_recv();

  switch(reply->event)
  {
    case EVENT_START:
      printf("con: console interface\n\n");
      busy = 1;      
      reply->event = EVENT_EXPIRE; /* forward startup message! */
      ipc_send(reply);
      
      break;

    case EVENT_EXPIRE:
      PTA2 ^= 1;
      ipc_send(reply); /* forward startup message again (loop) */
      
      if(request.event == EVENT_READY)
      {
        if(busy)
        {
          printf("# ");
          offset=busy=0;
        }
        if(SCRF)
        {
          buffer[offset]=getchar();
          if(offset==19||buffer[offset]=='\n'||buffer[offset]=='\r')
          {
            putchar('\n');
            buffer[offset]=0;
            busy = 1;
            if(!strcmp(buffer,"app"))
            {
              request.from  = con_task;
              request.to    = app_task;
              request.event = EVENT_START;
              request.body  = buffer;
              ipc_send(&request);
            }
            if(!strcmp(buffer,"clear"))
            {
              printf("\33[2J\33[H");
            }
            if(!strcmp(buffer,"dump"))
            {
              unsigned char i,j,*q=NULL,*p = NULL;

              for(i=0;i!=24;i++)
              {
                printf("%x: ",i);
                for(j=0;j!=16;j++,p++)
                {
                  printf("%x ",*p);
                }
                for(j=0;j!=16;j++,q++)
                {
                  if(*q>=32&&*q<128)
                  {
                    putchar(*q);
                  }
                  else
                  {
                    putchar('.');
                  }
                }
                putchar('\n');
              }
            }
          }
          else
          {
            offset++;
          }
        }
      }
      break;
  }
}
