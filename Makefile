HTML2MARKDOWN=html2text
GIT=git
GITFLAGS=

all: bin/tidy README.md VERSION

bin/tidy:
	$(MAKE) -C build/gmake

README.md: README.html
	$(HTML2MARKDOWN) $(HTML2MARKDOWNFLAGS) $< > $@

VERSION:
	$(GIT) $(GITFLAGS) log --pretty=format:'https://github.com/w3c/tidy-html5/tree/%h' -n 1 > $@

install:
	sudo $(MAKE) install -C build/gmake

clean:
	$(MAKE) clean -C build/gmake
	$(RM) README.md
