#ifndef __RX_FRAME_HANDLER_H__
#define __RX_FRAME_HANDLER_H__

/* -*- c++ -*- */
/*
 * Copyright 2009 Free Software Foundation, Inc.
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

#include <VITA49/BasicVRLFrame.h>
#include <stddef.h>

namespace vrt {

/*!
 * \brief Abstract function object called to handle received VRT packets.
 *
 * An object derived from this class is passed to vrt_rx_udp::rx_packets
 * to process the received packets.
 */
class rx_frame_handler {
public:
  virtual ~rx_frame_handler() = default;

  virtual bool operator()(BasicVRLFrame *frame);
};

}; // namespace vrt

#endif // __RX_FRAME_HANDLER_H__