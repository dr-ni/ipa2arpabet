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
 * compile: $(CC) ipa2arpabet.c -o ipa2arpabet
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>
#include <string.h>

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
 
int main(int argc, char* argv[]){

if(argc < 2){
    printf("Syntax: %s filename\n", argv[0]);
    exit(1);
}

replace("eɪ", "EY ", argv[1]);
replace("æ", "AE ", argv[1]);
replace("ˈaɪ", "AY ", argv[1]);
replace("aɪ", "AY ", argv[1]);
replace("aʊ", "AW ", argv[1]);
replace("ɑː", "AAH ", argv[1]);
replace("ɑ", "AA ", argv[1]);
replace("b", "B ", argv[1]);
replace("ç", "CC ", argv[1]);
replace("ð", "DH ", argv[1]);
replace("dʒ", "JH ", argv[1]);
replace("d", "D ", argv[1]);
replace("a", "AH ", argv[1]);
replace("ə", "AX ", argv[1]);
replace("eː", "EEH ", argv[1]);
replace("ɛː", "EHH ", argv[1]);
replace("ɛ", "EH ", argv[1]);
replace("ɚ", "AXR ", argv[1]);
replace("ɝ", "ER ", argv[1]);
replace("f", "F ", argv[1]);
replace("ɡ", "G ", argv[1]);
replace("h", "HH ", argv[1]);
replace("iː", "IIH ", argv[1]);
replace("i", "IY ", argv[1]);
replace("ɪ", "IH ", argv[1]);
replace("j", "Y ", argv[1]);
replace("k", "K ", argv[1]);
replace("l", "L ", argv[1]);
replace("ɫ", "L ", argv[1]);
replace("ɫ̩", "EL ", argv[1]);
replace("m", "M ", argv[1]);
replace("m̩", "EM ", argv[1]);
replace("ɒn", "EN ", argv[1]);
replace("n", "N ", argv[1]);
replace("n̩", "EN ", argv[1]);
replace("ŋ", "NG ", argv[1]);
replace("ŋ̍", "ENG ", argv[1]);
replace("œ", "OH ", argv[1]);
replace("oʊ", "OW ", argv[1]);
replace("øː", "OOH ", argv[1]);
replace("oː", "OOH ", argv[1]);
replace("ɔø", "OY ", argv[1]);
replace("ˈɔ", "OO ", argv[1]);
replace("ɔɪ", "OY ", argv[1]);
replace("ɔ", "AO ", argv[1]);
replace("p", "P ", argv[1]);
replace("r", "RR ", argv[1]);
replace("ɹ", "R ", argv[1]);
replace("ɐ", "EX ", argv[1]);
replace("ɜː", "ER ", argv[1]);
replace("ɜ", "EX ", argv[1]);
replace("ɾ", "EX ", argv[1]);
replace("ts", "TS ", argv[1]);
replace("s", "S ", argv[1]);
replace("tʃ", "CH ", argv[1]);
replace("ʃ", "SH ", argv[1]);
replace("t", "T ", argv[1]);
replace("uː", "UUH ", argv[1]);
replace("u", "UW ", argv[1]);
replace("ʊ", "UU ", argv[1]);
replace("v", "V ", argv[1]);
replace("ʌ", "AH ", argv[1]);
replace("w", "W ", argv[1]);
replace("x", "X ", argv[1]);
replace("yː", "YYH ", argv[1]);
replace("ʏ", "YY ", argv[1]);
replace("z", "Z ", argv[1]);
replace("ʒ", "ZH ", argv[1]);
replace("ʔ", "Q ", argv[1]);
replace("θ", "TH ", argv[1]);
//remove not used
//
//Hauptbetonung 
replace("ˈ", "", argv[1]);
//Nebenbetonung 
replace("ˌ", "", argv[1]);
//Anglizismen
replace("(eN )", "", argv[1]);
replace("(D e)", "", argv[1]);
return 0;
}
