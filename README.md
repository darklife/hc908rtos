# HC908 RTOS

This is an early and experimental RTOS for HC908 microcontrollers. It was
released some years ago on Sourceforge on the framework.sf.net project, but
for some reason the project was removed by Sourceforge, so I located an
early wget from the site, cleaned the sf.net files and released here again!

# Features

Designed back in 2008, it includes:
- cooperative multitasking
- state machine based tasks
- task switching based on message passing
- inter-process messages
- interrupt support

# History & Motivation

I worked many years with the HC908 but with single-task applications, so I
was wondering the possibility of support multitasking. Because the small
memory footprint (256bytes of RAM!), preemptive multitasking with separated
stack per task appeared not possible, instead a more simple cooperative
multitasking was proposed.

In order to reach this, I tested lots of different configurations until
reached the concept of state machine tasks, in a way that messages are
passed to the tasks and the tasks will change the states according to that
messages. With some additional complexity, tasks can handle different
requests from different source tasks, in a way there is a flow of requests
and replies. The scheduller is very simple, basically get message by message
from a message queue and wakeup the respective task.

Since there is a message queue, tasks can send any number of messages
between zero and the max message size in the queue, which means a single
task can activate multiple other tasks in sequence.

Finally, interrupts were added in the way only the basic peripheral handling
is done in the interrupt level, typically packing any data or event in the
form of message, so normal tasks can handle it outside the interrupt time.

# Development System

The RTOS was designed to be compiled with SDCC. An additional tool called
hc908sh was part of it, but did not find it yet, so someone trying test it
on real hc908 will probably need another tool to program the
microcontroller. Anyway, the code is supposed to work!

# Conclusion

Back in 2024, the HC908 RTOS was long time lost and forgotten until I read 
an article about the RIOS RTOS:

    https://www.cs.ucr.edu/~vahid/pubs/wese12_rios.pdf

Future directions may be port it to RISC-V, in order to continue the
development with the same concepts!
