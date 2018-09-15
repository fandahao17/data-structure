clang-tidy $1 -quiet -checks=google-*,cppcoreguidelines-*,readability-*,modernize-*,clang-analyzer-*
echo ''
read -p 'Need fix-it?(y\n) ' choice
test $choice == 'y' && clang-tidy $1 -checks=google-*,cppcoreguidelines-*,readability-*,modernize-*,clang-analyzer-* -fix
