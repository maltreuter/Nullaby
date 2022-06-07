CPPFLAGS = -Wall -std=c++0x -g 

all: nullaby
	
nullaby: pitch.o note.o rest.o nullaby.o main.o
	g++ $(CPPFLAGS) Pitch.o Note.o Rest.o Nullaby.o	main.o -o nullaby -lexpat -lm
	 
pitch.o: Pitch.cpp
	g++ $(CPPFLAGS) -c Pitch.cpp
	
note.o: Note.cpp
	g++ $(CPPFLAGS) -c Note.cpp
	
rest.o: Rest.cpp
	g++ $(CPPFLAGS) -c Rest.cpp
	
nullaby.o: Nullaby.cpp
	g++ $(CPPFLAGS) -c Nullaby.cpp
	
main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp
	
clean:
	rm -f *.o nullaby song.wav