#!/bin/bash

apt update
apt install -y --no-install-recommends checkinstall

checkinstall -D -y \
  --install=no \
  --fstrans=no \
  --nodoc \
  --reset-uids=yes \
  --pkgname=kinx \
  --pkgversion="$$VER_MAJ.$$VER_MIN.$$VER_PAT" \
  --pkgrelease="0" \
  --pkggroup="kinx" \
  --arch=amd64 \
  --pkglicense=MIT \
  --maintainer="Kray-G"
