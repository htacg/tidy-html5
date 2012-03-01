HTML2MARKDOWN=html2text
GIT=git
GITFLAGS=
DOXYGEN=doxygen
DOXYGENFLAGS=

.PHONEY: api-docs
all: bin/tidy

bin/tidy:
	$(MAKE) -C build/gmake
	$(MAKE) -C build/gmake doc

.FORCE:
# dummy target to force other targets to always get remade

README.md: README.html .FORCE
	$(HTML2MARKDOWN) $(HTML2MARKDOWNFLAGS) $< > $@

src/version.h: .FORCE
	$(GIT) $(GITFLAGS) log --pretty=format:'static const char TY_(release_date)[] = "https://github.com/w3c/tidy-html5/tree/%h";' -n 1 > $@

quickref.html: htmldoc/quickref.html .FORCE
	cp $< $@

api-docs:
	$(DOXYGEN) $(DOXYGENFLAGS) htmldoc/doxygen.cfg

install:
	sudo $(MAKE) install -C build/gmake

version: all src/version.h README.md quickref.html

clean:
	$(MAKE) clean -C build/gmake
	$(RM) test/testall.log
	$(RM) -r test/tmp
