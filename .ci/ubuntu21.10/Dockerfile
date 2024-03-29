FROM ubuntu:21.10

MAINTAINER DESY, Jan Kotanski <jankotan@gmail.com>

RUN apt-get update
RUN apt-get install -y base-passwd apt-utils dialog -y
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt-get -qq update && apt-get -qq install -y libterm-readline-gnu-perl software-properties-common coreutils gnupg2 procps curl apt-transport-https gnupg2 ca-certificates wget
RUN curl -s http://repos.pni-hdri.de/debian_repo.pub.gpg  | gpg --no-default-keyring --keyring gnupg-ring:/etc/apt/trusted.gpg.d/debian-hdri-repo.gpg --import
RUN chmod 644 /etc/apt/trusted.gpg.d/debian-hdri-repo.gpg
RUN add-apt-repository "deb http://repos.pni-hdri.de/apt/debian impish main" -y
RUN apt-get -qq update && export DEBIAN_FRONTEND=noninteractive && apt-get -qq dist-upgrade

RUN /bin/bash -c 'echo "Europe/Berlin" > /etc/timezone'
RUN apt-get -qq update && export DEBIAN_FRONTEND=noninteractive && apt-get -qq -y install cmake ninja-build python3-pip g++ doxygen python3-sphinx git libboost-all-dev gfortran graphviz graphviz libcppunit-dev texlive doxygen pkg-config texlive-latex-extra texlive-latex-recommended texlive-pictures python3-pygments libhdf5-dev libgtest-dev lsb-release python3-breathe texlive-pictures python3-sphinx-rtd-theme libjs-mathjax fonts-mathjax fonts-mathjax-extras ghostscript
RUN apt-get -qq update && apt-get -qq -y install libhdf5-dev
# RUN apt-get -qq update && apt-get -qq -y install libh5cpp0.4.1-dev libh5cpp0.4.1

RUN apt-get clean
RUN pip3 install jinja2==3.0.3
RUN pip3 install conan
RUN pip3 install gitpython

# RUN conan remote remove conan-center
RUN conan remote add conan-community https://api.bintray.com/conan/conan-community/conan
RUN conan remote add conan-center https://conan.bintray.com
RUN conan remote add conan-transit https://conan-transit.bintray.com

# install latest h5cpp
RUN mkdir -p /opt/h5cpp
RUN mkdir -p /h5cpp-src
RUN cd /h5cpp-src && git clone https://github.com/ess-dmsc/h5cpp && mkdir build
RUN cd /h5cpp-src/build && cmake -DCMAKE_INSTALL_PREFIX=/opt/h5cpp -DCMAKE_BUILD_TYPE=Release -DH5CPP_CONAN=DISABLE -DH5CPP_DISABLE_TESTS=True  ../h5cpp && make install -j4

RUN conan user
RUN mkdir /src
WORKDIR /src
