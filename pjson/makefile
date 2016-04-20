std=-std=c++11
obj=json.o pjson.o
name=json

main: $(obj)
	g++ $(std) -o $(name) $(obj)

json.o: pjson.h
	g++ $(std) -c json.cpp -o json.o
pjson.o: pjson.h
	g++ $(std) -c pjson.cpp -o pjson.o

clean:
	rm *.o
