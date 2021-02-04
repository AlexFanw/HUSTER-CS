#!/bin/bash

convert slides.pdf \
  -sharpen "0x1.0" \
  -type truecolor -resize 400x300 slides.bmp

mkdir -p $NAVY_HOME/fsimg/share/slides/
cp *.bmp $NAVY_HOME/fsimg/share/slides/
