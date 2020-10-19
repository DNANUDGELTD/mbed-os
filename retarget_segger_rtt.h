//----------------------------------------------------------------------------
// Namespace:   mbed
// Class:       SeggerRTT
// Description: Alternative stdio read/write interface function for Segger RTT
// Copyright:   (c) 2017 Mark <0x6d61726b@gmail.com>
// License:     MIT License
// SVN:         $Id: retarget_segger_rtt.h 269 2018-01-27 08:08:06Z mark@svn.srv02.net $
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
#include "platform/FileHandle.h"
#include "SeggerRTT/SEGGER_RTT.h"

namespace mbed {
    
    /** Class SeggerRTT
    *
    *  An interface to perform file-like operations for Segger RTT.
    *  The "file" in this implementation is the Segger RTT terminal itself.
    */
    class SeggerRTT : public FileHandle {
    public:
        /** Write the contents of a buffer to the terminal
         *
         *  @param buffer   The buffer to write from
         *  @param size     The number of bytes to write 
         *  @return         The number of bytes written, negative error on failure
         */
        virtual ssize_t write(const void *buffer, size_t size);
        
        /** Read the contents from the terminal into a buffer (blocking access)
         *
         *  @param buffer   The buffer to read in to
         *  @param size     The number of bytes to read
         *  @return         The number of bytes read, 0 at end of file, negative error on failure
         */
        virtual ssize_t read(void *buffer, size_t size);
        
        /** Move the file position to a given offset from a given location
         *  (this operation is not supported by SeggerRTT)
         *
         *  @return         -ESPIPE (illegal seek)
         */
        virtual off_t seek(off_t offset, int whence = SEEK_SET) {
            return -ESPIPE;
        }
        
        /** Get the size of the file
         *  (this operation is not supported by SeggerRTT)
         *
         *  @return         -EINVAL (invalid argument)
         */
        virtual off_t size() {
            return -EINVAL;
        }
        
        /** Check if the file in an interactive terminal device
         *
         *  @return         true (SeggerRTT is a terminal)
         */
        virtual int isatty() {
            return true;
        }
        
        /** Close the file to the terminal
         *
         *  @return         0 on success (no explicit open/close possible)
         */
        virtual int close() {
            return 0;
        }
        
        /** Check for poll event flags
         * Call is non-blocking - returns instantaneous state of events.
         *
         * @param events        bitmask of poll events we're interested in - POLLIN/POLLOUT etc.
         *
         * @returns             bitmask of poll events that have occurred.
         */
        virtual short poll(short events) const;
    };
}