#define     DEBUG_PRINT     1

#define     MAJOR_VERSION   0
#define     MINOR_VERSION   1

#define     RAMSIZE         256 * 1024

#define     NPROC           14

/* kernel module page definitions   */

#define     KMOD_FS         RAM_E

/* base of process RAM */
#define     PBASE           0x100
#define     PTOP            0x8000

/* IO */

#define MPCL_RAM            0x78
#define MPCL_ROM            0x7C

#define UART0_BASE          0x68
#define UART0_TRB           UART0_BASE  /* transmit-receive buffer */
#define UART0_LSR           UART0_BASE + 5
