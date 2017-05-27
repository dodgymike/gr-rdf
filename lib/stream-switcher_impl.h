/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_RDF_STREAM_SWITCHER_IMPL_H
#define INCLUDED_RDF_STREAM_SWITCHER_IMPL_H

#include <rdf/stream-switcher.h>

namespace gr {
  namespace rdf {

    class stream_switcher_impl : public stream_switcher
    {
     private:
      // Nothing to declare in this block.
	int m_current_stream_index;
	int m_samples_per_switch;
	int m_current_sample_count;
	int m_vec_length;

     public:
      stream_switcher_impl(vec_length, samples_per_switch);
      ~stream_switcher_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace rdf
} // namespace gr

#endif /* INCLUDED_RDF_STREAM_SWITCHER_IMPL_H */

