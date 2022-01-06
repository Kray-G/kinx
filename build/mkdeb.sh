#!/bin/bash

apt update
apt install -y --no-install-recommends checkinstall

checkinstall -D -y \
  --install=no \
  --fstrans=no \
  --nodoc \
  --reset-uids=yes \
  --pkgname=kinx \
  --pkgversion="1.1.2" \
  --pkgrelease="0" \
  --pkggroup="kinx" \
  --arch=amd64 \
  --pkglicense=MIT \
  --maintainer="Kray-G"

