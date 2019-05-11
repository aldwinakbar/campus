#!/bin/bash

#start only if not running yet
pidof -x ngrok > /dev/null
if [ $? -eq 1 ]; then
	echo "Start tunnelling..."
	/opt/stonut/ngrok tcp --log stdout 22 > /dev/null &
	echo "Running tunnel in background..."    
fi
