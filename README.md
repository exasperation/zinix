About
-----

This project (not yet named) is an attempt to write a small UNIX-ish
operating system for the N8VEM single-board computer.

In the process, I hope to help document the N8VEM hardware and architecture.

The N8VEM has a Z80 w/ 256 KB of bank-switched RAM.

Wait, UNIX on that?  Well, the earliest UNIX editions back at AT&T in the 1970s
were written to run on PDP-11 machines with 64 or 128 kilowords of memory.

Those supported a dozen typists doing roff document typesetting.

(The PDP-8 could support 4 word processing users in 32 kword)

Requirements
------------

Sadly, I don't actually have an N8VEM working yet.  When I acquire the hardware and have it
running reliably, I hope to port from the simh-altair simulator to the real deal. :)

At current:

* SDCC 3.3+
* srecord
* gmake, etc.
* the altair-z80 simulator with n8vem support
* a copy of the N8VEM ROM (it's open source, you can download it freely)

I hope to support most common N8VEM configurations in some way.  The absolute
minimum requirement would be some form of regular interrupt (Zilog peripherals board or some kind
of divider chip tied into the irq line) and the uart.

Ports to similar Z80 system should be relatively straightforward.

Architecture
------------

The memory management on the N8VEM is limited: there is a latch which drives
the high address lines (A15+) of the ROM/RAM chip, and a ROM/RAM toggle on bit 7 (from bit 0).

This pages the ROM/RAM into the lower half 0000-7FFF of the 64 KB of the Z80.

The upper half 8000-FFFF is fixed to the high page of the RAM.

The lower page is either kernel data or a process's 32 KB of address space.  User processes are restricted
to the address range of 0100-7FFF.  Conventionally, the process stack is at top of process memory.

Process entry point is 0100.

The zero page 0000-0100 unfortunately contains the Z80 interrupt and reset vectors.  On boot and
during process initialization, a template zeropage (see zpage.s) is copied here.  User applications
must not alter any address below 0100.

SBC Mk. IV
----------

The SBC-IV is based on the Z180 processor which has an integrated MMU.  A port should be straightforward, and 
could either emulate the N8VEM architecture, or even extend process ram to ffff: kernel could be swapped in
in the ISR routine.
