#pragma once

#include <string.h>

#define     ROM_0    -1
#define     ROM_1    -2
#define     ROM_2    -3
#define     ROM_3    -4
#define     ROM_4    -5
#define     ROM_5    -6
#define     ROM_6    -7
#define     ROM_7    -8
#define     ROM_8    -9
#define     ROM_9    -10
#define     ROM_A    -11
#define     ROM_B    -12
#define     ROM_C    -13
#define     ROM_D    -14
#define     ROM_E    -15
#define     ROM_F    -16

#define     RAM_0    0
#define     RAM_1    1
#define     RAM_2    2
#define     RAM_3    3
#define     RAM_4    4
#define     RAM_5    5
#define     RAM_6    6
#define     RAM_7    7
#define     RAM_8    8
#define     RAM_9    9
#define     RAM_A    10
#define     RAM_B    11
#define     RAM_C    12
#define     RAM_D    13
#define     RAM_E    14

/* a value in case we want any free page for acquire_page */

#define     FREE_PAGE 100

/* attempt to acquire page p (perhaps FREE_PAGE), returns 
 * p if success, -1 if unable to acquire */
int acquire_page(char p);
int release_page(char p);

void mm_init();
void *kmalloc(size_t sz);
void kfree(void *a);

void swapbank(signed char bank);
void bankcpy(char dbank, int dst, char sbank, int src, int cnt);
