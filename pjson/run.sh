make
if [ $? -eq 0 ]; then
	./main
	rm *.o
	rm main
fi
