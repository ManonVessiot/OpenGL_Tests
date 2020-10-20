################################################################################
#                                   MAKEFILE                                   #
################################################################################

OPENGL_LIBS =  -lglfw -lGLEW -lGL

LIBS = $(OPENGL_LIBS)

INC = -I /usr/include/

IMGUI_TOOLKIT = ../ImGuiToolKit/vendor/imgui/imgui.o ../ImGuiToolKit/vendor/imgui/imgui_impl_glfw.o ../ImGuiToolKit/vendor/imgui/imgui_impl_opengl3.o \
	../ImGuiToolKit/vendor/imgui/imgui_widgets.o ../ImGuiToolKit/vendor/imgui/imgui_draw.o ../ImGuiToolKit/vendor/imgui/imgui_demo.o \
	../ImGuiToolKit/ImGuiManager.o

EASY_GL = ../easyGL/vendor/stb_image/stb_image.o ../easyGL/Renderer.o ../easyGL/VertexBuffer.o ../easyGL/IndexBuffer.o ../easyGL/VertexArray.o \
	../easyGL/VertexBufferLayout.o ../easyGL/Shader.o ../easyGL/Texture.o ../easyGL/TextureManager.o ../easyGL/ShaderManager.o

OPENGL_TOOLKIT = ../OpenglToolKit/WorldManager.o ../OpenglToolKit/Mesh.o ../OpenglToolKit/Transform.o \
	../OpenglToolKit/GameObject.o ../OpenglToolKit/GameObjectManager.o ../OpenglToolKit/Material.o ../OpenglToolKit/MaterialManager.o \
	../OpenglToolKit/Batch.o ../OpenglToolKit/BatchManager.o ../OpenglToolKit/MeshBuilder.o

MAZE_GAME = ../Maze/Maze.o ../Maze/Player.o

TESTS = ./tests/Test.o \
	./tests/Test1_ClearColor.o ./tests/Test2_Triangle.o ./tests/Test3_SquareAnimatedColor.o ./tests/Test4_Texture2D.o ./tests/Test5_MVP.o \
	./tests/Test6_Cube.o ./tests/Test7_SimpleBatching.o ./tests/Test8_SimpleDynamicBatching.o \
	./tests/Test9_GameObject.o ./tests/Test10_Material.o ./tests/Test11_ZBuffer.o \
	./tests/Test12_BatchManager.o ./tests/Test13_MeshBuilder.o ./tests/Test14_Maze.o

LOCAL = main.o 

all: exc

main.o: main.cpp
	$(CXX) -c main.cpp $(INC)

exc: $(LOCAL) $(TESTS) $(MAZE_GAME) $(OPENGL_TOOLKIT) $(EASY_GL) $(IMGUI_TOOLKIT)
	$(CXX) -o exc $(LOCAL) $(TESTS) $(MAZE_GAME) $(OPENGL_TOOLKIT) $(EASY_GL) $(IMGUI_TOOLKIT) $(LIBS)

clean :
	rm -f *.o exc imgui.ini && \
	cd ./tests && \
	rm -f *.o && \
	cd ..