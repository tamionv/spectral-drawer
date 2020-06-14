img:
	mkdir img

bin:
	mkdir bin

bin/%.exe: src/%.cpp bin
	g++ $< -o $@ -std=c++11 -O2

img/%.pgm: graphs/% bin/main.exe img
	./bin/main.exe < $< > $@

graphs/%: bin/%.exe
	./$< > $@

PremadeExamples=foster levi shrikhande sylvester schlaafli ljublijana hypercube4 26fullerene 24fullerene archimedes1 archimedes10 archimedes11 archimedes12 archimedes13 archimedes2 archimedes3 archimedes4 archimedes5 archimedes6 archimedes7 archimedes8 archimedes9 petersen platonic1 platonic2 platonic3 platonic4 platonic5

GeneratedExamples=bendy loopy meandering random square_surface triangular_surface tesselated_cubes hypercube6d ring

Examples=$(PremadeExamples) $(GeneratedExamples)

examples: $(patsubst %,img/%.pgm,$(Examples))

clean:
	rm $(patsubst %,graphs/%,$(GeneratedExamples))
