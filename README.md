g++ -c Book.cpp -o Book.o
g++ -c User.cpp -o User.o
g++ -c Library.cpp -o Library.o
g++ -c Source.cpp -o Source.o
g++ Book.o User.o Library.o Source.o -o Source.exe
./Source.exe 
