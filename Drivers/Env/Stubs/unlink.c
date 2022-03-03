
/* See LICENSE of license details. */
#include <errno.h>
#include <nuclei_sdk_soc.h>

#undef errno
extern int errno;

__WEAK int _unlink(const char* name)
{
    return -1;
}
