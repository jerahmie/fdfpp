// main routine for fdfpp

#if defined(_MSC_VER)
  #define _WIN32_WINNT 0X0500
  #include<Windows.h>
#else
  #define PREAMBLE(X)
#endif


#include<cstdio>  // required for file*
#include "fdfpp.h"   // fdf library definition
#include<iostream> 


int main(int argc, char* argv[])
{
  std::cout << "Hello from C++." << std::endl;
  // create a new fdf file and fill it with something.
  FILE* myfdf = fdf_open_write("test_cpp.fdf", 0);
  fdf_close(myfdf);
  
  return EXIT_SUCCESS;
}
