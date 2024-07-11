CC=clang
SRCDIR=./src
BUILDDIR=./build
OBJDIR=$(BUILDDIR)/obj
PPMACROS=
CFLAGS=-Wall
LIBFLAGS=-fPIC
LIBTARGET=
osname:=$(shell uname -s)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/obj/%.o,$(wildcard $(SRCDIR)/*.c))
ifdef DEBUG
CFLAGS+=-DDEBUG -g
endif

ifeq ($(osname), Darwin)
LIBFLAGS+=-dynamiclib
LIBTARGET=libnotmalloc.dylib
else ($(osname),Linux)
LIBFLAGS+=-shared 
LIBTARGET=libnotmalloc.so
endif

all:build-lib
ifdef DEBUG
	$(CC) $(CFLAGS) test.c  -I./src/ -L$(BUILDDIR)/lib -lnotmalloc -o $(BUILDDIR)/test
endif


build-lib:$(OBJS)
	$(CC) $(wildcard $(BUILDDIR)/obj/*.o) $(CFLAGS) $(LIBFLAGS) -o $(BUILDDIR)/lib/$(LIBTARGET)


$(OBJDIR)/%.o:$(SRCDIR)/%.c build-debug 
	$(CC) $(CFLAGS) -c $< -o $@



build-debug:
ifdef DEBUG
	$(CC) $(CFLAGS) -c $(wildcard $(SRCDIR)/debug/*.c) -o $(BUILDDIR)/obj/debug.o
endif



clean:
	rm -rf $(BUILDDIR)/lib/*
	rm -rf $(BUILDDIR)/obj/*
	rm -rf $(BUILDDIR)/test.dSYM
	rm $(BUILDDIR)/test