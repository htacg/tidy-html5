HTML2MARKDOWN=html2text

all: bin/tidy README.md

bin/tidy:
	$(MAKE) -C build/gmake

README.md: README.html
	$(HTML2MARKDOWN) $(HTML2MARKDOWNFLAGS) $< > $@

install:
	sudo $(MAKE) install -C build/gmake

clean:
	$(MAKE) clean -C build/gmake
	$(RM) README.md
