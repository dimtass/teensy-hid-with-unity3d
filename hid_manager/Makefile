
OS = LINUX
#OS = MACOSX
#OS = WINDOWS

PROG = hid_manager

# To set up Ubuntu Linux to cross compile for Windows:
#
#    apt-get install mingw32 mingw32-binutils mingw32-runtime
#
# Just edit the variable above for WINDOWS, then use "make" to build rawhid.exe

TARGET = $(PROG)
CC = gcc
STRIP = strip
CFLAGS = -Wall -Ofast -DOS_$(OS)
LIBS = -lusb

OBJS = $(PROG).o hid.o


all: $(TARGET)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LIBS)
	$(STRIP) $(PROG)

$(PROG).exe: $(PROG)
	cp $(PROG) $(PROG).exe

hid.o: hid_$(OS).c hid.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(PROG) $(PROG).exe $(PROG).dmg
	rm -rf tmp

