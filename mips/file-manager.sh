#!/bin/bash

process=`ps aux | grep dde-file-manager | grep -v grep`;
  
if [ "$process" == "" ]; then
    dde-file-manager ~
else
    echo "{\"url\":\"\~\"}" |socat - $XDG_RUNTIME_DIR/dde-file-manager
fi