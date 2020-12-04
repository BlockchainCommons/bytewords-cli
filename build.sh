#!/bin/bash

set -e

git submodule init
git submodule update

source set_build_paths.sh

# Terminal colors
RED=`tput setaf 1`
GREEN=`tput setaf 2`
BLUE=`tput setaf 4`
RESET=`tput sgr0`

echo "${BLUE}== bc-crypto-base ==${RESET}"

pushd deps/bc-crypto-base
./configure --prefix ${SYSROOT}
make check
make install
popd

echo "${BLUE}== bc-bytewords ==${RESET}"

pushd deps/bc-bytewords
./configure --prefix ${SYSROOT}
make check
make install
popd

echo "${BLUE}== argp-standalone ==${RESET}"

pushd deps/argp-standalone/argp-standalone
patch -N <../patch-argp-fmtstream.h || echo "Patch not needed."
./configure --prefix ${SYSROOT}
make install
cp libargp.a ${SYSROOT}/lib/
cp argp.h ${SYSROOT}/include/
popd

echo "${BLUE}== bytewords ==${RESET}"

./configure
make check
echo "${GREEN}*** bytewords built.${RESET}"
echo "${GREEN}Next step: sudo make install${RESET}"
