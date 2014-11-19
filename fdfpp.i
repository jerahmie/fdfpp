/* File: fdf.i */
%module fdfpp
%include "std_map.i"
%include "std_string.i"
%{
#define SWIG_FILE_WITH_INIT
#include "src/fdf.h"
#include "src/fdfpp.h"
  %}

%include "src/fdf.h"
%include "src/fdfpp.h"
