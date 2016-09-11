#!/bin/bash

while ((1)) ; do
	process=`ps aux | grep dde-file-manager | grep -v grep`;
	  
	if [ "$process" == "" ]; then
	    dde-file-manager -d &
	fi
	sleep 1
done
