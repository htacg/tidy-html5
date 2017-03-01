# HTML Tidy Branches

## About Branches

Starting with **HTML Tidy** 5.4.0, HTACG will adopt a new branch management strategy utilizing **master** as the _release branch_, and **next** as the active development branch.

As described thoroughly in our [VERSION.md](VERSION.md) document, this means that **master** will always consist of an even-numbered minor version, and activity will remain relatively quiet unless we backport a critical bug fix from **next**.

The **next** branch, then will host the majority of our development activity, and any contributions and PR’s should be again this branch. This means that **next** will always consist of an odd minor version number.


## About Versioning

You can read the specifics about version numbers in our [VERSION.md](VERSION.md) document.


## FAQs

### Which version or branch should I choose?

As described above, the branch is very strongly correlated with the version. If you require a stable API and relatively stable output and don’t require the features and enhancements of an odd-numbered **next** version, then you should stick to **master**, even-numbered versions.

On the other hand if you are primarily a console application user, then the API isn’t likely as important to you, and you probably want the latest and greatest. If this describes you, you probably want to at least try out **next**.

If you are developing for Tidy, then you _definitely_ want to stick to **next**, even for bug fixes meant for **master**. If it’s a critical enough bug fix, then one of our friendly team will back-port the fix to **master**.



