/* See LICENSE of license details. */

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include "nuclei_sdk_soc.h"

/* NOTE : This function Should not be modified, when redirecting printf() is needed,
          the _put_char() could be implemented in the user file
*/
__attribute__((weak)) int _put_char(int ch)
{
    return ch;
}


ssize_t _write(int fd, const void* ptr, size_t len)
{
    if (!isatty(fd)) {
        return -1;
    }

    const uint8_t * writebuf = (const uint8_t *)ptr;
	
    for (size_t i = 0; i < len; i++) {
        if (writebuf[i] == '\n') {
        	_put_char('\r');
        }

        _put_char(writebuf[i]);
    }
	
    return len;
}

