IDIR = ./includes
CC = g++
CXXFLAGS += -I$(IDIR) -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system -g

ODIR = ./build
CPPDIR = ./src

_DEPS = main.h SFMLUI.h button.h checkbox.h border.h details.h dropdown.h textbox.h radiobutton.h label.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o SFMLUI.o button.o checkbox.o border.o details.o dropdown.o textbox.o radiobutton.o label.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(CPPDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

ui: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(INCDIR)/*~ rm ui
