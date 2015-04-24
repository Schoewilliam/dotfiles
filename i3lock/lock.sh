#!/bin/bash
scrot /tmp/screen.png
convert /tmp/screen.png -scale 10% -scale 1000% /tmp/screen.png
[[ -f $HOME/Images/icons/lock.png ]] && convert /tmp/screen.png $HOME/Images/icons/lock.png -gravity center -composite -matte /tmp/screen.png
i3lock -u -i /tmp/screen.png