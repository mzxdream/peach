@echo off
cmake -S . -B build
cmake --build build --config Debug --target install