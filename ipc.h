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

#ifndef IPC_H
#define IPC_H

#include <main.h>

enum
{
  EVENT_IDLE,
  EVENT_START,
  EVENT_STOP,
  EVENT_EXPIRE,
  EVENT_READ,
  EVENT_WRITE,
  EVENT_REPLY,
  EVENT_READY
};

struct ipc_msg 
{
  volatile void (*from)(void);
  volatile void (*to  )(void);
  volatile char  event;
  volatile void *body;
  volatile struct ipc_msg *next;
};

volatile extern struct ipc_msg *ipc_queue_in;
volatile extern struct ipc_msg *ipc_queue;
volatile extern struct ipc_msg *ipc_queue_out;

extern void ipc_send(struct ipc_msg *);
extern struct ipc_msg *ipc_recv();

#endif
