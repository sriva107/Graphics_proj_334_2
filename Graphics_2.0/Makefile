sources = \
	src/main.cpp \
	src/Camera.cpp \
	src/Shader.cpp \
	src/Model.cpp \
	src/Mesh.cpp \
	src/OBJLoader.cpp

inc = -Iinclude
libs = -lGL -lGLU -lglut -lGLEW
out = FreeGLUT_Contour_Project

all:
	g++ -std=c++17 $(sources) $(inc) $(libs) -o $(out)

clean:
	rm -f $(out)
