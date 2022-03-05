bison -d -y 1605042.y
echo '1'
bison -d -v 1605042.y
echo '2'
g++ -w -c -o y.o y.tab.c -g
echo '3'
flex 1605042.l
echo '4'
g++ -fpermissive -w -c -o l.o lex.yy.c -g
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo '5'
g++ -o a.out y.o l.o -lfl -ly -g
echo '6'
./a.out input.txt log.txt
