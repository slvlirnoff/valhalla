#!/usr/bin/env bash
set -e


# get the software installed
git clone \
  --depth=1 \
  --recurse-submodules \
  --single-branch \
  --branch=master \
  git@gitlab.intern.routerank.com:devteam/valhalla.git libvalhalla

#if you plan to compile with node bindings, run
# curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.33.11/install.sh | bash
# export NVM_DIR="$HOME/.nvm"
# [ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
# [ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"
# nvm install 10 && nvm use 10 # must use node 8.11.1 and up because of N-API
# npm install --ignore-scripts

cd libvalhalla
# new build if ever updated with upstream
#./autogen.sh
#./configure --enable-static
# old build
cmake . -DCMAKE_BUILD_TYPE=Release -DENABLE_NODE_BINDINGS=OFF -DENABLE_PYTHON_BINDINGS=OFF
make -j$(nproc)
make install
cd -

# clean up
ldconfig
rm -rf libvalhalla

#osmlr
# Enabled when using latest valhalla version!
# add-apt-repository ppa:valhalla-core/opentraffic
# apt-get update -y

# # get the software installed
# git clone \
#   --depth=1 \
#   --recurse-submodules \
#   --single-branch \
#   --branch=master \
#   https://github.com/opentraffic/osmlr.git osmlr

# cd osmlr
# ./autogen.sh
# ./configure --enable-static
# make -j$(nproc)
# make install
# cd -

# # clean up
# rm -rf osmlr