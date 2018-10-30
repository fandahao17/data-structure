# TODO: run without input and output files.
test ! -e "input" -o ! -e "answer" && \
	echo "Run: Can't find input or answer file" && exit 0
filename=$(head -n 1 input | cut -d ' ' -f 2)
if [ $# -gt 0 ]; then
	test -n "$1" && filename=$1
fi
executable=$(echo "$filename" | cut -d '.' -f 1)
exe_dest=$(echo "./bin/$executable")
test ! -e $filename && echo "Source file not exist." && exit 0
# compile
echo "Making $executable."
touch .run_tmp
g++-8 -std=c++11 -g -gdwarf-3 $filename -o $exe_dest
test ! $exe_dest -nt .run_tmp && test ! $exe_dest -nt .$filename && echo "Run: Failed to make $executable" && rm .run_tmp && exit 0
rm .run_tmp
echo "Completed!\n"
# run
echo "Running $executable."
echo "---------------------------------"
tail -n +2 input | $exe_dest | tee output
echo "---------------------------------"

# judge
diff answer output > .diff
test ! -s .diff && echo "PASS!" && exit 0
echo "Oops!Something wrong here."
# you may need to 'brew install colordiff'
colordiff answer output
rm .diff
