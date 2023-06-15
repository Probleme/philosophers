#!/bin/bash

if ! [[ $1 =~ ^[0-9]+$ ]]; then
  set -- 1
fi

sleep "$1"
defaults -currentHost write com.apple.screensaver idleTime 0
defaults write com.apple.universalaccess mouseDriverCursorSize -float 0
osascript -e 'beep'
current_idle_time=$(ioreg -c IOHIDSystem | awk '/HIDIdleTime/ {print $NF/1000000000; exit}')
current_button_state=$(ioreg -c IOHIDSystem | awk '/HIDMouseButtonState/ {print $NF; exit}')
while true; do
  new_idle_time=$(ioreg -c IOHIDSystem | awk '/HIDIdleTime/ {print $NF/1000000000; exit}')
  new_button_state=$(ioreg -c IOHIDSystem | awk '/HIDMouseButtonState/ {print $NF; exit}')
  if (( $(echo "$new_idle_time < $current_idle_time" | bc -l) )) || [[ "$new_button_state" != "$current_button_state" ]]; then
    usleep 100 # Add a delay before executing the sleep command
    osascript -e 'tell application "System Events" to sleep'
    exit 0
  fi
  current_idle_time=$new_idle_time
  current_button_state=$new_button_state
  usleep 100
done
