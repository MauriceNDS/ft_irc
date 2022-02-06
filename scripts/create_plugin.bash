FOLDER=plugins/$1

if [ -z "`ls $FOLDER 2>/dev/null || true`" ]; then
	if [ ! -d $FOLDER ]; then
		mkdir -p $FOLDER
	fi
	cp templates/plugin/* $FOLDER
else
	echo \`$1\' is not an empty directory.
fi
