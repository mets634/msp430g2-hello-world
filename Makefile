CC=msp430-gcc
CFLAGS=-mmcu=msp430g2553 -g
LDFLAGS=

SRCDIR=source
BINDIR=bin


.PHONY: all
all:
	bash compile_all.sh


$(BINDIR)/$(TARGET).elf: $(SRCDIR)/$(TARGET)/main.c $(EXTRADEP)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

build: $(BINDIR)/$(TARGET).elf
run: $(BINDIR)/$(TARGET).elf
	echo "prog $<\n exit" | mspdebug rf2500


.PHONY: debug
debug:
	mspdebug rf2500

.PHONY: clean
clean:
	rm -r $(BINDIR) 2>/dev/null; true
