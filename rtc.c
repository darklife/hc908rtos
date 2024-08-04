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

#include <rtc.h>

void rtc_isr(void) interrupt 17
{
  static struct ipc_msg msg = { NULL, rtc_task, EVENT_READY }; 

  TACK  = 1;
  
  if(msg.event == EVENT_READY)
  {
    msg.event = EVENT_EXPIRE;
    ipc_send(&msg);
  }
  else
  {
    PTA1 ^= 1; /* buffer busy */
  }
}

void rtc_task()
{

  static struct rtc_msg rtc = { 0, 0, 0, 0 };
  static int    tic=0; 

  struct ipc_msg *reply = ipc_recv();

  switch(reply->event)
  {
    case EVENT_START:
      TBR0    = 0;
      TBR1    = 0;
      TBR2    = 0;
      TBON    = 1;
      TBIE    = 1;
      DDRA    = 0xf;
      printf("rtc: realtime clock 305Hz\n");
      break;

    case EVENT_STOP:
      TBON    = 0;
      TBIE    = 0;
      printf("rtc: realtime clock stop\n");
      break;

    case EVENT_EXPIRE:
      reply->event = EVENT_READY;
      if(++tic==305)
      {
        tic=0;
        PTA0 ^= 1;

        if(++rtc.sec==60)
        {
          rtc.sec = 0;
          if(++rtc.min==60)
          {
            rtc.min=0;
            if(++rtc.hour==24)
            {
              rtc.hour=0;
              ++rtc.day;
            }
          }
        }
      }
      break;

    case EVENT_READ:
      reply->to    = reply->from;
      reply->from  = rtc_task;
      reply->event = EVENT_REPLY;
      reply->body  = &rtc;
      ipc_send(reply);
      break;
  }
}
