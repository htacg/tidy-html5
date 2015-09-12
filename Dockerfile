FROM ubuntu:14.04
MAINTAINER Edward M. Vielmetti <edward.vielmetti@gmail.com>

# install prerequisites
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    curl \
    zip \
    xsltproc \
    doxygen \
    rpm \
    git

# grab the tarball
WORKDIR /root
RUN curl -L -o 5.1.9.zip https://github.com/htacg/tidy-html5/archive/5.1.9.zip && \
    unzip 5.1.9.zip

# do the build
# build everything I possibly can

WORKDIR /root/tidy-html5-5.1.9/build/cmake 
RUN cmake ../.. && make 

WORKDIR /root/tidy-html5-5.1.9/build/documentation
RUN cp ../cmake/tidy ../cmake/tidy5 && ./build_docs.sh

WORKDIR /root/tidy-html5-5.1.9/build/cmake 
RUN make package && make install 

# run the command
CMD "/usr/local/bin/tidy"
