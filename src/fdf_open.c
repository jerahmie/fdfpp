// This file is part of the DAQ data acquisition system of the HSX Stellarator
// Laboratory at the University of Wisconsin - Madison. This system was developed
// by Paul Probert, starting in about 2003. See the files in the docs subdirectory
// for some help. This work was supported by the US Taxpayers through the
// US Department of Energy under grant DE-FG02-93ER54222. It is freely available
// for any use. There is no warranty that this software is fit for any purpose.
// Use at your own risk. Please report bugs to pprobert@wisc.edu.
#include <stdio.h>
#include "fdf.h"
#include "string.h"

FILE *fdf_open(char *fname, long *ptypecode){
	/*
	returns a file pointer or null if error.
	*ptypecode is returned as follows:
		if no error:
		the typecode is read from the file
		0        file is a valid fdf file, returned pointer not NULL
		x        other positive integers for future file types
		if error:
		-1       file not found
		-2       the fdf marker is missing
		-3       file has an unknown typecode
		-4       header size bad
		-5       weird nheader
		-6       program error (fallthrough)

	*/

	long err;
	FILE *fid;
	long nheader, nbytes;
	char header[256];
	char buff[4];
	enum { type0, link, bad} ftype;
	err=0;

	fid=fopen(fname,"rb");
	if( fid == NULL){
		err = -1;  // return code -1: file not found
	}
	
	nbytes=4;
	err = fread_err(buff,1,nbytes,fid, err);
	buff[nbytes-1]=0x00;
	if( !err){
		if(strcmp(buff,"fdf") != 0){
			if(fid != NULL)fclose(fid);
			err = -2;  // -2 return code: file not of fdf format
		}
	}
	
	err = fread_err(ptypecode,sizeof *ptypecode,1,fid,err);
	if( !err){
		switch(*ptypecode){
		case 0:
			//file is ok
			ftype = type0;
			break;
		case 0x42424242:
			//file is a link
			ftype = link;
			break;
		default:
			ftype=bad;
			if(fid != NULL)fclose(fid);
			err = -3;  // -3 return code: not proper typecode
			break;
		}
	}

	if( !err && ftype != bad && ftype != link){
		//is a regular fdf file, return the file pointer
		fseek(fid, 8, SEEK_SET); // rewind to position of nheader
		return fid;
	}

	//is bad or is a link. if not bad, read nheader
	err = fread_err(&nheader, sizeof nheader, 1, fid, err);

	if( !err ){
		if(nheader <0 || nheader > FDF_HEADER_MAX_LENGTH){
			err=-4; // -4 return code, header size bad
		}
		if( !err && nheader > 0){
			err = fread_err( header, 1, nheader, fid, err);
			header[nheader]=0x00;
		}else{
			header[0] = 0x00;
		}
	}

	if( !err && ftype == link && nheader > 0){
		if(fid != NULL)fclose(fid);
		fid = fdf_open( header, ptypecode ); //recurse, using header as new file name
		return fid;
	}

	if( !err && ftype == link && nheader <= 0){
		*ptypecode = -5; // -5 return code, weird nheader
		if(fid != NULL)fclose(fid);
		return NULL;
	}


	if( ftype == bad || err){
		*ptypecode = err;
		if(fid != NULL)fclose(fid);
		return NULL;
	}
	*ptypecode = -6; // -6 return code, fallthrough error
	if(fid != NULL)fclose(fid);
	return NULL;
}

