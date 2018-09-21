cp test/template.cpp test/$1_test.cpp
echo "#include \"$1.hpp\"" > src/$1.cpp
echo "#include \"../src/$1.hpp\"" >> test/$1_test.cpp
sed -i "_recover" "s/TARGET = .*/TARGET = $1/" Makefile
vim src/$1.hpp test/$1_test.cpp src/$1.cpp
