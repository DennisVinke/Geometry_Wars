Advanced Programming Project:
Creating a 2d Game using C++ and OpenGL.

Aart Odding,         s1595555
Dennis Vinke,        s1390082
Robin van Emmerloot, s1538683


Steps to compile the project:

* Source code will only compile with C++17 standard.
  In visual studio this settings can be found in the project properties under
  C/C++ >> Language >> C++ Language Standard >> ISO C++ 17 (/std:c++17)

* Create a new solution and add all the .h and .cpp files found in:
  - /Geometry_Wars/
  - /Geometry_Wars/io/
  - /Geometry_Wars/opengl/

* Make sure that the shaders folder is inside of the Geometry_Wars folder, and the Geometry Wars folder can be found, by moving up folders from the executable's directory.

  IE. 

  When the executable is in:
  C:\Users\aart\Documents\AP\AP\x64\Debug\Geometry_Wars.exe

  then having the shader folder located at:
  C:\Users\aart\Documents\AP\Geometry_Wars\shaders

  Is okay because the "Geometry_Wars" folder is visible by moving up from  
  C:\Users\aart\Documents\AP\AP\x64\Debug\Geometry_Wars.exe to
  C:\Users\aart\Documents\AP\

* Three external libraries are used (with Johan's permission): GLM, glad, and SDL2. For each:

* GLM is header only and thus the only thing that needs to be done is add the folder /Geometry_Wars/glm_include/ to the include directories, under project properties. 

* glad has one c file that we have added to /Geometry_Wars/ so that should be compiled properly by following step 2. Furthermore the headers of glad need to be added by including the folder "/Geometry_Wars/glad_include" under project properties

* SDL2: add the folder /Geometry_Wars/SDL2-2.0.9/include/ to the solutions include directories, SDL3 has three.lib files, that need to be added. Under project properties >> VC++ Directories >> Library Directories, add /Geometry_Wars/SDL2-2.0.9/lib/x86/ or /Geometry_Wars/SDL2-2.0.9/lib/x64/, and under Linker >> Input >> Additional Dependencies add SDL2.lib, SDL2main.lib, SDL2test.lib. Lastly add SDL2.dll to the executable directory. For more information see: https://www.wikihow.com/Set-Up-SDL-with-Visual-Studio-2017

* Lastly when using SDL sometimes it is necessary to specify the subsystem: in project properties, under linker >> system >> SubSystem, select Console. If you do not follow this step, you will get a runtime error when executing the application.

