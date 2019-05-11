#!/bin/bash

#start only if not running yet
pidof -x python3 /opt/stonut/telegram-bot.py > /dev/null
if [ $? -eq 1 ]; then
	while :
        do
            echo "Start telegram bot..."
            python3 /opt/stonut/telegram-bot.py
            echo "Running telegram bot..."
            sleep 3600
        done
fi
