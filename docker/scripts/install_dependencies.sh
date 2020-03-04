#!/usr/bin/env bash
set -e


# get all the ppas we might need
add-apt-repository -y ppa:valhalla-core/valhalla
apt-get update -y

# get all the dependencies might need
apt-get install -y \
  git \
  autoconf \
  automake \
  make \
  libtool \
  pkg-config \
  g++ \
  gcc \
  jq \
  lcov \
  protobuf-compiler \
  vim-common \
  libboost-all-dev \
  libboost-all-dev \
  libcurl4-openssl-dev \
  zlib1g-dev \
  liblz4-dev \
  libprime-server0.6.3-dev \
  libprotobuf-dev prime-server0.6.3-bin \
  libgeos-dev \
  libgeos++-dev \
  liblua5.2-dev \
  libspatialite-dev \
  libsqlite3-dev \
  spatialite-bin \
  wget \
  unzip \
  lua5.2 \
  locales \
  python-all-dev \
  cmake


if [[ $(grep -cF xenial /etc/lsb-release) > 0 ]]; then
  apt-get install -y libsqlite3-mod-spatialite
fi