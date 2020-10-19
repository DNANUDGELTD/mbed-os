//----------------------------------------------------------------------------
// Namespace:   mbed
// Class:       SeggerRTT
// Description: Alternative stdio read/write interface function for Segger RTT
// Copyright:   (c) 2017 Mark <0x6d61726b@gmail.com>
// License:     MIT License
// SVN:         $Id: retarget_segger_rtt.cpp 269 2018-01-27 08:08:06Z mark@svn.srv02.net $
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//----------------------------------------------------------------------------
#include "retarget_segger_rtt.h"
#include "platform/mbed_retarget.h"
#include "platform/mbed_poll.h"

namespace mbed {
    
    // retarget stdin/stdout/stderr to Segger RTT
    static SeggerRTT fhSeggerRtt;
    FileHandle *mbed_override_console(int fd) {
        return &fhSeggerRtt;
    }
    
    ssize_t SeggerRTT::write(const void *buffer, size_t size) {
        // write the buffer content to the terminal
        return SEGGER_RTT_Write(0, buffer, size);
    }
    
    ssize_t SeggerRTT::read(void *buffer, size_t size) {
        // wait until a character becomes available
        while (!SEGGER_RTT_HasKey()) {}
    
        // read the characters from the terminal into the buffer
        return SEGGER_RTT_Read(0, buffer, size);
    }
    
    short SeggerRTT::poll(short events) const {
        short revents = 0;
        if ((events & POLLIN) && SEGGER_RTT_HasKey()) {
            revents |= POLLIN;
        }
        if (events & POLLOUT) {
            revents |= POLLOUT;
        }
        return revents;
    }
}