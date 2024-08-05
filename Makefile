# Copyright (c) 2008, Marcelo Samsoniuk
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#
#     * Neither the name of the copyright holder nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER 'AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

ARCH    = hc908
FORMAT  = S19
SRCS    = main.c sci.c rtc.c con.c app.c ipc.c stdio.c strings.c
OBJS    = $(SRCS:%.c=%.rel)
DEPS    = $(SRCS:%.c=%.h) Makefile
TARGET  = $(ARCH)rtos.$(FORMAT)

CC      = sdcc
INCS    = -I.
CFLAGS  = -mhc08 --profile --data-loc 0x40 --stack-loc 0x1BF --code-loc 0xEE00 $(INCS)
LDFLAGS = -mhc08 --profile --data-loc 0x40 --stack-loc 0x1BF --code-loc 0xEE00

%.rel: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

install: $(TARGET)
	hc908sh /dev/ttyS0 -start -erase -upload $(TARGET) -end

clean:
	rm -f *.{S19,asm,lnk,lst,map,mem,rel,rst,sym,o,cdb,lk}
