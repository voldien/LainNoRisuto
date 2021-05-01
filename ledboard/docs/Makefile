#!/bin/bash

TARGET := ledboard.dvi

all : $(TARGET)
	echo ""

$(TARGET) : ledboard.tex
	latex $^ -o $(TARGET)
