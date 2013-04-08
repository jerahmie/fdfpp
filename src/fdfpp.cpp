// fdfpp.cpp
// C++ interface for fdf
//
// created by Jerahmie W. Radder, 22Mar2013.
//

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include "fdfpp.h"


FdfPP::FdfPP()
{
  // FdfPP constructor
  // initialize err_
  err_ = 0;
  fp_ = NULL;
  fdfpp_file_type_ = t0dt_scaled;   // most common fdf file type
  header_ = "";
  units_ = "";
  zcv_ = 0.0;
  vpc_ = 0.0;
  t0_ = 0.0;
  dt_ = 0.0;
  nbits_ = 32;
}

FdfPP::~FdfPP()
{
  // FdfPP destructor
}

// Copy Constructor
FdfPP::FdfPP(const FdfPP &other)
  : err_(other.err_),
    fdfpp_file_type_(other.fdfpp_file_type_),
    header_(other.header_),
    units_(other.units_),
    zcv_(other.zcv_),
    vpc_(other.vpc_),
    t0_(other.t0_),
    dt_(other.dt_),
    nbits_(other.nbits_),
    dims_(other.dims_)
{
  fp_ = NULL;
}

// Assignment Operator
FdfPP & FdfPP::operator=(const FdfPP &other)
{
  if (this != &other)
    {
      fp_ = NULL;  // do not copy the file pointer, only the fdfpp member data
      err_ = 0; // other object error state is not tracked
      fdfpp_file_type_ = other.fdfpp_file_type_;
      header_ = other.header_;
      units_ = other.units_;
      zcv_ = other.zcv_;
      vpc_ = other.vpc_;
      t0_ = other.t0_;
      dt_ = other.dt_;
      nbits_ = other.nbits_;
      dims_ = other.dims_;      
    }
  return *this;
}

// Constructor with initialization
FdfPP::FdfPP(fdfpp_file_type ft, const std::string &header, double zcv,
             double vpc, double t0, double dt, int nbits,
             const std::string &units, const std::vector<int> &dims)
{
  fdfpp_file_type_ = ft;
  header_ = header;
  zcv_ = zcv;
  vpc_ = vpc;
  t0_ = t0;
  dt_ = dt;
  nbits_ = nbits;
  units_ = units;
  dims_ = dims;  
}

  
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


void FdfPP::writeT0DTScaledPreamble(void)
{
  /// format the fdf preamble and write to file
  /// FDF preamble items are 64 bits in length and need to be blanked before
  /// writing to the target fdf file.
  /// This is performed using low-level C-style memory manipulation routines
  /// memset() and memcpy() on a buffer before calling the low-level
  /// fdf_write_item() function

  int dim_header_item_name_length;
  int *pdim_header_item_name_length;

  const char* fdfname_str = "filetype";
  char * filetype_str;
  if ( fdfpp_file_type_ == t0dt_scaled)
    {
      filetype_str = "t0dt_scaled";
    }

  char buffer[FDF_ITEMNAME_LENGTH];
  std::cout << "FDF_ITEMNAME_LENGTH: " << FDF_ITEMNAME_LENGTH << std::endl;
  std::cout  << "strlen(buffer): " << strlen(buffer) << std::endl;
  memset(&buffer, 0, FDF_ITEMNAME_LENGTH);
  memcpy(&buffer, fdfname_str, strlen(fdfname_str));
  std::cout  << "strlen(buffer): " << strlen(buffer) << std::endl;
  std::cout << "strlen(fdfname_str): " << strlen(fdfname_str) << std::endl;
  // write the fdf file type item
  dim_header_item_name_length = strlen(filetype_str);
  pdim_header_item_name_length = &dim_header_item_name_length;
  err_ = fdf_write_item(fp_, 0, buffer, 1,
                        pdim_header_item_name_length,
                        fdf_char, (void*)filetype_str, err_);
  // write the header
  memset(&buffer, 0, FDF_ITEMNAME_LENGTH);
  memcpy(&buffer, "header", strlen("header"));
  dim_header_item_name_length = header_.length();
  std::cout << "header_length: " << dim_header_item_name_length
	    << " " << *pdim_header_item_name_length<< std::endl;
  err_ = fdf_write_item(fp_, 1, buffer, 1,
                        pdim_header_item_name_length,
                        fdf_char, (void*)header_.c_str(), err_);
  std::cout << (void *)header_.c_str() << std::endl;
  std::cout << header_.c_str() << std::endl;
  // zcv
  memset(&buffer, 0, FDF_ITEMNAME_LENGTH);
  memcpy(&buffer, "zcv", strlen("zcv"));
  dim_header_item_name_length = 1;
  err_ = fdf_write_item(fp_, 1, buffer, 1,
                        pdim_header_item_name_length,
                        fdf_double, (void*)&zcv_, err_);

  // vpc
  memset(&buffer, 0, FDF_ITEMNAME_LENGTH);
  memcpy(&buffer, "vpc", strlen("vpc"));
  dim_header_item_name_length = 1;
  err_ = fdf_write_item(fp_, 1, buffer, 1,
                        pdim_header_item_name_length,
                        fdf_double, (void*)&vpc_, err_);  
  // t0
  memset(&buffer, 0, FDF_ITEMNAME_LENGTH);
  memcpy(&buffer, "t0", strlen("t0"));
  dim_header_item_name_length = 1;
  err_ = fdf_write_item(fp_, 1, buffer, 1,
                        pdim_header_item_name_length,
                        fdf_double, (void*)&t0_, err_);    
  // dt
  memset(&buffer, 0, FDF_ITEMNAME_LENGTH);
  memcpy(&buffer, "dt", strlen("dt"));
  dim_header_item_name_length = 1;
  err_ = fdf_write_item(fp_, 1, buffer, 1,
                        pdim_header_item_name_length,
                        fdf_double, (void*)&dt_, err_);      
  // nbits
  memset(&buffer, 0, FDF_ITEMNAME_LENGTH);
  memcpy(&buffer, "nbits", strlen("nbits"));
  dim_header_item_name_length = 1;
  err_ = fdf_write_item(fp_, 1, buffer, 1,
                        pdim_header_item_name_length,
                        fdf_i32, (void*)&nbits_, err_);      
  
  // units
  memset(&buffer, 0, FDF_ITEMNAME_LENGTH);
  memcpy(&buffer, "units", strlen("units"));
  dim_header_item_name_length = units_.length();
  err_ = fdf_write_item(fp_, 1, buffer, 1,
                        pdim_header_item_name_length,
                        fdf_char, (void*)units_.c_str(), err_);  
}

void FdfPP::writeT0DTScaledData(long fdf_type, void* data)
{
  // check for valid preamble, write preamble, then write data
  writeT0DTScaledPreamble();
  std::cout << "after write preamble()" << std::endl;
  char buffer[FDF_ITEMNAME_LENGTH];
  memset(&buffer, 0, FDF_ITEMNAME_LENGTH);
  memcpy(&buffer, "data", strlen("data"));
  long ndims = dims_.size();
  int* dims;
  std::cout << "before memory allocation" << std::endl;
  // allocate memory for dimensions structure and populate from member
  // variable dims_
  dims = (int*) malloc(ndims * sizeof(int)); 
  std::cout << "ndims: " << ndims << std::endl;
  for (int indx=0; indx<ndims; indx++)
    {
      std::cout << "indx: " << indx << std::endl;
      dims[indx] = dims_[indx];
    }
  std::cout << "after fill array" << std::endl;
  //let's just check the result
  for (int jndx=0; jndx<ndims; jndx++)
    {
      std::cout << "dims["  << jndx << "]: " << dims[jndx] << std::endl;
    }
  
  err_ = fdf_write_item(fp_, 1, buffer, ndims,
                        dims, fdf_double, data, err_);
}

void FdfPP::readPreamble(void)
{
  // load header data from an open fdf file
  int *dims;
  dims = new int[FDF_MAXDIMS];
  char *name;
  name = new char[FDF_ITEMNAME_LENGTH];
  //  char *pname = &name;
  long ndims, type, nbytes;
  long *nitems;
  void* data_buffer;
  nitems = new long[1];
  err_ = fdf_seek_end( fp_, nitems, err_ );
  std::cout << "readPreamble(): nitems: " << *nitems << std::endl;
  for (long item = 0; item < *nitems; item++)
    {
      seekItem(&item, name, &ndims, dims, &type, &nbytes);
      std::cout << "nbytes: " << nbytes << std::endl;
      // allocate temporary c-style buffer
      data_buffer = malloc(nbytes);
      readData(nbytes, data_buffer);      
      // set appropriate member variable
      if (std::strcmp(name, "filetype") == 0)
        {

          if (std::strcmp((char *)data_buffer, "t0dt_scaled") == 0)
            {
              fdfpp_file_type_ = t0dt_scaled;
            }
          else if (std::strcmp((char *)data_buffer, "cp_info") == 0)
            {
              fdfpp_file_type_ = cp_info;
            }
          else
            std::cout << "Invalid FDF file type detected." << std::endl;
            
        }
      else if (std::strcmp(name, "header") == 0)
        {
          std::stringstream header_ss;
          header_ss << (char*) data_buffer;
          header_ = header_ss.str();
        }
      else if (std::strcmp(name, "zcv") == 0)
        {
          zcv_ = *((double*) data_buffer);
        }
      else if (std::strcmp(name, "vpc") == 0)
        {
          vpc_ = *((double*) data_buffer);
        }
      else if (std::strcmp(name, "t0") == 0)
        {
          t0_ = *((double*) data_buffer);
        }
      else if (std::strcmp(name, "dt") == 0)
        {
          dt_ = *((double*) data_buffer);
        }      
      else if (std::strcmp(name, "nbits") == 0)
        {
          nbits_ = *((int*)data_buffer);
        }
      else if (std::strcmp(name, "units") == 0)
        {
          std::stringstream units_ss;
          units_ss << (char*) data_buffer;
          units_ = units_ss.str();
        }      
      else
        std::cout << "could not determine value" << std::endl;
    }
  delete nitems;
  delete name;
  delete dims;
  // free the c-style memory 
  free(data_buffer);
}

void FdfPP::writeItem(long append, char* name, long ndims, const int *dims,
                      long type, void *data)
{
  err_ = fdf_write_item(fp_, append, name,
                 ndims, dims, type, data, err_);

}
//long FdfPP::writeItem(long append, const std::string &name, )
void FdfPP::seekItem(long *item, char *name, long *ndims, int *dims,
                     long *type, long *nbytes)
{
  err_ = fdf_seek_item(fp_, item, name,
                       ndims, dims, type, nbytes,err_);
}

void FdfPP::isLink(char *fname, long *islink)
{
  err_ = fdf_is_link(fname, islink);
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
