/*
  Copyright (c) 2008, Marcelo Samsoniuk
  All rights reserved.
B 
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

#include <ipc.h>

volatile struct ipc_msg *ipc_queue_in  = NULL;
volatile struct ipc_msg *ipc_queue     = NULL;
volatile struct ipc_msg *ipc_queue_out = NULL;

void ipc_send(struct ipc_msg *msg) __critical   
{
  msg->next = NULL;
  if(ipc_queue_in)
  {
    ipc_queue_in->next = msg;
    ipc_queue_in = msg;
  }
  else
  {
    ipc_queue_in =  ipc_queue = msg;
  } 
}

struct ipc_msg *ipc_recv() __critical
{
  if((ipc_queue_out = ipc_queue))
  {  
    if(!(ipc_queue = ipc_queue->next))
    {
      ipc_queue_in = NULL;
    }
  }
  return ipc_queue_out;
}
