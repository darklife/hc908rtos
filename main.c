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

#include <main.h>

void main()
{
  static struct ipc_msg msg[] = 
  {
    { main, sci_task, EVENT_START },
    { main, rtc_task, EVENT_START },
    { main, con_task, EVENT_START },
    { NULL }
  };

  char task;

  /* clean watchdog timer */
  wtd_clean();

  /* start rtos tasks */
  for(task=0;msg[task].from;task++)
  {
    /* send EVENT_START */
    ipc_send(&msg[task]);
  }

  /* enable interrupts */
  isr_start();

  /* start rtos scheduler */
  for(;;)
  {
    /* clean watchdog timer */
    wtd_clean();
    /* test message queue */
    if(ipc_queue)
    {
      /* run task */
      ipc_queue->to();
    }
    /* stop and wait for interrupt */
    // isr_wait();
  }
}
