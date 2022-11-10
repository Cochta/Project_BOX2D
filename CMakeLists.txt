# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

# Solution
project ("Project_BOX2D")

# Each sub-project
set(EXECUTABLE_CUSTOM_NAME "00_Starter")
add_subdirectory ("00_Starter")

set(EXECUTABLE_CUSTOM_NAME "01_Test")
add_subdirectory ("01_Test")

set(EXECUTABLE_CUSTOM_NAME "02_Space_Shooter")
add_subdirectory ("02_Space_Shooter")