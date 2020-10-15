/* -*- c++ -*- */
/*
 * Copyright 2009,2010 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <vrt/rx.h>

#include "data_handler.h"
#include "socket_rx_buffer.h"
#include <stdexcept>
#include <stdio.h>
#include <unistd.h>
#include <vrt/expanded_header.h>

static void print_words(FILE *fp, size_t offset, const uint32_t *buf,
                        size_t n) {
  size_t i;
  for (i = 0; i < n; i++) {
    if (i % 4 == 0) {
      fprintf(fp, "%04zx:", i);
    }

    putc(' ', fp);
    fprintf(fp, "%08x", buf[i]);
    if (i % 4 == 3)
      putc('\n', fp);
  }

  putc('\n', fp);
}

namespace vrt {

rx::sptr rx::make(int socket_fd, size_t rx_bufsize) {
  return sptr(new rx(socket_fd, rx_bufsize));
}

rx::rx(int socket_fd, size_t rx_bufsize)
    : d_socket_fd(socket_fd),
      d_srb(new socket_rx_buffer(socket_fd, rx_bufsize)) {}

rx::~rx() {
  delete d_srb;
  ::close(d_socket_fd);
}

class vrt_data_handler : public data_handler {
  rx_packet_handler *d_handler;
  rx_frame_handler *f_handler;

public:
  vrt_data_handler(rx_packet_handler *handler)
      : d_handler(handler), f_handler(nullptr) {}
  vrt_data_handler(rx_frame_handler *handler)
      : f_handler(handler), d_handler(nullptr) {}

  ~vrt_data_handler();

  bool operator()(const void *base, size_t len);
};

vrt_data_handler::~vrt_data_handler() {}

// N.B., There may be more than 1 VRT packet in a frame (usually IF-Context
// packets)
bool vrt_data_handler::operator()(const void *base, size_t len) {
  const uint32_t *word_base = (const uint32_t *)base;
  size_t word_len = len / (sizeof(uint32_t));

  bool want_more = true;
  while (word_len > 0 && want_more) {
    if (d_handler != nullptr) {
      const uint32_t *payload;
      size_t n32_bit_words;
      expanded_header hdr;
      if (!expanded_header::unpack(word_base, word_len, &hdr, &payload,
                                   &n32_bit_words)) {
        fprintf(stderr, "vrt_data_handler: malformed VRT packet!\n");
        print_words(stderr, 0, word_base, word_len);
        return true;
      }

      want_more = (*d_handler)(payload, n32_bit_words, &hdr);
      word_base += hdr.pkt_size();
      word_len -= hdr.pkt_size();
    } else {
      BasicVRTPacket *frame = new BasicVRTPacket(word_base, word_len, true);
      want_more = (*f_handler)(frame);
      word_len = 0;
    }
  }
  return want_more;
}

bool rx::rx_packets(rx_packet_handler *handler, bool dont_wait) {
  vrt_data_handler h(handler);
  socket_rx_buffer::result r = d_srb->rx_frames(&h, dont_wait ? 0 : -1);
  return r == socket_rx_buffer::EB_OK || r == socket_rx_buffer::EB_WOULD_BLOCK;
}

bool rx::rx_frames(rx_frame_handler *handler, bool dont_wait) {
  vrt_data_handler h(handler);
  socket_rx_buffer::result r = d_srb->rx_frames(&h, dont_wait ? 0 : -1);
  return r == socket_rx_buffer::EB_OK || r == socket_rx_buffer::EB_WOULD_BLOCK;
}

}; // namespace vrt
