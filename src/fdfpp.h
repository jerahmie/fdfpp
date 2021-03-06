// fdfpp.h
// C++ interface for fdf
//
// created by Jerahmie W. Radder, 22Mar2013.

#ifndef FDFPP_H_
#define FDFPP_H_

#if defined(_MSC_VER)
//  #define _WIN32_WINNT 0X0500
  #include <Windows.h>
#else
  #define PREAMBLE(X)
#endif

#include<string>
#include<vector>
#include "fdf.h"

namespace fdfpp
{

typedef enum fdfpp_file_type_tag{ t0dt_scaled, cp_info } fdfpp_file_type;

class FdfPP
{
 public:
  FdfPP();
  FdfPP(const FdfPP &other);                  // copy constructor
  FdfPP& operator=(const FdfPP& other);       // assignment operator
  FdfPP(fdfpp_file_type ft, const std::string &header, double zcv,
	double vpc, double t0, double dt, int nbits,
	const std::string &units,
	const std::vector<int> &dims); // constructor with init
  virtual ~FdfPP();

  void open(char *fname);
  void open(const std::string &fname);
  void openNoLink(char *fname);
  void openNoLink(const std::string &fname);
  void close();
  void openWrite(char* fname, long append);
  void openWrite(const std::string &fname, long append);
  void readData(long, void*);

  // setters
  void fileType(fdfpp_file_type);
  void header(const std::string &header);
  void units(const std::string &units);
  void zcv(double);
  void vpc(double);
  void t0(double);
  void dt(double);
  void nbits(int);
  void dims(const std::vector<int> &dims);
  void preamble(fdfpp_file_type ft, const std::string &header,
                double zcv, double vpc, double t0, double dt,
                int nbits, const std::string &units,
                const std::vector<int> &dims);

  // getters
  fdfpp_file_type fileType(void);
  std::string header(void) const;
  std::string units(void) const;
  double zcv(void);
  double vpc(void);
  double t0(void);
  double dt(void);
  int nbits(void);
  std::vector<int> dims(void) const;
  
//long seekEnd(long *nitems);
  void writeItem(long append, char *name, long ndims , const int *dims,
                 long type, void *data);
  void writeT0DTScaledData(long fdf_type, void* data);
  void seekItem(long *item, char *name, long *ndims , int *dims,
                long *type, long *nbytes);
  void isLink(char*, long*);
//  long dataLength(long, const int*, long);
//  long readPreamble(char*, long*, int*, long*);  
//  long typeNBytes();
//  long freadErr();
//  long fwriteErr();
  void readT0DT_Scaled(void* data);
private:
  void writeT0DTScaledPreamble(void);

  FILE* fp_;
  long err_;
  fdfpp_file_type fdfpp_file_type_;    // 't0dt_scaled' or 'cp_info'
  std::string  header_, units_;
  double zcv_, vpc_, t0_, dt_;
  int nbits_;
  std::vector<int> dims_;
};
}
#endif // FDFPP_H_

