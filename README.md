# DSA-Project - Left-Leaning Red-Black Binary Search Tree Stock Simulation
## Creators:
Aidan Languedoc, Annie Liang, Cody Giroux, and Luca Spinella
## Requirements:
- Clion with minimum of C++ ver. 3.24
- SFML downloadable folder (included in main branch)
- .ttf files (fonts included in main branch)
- .csv files (input files included in main branch)

## How to implement SFML:
-relocate the SFML.zip file (included in the main branch) directly in front of your C drive
the file path should look like this: "C:\SFML"
- In order to account for the naming convention of the project, it is recommended that you name the project "MarketSimulation" so that you don't need to modify the CMakeLists.txt
- In order to run the program using the GUI, the two font files, IBMPlexMono-Regular.ttf and IBMPlexMono-Medium.ttf, must be added to the cmake-build-debug along with the dataset .csv file (all are included in main)

## Input for running the program:
- Once the above sections are accounted for, the prgram will prompt the user for an input file which exists on the cmake-build-debug folder.
- If given a proper file, the program will then give the user the option of adding animations during runtime (this changes the colors to fade in and out).
- Once the user has entered either 'y' for yes and 'n' for no, the program will open in a window outside the CLion application and the program will run.
- To terminate the program, hit the top right-most button of the window (the button with the red x).
