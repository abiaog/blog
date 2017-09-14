#!/bin/bash


function list-temp
{
	echo "temp files as below,"
	find . -name "*.sw[o|p]"
}

function clean
{
	echo "cleaning..."
	find . -name "*.sw[o|p]" | xargs rm
}

function help
{
	echo "Usage: $0 [command] [variable=value ...]"
	echo " --------------+--------------------------------"
	echo " command       | usage "
	echo " --------------+--------------------------------"
	echo " clean         | clean temp files"
	echo " list-temp     | list temp files"
}

if [ "$@x" == "x" ]; then
    help
fi

($@)
