#define     setb(A,k)     ( A[(k/8)] |= (1 << (k%8)) )
#define     clrb(A,k)   ( A[(k/8)] &= ~(1 << (k%8)) )            
#define     tstb(A,k)     ( A[(k/8)] & (1 << (k%8)) )
