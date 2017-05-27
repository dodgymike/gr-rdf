/* -*- c++ -*- */

#define RDF_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "rdf_swig_doc.i"

%{
#include "rdf/stream-switcher.h"
%}


%include "rdf/stream-switcher.h"
GR_SWIG_BLOCK_MAGIC2(rdf, stream-switcher);
