TARGET   	= ../bin/HPComp
OBJPATH 	= .
SOURCES		= $(wildcard *.cpp)
OBJS    	= $(patsubst %.cpp,%.o,$(SOURCES))
FULLOBJS 	= $(patsubst %.cpp,$(OBJPATH)/%.o,$(SOURCES))
INCPATH		= -I. -I../include
LIBPATH		= -L../lib -lkbase -lnetec -ldts -lhpatc -lhpcomp -Wl,-rpath='/home/ricci/workdir/HPComp/lib/'
LFLAGS		= -w -rdynamic
CFLAGS		= -w -c
CXX     	= g++

$(TARGET):$(OBJS)
	$(CXX) $(LFLAGS) $(FULLOBJS) -o $(TARGET) $(LIBPATH)
	
$(OBJS):$(SOURCES)
	$(CXX) $(CFLAGS) $*.cpp -o $(OBJPATH)/$@ $(INCPATH)

clean:
	rm -f $(OBJPATH)/*.o
	rm -f $(TARGET)

