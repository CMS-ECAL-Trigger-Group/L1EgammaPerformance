#makefile 

CC   =   g++ -std=c++17
UCFLAGS = -g -O3 -Wall -Wextra

#CC   =   g++
#UCFLAGS = -O0 -g3 -Wall -gstabs+  
#UCFLAGS = -O3 -Wall -gstabs+ -std=c++0x 

RUCFLAGS := $(root-config --cflags) -I${ROOFITSYS}/include/ -I./include/
LIBS :=  $(root-config --libs) -lTreePlayer -lGpad -lHist -lRIO -lCore -L${ROOFITSYS}/lib/ -lRooFit  -lRooFitCore ./obj/FuncCB_cpp.so
GLIBS := $(root-config --glibs)

$(root-config --cflags --libs)


VPATH = ./src/

SRCPP = main.cpp\
	Utilities.cpp\
	TurnonFit.cpp\
	TurnonManager.cpp
         
#OBJCPP = $(SRCPP:.cpp=.o)
OBJCPP = $(patsubst %.cpp,obj/%.o,$(SRCPP))


all : obj/FuncCB_cpp.so fit.exe 

obj/%.o : %.cpp
	@mkdir -p obj/
	@echo compiling $*
	@$(CC) -c $< $(UCFLAGS) $(RUCFLAGS) -o $@

fit.exe : $(OBJCPP) 
	@echo linking
	@$(CC) $^ $(ACLIBS) $(LIBS) $(GLIBS) -o $@

obj/FuncCB_cpp.so: include/FuncCB.cpp createCBLib.sh
	sh createCBLib.sh

clean:
	@rm  -f obj/*.o
	@rm -f fit.exe

cleanall: clean
	@rm obj/FuncCB_cpp.so

