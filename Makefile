CC=gcc

all: ipa2arpabet-de

ipa2arpabet-de: ipa2arpabet.c ipa2arpabet-de.c
	$(CC) ipa2arpabet.c ipa2arpabet-de.c -o ipa2arpabet-de

install:
	sudo cp ipa2arpabet-de /usr/local/bin/
uninstall:
	sudo rm -f /usr/local/bin/ipa2arpabet-de
clean:
	rm -f ipa2arpabet-de
	rm -f *.o
