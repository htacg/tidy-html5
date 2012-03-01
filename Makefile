HTML2MARKDOWN=html2text
GIT=git
GITFLAGS=

all: README.md src/version.h bin/tidy

bin/tidy:
	$(MAKE) -C build/gmake
	$(MAKE) -C build/gmake doc

README.md: README.html
	$(HTML2MARKDOWN) $(HTML2MARKDOWNFLAGS) $< > $@

src/version.h:
	$(GIT) $(GITFLAGS) log --pretty=format:'static const char TY_(release_date)[] = "https://github.com/w3c/tidy-html5/tree/%h";' -n 1 > $@

install:
	sudo $(MAKE) install -C build/gmake

clean:
	$(MAKE) clean -C build/gmake
	$(RM) README.md
	$(RM) src/version.h
