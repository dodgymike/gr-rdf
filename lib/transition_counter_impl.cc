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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "transition_counter_impl.h"

namespace gr {
  namespace rdf {

    transition_counter::sptr
    transition_counter::make()
    {
      return gnuradio::get_initial_sptr
        (new transition_counter_impl());
    }

    /*
     * The private constructor
     */
    transition_counter_impl::transition_counter_impl()
      : gr::sync_block("transition_counter",
              gr::io_signature::make(2, 2, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      m_count = 0;
    }

    /*
     * Our virtual destructor.
     */
    transition_counter_impl::~transition_counter_impl()
    {
      m_previously_high = false;
    }

    int
    transition_counter_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      const int *reset_in = (const int *) input_items[1];
      float *out = (float *) output_items[0];

      for(int i = 0; i < noutput_items; i++) {
        float current_sample = *(in + i);
        int current_reset = *(reset_in + i);

        if(current_reset == 0) {
          m_count = 0;
        }

        if(!m_previously_high && (current_sample > 0)) {
          m_previously_high = true;
          m_count++;
        }

        if(current_sample < 0) {
          m_previously_high = false;
        }

        *out++ =(float) m_count;
      }

      return noutput_items;
    }

  } /* namespace rdf */
} /* namespace gr */

