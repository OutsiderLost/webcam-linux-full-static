#!/bin/bash

# (start continuous camera monitoring)
# while :; do ./camcheck.sh; sleep 1;done

./OCVimage

timeout 5 display -geometry 800x600+100+100 ./output.png

