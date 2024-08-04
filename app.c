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

#include <app.h>

void app_task()
{
  static struct ipc_msg *wait=NULL;
  static struct ipc_msg request;
         struct rtc_msg *rtc;

  struct ipc_msg *reply;
  
  reply = ipc_recv();

  switch(reply->event)
  {
    case EVENT_START:
      request.from  = app_task;
      request.to    = rtc_task;
      request.event = EVENT_READ;
      ipc_send(&request);
      wait = reply;
      break;

    case EVENT_REPLY:
      rtc = reply->body;
      if(rtc->day)
      {
         printf("app: %dd+%d:%d:%d\n",
           rtc->day,
           rtc->hour,
           rtc->min,
           rtc->sec);
      }
      else
      {
         printf("app: %d:%d:%d\n",
           rtc->hour,
           rtc->min,
           rtc->sec);      
      }
      wait->event = EVENT_READY;
      /* ipc_send(wait); */
      break;
  }
}
