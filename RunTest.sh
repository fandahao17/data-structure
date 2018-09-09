filename=$1
executable=$(echo "$filename" | cut -d '.' -f 1)
exe_dest=$(echo "./bin/$executable")
test ! -e "input" -o ! -e "answer" && \
	echo "Run: Can't find input or answer file" && exit 0
test ! -e $filename && echo "Source file not exist." && exit 0
# compile
echo "Making $executable."
clang++ -g $filename -o $exe_dest
test $exe_dest -ot $filename && echo "Run: Failed to make $executable" && exit 0
echo "Completed!\n"
# run
echo "Running $executable."
echo "---------------------------------"
./$exe_dest < input | tee output
echo "---------------------------------"

# judge
diff answer output > .diff
test -s .diff && echo "PASS!" && exit 0
echo "Oops!Something wrong here."
# you may need to 'brew install colordiff'
colordiff answer output
rm .diff
