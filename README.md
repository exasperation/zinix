About
-----

This project (not yet named) is an attempt to write a small UNIX-ish
operating system for the N8VEM single-board computer.

The N8VEM has a Z80 w/ 256 KB of bank-switched RAM.

UNIX on that??  Well, the earliest UNIX editions back at AT&T in the 1970s
were written to run on PDP-11 machines with 64 or 128 kilowords of memory.

Those supported a dozen typists doing roff document typesetting.

(The PDP-8 could support 4 word processing users in 32 kword)

Architecture
------------

The memory management on the N8VEM is limited: there is a latch which controls
the address lines above 
