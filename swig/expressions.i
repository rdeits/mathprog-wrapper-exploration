%module expressions

%{
#define SWIG_FILE_WITH_INIT
#include <Python.h>
#include "../../src/expressions.h"
%}

%include <std_string.i>

%include ../src/expressions.h

