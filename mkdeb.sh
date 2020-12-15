#!/bin/bash

checkinstall -D -y \
  --install=no \
  --fstrans=no \
  --nodoc \
  --reset-uids=yes \
  --pkgname=kinx \
  --pkgversion="0.17.0" \
  --pkgrelease="0" \
  --pkggroup="kinx" \
  --arch=amd64 \
  --pkglicense=MIT \
  --maintainer="Kray-G"

