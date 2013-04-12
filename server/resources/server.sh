#!/bin/sh
export DISTOCACHE_PATH=`echo $(dirname $(readlink -f $0))`
#/usr/sbin/setenforce 0
./distocache > distocache.log 2>&1