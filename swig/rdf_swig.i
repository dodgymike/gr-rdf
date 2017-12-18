/* -*- c++ -*- */

#define RDF_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "rdf_swig_doc.i"

%{
#include "rdf/stream_switcher.h"
#include "rdf/simple_derivative.h"
#include "rdf/transition_counter.h"
%}


%include "rdf/stream_switcher.h"
GR_SWIG_BLOCK_MAGIC2(rdf, stream_switcher);
%include "rdf/simple_derivative.h"
GR_SWIG_BLOCK_MAGIC2(rdf, simple_derivative);
%include "rdf/transition_counter.h"
GR_SWIG_BLOCK_MAGIC2(rdf, transition_counter);
