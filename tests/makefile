################################################################################
#                                   MAKEFILE                                   #
################################################################################

INC = -I /usr/include/

TESTS = Test.o Test1_GameObject.o Test2_Material.o Test3_ZBuffer.o Test4_BatchManager.o Test5_MeshBuilder.o

all: $(TESTS)

Test5_MeshBuilder.o: Test5_MeshBuilder.cpp Test5_MeshBuilder.h Test.h
	$(CXX) -c Test5_MeshBuilder.cpp $(INC)

Test4_BatchManager.o: Test4_BatchManager.cpp Test4_BatchManager.h Test.h
	$(CXX) -c Test4_BatchManager.cpp $(INC)

Test3_ZBuffer.o: Test3_ZBuffer.cpp Test3_ZBuffer.h Test.h
	$(CXX) -c Test3_ZBuffer.cpp $(INC)

Test2_Material.o: Test2_Material.cpp Test2_Material.h Test.h
	$(CXX) -c Test2_Material.cpp $(INC)

Test1_GameObject.o: Test1_GameObject.cpp Test1_GameObject.h Test.h
	$(CXX) -c Test1_GameObject.cpp $(INC)

Test.o: Test.cpp Test.h
	$(CXX) -c Test.cpp $(INC)

clean :
	rm -f *.o