#!/bin/bash

# Version
MAJOR := 1
MINOR := 0
PATCH := 0
STATE := a
VERSION := $(MAJOR).$(MINOR)$(STATE)$(PATCH)
# Utilitys
RM := rm -f
CP := cp
MKDIR := mkdir -p
CHMOD := chmod
# Compilers.
LATEX := latex
PDFLATEX := pdflatex
DVI2PDF := dvipdfm 
BIBTEX := bibtex
# Source files.
SRCS := $(wildcard *.tex)
BIBSRCS := $(wildcard *.aux)
BIBSRCS :=  $(notdir $(subst .tex,.aux,$(SRCS))) 

# Sub targets.
PDFTARGET := $(notdir $(subst .tex,.pdf,$(SRCS)))
BIBTARGET := $(notdir $(subst .tex,.aux,$(SRCS))) 

TARGET := latex-demo
TARGETS := $(PDFTARGET) $(BIBTARGET)

all : $(TARGETS)
	@echo "Finished compiling document."

%.pdf : %.tex
	$(PDFLATEX) $^
	$(BIBTEX) $(BIBTARGET)
	$(PDFLATEX) $^
	$(PDFLATEX) $^

%.bbl : %.aux
	$(BIBTEX) $^

clean :
	$(RM) *.pdf *.dvi *.log *.aux *.toc *.out *.bbl *.blg *.bst

distribution:
	$(RM) -r $(TARGET)-$(VERSION)
	$(MKDIR) $(TARGET)-$(VERSION)
	$(CP) -r code img $(TARGET)-$(VERSION)
	$(CP) *.tex *.bib Makefile $(TARGET)-$(VERSION)
	tar cf - $(TARGET)-$(VERSION) | gzip -c > $(TARGET)-$(VERSION).tar.gz
	$(RM) -r $(TARGET)-$(VERSION)

.PHONY : clean distribution

