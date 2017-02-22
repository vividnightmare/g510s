default: g510s

g510s.o: g510s.c g510s.h
	gcc -Wall `pkg-config --cflags gtk+-3.0 appindicator3-0.1` -c g510s.c -o g510s.o

g510s-clock.o: g510s-clock.c g510s.h
	gcc -Wall -c g510s-clock.c -o g510s-clock.o

g510s-config.o: g510s-config.c g510s.h
	gcc -Wall -c g510s-config.c -o g510s-config.o

g510s-keys.o: g510s-keys.c g510s.h
	gcc -Wall -c g510s-keys.c -o g510s-keys.o

g510s-list.o: g510s-list.c g510s.h
	gcc -Wall -c g510s-list.c -o g510s-list.o

g510s-misc.o: g510s-misc.c g510s.h
	gcc -Wall -c g510s-misc.c -o g510s-misc.o

g510s-net.o: g510s-net.c g510s.h
	gcc -Wall -c g510s-net.c -o g510s-net.o

g510s-signals.o: g510s-signals.c g510s.h
	gcc -Wall `pkg-config --cflags gtk+-3.0` -c g510s-signals.c -o g510s-signals.o

g510s-threads.o: g510s-threads.c g510s.h
	gcc -Wall `pkg-config --cflags appindicator3-0.1` -c g510s-threads.c -o g510s-threads.o

g510s: g510s.o g510s-clock.o g510s-config.o g510s-keys.o g510s-list.o g510s-misc.o g510s-net.o g510s-signals.o g510s-threads.o
	gcc -O3 -Wall g510s.o g510s-clock.o g510s-config.o g510s-keys.o g510s-list.o g510s-misc.o g510s-net.o g510s-signals.o g510s-threads.o -o g510s -lg15 -lg15render -lpthread -rdynamic `pkg-config --libs gtk+-3.0 appindicator3-0.1`

install:
	-mkdir /usr/local/share/g510s
	-cp g510s.svg /usr/local/share/g510s
	-cp g510s-alert.svg /usr/local/share/g510s
	-cp g510s.glade /usr/local/share/g510s
	-cp g510s /usr/local/bin
	-cp 99-g510s.rules /lib/udev/rules.d
	-cp g510s.desktop /etc/xdg/autostart

uninstall:
	-rm -f /usr/local/share/g510s/g510s.svg
	-rm -f /usr/local/share/g510s/g510s-alert.svg
	-rm -f /usr/local/share/g510s/g510s.glade
	-rm -f /usr/local/bin/g510s
	-rm -f /lib/udev/rules.d/99-g510s.rules
	-rm -f /etc/xdg/autostart/g510s.desktop
	-rmdir /usr/local/share/g510s

clean:
	-rm -f g510s
	-rm -f g510s.o
	-rm -f g510s-clock.o
	-rm -f g510s-config.o
	-rm -f g510s-keys.o
	-rm -f g510s-list.o
	-rm -f g510s-misc.o
	-rm -f g510s-net.o
	-rm -f g510s-signals.o
	-rm -f g510s-threads.o
