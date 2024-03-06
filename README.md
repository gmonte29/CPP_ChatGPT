Setup

1. Add ChatGPT API Key to src/info.cxx

2. Run following to clean build directory:

	make clean

3. Run following to build executable after cleaning:

	cd build
	cmake ..
	cmake --build .

4. While in build directory run following to execute ChatGPT API Request:

	./app/main
    
