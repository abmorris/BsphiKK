# RapidFit directory
RAPIDDIR   = ../../RapidFit

# Compiler and shell
CC         = g++
SHELL      = /bin/bash
RM         = rm -f

# Include ROOT files as system headers as they're NOT standards complient and we do not want to waste time fixing them!
# ROOT has some broken backwards compatability for OSX so won't claim to be a set of system headers
ROOTCFLAGS = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --cflags | awk -F "-I" '{print $$1" -isystem"$$2}' )
ROOTLIBS   = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --libs)
#EXTRA_ROOTLIBS=-lRooFit -lRooStats -lRooFitCore

# Extensions
SRCEXT     = cpp
HDREXT     = h
OBJEXT     = o
LIBEXT     = so

# Directories
PWD        = $(shell pwd)
SRCDIR     = src
BINSRCDIR  = app
LIBSRCDIR  = lib
HDRDIR     = include
OBJDIR     = build
LIBDIR     = lib
BINDIR     = bin

# RapidFit directories
RFINCDIR    = $(RAPIDDIR)/framework/include
RFINCPDFDIR = $(RAPIDDIR)/pdfs/include
RFINCUTILS  = $(RAPIDDIR)/utils/include
RFLIBDIR    = $(RAPIDDIR)/lib

# Get files and make list of objects and libraries
BINSRCS   := $(shell find $(SRCDIR)/$(BINSRCDIR) -name '*.$(SRCEXT)')
LIBSRCS   := $(shell find $(SRCDIR)/$(LIBSRCDIR) -name '*.$(SRCEXT)')
HDRS      := $(shell find $(HDRDIR) -name '*.$(HDREXT)')
LIBS      := $(patsubst $(SRCDIR)/$(LIBSRCDIR)/%.$(SRCEXT), $(LIBDIR)/lib%.$(LIBEXT), $(LIBSRCS))
BINS      := $(patsubst $(SRCDIR)/$(BINSRCDIR)/%.$(SRCEXT), $(BINDIR)/%, $(BINSRCS))
RFLIBS    := $(shell find $(RFLIBDIR) -name '*.$(LIBEXT)')

# Where the output is
OUTPUT     = $(OBJDIR)/*/*.$(OBJEXT) $(OBJDIR)/*.$(OBJEXT) $(LIBDIR)/*.$(LIBEXT) $(BINDIR)/*

# Compiler flags
CXXFLAGS   = -Wall -fPIC -I$(HDRDIR) -I$(RFINCDIR) -I$(RFINCPDFDIR) -I$(RFINCUTILS) $(ROOTCFLAGS) 
LIBFLAGS   = -L$(LIBDIR) -L$(RFLIBDIR) $(ROOTLIBS) -lprogbar -lGetTree -lboost_program_options $(EXTRA_ROOTLIBS) 

all : $(BINS) Makefile
libs : $(LIBS)
# Build binaries
$(BINDIR)/% : $(OBJDIR)/$(BINSRCDIR)/%.$(OBJEXT) $(LIBS)
	$(CC) $(LIBFLAGS) $^ $(LIBS) $(RFLIBS) -o $@
# Build libraries
$(LIBDIR)/lib%.$(LIBEXT) : $(OBJDIR)/$(LIBSRCDIR)/%.$(OBJEXT)
	$(CC) -shared $< -o $@
# Build objects
$(OBJDIR)/%.$(OBJEXT) : $(SRCDIR)/%.$(SRCEXT)
	$(CC) $(CXXFLAGS) -c $< -o $@
# Remove all the output
clean :
	$(RM) $(OUTPUT)