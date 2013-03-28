// fdfpp.cpp
// C++ interface for fdf
//
// created by Jerahmie W. Radder, 22Mar2013.
//

#include<cstdio>
#include<iostream>
#include<string>
#include "fdfpp.h"


FdfPP::FdfPP()
{
  // FdfPP constructor
  // initialize err
  err = 0;
}

FdfPP::~FdfPP()
{
  // FdfPP destructor
}

// Copy Constructor
// FdfPP::FdfPP(const FdfPP &other){}

// Assignment Operator
// FdfPP & FdfPP::operator=(const FdfPP &other){}

// fdf functions
void FdfPP::open(char *fname)
{
  fp = fdf_open(fname);
}

void FdfPP::open(const std::string &fname)
{
  fp = fdf_open(const_cast <char *>(fname.c_str()));
}

void FdfPP::openNoLink(char *fname)
{
  fp = fdf_open_nolink(fname);
}

void FdfPP::openNoLink(const std::string &fname)
{
  fp = fdf_open_nolink(const_cast <char *>(fname.c_str()));
}

void FdfPP::openWrite(char* fname, long append)
{
  fp = fdf_open_write(fname,append);
}

void FdfPP::openWrite(const std::string &fname, long append)
{
  fp = fdf_open_write(const_cast <char *>(fname.c_str()),append);
  std::cout << "open_write()" << std::endl;
}

void FdfPP::close()
{
  fdf_close(fp);
  std::cout << "close()" << std::endl;
}

long FdfPP::readData(long nbytes, void *data)
{
  long fdf_data_read_status = fdf_read_data(fp, nbytes, data, err);
  return(fdf_data_read_status);
  
}

//long FdfPP::seekEnd(long *nitems)
//{
//  long seek_end_status = fdf_seek_end(fp, nitems, err);
//  return(seek_end_status);
//}

long FdfPP::writeItem(long append, char* name, long ndims, const int *dims,
		      long type, void *data)
{
  long fdf_write_status = fdf_write_item(fp, append, name,
					 ndims, dims, type, data, err);
  return(fdf_write_status);
}

long FdfPP::writeItem(long append, char* name, long ndims, const int *dims,
		      long type, void *data)
{
  long fdf_write_status = fdf_write_item(fp, append, name,
					 ndims, dims, type, data, err);
  return(fdf_write_status);
}
long FdfPP::writeItem(long append, const std::string &name, )
long FdfPP::seekItem(long *item, char *name, long *ndims, int *dims,
		     long *type, long *nbytes)
{
  long fdf_seek_item_status = fdf_seek_item(fp, item, name,
					    ndims, dims, type, nbytes,err);
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
//						    dims, type, err);
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
