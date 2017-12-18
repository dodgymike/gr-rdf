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
#include "simple_derivative_impl.h"

namespace gr {
  namespace rdf {

    simple_derivative::sptr
    simple_derivative::make(int window)
    {
      return gnuradio::get_initial_sptr
        (new simple_derivative_impl(window));
    }

    /*
     * The private constructor
     */
    simple_derivative_impl::simple_derivative_impl(int window)
      : gr::sync_block("simple_derivative",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      m_window = window;
    }

    /*
     * Our virtual destructor.
     */
    simple_derivative_impl::~simple_derivative_impl()
    {
    }

    int
    simple_derivative_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      int processed_count = 0;
      while((noutput_items - processed_count) > m_window) {
        float max = INT_MIN;
        float min = INT_MAX;

        int midpoint = m_window/2;
        float left_sum = 0;
        for(int i = 0; i < midpoint; i++) {
          float current_sample = *(in + processed_count + i);
          left_sum += current_sample;
        }
        float left_average = left_sum / midpoint;

        float right_sum = 0;
        for(int i = midpoint; i < m_window; i++) {
          float current_sample = *(in + processed_count + i);
          right_sum += current_sample;
        }
        float right_average = right_sum / midpoint;

/*
        for(int i = 0; i < m_window; i++) {
          float current_sample = *(in + processed_count + i);
          if(current_sample > max) {
            max = current_sample;
          }

          if(current_sample < min) {
            min = current_sample;
          }
        }
*/

        *out++ = right_average - left_average;

        processed_count++;
      }

      // Tell runtime system how many output items we produced.
      return processed_count;
    }

  } /* namespace rdf */
} /* namespace gr */

