CFLAGS := -g -Wall -Werror

twyc:twyc.c
	$(CC) $^ $(CFLAGS) -o $@
	cp ./twyc /usr/bin/

