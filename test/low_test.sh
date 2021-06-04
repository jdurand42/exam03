#/bin/bash
echo "generating"
#./gen
#1sleep 1
#cat example_
echo "testing"
./my example_ > myR
echo $? >> myR
./their example_ > theirR
echo $? >> theirR
cat myR
echo ""
echo "----"
cat theirR
echo ""

echo "diff:"
echo $(diff myR theirR)
diff myR theirR 
echo "end diff"
echo "finished" 
