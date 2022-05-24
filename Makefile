 #=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#
#	KhajiitBot 2.0
#	NotArtyom
#	01/04/22
#
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

export

PREFIX ?= /usr/share

CC = gcc
AR = ar
LD = ld

#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

BASEDIR := $(shell pwd)
BINDIR := $(BASEDIR)/bin
OBJDIR := $(BASEDIR)/obj
SRCDIR := $(BASEDIR)/src
RESDIR := $(BASEDIR)/res
BINARY_NAME := khajiitbot

#--------
LIBS = -lpthread -ldiscord -lcurl
#--------

SOURCES := $(shell find ./src -name '*.c')
OBJECTS := $(foreach tmp, $(SOURCES:%.c=%.o), $(OBJDIR)/$(tmp))

CFLAGS := -w $(LIBS) -I $(SRCDIR)
LDFLAGS := -L /usr/lib -fwhole-program $(LIBS)

#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

.PHONY: all clean test install uninstall
all: clean
	mkdir -p $(BINDIR) $(OBJDIR)
	$(MAKE) $(OBJECTS)
	$(MAKE) $(BINARY_NAME)
	
.SECONDEXPANSION :
$(BINARY_NAME): $(OBJECTS)
	@echo "[LD] Creating final binary"
	@mkdir -p $(BINDIR)
	$(CC) $(shell find $(OBJDIR) -name '*.o') $(LDFLAGS) -o $(BINDIR)/$@

$(OBJECTS): $$(patsubst $$(OBJDIR)%.o, $$(BASEDIR)%.c, $$@)
	@echo "[CC] -c $(shell realpath -m --relative-to=$(PWD) $(patsubst $(OBJDIR)%, $(BASEDIR)%, $(@:%.o=%.c))) -o $(shell realpath -m --relative-to=$(PWD) $(@))"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $(patsubst $(OBJDIR)%, $(BASEDIR)%, $(@:%.o=%.c)) -o $@ -pthread

#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

clean:
	rm $(OBJDIR) -vfr
	rm $(BINDIR) -vfr

run:
	cd $(BINDIR) && ./$(BINARY_NAME) -d $(BASEDIR)/config.json
