# Script for Building tidy rpm packages


# To build the RPM packages for tidy on Redhat and other distros which support rpm.
# For making Debian packages, first create rpm package and then generate
# debian package by command "rpm2deb filename"



The steps are as follows:


1. Let's suppose TIDY_VERSION you are building is 02October2003


2. Unpack original source tree
        tar zxvf tidy_src.tgz
   This will extract to a directory called tidy


3. mv tidy tidy-02October2003
   Edit the tidy.spec file inside directory tidy-02October2003
   and make sure the Version variable is changed to 02October2003.
   Also edit the Makefile and change prefix to "exactly" say this:
        runinst_prefix=${RPMTMP}
        devinst_prefix=${RPMTMP}


4. tar zcvf tidy-02October2003.tgz tidy-02October2003


5. rpmbuild -ta tidy-02October2003.tgz


6. rm tidy-02October2003.tgz


7. To derive Debian package for tidy run command on created rpm packages
        rpm2deb tidy-02October2003-1.rpm

