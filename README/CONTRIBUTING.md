# Contributing to HTML Tidy

So you want to contribute to Tidy? Fantastic! Here's a brief overview on how best to do so.

### Support request

If you are having trouble running console `Tidy`, or using the `LibTidy` API in your own project, then maybe the best places to get help is either via a comment in [Tidy Issues](https://github.com/htacg/tidy-html5/issues), or on the [Tidy Mail Archive](https://lists.w3.org/Archives/Public/html-tidy/) list.

In either place please start with a short subject to describe the issue. If it involves running Tidy on an html file, or if it’s an API question, make sure to include:

  - the version: `$ tidy -v`
  - what was the configuration used
  - a small sample input
  - the output
  - the _expected_ output expected
  - some sample code (if an API question).
  
These data will make replication of your issue much simpler for us.

If you do add sample HTML input, then it can also be very helpful if that sample **passes** the W3C [validator](https://validator.w3.org/#validate_by_upload). Tidy attempts to follow all current W3C standards.

If you are able to build tidy from [source](https://github.com/htacg/tidy-html5) (requires [CMake](https://cmake.org/download/)), and you can find the problem in the source code, then read on about how you can create a Pull Request (“PR”) to share your code and ideas.


### What to change

Here are some examples of things you might want to make a PR for:

 - New features
 - Bug fixes
 - Inefficient blocks of code
 - Memory problems
 - Language translations

If you have a more deeply-rooted problem with how the program is built or some of the stylistic decisions made in the code, it is best to [create an issue](https://github.com/htacg/tidy-html5/issues/new) before putting the effort into a pull request. The same goes for new features - it might be best to check the project's direction, existing pull requests, and currently open and closed issues first.

Concerning the “Tidy Code Style,” checkout [CODESTYLE.md](CODESTYLE.md), but looking at existing code is the best way to get a good feel for the patterns we use.


### Using Git appropriately

 1. Fork the repository to your GitHub account.
 2. Optionally create a **topical branch**, a branch whose name is succint but explains what you're doing, such as "feature/add-new-lines".
 3. Make your changes, committing at logical breaks.
 4. Push your work to your personal account.
 5. [Create a pull request](https://help.github.com/articles/using-pull-requests).
 6. Watch for comments or acceptance.

Please note - if you want to change multiple things that don't depend on each
other, it is better to use `branches`, and make sure you check the master branch back out before making more changes - that way we can take in each change seperately, otherwise Github has a tendancy to combine your requests into one.

If you are a continuing contributor then you will need to `rebase` your fork, to htacg `next`, **before** doing any more work, and likewise branches, otherwise we may not be able to cleanly merge your PR. This is a simple process:

```
$ git remote add upstream git@github.com:htacg/tidy-html5.git # once only
$ git checkout next
$ git status
$ git stash # if not clean
$ git fetch upstream
$ git rebase upstream/next
$ git stash pop # if required, and fix conflicts
$ git push      # update the fork next
```

This can be repeated for other branches, too.

### Help Tidy Get Better

It goes without saying **all help is appreciated**. We need to work together to make Tidy better!
