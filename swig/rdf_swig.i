/* -*- c++ -*- */

#define RDF_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "rdf_swig_doc.i"

%{
#include "rdf/stream_switcher.h"
%}


%include "rdf/stream_switcher.h"
GR_SWIG_BLOCK_MAGIC2(rdf, stream_switcher);
