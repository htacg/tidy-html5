=============================
README for HTACG GitHub Pages
=============================

This repository consists of the HTML Tidy homepages.

For ease of maintenance by multiple contributors HTACG's GitHub pages take advantage of
GitHub’s Jekyll integration. Therefor it is necessary to be slightly familiar with Jekyll
and GitHub’s implementation of Jekyll in order to make changes to our sites.


References
----------

Everything you need to know about Jekyll can be found on
[jekyllrb.com](http://jekyllrb.com).


About Github and HTACG Pages
----------------------------

The HTAGC group main project page is served from files located in
[https://github.com/htacg/htacg.github.io](https://github.com/htacg/htacg.github.io). It
can be reached from [http://www.htacg.org](http://www.htacg.org) or 
[http://htacg.github.io](http://htacg.github.io). The latter is the standard means of
accessing the project page, however the former works because we've set up a domain name
and configured GitHub to use the domain name via the `CNAME` file in the repository.

HTACG Project pages are available as subdirectories of the HTACG domain, for example:

- [http://www.htacg.org/html-tidy](http://www.htacg.org/html-tidy)
- [http://www.htacg.org/binaries](http://www.htacg.org/binaries)
- etc.

In general this is intuitive behaviour of GitHub pages but it can cause some issues with
relative paths used for project web pages. For example:

The HTML-Tidy main project page is served from files located in
[https://github.com/htacg/tidy-html5/tree/gh-pages](https://github.com/htacg/tidy-html5/tree/gh-pages).
It can be reached from [http://www.html-tidy.org](http://www.html-tidy.org), or as above,
from [http://www.htacg.org/html-tidy](http://www.htacg.org/html-tidy).

This is where resource paths can be an issue. Thus it's important to follow the advice
given on [Jekyll's](http://jekyllrb.com/docs/github-pages/#project-page-url-structure)
site. This will ensure that resources such as stylesheets and images are served from the
appropriate directory.

In summary use the `site.baseurl` variable as described in the linked document, and when
performing local previewing start Jekyll's server with:

~~~
jekyll serve --baseurl ''
~~~

or

~~~
bundle exec jekyll serve --baseurl ''
~~~

Specifying the `baseurl` on the command line will override the base URL set in
`_config.yml`.


