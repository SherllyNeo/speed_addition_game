CFLAGS = -g -O -Wall -W -pedantic -std=c99 -O0 -I. -I/raylib/src -I../src -DPLATFORM_RPI

LDFLAGS = -L/raylib/src -L/opt/vc/lib
LDLIBS = -lraylib -lm 

quick_maths: src_files/main.c src_files/config.h
	gcc $(CFLAGS) $(LDFLAGS) src_files/main.c -o quick_maths $(LDLIBS)
install: src_files/main.c src_files/config.h
	gcc $(CFLAGS) $(LDFLAGS) src_files/main.c -o quick_maths $(LDLIBS) && cp -f ./quick_maths $(HOME)/.local/bin/
web: src_files/main.c src_files/config.h
	emcc $(CFLAGS) $(LDFLAGS) src_files/main.c -o quick_maths $(LDLIBS)
