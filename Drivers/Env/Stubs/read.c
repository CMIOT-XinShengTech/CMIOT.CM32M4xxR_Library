#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include "nuclei_sdk_soc.h"

/* NOTE : This function Should not be modified, when redirecting scanf() is needed,
          the _get_char() could be implemented in the user file
*/
__attribute__((weak)) int _get_char(void)
{
	return 0;
}

ssize_t _read(int fd, void* ptr, size_t len)
{
    if (fd != STDIN_FILENO) {
        return -1;
    }
	
    uint8_t *readbuf = (uint8_t *)ptr;
    uint8_t c = (uint8_t)_get_char();
    /* '\n' or "\r\n" as the end of input */
    if(c == '\r') {
    	c = (uint8_t)_get_char();
    }
    readbuf[0] = c;

    return 1;
}
