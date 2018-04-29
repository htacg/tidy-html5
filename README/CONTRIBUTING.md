# Contributing to HTML Tidy

So you want to contribute to Tidy? Fantastic! Here's a brief overview on how best to do so.

### Support request

If you are having trouble running `Tidy`, or using the `LibTidy` API in your own project, then maybe the best places to get help is either via a comment in [Tidy Issues](https://github.com/htacg/tidy-html5/issues), or on the [Tidy Mail Archive](https://lists.w3.org/Archives/Public/html-tidy/) list.

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

 1. Fork tidy to your own github account. Use the top right `Fork` icon at https://github.com/htacg/tidy-html5/
 2. Clone your own fork
    - using ssh
      Generate a SSH Key, and add it to your SSH and GPG keys (https://github.com/settings/keys)
      Note that if you generate the ssh key without a passphrase, operations like `git push` can be done without a password.
      Then do
 ` cd <some_root> # into some root directory`
 ` git clone git@github.com:<name>/tidy-html5.git`

    - using https
 ` cd <some_root> # into some root directory`
 ` git clone https://github.com/<name>/tidy-html5.git`
 3. Set your user name and email address
    If you want to keep your email address private, go to https://github.com/settings/emails to find your GitHub provided no-reply email address and use that when setting your email address.
 ` cd tidy-html5`
 ` git config user.name <name>`
 ` git config user.email <email address>`
 4. Create a branch
 ` git checkout -b <branch-name>`
 5. Edit, and commit your changes to this branch of your fork.
    Please note: if you want to change multiple things that don't depend on each other, use different branches, and make sure you
 ` git checkout next`
    before making another branch. That way we can take in each change separately, otherwise Github will combine all your branch commits into one PR.
 6. Build tidy (see [BUILD.md](https://github.com/htacg/tidy-html5/blob/next/README/BUILD.md))
 ` cd build/cmake`
 ` cmake ../.. -DCMAKE_BUILD_TYPE=Debug`
 ` make`
 7. Test your changes, and if you made any code changes, run the [regression](https://github.com/htacg/tidy-html5-tests/blob/next/README/RUNTESTS.md) tests.  Very briefly, to run the regression tests
 ` cd <some_root> # the same root directory that was used for tidy`
 ` git clone git@github.com:htacg/tidy-html5-tests.git`
 ` cd tidy-html5-tests/tools-sh`
 ` ./testall.sh ../../tidy-html5/build/cmake/tidy`
 ` diff -u ../cases/testbase-expects ../cases/testbase-results`
 8. Push your local changes to your github account.
 ` git push -u origin <branch-name>`
 9. Create a PR ([Pull Request](https://help.github.com/articles/about-pull-requests/)), here.
10. Watch for comments, acceptance.

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

If the `tests` shows a different exit value, or there are differences between the `expects` and `results`, these **must** be studied, and checked, very carefully. There may be cases where the **new** `results` are correct, in which case a simultaneous **PR** for the forked `tests` **must** be created to match your forked source **PR**.

Do **NOT** change either the root `version.txt` here, nor the `cases/_version.txt` in `tests`. This will be handled by the person that does the **PR** merge. To differentiate your modified `tidy` there is a cmake option, like `-DTIDY_RC_NUMBER=I123`, which will appear in `tidy -v` as `5.7.16.I123`. The number can be anything, but using the relevant issue value is a good choice.

Add an `issue` if you need further **help**... thanks...

### Help Tidy Get Better

It goes without saying **all help is appreciated**. We need to work together to make Tidy better!

