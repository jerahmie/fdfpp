// This file is part of the DAQ data acquisition system of the HSX Stellarator
// Laboratory at the University of Wisconsin - Madison. This system was developed
// by Paul Probert, starting in about 2003. See the files in the docs subdirectory
// for some help. This work was supported by the US Taxpayers through the
// US Department of Energy under grant DE-FG02-93ER54222. It is freely available
// for any use. There is no warranty that this software is fit for any purpose.
// Use at your own risk. Please report bugs to pprobert@wisc.edu.
#if defined(_MSC_VER)
  #define _WIN32_WINNT 0X0500
  #include <windows.h>
#else
  #define PREAMBLE(X)
#endif

#include <stdio.h>
#include <string.h>
#include "fdf.h"

PREAMBLE(dllexport) void fdf_close( FILE* fp){
  if(fp != NULL)fclose(fp);
}
PREAMBLE(dllexport) FILE* fdf_open_write( char *fname,long append){
  if(append){
    return fopen(fname,"r+b");
  }else{
    return fopen(fname,"w+b");
  }
}

PREAMBLE(dllexport) FILE* fdf_open( char *fname ){
  FILE *fp;
  char name[FDF_ITEMNAME_LENGTH];
  long ndims, type, nbytes, err,seekitem;
  int dims[FDF_MAXDIMS];
  err=0;
  if( (fp = fopen(fname, "rb")) == NULL)err=1;
  seekitem=0;
  err = fdf_seek_item( fp, &seekitem, name, &ndims, dims, &type, &nbytes,err);
  if( err == 0){
    if( strcmp(name,"fdf_link") == 0){
      //this file is a link
      char linkname[256];
      //this file is a link, get the data and use it as a file name and
      //open that file
      if( type != fdf_char)err=1;
      linkname[255]=0x00; //just to be sure
      if(nbytes > 255){
        err=1;
      }
      //read the path from the link file
      err=fdf_read_data( fp, nbytes, linkname, err);
      if(err == 0){
        fclose(fp);
        linkname[nbytes]=0x00;
        //recursively call ourself to open the linked-to file
        fp = fdf_open( linkname);
        if(fp == NULL)err=1;
      }
    }
  }
  //if err is 0, we have an open file which is not a link and is a good fdf file
  if(err == 0)return fp; else return NULL;
}

PREAMBLE(dllexport) FILE* fdf_open_nolink( char *fname ){
  FILE *fp;
  long err;
  char stuff[4];
  err=0;
  if( (fp = fopen(fname, "rb")) == NULL)err=1;
  if(fseek( fp, 0, SEEK_SET ) != 0)err=1;
  err = fread_err(stuff, 1, 4, fp, err);
  if(err == 0){
    if( memcmp(stuff,"fdf",3) != 0)err=1;
  }
  //if err is 0, we have an open file which is an fdf file
  if(err == 0)return fp; else return NULL;
}


PREAMBLE(dllexport) long fdf_is_link( char *fname, long *islink ){
  FILE *fp;
  char name[FDF_ITEMNAME_LENGTH];
  long ndims, type, nbytes, err,seekitem;
  int dims[FDF_MAXDIMS];
  err=0;
  *islink=0;
  fp = NULL;
  if( (fp = fopen(fname, "rb")) == NULL)err=1;
  seekitem=0;
  err = fdf_seek_item( fp, &seekitem, name, &ndims, dims, &type, &nbytes,err);
  if( err == 0){
    if( strcmp(name,"fdf_link") == 0){
      //this file is a link, but check the data type
      if( type != fdf_char){
        //wrong data type
        err=1;
      }else{
        *islink=1;
      }
    }
  }
  if(fp != NULL)fclose(fp);
  return err;
}


PREAMBLE(dllexport) long fdf_read_data( FILE *fp,
                    long nbytes,
                    void *data, long err){
  //caller must have called fdf_seek_item first
  //to position the file
  //the nbytes returned from that call should be used in this call
  if(err)return err;
  if(fp == NULL)return 1;
  err = fread_err( data, 1, nbytes, fp, err);
  return err;
}

PREAMBLE(dllexport) long fdf_write_item( FILE *fp, long append, char *name,
                     long ndims, const int *dims, long type,
                    void *data, long err){
  long nitems;
  if( fp == NULL)return 1;
  if(err != 0)return err;
  if(append){
    err= fdf_seek_end( fp, &nitems, err);
    if(err)return err;
  }else{
    if( fseek(fp,0,SEEK_SET) != 0)err=1;
    err=fwrite_err("fdf", 1, 4, fp, err);
  }
  err=fwrite_err(name, 1, FDF_ITEMNAME_LENGTH, fp, err);
  err = fwrite_err( &ndims, sizeof ndims, 1, fp, err);
  err = fwrite_err( dims, sizeof dims[0], ndims, fp, err);
  err = fwrite_err( &type, sizeof type, 1, fp, err);
  err = fwrite_err( data, 1, fdf_data_length( ndims, dims, type),fp, err);
  return err;
}

PREAMBLE(dllexport) long fdf_seek_item( FILE *fp, long *item, char *name,
                     long *ndims, int *dims,
                    long *type, long *nbytes,
                    long err ){
  /*attempts to go to item, where items are numbered starting from 0,
  and returns 1 if not able to
  else returns 0

  if called with *item >= 0, and that item exists, leaves the file
  positioned at the beginning of that item's data
  
  if called with *item < 0, returns the total number of
  items in *item, and positions the file at the very end.
  
  caller should dimension dims and name as follows:
  long dims[FDF_MAXDIMS];
  char name[FDF_ITEMNAME_LENGTH];
  long ndims,type,pos;
  */

  char stuff[4];
  long nitems,pos;
  if( fp == NULL)return 1;
  if(err != 0)return err;
  if(fseek( fp, 0, SEEK_SET ) != 0)err=1;
  err = fread_err(stuff, 1, 4, fp, err);
  if(err == 0){
    if( memcmp(stuff,"fdf",3) != 0)err=1;
  }
  nitems=0;
  for(;;){
    //try to read in name,ndims,dims,type
    if(err)break;
    if(nitems != 0){
      //skip the data region of the previous item
      if( fseek( fp, *nbytes, SEEK_CUR)
        != 0)err=1;
      if(err)break;
    }
    err = fdf_read_preamble(fp, name, ndims, dims, type, err);
    if(err == 0){
      //there was a preamble
      nitems++;
      *nbytes = fdf_data_length( *ndims, dims, *type);
      //if this is the item we were looking for, done
      if(nitems-1 >= *item && *item >= 0)break;
      pos = ftell(fp); //remember this position, at start of data
    }else{
      //no preamble, so we are at the end
      if( *item >= 0){
        //we got to the end without finding the item
        err=1;
      }else{
        //we were looking for, and have found, the end of the file
        *item=nitems;
        //go to the end of the data region
        if( fseek( fp, *nbytes+pos, SEEK_SET) != 0){
          err=1;
        }else{
          err=0;
        }
        break;
      }
    }
  }
  return err;
}

PREAMBLE(dllexport) long fdf_seek_end( FILE *fp, long *nitems, long err ){
  int dims[FDF_MAXDIMS];
  char name[FDF_ITEMNAME_LENGTH];
  long ndims,type,nbytes;
  *nitems = -1;
  if( fp == NULL)return 1;
  if(err != 0)return err;
  err=fdf_seek_item( fp, nitems, name, &ndims, dims, &type, &nbytes, err);
  return err;
}

long fdf_data_length( long ndims, const int *dims, long type ){
  long idim, len, typelen;
  typelen=fdf_type_nbytes(type);
  len=1;
  for(idim=0; idim < ndims; idim++){
    len=len*dims[idim];
  }
  return len*typelen;
}

long fdf_read_preamble( FILE *fp, char *name, long *ndims,
             int *dims, long *type, 
             long err){
  //reads the preamble of the item, assuming current file position is at the
  //beginning of an item, and leaves the file position at the beginning
  //of the item's data
  if(err != 0)return err;
  err=fread_err(name, 1, FDF_ITEMNAME_LENGTH, fp,err);
  err=fread_err(ndims, sizeof *ndims, 1, fp, err);
  err=fread_err(dims, sizeof dims[0], *ndims, fp, err);
  err=fread_err(type, sizeof *type, 1, fp, err);
  return err;
}

long fdf_type_nbytes( long type ){
  long nbytes;
  switch(type){
  case fdf_char:
    nbytes=1;
    break;
  case fdf_i8:
    nbytes=1;
    break;
  case fdf_u8:
    nbytes=1;
    break;
  case fdf_i16:
    nbytes = 2;
    break;
  case fdf_u16:
    nbytes = 2;
    break;
  case fdf_i32:
    nbytes = 4;
    break;
  case fdf_u32:
    nbytes = 4;
    break;
  case fdf_float:
    nbytes = 4;
    break;
  case fdf_double:
    nbytes = 8;
    break;
  case fdf_complex:
    nbytes=8;
    break;
  case fdf_dcomplex:
    nbytes=16;
    break;
  default:
    nbytes=0;
    break;
  }
  return nbytes;
}


long fread_err( void *buff, size_t size, size_t count, FILE *fid, long err){
  size_t nread;
  if(err)return err;
  if(fid == NULL)return 1;
  nread = fread( buff, size, count, fid);
  if(nread != count)return 1; else return 0;
}

long fwrite_err( const void *buff, size_t size, size_t count, FILE *fid, long err){
  size_t nwrite;
  if(err)return err;
  if(fid == NULL)return err;
  nwrite = fwrite( buff, size, count, fid);
  if(nwrite != count)return 1; else return 0;
}
