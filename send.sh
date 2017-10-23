#!/bin/sh

# exit error
set -e

# compile
eval "make"

set +e

APP="reddit_3dshack"
# IP="192.168.1.131"
IP="192.168.1.127"
RETRY=2
CMD="$DEVKITARM/bin/3dslink --address=$IP $APP.3dsx"

eval $CMD

while [[ $? -ne 0 ]]; do
    eval $CMD
done
