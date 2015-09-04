# Contributing to HTML Tidy

So you want to contribute to Tidy? Fantastic! Here's a brief overview on how best to do so.

### Support request

If you are having trouble running console `Tidy`, or using the `Tidy Library` API in your own project, then maybe the best places to get help is either via a comment in [Tidy Issues](https://github.com/htacg/tidy-html5/issues), or on the [Tidy Mail Archive](https://lists.w3.org/Archives/Public/html-tidy/) list.

### What to change

Here's some examples of things you might want to make a pull request for:

 - New features
 - Bug fixes
 - Inefficient blocks of code
 - Memory problems

If you have a more deeply-rooted problem with how the program is built or some of the stylistic decisions made in the code, it is best to [create an issue](https://github.com/htacg/tidy-html5/issues/new) before putting the effort into a pull request. The same goes for new features - it might be best to check the project's direction, existing pull requests, and currently open and closed issues first.

Concerning the 'Tidy Code Style', checkout [CODESTYLE.md](CODESTYLE.md), but looking at existing code is the best way to get a good feel for the patterns we use.

### Using Git appropriately

 1. Fork the repository to your GitHub account.
 2. Optionally create a **topical branch** - a branch whose name is succint but explains what
you're doing, such as "feature/add-new-lines"...
 3. Make your changes, committing at logical breaks.
 4. Push your work to your personal account.
 5. [Create a pull request](https://help.github.com/articles/using-pull-requests).
 6. Watch for comments or acceptance.

Please note - if you want to change multiple things that don't depend on each
other, it is better to use `branches`, and make sure you check the master branch back out before making more changes - that way we can take in each change seperate. Else github has a tendancy to combine your requests into one.

### Help Tidy Get Better

It goes without saying **all help is appreciated**. We need to work together to make Tidy! better...

; eof
