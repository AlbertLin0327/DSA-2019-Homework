source = printer
CPPOPTION = -std=c++17 -m32

all: $(source)
$(source):
%: %.cpp
	g++ $(CPPOPTION) $< -o $@
	
clean:
	rm -rf $(source)
