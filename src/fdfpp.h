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


typdef enum fdf_file_type_tag{ fdf_t0dt_scaled, cp_info} fdf_file_type;

class FdfPP
{
 public:
  FdfPP();
  //  FdfPP(const FdfPP &other); // copy constructor
  // FdfPP& operator=(const FdfPP& other) // assignment operator
  FdfPP::FdfPP(fdfpp_file_type, const std::string &header, double,
                double, double, double, int, const std::string &units,
               const std::vector<int> &dims); // constructor with init
  virtual ~FdfPP();

  void open(char *fname);
  void open(const std::string &fname);
  void openNoLink(char *fname);
  void openNoLink(const std::string &fname);
  void close();
  void openWrite(char* fname, long append);
  void openWrite(const std::string &fname, long append);
  long readData(long, void*);
  long preamble(fdfpp_file_type, const std::string &header,
                double, double, double, double,
                int, const std::string &units,
                const std::vector<int> &dims);
//long seekEnd(long *nitems);
  long writeItem(long, char*, long, const int*, long, void*);
  long writeData(long, void*);
  long seekItem(long*, char*, long*, int*, long*, long*);
  long isLink(char*, long*);
//  long dataLength(long, const int*, long);
//  long readPreamble(char*, long*, int*, long*);  
// long typeNBytes();
//  long freadErr();
//  long fwriteErr();

private:
  long writeHeader(void);
  FILE* fp_;
  long err_;
  fdf_file_type fdfpp_file_type_;    // 't0dt_scaled' or 'cp_info'
  std::string  header_, units_;
  double zcv_, vpc_, t0_, dt_;
  int nbits_;
};

#endif // FDFPP_H_

