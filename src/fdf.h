/* This file is part of the DAQ data acquisition system of the HSX Stellarator
// Laboratory at the University of Wisconsin - Madison. This system was developed
// by Paul Probert, starting in about 2003. See the files in the docs subdirectory
// for some help. This work was supported by the US Taxpayers through the
// US Department of Energy under grant DE-FG02-93ER54222. It is freely available
// for any use. There is no warranty that this software is fit for any purpose.
// Use at your own risk. Please report bugs to pprobert@wisc.edu.
*/

#ifndef FDF_H_
#define FDF_H_

#ifdef __cplusplus
extern "C" {
#endif

#define FDF_ITEMNAME_LENGTH     64
#define	FDF_MAXDIMS		32

#if defined(_MSC_VER)
  #if defined(FDF_IMPORT)
    #define IMPEX dllimport
  #else
    #define IMPEX dllexport
  #endif

  #if defined(FDF_STATIC)
    #define PREAMBLE(x)
  #else
    #define PREAMBLE(x) __declspec(x)
  #endif
#else
  #define PREAMBLE(X)
  #define IMPEX
#endif

typedef struct complex_tag{
	float real;
	float imag;
}	complex;

typedef struct dcomplex_tag{
	double real;
	double imag;
}		dcomplex;

typedef union pfdf_data_tag {
	void *pvoid;
	char *pi8;
	unsigned char *pu8;
	short *pi16;
	unsigned short *pu16;
	long *pi32;
	unsigned long *pu32;
	float *pfloat;
	double *pdouble;
	complex *pcomplex;
	dcomplex *pdcomplex;
} pfdf_data;

typedef enum fdf_type_tag{ fdf_char, fdf_i8, fdf_u8, fdf_i16, fdf_u16,
			fdf_i32, fdf_u32,
			fdf_float, fdf_double, fdf_complex,
			fdf_dcomplex} fdf_type;

PREAMBLE(IMPEX) FILE* fdf_open( char *fname );

PREAMBLE(IMPEX) FILE* fdf_open_nolink( char *fname );
PREAMBLE(IMPEX) void fdf_close( FILE* fp);

PREAMBLE(IMPEX) FILE* fdf_open_write( char *fname, long append);

PREAMBLE(IMPEX) long fdf_read_data( FILE *fp,
				long nbytes,
				void *data, long err);

PREAMBLE(IMPEX) long fdf_seek_end( FILE *fp, long *nitems, long err );

PREAMBLE(IMPEX) long fdf_write_item( FILE *fp, long append, char *name,
				long ndims, const int *dims, long type,
				void *data, long err);

PREAMBLE(IMPEX) long fdf_seek_item( FILE *fp, long *item, char *name,
				long *ndims, int *dims,
				long *type, long *nbytes,
				long err );

PREAMBLE(dllexport) long fdf_is_link( char *fname, long *islink );

long fdf_data_length( long ndims, const int *dims, long type );

long fdf_read_preamble( FILE *fp, char *name, long *ndims, int *dims,
                                long *type, long err);

long fdf_type_nbytes( long type );

long fread_err( void *buff, size_t size, size_t count, FILE *fid, long err);

long fwrite_err( const void *buff, size_t size,
				size_t count, FILE *fid, long err);

#ifdef __cplusplus
}
#endif

#endif  /* FDF_H_ */
