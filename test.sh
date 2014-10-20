#!/bin/bash

if [ "$1" == "localization" ] 
then
	./agent test localization Phoenix & sleep 1
	./agent trainer trainer/localization.phx 
elif [ "$1" == "dribble" ]
then
	./agent test dribble & sleep 1
	./agent trainer trainer/dribble.phx
elif [ "$1" == "world" ]
then
	./agent test world Phoenix & sleep 1
	./agent test world Nemesis & sleep 1
	./agent test world Nemesis & sleep 1
	./agent test world Nemesis & sleep 1
	./agent test world Nemesis & sleep 1
	./agent test world Nemesis & sleep 1
	./agent trainer trainer/world.phx
elif [ "$1" == "goalie" ]
then
	./agent test goalie Phoenix & sleep 1
	./agent test goalie Nemesis g & sleep 1
	./agent trainer trainer/ball.phx
else
	echo "Phoenix2D - 2014"
	echo "Available tests:"
	echo "- localization: test the self localization method"
	echo "- dribble:      test the dribble algorithm"
	echo "- world:        test the world model generation"
	echo ""
	echo "usage: ./test.sh <TEST_NAME>"
fi
