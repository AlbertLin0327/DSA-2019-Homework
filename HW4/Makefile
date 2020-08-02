source = tree
CPPOPTION = -std=c++17 -O2

all: $(source)
$(source):
%: %.cpp
	g++ $(CPPOPTION) $< -o $@
	
clean:
	rm -rf $(source)
