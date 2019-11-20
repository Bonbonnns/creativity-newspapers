while read x
do
	echo $x
	x_dir=`expr $x : '\(.*\).tar.bz2'`	
	mkdir $x_dir
	tar -xvjf $x -C $x_dir
done < "${1:-/dev/stdin}"
