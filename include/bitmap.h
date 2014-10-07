#define     setb(A,k)     ( A[(k/8)] |= (1 << (k%8)) )
#define     clrbit(A,k)   ( A[(k/8)] &= ~(1 << (k%8)) )            
#define     tstb(A,k)     ( A[(k/8)] & (1 << (k%8)) )
