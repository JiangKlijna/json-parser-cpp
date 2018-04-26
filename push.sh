
function push() {
	git add $1
	git commit -m '"'$2'"'
	git push
	if [[ ! -z $3 && ! -z $4 ]]; then
		$3 # ouput git username
		$4 # ouput git password
	fi
}

function check() {
	if [ -z $1 ]; then
		echo $2
		exit 1
	fi
}

check "$1" "git add ?"
check "$2" "git commit -m ?"

push $1 $2 $3 $4
