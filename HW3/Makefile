source = hw3_1 hw3_2
CPPOPTION = -std=c++17 -O2

all: $(source)
$(source):
%: %.cpp
	g++ $(CPPOPTION) $< -o $@
	
clean:
	rm -rf $(source)
