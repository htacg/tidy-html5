# Contributing to HTML Tidy

So you want to contribute to Tidy? Fantastic! Here's a brief overview on how best to do so.

### Support request

If you are having trouble running console `Tidy`, or using the `LibTidy` API in your own project, then maybe the best places to get help is either via a comment in [Tidy Issues](https://github.com/htacg/tidy-html5/issues), or on the [Tidy Mail Archive](https://lists.w3.org/Archives/Public/html-tidy/) list.

And please do a **search** using different **key** words - see [searching](https://help.github.com/articles/searching-issues-and-pull-requests/) - to make sure it is **not** a duplicate. If something similar has been discussed before, but you still feel this is **different**, then add that related reference in your post...

In either place please start with a short subject to describe the issue. If it involves running Tidy on an html file, or if it’s an API question, make sure to include:

  - the version: `$ tidy -v`
  - what was the configuration used
  - a small sample input
  - the output
  - the _expected_ output
  - some sample code (if an API question).
  
This information will make replication of your issue much simpler for us.

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

 1. Fork tidy to your own github account. Use top right `Fork` icon.
 2. Optional: Generate a SSH Key, and add it to your `https://github.com/<name>` settings, SSH and GPG keys
 3. Clone your own fork - `$ git clone git@github.com:<name>/tidy-html5.git [tidy-fork]` Or using `https`.
 4. Create a branch - `$ cd tidy-fork; $ git checkout -b <branch-name>`
 5. Edit, and commit your changes to this `branch` of your fork.
 6. Test your changes, and if appropriate run [regression](https://github.com/htacg/tidy-html5-tests/blob/next/README/RUNTESTS.md) tests.
 7. Publish the branch - `$ git push -u origin <branch-name.` - to your remote fork.
 8. Create a [Pull Request](https://help.github.com/articles/about-pull-requests/), a **PR**, here.
 9. Watch for comments, acceptance.

Item 2., SSH Key, is optional, and only required if you want to use `clone git@github.com...`. And if you generate the ssh without a `passphrase`, things like `git push` can be done without a password. Just convenience. Alternatively you can use the `HTTPS` protocol...

Concerning 5., editing and committing your changes, **generally** it is better to `commit` changes often, adding an appropriate commit message to each, like `$ git commit -m "Is. #NNN - reason for change" <file[s]>`. This also aids in the **PR** review. 

But the situation varies. Like adding say an option, which can mean several files have to be edited, where it is likely appropriate to combine a considerable number of edits into one commit. There can be no hard and fast rules on this.

Please note, if you want to change **multiple** things that don't depend on each other, use **different** `branches`, and make sure you check the `next` branch back out, before making more changes in a **new** branch name. That way we can take in each **change** separately, otherwise Github will **combine** all your branch commits into one **PR**. 

See below on keeping your forks `next` fully in sync with here, called `upstream` - **this is important**.

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

This has to be repeated for other branches, too. `$ git checkout <your-branch>`, `$ git rebase next`, fix conflict, if any, and `$ git push`, for **each** branch. It is **not** fun to keep multiple `branches` fully up-to-date with an active `upstream`...

Of course, the **regression** tests, 6., are really only if you have made `code` changes, but it is a good habit to get into. As can be seen the `tests` are in a **separate** repo, so you must also clone that, or **fork** and clone that, to be able to present a **PR**. This is best done in the same `root` folder where where you cloned `tidy-html5`, and your `tidy-fork`. See [RUNTESTS.md](https://github.com/htacg/tidy-html5-tests/blob/next/README/RUNTESTS.md).

In brief, for unix, to use your potentially **new** `tidy-fork` tidy executable -

```
$ git clone git@github.com:htacg/tidy-html5-tests.git
$ cd tidy-html5-tests/tools-sh
$ ./testall.sh ../../tidy-fork/build/cmake/tidy
$ diff -u ../cases/testbase-expects ../cases/testbase-results
```

Use folder `tools-cmd` for windows. Run `alltest.bat --help`. 

If the `tests` shows a different exit value, or there are differences between the `expects` and `results`, these **must** be studied, and checked, very carefully. There may be cases where the **new** `results` are correct, in which case a simultaneous **PR** for the forked `tests` **must** be created to match your forked source **PR**.

Do **NOT** change either the root `version.txt` here, nor the `cases/_version.txt` in `tests`. This will be handled by the person that does the **PR** merge. To differentiate your modified `tidy` there is a cmake option, like `-DTIDY_RC_NUMBER=I123`, which will appear in `tidy -v` as `5.7.16.I123`. The number can be anything, but using the relevant issue value is a good choice.

Add an `issue` if you need further **help**... thanks...

### Help Tidy Get Better

It goes without saying **all help is appreciated**. We need to work together to make Tidy better!

