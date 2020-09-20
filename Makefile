CC=msp430-gcc
CFLAGS=-mmcu=msp430g2553 -g
LDFLAGS=

SRCDIR=source
BINDIR=bin

TARGET=


.PHONY: all
all: run

$(BINDIR)/$(TARGET).elf: $(SRCDIR)/$(TARGET)/main.c
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

build: $(BINDIR)/$(TARGET).elf
run: $(BINDIR)/$(TARGET).elf
	echo "prog $<\n exit" | mspdebug rf2500

.PHONY: clean
clean:
	rm -r $(BINDIR) 2>/dev/null; true
