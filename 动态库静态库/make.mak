    SHELL = /bin/sh
    cc = g++

main : main.cpp
    $(cc) -o main.cpp -L./bin -lfun
clean:
    rm -f $(MAIN_TARGET)