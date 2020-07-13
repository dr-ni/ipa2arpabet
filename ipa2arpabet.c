/* Copyright (C) 2018 U. Niethammer
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Straight-forward german translator from International Phonetic Alphabet (IPA) to CMU ARPAbet
 */


#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
#include "ipa2arpabet.h"

char * find_match(const char *buf, const char * buf_end, const char *pat, size_t len){
	ptrdiff_t i;
	const char *start = buf;
	while (start + len < buf_end) {
		for (i = 0; i < len; i++)
			if (start[i] != pat[i]) break;
 
		if (i == len) return (char *)start;
		start++;
	}
	return 0;
}
 
int replace(const char *from, const char *to, const char *fname){
#define bail(msg) { warn(msg" '%s'", fname); goto done; }
	struct stat st;
	int ret = 0;
	char *buf = 0, *start, *end;
	size_t len = strlen(from), nlen = strlen(to);
	int fd = open(fname, O_RDWR);
 
	if (fd == -1) bail("Can't open");
	if (fstat(fd, &st) == -1) bail("Can't stat");
	if (!(buf = malloc(st.st_size))) bail("Can't alloc");
	if (read(fd, buf, st.st_size) != st.st_size) bail("Bad read");
 
	start = buf;
	end = find_match(start, buf + st.st_size, from, len);
	if (!end) goto done; /* no match found, don't change file */
 
	ftruncate(fd, 0);
	lseek(fd, 0, 0);
	do {
		write(fd, start, end - start);	/* write content before match */
		write(fd, to, nlen);		/* write replacement of match */
		start = end + len;		/* skip to end of match */
						/* find match again */
		end = find_match(start, buf + st.st_size, from, len);
	} while (end);
 
	/* write leftover after last match */
	if (start < buf + st.st_size)
		write(fd, start, buf + st.st_size - start);
 
done:
	if (fd != -1) close(fd);
	if (buf) free(buf);
	return ret;
}

