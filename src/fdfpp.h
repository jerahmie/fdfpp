// fdfpp.h
// C++ interface for fdf
//
// created by Jerahmie W. Radder, 22Mar2013.

#ifndef FDFPP_H_
#define FDFPP_H_

#if defined(_MSC_VER)
  #define _WIN32_WINNT 0X0500
  #include <Windows.h>
#else
  #define PREAMBLE(X)
#endif

#include <string>
#include "fdf.h"

class FdfPP
{
 public:
  FdfPP();
  //  FdfPP(const FdfPP &other); // copy constructor
  // FdfPP& operator=(const FdfPP& other) // assignment operator
  virtual ~FdfPP();

  void open(char *fname);
  void open(const std::string &fname);
  void openNoLink(char *fname);
  void openNoLink(const std::string &fname);
  void close();
  void openWrite(char* fname, long append);
  void openWrite(const std::string &fname, long append);
  long readData(long, void*);
//long seekEnd(long *nitems);
  long writeItem(long, char*, long, const int*, long, void*);
  long seekItem(long*, char*, long*, int*, long*, long*);
  long isLink(char*, long*);
//  long dataLength(long, const int*, long);
//  long readPreamble(char*, long*, int*, long*);  
// long typeNBytes();
//  long freadErr();
//  long fwriteErr();

private:
FILE* fp;
long err;
};

#endif // FDFPP_H_
