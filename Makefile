CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -g -MMD
EXEC = Watopoly
OBJECTS = main.o academicbuilding.o board.o dice.o game.o gym.o player.o property.o subject.o textdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean

