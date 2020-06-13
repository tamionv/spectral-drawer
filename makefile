main.exe: main.cpp
	g++ -g main.cpp -o main.exe -std=c++11 -O2

img:
	mkdir img

img/%.pgm: graphs/% main.exe img
	./main.exe < $< > $@

Examples=foster levi shrikhande sylvester schlaafli ljublijana hypercube4 26fullerene 24fullerene archimedes1 archimedes10 archimedes11 archimedes12 archimedes13 archimedes2 archimedes3 archimedes4 archimedes5 archimedes6 archimedes7 archimedes8 archimedes9 petersen platonic1 platonic2 platonic3 platonic4 platonic5

examples: $(patsubst %,img/%.pgm,$(Examples))
