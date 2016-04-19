obj=json.o pjson.o

main: $(obj)
	g++ -std=c++11 -o json $(obj)

json.o: pjson.h
	g++ -std=c++11 -c json.cpp -o json.o
pjson.o: pjson.h
	g++ -std=c++11 -c pjson.cpp -o pjson.o

clean:
	rm *.o