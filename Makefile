randomkeys: randomkeys.c
	cc randomkeys.c

install: randomkeys.c
	cc randomkeys.c
	cp a.out ~/.local/bin/randomkeys
	cp ukwords.txt ~/.local/bin/ukwords.txt
