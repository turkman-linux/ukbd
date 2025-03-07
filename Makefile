SHELL=/bin/bash
DESTDIR=/
LIBDIR=/lib/
SERVICE=openrc
library_files = $(patsubst %.c, %.o, $(wildcard library/*.c))
service_files = $(patsubst %.c, %.o, $(wildcard service/*.c))
gtk_files = $(patsubst %.c, %.o, $(wildcard gtk/*.c))

GTK_FLAGS = `pkg-config --cflags gtk+-3.0 gio-2.0` -g3
LD_FLAGS  = `pkg-config --libs gtk+-3.0 gio-2.0` -g3
all: clean build

%.o: %.c
	$(CC) -c $< -o $@ -Ilibrary -Ibuild -fPIC $(CFLAGS) $(GTK_FLAGS) -Igtk

main: $(service_files)
	mkdir -p build
	$(CC) $(service_files) \
	    -Ilibrary -nostdlib -lukbd  -Lbuild -lc -o build/main
	strip build/main

libukbd: $(library_files)
	mkdir -p build
	$(CC) $(library_files) -o build/libukbd.so \
	    -shared -fPIC -Ilibrary -nostdlib -lc
	strip build/libukbd.so


gui-gtk: libukbd $(gtk_files)
	mkdir -p build
	$(CC) atspi/atspi.c -o build/atspi  $(CFLAGS) $(GTK_FLAGS) \
	    $(LDFLAGS) $(LD_FLAGS) $(shell pkg-config --cflags --libs atspi-2 gtk+-3.0)
	bash gtk/generate_keytab.sh > build/str.c
	$(CC) $(gtk_files) -Ibuild build/str.c $(LDFLAGS) $(LD_FLAGS) \
	    -lX11 \
	    -Ilibrary -lukbd  -Lbuild -o build/gui-gtk

run: build
	LD_LIBRARY_PATH=$$PWD/build build/main

run-gtk: gui-gtk
	LD_LIBRARY_PATH=$$PWD/build build/gui-gtk

test:
	valac data/test.vala -o build/test-vala --vapidir=./library/ --pkg libukbd -X -I./library -X -L./build -X -lukbd  || true
	$(CC) data/test.c -o build/test-c -Ilibrary -lukbd -Lbuild || true
	@echo -ne "\033[33mPython test\033[;0m\n"
	LD_LIBRARY_PATH=$$PWD/build python3 data/test.py || true
	@echo -ne "\033[33mC test\033[;0m\n"
	LD_LIBRARY_PATH=$$PWD/build build/test-c || true
	@echo -ne "\033[33mVala test\033[;0m\n"
	LD_LIBRARY_PATH=$$PWD/build build/test-vala || true
	@if [[ `uname -m` == "x86_64" ]]; then \
	    make test-x86  || true ;\
	fi

test-x86:
	$(CC) data/test.s -o build/test-asm -Ilibrary -lukbd -Lbuild -nostdlib
	@echo -ne "\033[33mx86_64 Assembly test\033[;0m\n"
	LD_LIBRARY_PATH=$$PWD/build build/test-asm


build: libukbd main gui-gtk

install:
	install -Dm755 build/main $(DESTDIR)/usr/libexec/ukbd
	install -Dm755 build/libukbd.so $(DESTDIR)/usr/$(LIBDIR)
	install -Dm755 build/gui-gtk $(DESTDIR)/usr/bin/ukbd-gtk
	install -Dm755 build/atspi $(DESTDIR)/usr/bin/ukbd-atspi
	install -Dm755 data/ukbd.desktop $(DESTDIR)/usr/share/applications/
	install -Dm755 data/ukbd-atspi.desktop $(DESTDIR)/etc/xdg/autostart/
	install -Dm644 data/icon.svg $(DESTDIR)/usr/share/icons/hicolor/scalable/apps/ukbd.svg
	install -Dm644 data/gsettings.xml $(DESTDIR)/usr/share/glib-2.0/schemas/org.turkman.ukbd.gschema.xml
	make install_$(SERVICE) DESTDIR=$(DESTDIR)
	for file in data/icons/*.svg ; do \
	    install -Dm644 $$file $(DESTDIR)/usr/share/icons/hicolor/scalable/actions/ ;\
	done

install_systemd:
	install -Dm755 data/systemd.service $(DESTDIR)/lib/systemd/system/ukbd.service

install_openrc:
	install -Dm755 data/openrc.service $(DESTDIR)/etc/init.d/ukbd

install_sysvinit:
	install -Dm755 data/sysvinit.service $(DESTDIR)/etc/init.d/ukbd

clean:
	rm -vfr $(service_files) $(gtk_files) $(library_files) build */__pycache__
