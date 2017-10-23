#!/bin/sh

program_name="ngrok"

process_count=$(pgrep -c $program_name)	

if [ "$process_count" -gt 0 ]
then
	echo "Killing all $program_name $process_count process"
    kill $(pgrep $program_name)
fi
