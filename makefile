CC=clang
SRCDIR=./src
BUILDDIR=./build
OBJDIR=$(BUILDDIR)/obj
PPMACROS=
CFLAGS=-Wall
LIBFLAGS=
LIBTARGET=
osname:=$(shell uname -s)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/obj/%.o,$(wildcard $(SRCDIR)/*.c))
SYSMEM=$(patsubst $(SRCDIR)/systemMem/%.c,$(BUILDDIR)/obj/%.o,$(wildcard $(SRCDIR)/systemMem/*.c))
$(info $(SYSMEM))
ifdef DEBUG
	PPMACROS=-DDEBUG
endif

ifeq ($(osname), Darwin)
LIBFLAGS=-dynamiclib -fPIC
LIBTARGET=libnotmalloc.dylib
endif

all:build-lib
ifdef DEBUG
	$(CC) $(CFLAGS) test.c -L$(BUILDDIR)/lib -lnotmalloc -o $(BUILDDIR)/test
endif


build-lib:$(OBJS)
	$(CC) $(wildcard $(BUILDDIR)/obj/*.o)  $(LIBFLAGS) -o $(BUILDDIR)/lib/$(LIBTARGET)


$(OBJDIR)/%.o:$(SRCDIR)/%.c build-debug 
	$(CC) $(CFLAGS) $(PPMACROS) -c $< -o $@



build-debug:
ifdef DEBUG
	$(CC) $(PPMACROS) -c $(wildcard $(SRCDIR)/debug/*.c) -o $(BUILDDIR)/obj/debug.o
endif



clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(BUILDDIR)/lib/*
	rm -rf $(BUILDDIR)/test