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

#include <sci.h>

int putchar(char c) 
{
	while(!SCTE)
	{
		COPCTL = 0;
	}
	SCDR=c;
	
	if(c=='\n') 
	{	
		putchar('\r');
	}
	return c;
}

int getchar() 
{
	while(!SCRF)
	{
		COPCTL = 0;
	}	
	return putchar(SCDR);
}

/*
	HC908GR4 SCI configuration:
	
	SCP = 00    1*64 (*)
			= 01    3*64
			= 10    4*64
			= 11   13*64
			
	SCR = 000   1
			= 001   2
			= 010   4
			= 011   8
			= 100  16 (*)
			= 101  32
			= 110  64
			= 111 128
			
	(*) selected configuration for 9600 bps
*/

void sci_task()
{
	struct ipc_msg *reply = ipc_recv();
	
	switch(reply->event)
	{
		case EVENT_START:
			SCP1  = 0;	/* 00 = 1x64 */
			SCP0  = 0;
			SCR2  = 1;  /* 100 = 1x64x16 = 9600 bps */
			SCR1  = 0;
			SCR0  = 0;
			ENSCI	= 1;  /* enable SCI */
			TE	  = 1;	/* enable transmiter */
			RE	  = 1;	/* enable receiver */

			printf("\33[H\33[2JHC908 RTOS\n");
			printf("Copyright (c) 2008, Marcelo Samsoniuk\n");
      printf("All rights reserved.\n\n");
      printf("starting HC908 system...\n");
			printf("sci: serial interface 9600bps (polling)\n");
			break;
	}
}
