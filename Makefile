CFLAGS = -g -O -Wall -W -pedantic -std=c99 -O0 -I. -I/raylib/src -I../src -DPLATFORM_RPI
CFLAGS_WEB = -g -O -Wall -W -pedantic -std=c99 -O0 -I. -I/raylib/src/web -I../src/web  -DPLATFORM_WEB
CWEB =-Wall -std=c99 -Wno-missing-braces -O3 -s USE_GLFW=3 -s FORCE_FILESYSTEM=1 -s ASYNCIFY  -I. -I$(HOME)/git/raylib/src -I$(HOME)/git/raylib/src/external -L. -L$(HOME)/git/raylib/src -L$(HOME)/git/raylib/src $(HOME)/git/raylib/src/web/libraylib.a -DPLATFORM_WEB 


LDFLAGS = -L/raylib/src -L/opt/vc/lib
LDFLAGS_WEB = -L/raylib/src/web
LDLIBS = -lraylib -lm 

quick_maths: src_files/main.c src_files/config.h
	gcc $(CFLAGS) $(LDFLAGS) src_files/main.c -o quick_maths $(LDLIBS)
install: src_files/main.c src_files/config.h
	gcc $(CFLAGS) $(LDFLAGS) src_files/main.c -o quick_maths $(LDLIBS) && cp -f ./quick_maths $(HOME)/.local/bin/
web: src_files/main.c src_files/config.h
	emcc src_files/main.c -o quick_maths.html $(CWEB) -lm
