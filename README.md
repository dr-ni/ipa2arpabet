# ipa2arpabet
Straightforward translator from International Phonetic Alphabet (IPA) to CMU ARPAbet. Currently only German language support.

Build:
make

Install:
sudo make install

Uninstall:
sudo make uninstall


    Usage: ipa2arpabet-de filename

Example:

$ echo "Hallo Welt!" | espeak -v de -x --ipa -q > ipafile.txt

$ cat ipafile.txt

$ hˈaloː vˈɛlt

$ cp ipafile.txt arpafile.txt

$ ipa2arpabet-de arpafile.txt

$ cat arpafile.txt

$ HH AH L OOH  V EH L T





