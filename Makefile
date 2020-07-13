CC=gcc

all: ipa2arpabet

ipa2arpabet: ipa2arpabet.c 
	$(CC) ipa2arpabet.c -o ipa2arpabet

install:
	sudo cp ipa2arpabet /usr/local/bin/
uninstall:
	sudo rm -f /usr/local/bin/ipa2arpabet
clean:
	rm -f ipa2arpabet
	rm -f *.o
