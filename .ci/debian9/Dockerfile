FROM debian:stretch

MAINTAINER DESY, Jan Kotanski <jankotan@gmail.com>

RUN /bin/bash -c 'echo "deb http://ftp.de.debian.org/debian stretch main" > /etc/apt/sources.list.d/debian9de.list'
RUN /bin/bash -c 'echo "deb http://deb.debian.org/debian stretch-backports main" > /etc/apt/sources.list.d/debian9bp.list'
RUN /bin/bash -c 'echo "deb http://deb.debian.org/debian stretch-backports-sloppy main" > /etc/apt/sources.list.d/debian9bps.list'

RUN apt-get update
RUN apt-get install -y base-passwd apt-utils dialog -y
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt-get -qq update && apt-get -qq install -y libterm-readline-gnu-perl software-properties-common coreutils gnupg2 procps curl apt-transport-https gnupg2 ca-certificates wget
RUN curl -s http://repos.pni-hdri.de/debian_repo.pub.gpg  | gpg --no-default-keyring --keyring gnupg-ring:/etc/apt/trusted.gpg.d/debian-hdri-repo.gpg --import
RUN chmod 644 /etc/apt/trusted.gpg.d/debian-hdri-repo.gpg
RUN add-apt-repository "deb http://repos.pni-hdri.de/apt/debian stretch main" -y
RUN apt-get -qq update && apt-get -qq -y dist-upgrade

RUN apt-get -qq update && apt-get -qq -y install cmake g++ doxygen python3-sphinx git libboost-all-dev gfortran graphviz libcppunit-dev texlive doxygen pkg-config texlive-latex-extra texlive-latex-recommended texlive-pictures python3-pygments libhdf5-dev libgtest-dev lsb-release python3-breathe texlive-pictures python3-sphinx-rtd-theme libjs-mathjax fonts-mathjax fonts-mathjax-extras ghostscript adduser
RUN apt-get -qq update && apt-get -qq -y install libhdf5-dev
RUN apt-get -qq update && apt-get -t stretch-backports-sloppy -y install libarchive13
RUN apt-get -qq update && apt-get -t stretch-backports -y install cmake
RUN apt-get -qq update && apt-get -qq -y install libh5cpp0.5.2-dev libh5cpp0.5.2

RUN apt-get clean

# # install latest h5cpp
# RUN mkdir -p /opt/h5cpp
# RUN mkdir -p /h5cpp-src
# RUN cd /h5cpp-src && git clone https://github.com/ess-dmsc/h5cpp && mkdir build
# RUN cd /h5cpp-src/build && cmake -DCMAKE_INSTALL_PREFIX=/opt/h5cpp -DCMAKE_BUILD_TYPE=Release -DH5CPP_CONAN=DISABLE -DCMAKE_CXX_STANDARD=11 -DH5CPP_DISABLE_TESTS=True  ../h5cpp && make install -j4

# add p00user
RUN useradd -rm -d /home/p00user -s /bin/bash p00user
USER p00user
RUN mkdir -p /home/p00user/src
WORKDIR /home/p00user/src
