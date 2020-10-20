################################################################################
#                                   MAKEFILE                                   #
################################################################################

OPENGL_LIBS =  -lglfw -lGLEW -lGL

BULLET_LIBS = -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath

LIBS = $(OPENGL_LIBS) $(BULLET_LIBS)

INC = -I /usr/include/ -I /usr/local/include/bullet

TESTS = Test.o \
	Test1_ClearColor.o Test2_Triangle.o Test3_SquareAnimatedColor.o Test4_Texture2D.o Test5_MVP.o \
	Test6_Cube.o Test7_SimpleBatching.o Test8_SimpleDynamicBatching.o \
	Test9_GameObject.o Test10_Material.o Test11_ZBuffer.o \
	Test12_BatchManager.o Test13_MeshBuilder.o Test14_Maze.o Test15_MazeWithBullet.o 

all: $(TESTS)

Test15_MazeWithBullet.o: Test15_MazeWithBullet.cpp
	$(CXX) -c Test15_MazeWithBullet.cpp $(INC)

Test14_Maze.o: Test14_Maze.cpp
	$(CXX) -c Test14_Maze.cpp $(INC)

Test13_MeshBuilder.o: Test13_MeshBuilder.cpp
	$(CXX) -c Test13_MeshBuilder.cpp $(INC)

Test12_BatchManager.o: Test12_BatchManager.cpp
	$(CXX) -c Test12_BatchManager.cpp $(INC)

Test11_ZBuffer.o: Test11_ZBuffer.cpp
	$(CXX) -c Test11_ZBuffer.cpp $(INC)

Test10_Material.o: Test10_Material.cpp
	$(CXX) -c Test10_Material.cpp $(INC)

Test9_GameObject.o: Test9_GameObject.cpp
	$(CXX) -c Test9_GameObject.cpp $(INC)

Test8_SimpleDynamicBatching.o: Test8_SimpleDynamicBatching.cpp
	$(CXX) -c Test8_SimpleDynamicBatching.cpp $(INC)

Test7_SimpleBatching.o: Test7_SimpleBatching.cpp
	$(CXX) -c Test7_SimpleBatching.cpp $(INC)

Test6_Cube.o: Test6_Cube.cpp
	$(CXX) -c Test6_Cube.cpp $(INC)

Test5_MVP.o: Test5_MVP.cpp
	$(CXX) -c Test5_MVP.cpp $(INC)

Test4_Texture2D.o: Test4_Texture2D.cpp
	$(CXX) -c Test4_Texture2D.cpp $(INC)

Test3_SquareAnimatedColor.o: Test3_SquareAnimatedColor.cpp
	$(CXX) -c Test3_SquareAnimatedColor.cpp $(INC)

Test2_Triangle.o: Test2_Triangle.cpp
	$(CXX) -c Test2_Triangle.cpp $(INC)

Test1_ClearColor.o: Test1_ClearColor.cpp
	$(CXX) -c Test1_ClearColor.cpp $(INC)

Test.o: Test.cpp
	$(CXX) -c Test.cpp $(INC)

clean :
	rm -f *.o