g++ src/main.cpp src/button.cpp -o Calculator.exe -O1 -Wall -std=c++14 -Wno-missing-braces -I src/include/ -L src/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm