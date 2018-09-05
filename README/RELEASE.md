# HTACG HTML Tidy

The **Release Process** is made up of many little steps. These have been documented before in issues like [394-1](https://github.com/htacg/tidy-html5/issues/394#issuecomment-206952915), and [394-2](https://github.com/htacg/tidy-html5/issues/394#issuecomment-207814834), and others, but this is to further **document** the process...

This assumes the current `next` branch is version 5.7.XXX. See VERSION.md for chosen version scheme.

## Release Process for 5.8.0

### Lead up:

 - Create the next release milestone, 5.10, if not already done...
 - Decide on PR's to include, bumping version.txt, accordingly...
 - Decide on any show-stopper outstanding issues, and action...
 - Change milestone of all excluded this time issues to the next 5.10 milestone, or to indefinite...
 - Decide target date for release...
 
### The Release:
 
 1. Update version.txt to 5.8.0, and date... commit
 2. Create branch, `$ git checkout -b release/5.8`
 3. Update README/vershist.log... perl script... commit
 4. Add `$ git tag 5.8.0`
 5. Publish `$ git push -u origin release/5.8 --tags`
 6. Generate release 5.8.0.html... perl script... copy to...
 7. Create Github release v5.8.0 - becomes [Latest Release](https://github.com/htacg/tidy-html5/releases)
 8. Other things?
    - Generate release binaries
    - Add [binaries](http://binaries.html-tidy.org/)
    - Add api [docs](http://api.html-tidy.org/#part_apiref)
    - Update web pages [html-tidy.org](http://www.html-tidy.org/)

### Post:

 - Update `master` branch to `release`
 - Update `next` version.txt to 5.9.0, open for new fixes...
 - Add more binaries...

## Notes on `Release Process`:
 
This **HTACG HTML Tidy** `official` release process must be supplemented with distribution by others. 

Of course, if possible, we recomend building tidy from the git source, it is easy, but also in some OS'es others offer distribution in various ways... 

See [Get Tidy](http://www.html-tidy.org/#homepage19700601get_tidy) - This page really needs expanding. There are some suggestions pending, and more feedback welcome...

; eof
