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
#include "stream_switcher_impl.h"

namespace gr {
  namespace rdf {

    stream_switcher::sptr
    stream_switcher::make(int vec_length, int samples_per_switch)
    {
      return gnuradio::get_initial_sptr
        (new stream_switcher_impl(vec_length, samples_per_switch));
    }

    /*
     * The private constructor
     */
    stream_switcher_impl::stream_switcher_impl(int vec_length, int samples_per_switch)
      : gr::sync_block("stream_switcher",
              gr::io_signature::make(1, 1, vec_length * sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
	m_current_stream_index = 0;
	m_samples_per_switch = samples_per_switch;
	m_current_sample_count = 0;
	m_vec_length = vec_length;
    }

    /*
     * Our virtual destructor.
     */
    stream_switcher_impl::~stream_switcher_impl()
    {
    }

    int
    stream_switcher_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
	gr_complex *out = (gr_complex *) output_items[0];

	if(m_current_sample_count++ >= m_samples_per_switch) {
		m_current_sample_count = 0;
		m_current_stream_index++;
		//std::cerr << "bumping stream index" << std::endl;
	}

	if(m_current_stream_index > (m_vec_length) - 1) {
		m_current_stream_index = 0;
	}

	//const gr_complex *in = (const gr_complex *) input_items[m_current_stream_index];
	const gr_complex *in = (const gr_complex *) input_items[0];

		out[0] = in[m_current_stream_index];
	
	//return noutput_items;
	return 1;
    }

  } /* namespace rdf */
} /* namespace gr */

/*
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];


        int signal_index = 0;
        int signal_averaging_window_size = m_output_size / 10;
        int half_window_size = signal_averaging_window_size / 2;

        int half_output_row_size = m_output_size / 2;

        float max_average = 0.0f;
        for(int row_index = 0; row_index < (m_fft_size - signal_averaging_window_size); row_index++) {
          long sum = 0;
          for(int averaging_window_index = 0; averaging_window_index < signal_averaging_window_size; averaging_window_index++) {
            gr_complex input_item = in[row_index + averaging_window_index];
            sum += abs(input_item.real());
          }
          float average = sum / signal_averaging_window_size;
          if(average > max_average) {
            signal_index = row_index + half_window_size;
            max_average = average;
          }
        }

        int output_start_index = find_output_start_index(signal_index, m_output_size, m_fft_size, half_output_row_size);

        int output_index = 0;
        for(int write_index = output_start_index; write_index < (output_start_index + m_output_size); write_index++) {
          out[output_index++] = in[write_index];
        }
        // Tell runtime system how many output items we produced.
        return noutput_items;
*/
