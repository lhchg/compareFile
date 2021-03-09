g++ -o compare compare.cpp -std=gnu++0x
./compare <file1> <file2>
#<file1> <file2> are the files need to compare
RESULT=$?
if [ "$RESULT" == 3 ];then
    echo "cpu output file is different from golden"
elif [ "$RESULT" == 2 ];then
    echo "cpu output file is same as golden"
elif [ "$RESULT" == 255 ];then
    echo "cpu file compare has something wrong"
fi
