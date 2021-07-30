HTML Tidy Release Process Single Point Lesson (SPL)
===================================================

Purpose
-------
This lesson documents how to release a new, officially released version of HTML Tidy. Following the steps in this SPL ensures consistency between releases and results in a predictable experience for the end users of HTML Tidy.


Definition
----------
HTACG HTML Tidy is a library and console application, and the release process is intended to officially designate a point of stability, where "stability" is ABI and API stability. "Stability" is represented by an even minor version number, and "released" means the HTACG has published and made available an even minor version number version of HTML Tidy.

Due to the number of platforms and language bindings which have adopted HTML Tidy, we are highly dependent on package managers to track the latest release versions of HTML Tidy, and release it on these other platforms. We cannot maintain distributions and language bindings for your favorite operating system or language package manager.


Release Process Overview
------------------------
The release process consists largely of the following steps:

### Lead up:

 - Create the next release milestone on Github if not already done.
 - Decide on PR's to include in the release, bumping version.txt, accordingly.
 - Decide on any show-stopper outstanding issues, and action them.
 - Change milestone of all excluded-this-time issues to the next milestone, or to indefinite.
 - Decide target date for release.

### Release:

- Update the version number to the next release version, e.g., from 5.5.xx to 5.6.0.
- Generate a change log.
- Push this change to `next`.
- Merge this branch to `master`.
- Tag the release on `master`.
- Update the version number of the `next` branch to the next development version, e.g., from 5.8.0 to 5.9.0. At this point, both versions are identical except for the version number.
- Generate the API documentation for `next`.
- Generate the API documentation for `master`.
- Update the https://api.html-tidy.org/ website with the new API documentation.
- Update the https://www.html-tidy.org/ website with the new release version.
- Update the https://binaries.html-tidy.org/ website.
- Push all of the changes.
- Build binaries.
- Create a Github release per the Git tag created above.
- Post the binaries in the release.


Release Steps in Detail
--------------------------

### Update the version number to the next release version

In the `next` branch, modify the `version.txt` file to the next release version, for example, 5.8.0, and set the date.


### Generate a change log

If necessary, install the `github_changelog_generator`. This requires that you have a Ruby environment on your computer, which you probably do because the regression tests require it.

~~~
gem install github_changelog_generator
~~~

You’ll also need a Github personal access token in order for the tool to pull information from Github. You can acquire one [here](https://github.com/settings/tokens).

Generate the change log like so:

~~~
github_changelog_generator -u htacg -p tidy-html5 \
   --token [github_access_token] \
   --since-tag 5.6.0 \
   --usernames-as-github-logins \
   --future-release 5.8.0 \
   -o README/CHANGELOG.md
~~~

**Important**: the `--since-tag` value should be the git tag of the previous release, because we're only interested in the changes since then. The `--future-release` value should be the git tag that you _will apply_ (but have not yet) for this release.


### Commit this change to `next`

~~~
git add .
git commit -m 'Releasing HTML Tidy 5.8.0'
~~~


### Merge this branch to `master`

~~~
git checkout master
git merge next
~~~


### Tag the release on `master`

~~~
git tag -a 5.8.0 -m "HTML Tidy version 5.8.0"
~~~


### Update the version number of the `next` branch

For example, from from 5.8.0 to 5.9.0. At this point, both versions are identical except for the version number. Edit the `version.txt` file to make this change, and then
commit it to the repository.

### Generate the API documentation for `next`

First, build the `next` binary in `build/cmake`, so that API documentation tools have a correct version of HTML Tidy to work with. Perform a `git clean -xdf` in this directory prior to building for good measure.

After building, `cd` to the correct directory and build the documentation:

~~~
cd html-tidy.org.api/tidy-html5-doxygen
./build_docs.sh
~~~

Then in the `html-tidy.org.api/tidy-html5-doxygen/output` directory, rename the resulting directory and file to `tidylib_api_next/` and `quickref_next.html`, and move them into `html-tidy.org.api/tidy/`.


### Generate the API documentation for `master`

First, checkout `master` build the binary in `build/cmake`, so that API documentation tools have a correct version of HTML Tidy to work with. Perform a `git clean -xdf` in this directory prior to building for good measure.

After building, `cd` to the correct directory and build the documentation:

~~~
cd html-tidy.org.api/tidy-html5-doxygen
./build_docs.sh
~~~

Move the resulting directory and file into `html-tidy.org.api/tidy/` directly.

### Update the https://api.html-tidy.org/ website with the new API documentation

Check the copyright dates in `_includes/footer.md`.

~~~
cd html-tidy.org.api/
git add .
git commit -m "Added API documentation for master and next."
git push
~~~

### Update the https://www.html-tidy.org/ website with the new release version

Check the copyright dates in `_includes/footer.md`.

Update `html-tidy.org/homepage/_posts/1970-01-01-htmltidy.md` for the current release version and release year.

~~~
cd html-tidy.org/
git add .
git commit -m "Added API documentation for master and next."
git push
~~~


### Push all of the changes

Back in `tidy-html5/`

~~~
git checkout master
git push
git push origin <tag_name>
git checkout next
git push
~~~


### Build binaries

This is OS specific.

### Create a Github release per the Git tag created above

Do this on Github.

### Post the binaries in the release

Post the binaries here.

### Update the https://binaries.html-tidy.org/ website

Modify the files to point to the binaries in the Github releases.
