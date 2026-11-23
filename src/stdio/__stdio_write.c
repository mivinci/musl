#include "stdio_impl.h"
#include <sys/uio.h>

#ifdef MIVINCI_NATIVE
hidden ssize_t __mivinci_stdio_write(int, const void *, size_t, const void *, size_t);
#endif

size_t __stdio_write(FILE *f, const unsigned char *buf, size_t len)
{
	struct iovec iovs[2] = {
		{ .iov_base = f->wbase, .iov_len = f->wpos-f->wbase },
		{ .iov_base = (void *)buf, .iov_len = len }
	};
	struct iovec *iov = iovs;
	size_t rem = iov[0].iov_len + iov[1].iov_len;
	int iovcnt = 2;
	ssize_t cnt;
	for (;;) {
#ifdef MIVINCI_NATIVE
		cnt = __mivinci_stdio_write(f->fd, iov[0].iov_base, iov[0].iov_len,
			iovcnt == 2 ? iov[1].iov_base : 0, iovcnt == 2 ? iov[1].iov_len : 0);
		if (!cnt && rem) { errno = EIO; cnt = -1; }
#else
		cnt = syscall(SYS_writev, f->fd, iov, iovcnt);
#endif
		if (cnt == rem) {
			f->wend = f->buf + f->buf_size;
			f->wpos = f->wbase = f->buf;
			return len;
		}
		if (cnt < 0) {
			f->wpos = f->wbase = f->wend = 0;
			f->flags |= F_ERR;
			return iovcnt == 2 ? 0 : len-iov[0].iov_len;
		}
		rem -= cnt;
		if (cnt > iov[0].iov_len) {
			cnt -= iov[0].iov_len;
			iov++; iovcnt--;
		}
		iov[0].iov_base = (char *)iov[0].iov_base + cnt;
		iov[0].iov_len -= cnt;
	}
}
