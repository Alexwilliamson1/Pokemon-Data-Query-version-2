#!/bin/bash

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"

cd "$PROJECT_DIR" || exit 1

NUM_CLIENTS=${1:-1}

if ! [[ "$NUM_CLIENTS" =~ ^[1-9][0-9]*$ ]]; then
	echo "To run this file, run the command \"./run.sh\" followed by the number client interfaces you would like to open.  For example, \"./run.sh 3\" will open one server and three clients.  Running only \"./run.sh\" will open one server and one client."
	exit 1
fi

make || exit 1

case "$(uname -s)" in
	Darwin*)
		osascript -e "tell application \"Terminal\" to do script \"cd '$PROJECT_DIR'; ./server_app\""

		sleep 1

		for ((i=1; i<=NUM_CLIENTS; i++))
		do
			osascript -e "tell application \"Terminal\" to do script \"cd '$PROJECT_DIR'; ./client_app\""
		done
		;;
	MINGW*|MSYS*|CYGWIN*)
		cmd.exe /c start "Server" cmd.exe /k "cd /d \"$PROJECT_DIR\" && server_app.exe"

		sleep 1

		for ((i=1; i<=NUM_CLIENTS; i++))
		do
			cmd.exe /c start "Client $i" cmd.exe /k "cd /d \"$PROJECT_DIR\" && client_app.exe"
		done
		;;
	*)
		echo "This script only runs on operating systems and platforms with POSIX support, such as macOS, Linux, or Windows running Git Bash, MSYS2 or Cygwin."
	     	exit 1
		;;	
esac

