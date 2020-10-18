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

TESTS = ./tests/Test.o ./tests/Test1_GameObject.o ./tests/Test2_Material.o ./tests/Test3_ZBuffer.o \
	./tests/Test4_BatchManager.o ./tests/Test5_MeshBuilder.o

LOCAL = main.o 

all: exc

main.o: main.cpp
	$(CXX) -c main.cpp $(INC)

exc: $(LOCAL) $(TESTS) $(OPENGL_TOOLKIT) $(EASY_GL) $(IMGUI_TOOLKIT)
	$(CXX) -o exc $(LOCAL) $(TESTS) $(OPENGL_TOOLKIT) $(EASY_GL) $(IMGUI_TOOLKIT) $(LIBS)

clean :
	rm -f *.o exc imgui.ini