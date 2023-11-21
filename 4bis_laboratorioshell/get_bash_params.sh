echo "n params: $#"
echo "params: $*"
echo "process name: $0"
echo "1 param: $1"

for name in $* ; do 
	echo "arg: ${name}";
done
