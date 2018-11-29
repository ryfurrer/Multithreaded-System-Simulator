# ------------------------------------------------------------
# Makefile for CMPUT 379 A4
#
# Usage: make  // compile the programs
#        make tar // create a 'tar.gz' archive of 'allFiles'
#        make clean // remove unneeded files
# ------------------------------------------------------------

CC= g++
CFLAGS= -std=c++11 -Wall -I.
MKDIR = mkdir
target=	submit

BINARY = a4tasks
BUILDDIR = build
SOURCEDIR = src
HEADERDIR = src

CPP_FILES := $(shell find $(SOURCEDIR) -name '*.cpp')
SOURCES = $(shell find $(SOURCEDIR) -name '*')
OBJECTS := $(addprefix $(BUILDDIR)/,$(CPP_FILES:%.cpp=%.o))
SUBMIT_FILES = $(SOURCES) Makefile report.pdf

# ------------------------------------------------------------



all: setup $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BINARY)

$(BUILDDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(dir $<) -c $< -o $@

setup:
	$(MKDIR) -p $(BUILDDIR)/$(SOURCEDIR)

tar:
	tar -cvf $(target).tar $(SUBMIT_FILES)
	gzip $(target).tar

clean:
	rm $(BUILDDIR) -rf
	rm $(BINARY) -f
	rm $(target).tar.gz -f
