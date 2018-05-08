# Makefile
# 04-Jan-15 Markku-Juhani O. Saarinen <mjos@iki.fi>

BIN	= xtest 
OUT = libkuznechik.a
OBJS	= main.o \
	kuznechik_128bit.o \
	ctr.o
#	kuznechik_8bit.o

DIST	= kuznechik

CC	= g++ -std=c++11
CFLAGS	= -Ofast -static
LIBS	=
LDFLAGS	= -Ofast -s -static
INCS	=

# EXTRA   = -mcpu=cortex-a53 -mfpu=neon-fp-armv8 -D__ARM_NEON_
EXTRA = 

$(OUT): $(OBJS) 
	ar crf $(OUT) $(OBJS) $(LIBS)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(EXTRA) -o $(BIN) $(OBJS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCS) $(EXTRA) -c $< -o $@

clean:
	rm -rf $(DIST)-*.t?z $(OBJS) $(BIN) *~

dist:	clean
	cd ..; \
	tar cfvJ $(DIST)/$(DIST)-`date -u "+%Y%m%d%H%M00"`.txz $(DIST)/*
