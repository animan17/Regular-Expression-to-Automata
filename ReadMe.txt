A. How to run,

(Use Windows)

Using command line interface,

	1. Navigate to CS201_Project_Group_3 folder and then run,

	2. CS201_Project_Group_3\imguitest\main.exe
	
Note,

Command line may not be given permission to open foreign files OR Antivirus software may block it.

In that case use Windows File Explorer to navigate to CS201_Project_Group_3\imguitest folder and double click on main.exe




B. How to compile exe,

Using command line interface,

	1. Navigate to CS201_Project_Group_3\Code_file_Group_3\imguitest folder and then run,

	2. g++ -c ../automata.cpp -o ../automata.o
	
	3. g++ -c ../graphviz.cpp -o ../graphviz.o
	
	4. g++ -fdiagnostics-color=always -g -I imgui -o main.exe gui.cpp imgui/*.cpp ../graphviz.o ../automata.o -L imgui -l d3d9 -l d3dcompiler -l dxgi -l dwmapi -l gdi32 -l d3dx9
	
Note,

The following library files should be installed on your device,

d3d9, d3dcompiler, dxgi, dwmapi, gdi32, d3dx9