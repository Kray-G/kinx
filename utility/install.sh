#!/bin/sh

if [ ! -d /usr/bin/kinxlib ]; then mkdir -p /usr/bin/kinxlib; fi;
cp -f ./kinx /usr/bin/kinx
cp -f ./kxrepl /usr/bin/kxrepl
cp -f ./kxtest /usr/bin/kxtest
cp -rf lib/* /usr/bin/kinxlib/

