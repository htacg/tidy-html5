HTML2MARKDOWN=html2text
GIT=git
GITFLAGS=
DOXYGEN=doxygen
DOXYGENFLAGS=

.PHONEY: api-docs src/version.h
all: README.md src/version.h bin/tidy quickref.html api-docs

bin/tidy:
	$(MAKE) -C build/gmake
	$(MAKE) -C build/gmake doc

README.md: README.html
	$(HTML2MARKDOWN) $(HTML2MARKDOWNFLAGS) $< > $@

src/version.h:
	$(GIT) $(GITFLAGS) log --pretty=format:'static const char TY_(release_date)[] = "https://github.com/w3c/tidy-html5/tree/%h";' -n 1 > $@

quickref.html: htmldoc/quickref.html
	cp $< $@

api-docs:
	$(DOXYGEN) $(DOXYGENFLAGS) htmldoc/doxygen.cfg

install:
	sudo $(MAKE) install -C build/gmake

clean:
	$(MAKE) clean -C build/gmake
	$(RM) README.md
	$(RM) test/testall.log
	$(RM) -r test/tmp
