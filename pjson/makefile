std=-std=c++11
obj=main.o json.o
name=main

main: $(obj)
	g++ $(std) -o $(name) $(obj)

main.o: json.h
	g++ $(std) -c main.cpp -o main.o
json.o: json.h
	g++ $(std) -c json.cpp -o json.o

clean:
	rm *.o
