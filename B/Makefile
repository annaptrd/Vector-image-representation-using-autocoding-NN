CC=g++
CXXFLAGS = -g -Wall
CPPFLAGS = -I eigen
LDLIBS   = -lm
DEPS = Reading.h	../Functions_for_both_algorithms/Modulos.h	../Functions_for_both_algorithms/Calculate_Distances.h		Hash.h		LSH.h	../Functions_for_both_algorithms/h_Function.h	Writing.h	Reduced_space.h		../Functions_for_both_algorithms/Quicksort.h	Nearest_Neighbor.h
OBJ = search.o	Reading.o	../Functions_for_both_algorithms/Modulos.o	../Functions_for_both_algorithms/Calculate_Distances.o		Hash.o		LSH.o	../Functions_for_both_algorithms/h_Function.o	Writing.o	Reduced_Space.o		../Functions_for_both_algorithms/Quicksort.o	Nearest_Neighbor.o

%o.: %.c ${DEPS}
	$(CC) -c -O3 -o $@ $< $(CXXFLAGS)
search: $(OBJ)
	$(CC) -O3 -o $@ $^ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f *.o search
