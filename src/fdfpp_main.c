/* main routine for fdfpp */

#if defined(_MSC_VER)
  #define _WIN32_WINNT 0X0500
  #include<Windows.h>
#else
  #define PREAMBLE(X)
#endif

#include<stdio.h>
#include "fdf.h" 


int main(int argc, char* argv[])
{
FILE * myfdf;

myfdf = fdf_open_write("test_c.fdf", 0);
printf( "Hello.\n");
fdf_close(myfdf);
return 0;
}
