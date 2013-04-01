// fdfpp.cpp
// C++ interface for fdf
//
// created by Jerahmie W. Radder, 22Mar2013.
//

#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include "fdfpp.h"


FdfPP::FdfPP()
{
  // FdfPP constructor
  // initialize err_
  err_ = 0;
  fp_ = NULL;
}

FdfPP::~FdfPP()
{
  // FdfPP destructor
}

// Copy Constructor
// FdfPP::FdfPP(const FdfPP &other){}

// Assignment Operator
// FdfPP & FdfPP::operator=(const FdfPP &other){}

// Constructor with initialization
//FdfPP::FdfPP(fdfpp_file_type ft, const std::string &header, double zcv,
//             double vpc, double t0, double dt, int nbits,
//             const std::string &units, const std::vector<int> &dims)
//{
//  fdfpp_file_type_ = ft;
//  header_ = header;
//  zcv_ = zcv;
//  vpc_ = vpc;
//  t0_ = t0;
//  dt_ = dt;
//  nbits_ = nbits;
//  units_ = units;
//  dims_ = dims;  
//}

  
// fdf functions
void FdfPP::open(char *fname)
{
  /// open fdf file read-only
  fp_ = fdf_open(fname);
}

void FdfPP::open(const std::string &fname)
{
  /// open fdf file read-only
  fp_ = fdf_open(const_cast <char *>(fname.c_str()));
}

void FdfPP::openNoLink(char *fname)
{
  fp_ = fdf_open_nolink(fname);
}

void FdfPP::openNoLink(const std::string &fname)
{
  fp_ = fdf_open_nolink(const_cast <char *>(fname.c_str()));
}

void FdfPP::openWrite(char* fname, long append)
{
  /// open fdf file for writing ("r+w")
  fp_ = fdf_open_write(fname,append);
}

void FdfPP::openWrite(const std::string &fname, long append)
{
  /// open fdf file for writing ("r+w")
  fp_ = fdf_open_write(const_cast <char *>(fname.c_str()),append);
  std::cout << "open_write()" << std::endl;
}

void FdfPP::close()
{
  /// close our fdf file
  fdf_close(fp_);
  std::cout << "close()" << std::endl;
}

long FdfPP::readData(long nbytes, void *data)
{
  /// read data from our fdf file
  long fdf_data_read_status = fdf_read_data(fp_, nbytes, data, err_);
  return(fdf_data_read_status);
  
}

//long FdfPP::seekEnd(long *nitems)
//{
//  long seek_end_status = fdf_seek_end(fp_, nitems, err_);
//  return(seek_end_status);
//}


// setters and getters 
void FdfPP::fileType(fdfpp_file_type ft)
{
  /// set the fdf filetype: fdfpp_file_type fdf_t0dt_scaled or
  /// fdfpp_file_type cp_info
  fdfpp_file_type_ = ft;
}

void FdfPP::header(const std::string &header)
{
  /// set the header, a string of up to 64 characters
  /// (over 64 characters will be truncated)
  header_ = header;
}

void FdfPP::units(const std::string &units)
{
  /// set the signal units (i.e. 'volts') 
  units_ = units;
}

void FdfPP::zcv(double zcv)
{
  /// set the 'zero club voltage', which is just the offset 
  zcv_ = zcv;
}

void FdfPP::vpc(double vpc)
{
  /// set 'volts per count' to convert from integer data to voltage
  vpc_ = vpc; 
}

void FdfPP::t0(double t0)
{
  /// set t0, the time of the first sample
  t0_ = t0;
}

void FdfPP::dt(double dt)
{
  /// set dt, the sample interval
  // this should be positive double value, greater than 0.0
  if (dt > 0.0)
    dt_ = dt;
}

void FdfPP::nbits(int nbits)
{
  /// set the number of significant bits in the data.  for NI digitizers: 12
  /// for Innovative Integration X3-10M: 16
  if ( nbits > 0 )
    nbits_ = nbits;
}

void FdfPP::dims(const std::vector<int> &dims)
{
  /// set dims, a vector containing the dimensions of the data.
  dims_ = dims;
}

void FdfPP::preamble(fdfpp_file_type ft, const std::string &header,
                     double zcv, double vpc, double t0, double dt,
                     int nbits, const std::string &units,
                     const std::vector<int> &dims)
{
  /// set entire preamble with one command, which is convenient when writing
  /// C++ applications
  fdfpp_file_type_ = ft;
  header_ = header;
  zcv_ = zcv;
  vpc_ = vpc;
  t0_ = t0;
  if ( dt > 0.0 )
    dt_ = dt;
  if ( nbits > 0 )
    nbits_ = nbits;
  units_ = units;
  dims_ = dims;
}


// getters
fdfpp_file_type FdfPP::fileType(void)
{
  return(fdfpp_file_type_);
}

std::string FdfPP::header(void) const
{
  return(header_);
}

std::string FdfPP::units(void) const
{
  return(units_);
}

double FdfPP::zcv(void)
{
  return(zcv_);
}

double FdfPP::vpc(void)
{
  return(vpc_);
}

double FdfPP::t0(void)
{
  return(t0_);
}

double FdfPP::dt(void)
{
  return(dt_);
}

int FdfPP::nbits(void)
{
  return(nbits_);
}

std::vector<int> FdfPP::dims(void) const
{
  return(dims_);
}


long FdfPP::writePreamble(void)
{
  /// format the fdf preamble and write to file
  /// FDF preamble items are 64 bits in length and need to be blanked before
  /// writing to the target fdf file.
  /// This is performed using low-level C-style memory manipulation routines
  /// memset() and memcpy() on a buffer before calling the low-level
  /// fdf_write_item() function
  long fdf_status = 0;
  long *pdim_header_item_name_length;

  *pdim_header_item_name_length = FDF_ITEMNAME_LENGTH;
  
  const char* fdfname_str = "filetype";
  char * filetype_str;
  if ( fdfpp_file_type_ == t0dt_scaled)
    {
      filetype_str = "t0dt_scaled";
    }
  else
    {
      filetype_str = "cp_info";
    }

  char fdfname[FDF_ITEMNAME_LENGTH];
  char filetype[FDF_ITEMNAME_LENGTH];  
  memset(&fdfname, 0x0, FDF_ITEMNAME_LENGTH);
  memset(&filetype, 0x0, FDF_ITEMNAME_LENGTH);
  memcpy(&fdfname, fdfname_str, strlen(fdfname_str));
  memcpy(&filetype, filetype_str, strlen(filetype_str));
//
//  // write the fdf file type item
//  fdf_status = fdf_write_item(fp_, 0, fdfname, 1,
//                              pdim_header_item_name_length,
//                              fdf_char, (void*)filetype, err_);
  return(fdf_status);
}
// long FdfPP::writeData(long fdf_type, void* data)
// {
// // check for valid header, write header, then write data
// }



long FdfPP::writeItem(long append, char* name, long ndims, const int *dims,
                      long type, void *data)
{
  long fdf_write_status = fdf_write_item(fp_, append, name,
                                         ndims, dims, type, data, err_);
  return(fdf_write_status);
}
//long FdfPP::writeItem(long append, const std::string &name, )
long FdfPP::seekItem(long *item, char *name, long *ndims, int *dims,
                     long *type, long *nbytes)
{
  long fdf_seek_item_status = fdf_seek_item(fp_, item, name,
                                            ndims, dims, type, nbytes,err_);
    return(fdf_seek_item_status);
}

long FdfPP::isLink(char *fname, long *islink)
{
  long fdf_is_link_status = fdf_is_link(fname, islink);
  return(fdf_is_link_status);
}

//long FdfPP::dataLength(long ndims, const int *dims, long type)
//{
//  long fdf_data_length_status = fdf_data_length(ndims, dims, type);
//  return(fdf_data_length_status);
//}

//long FdfPP::readPreamble(char* name, long *ndims, int *dims, long *type)
//{
//  long fdf_read_preamble_status = fdf_read_preamble(fp, name, ndims,
//                                                  dims, type, err_);
//  return(fdf_read_preamble_status);
//  
//}

// long FdfPP::typeNBytes(long type)
// {
// 
// }
// 
// long FdfPP::freadErr(void *buff, size_t size, size_t count)
// {
// 
// }
// 
// long FdfPP::fwriteErr(const void *buff, size_t size, size_t count)
// {
// 
// }
