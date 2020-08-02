%include "std_string.i"
%include "std_map.i"
%include "std_vector.i"
%include "cpointer.i"

%module cpp_stylist
%{
#include "stylist.h"
#include "cpp_stylist.h"
%}
%include "stylist.h"
%include "cpp_stylist.h"