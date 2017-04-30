CC					=	g++

CXXFLAGS			+=	-W -Wall -Wextra -std=c++14
CXXFLAGS			+= -O3
#CXXFLAGS			+= -g3
CXXFLAGS			+=	-I./include/ 

ifeq ($(shell uname -s), Darwin)
LDFLAGS   		= -framework GLUT -framework OpenGL
else
LDFLAGS 			= -lGL -lGLU -lglut
endif


EXENAME			=	project3


SRCS 				= 	src/camera.cpp			\
						src/core.cpp			\
						src/cube.cpp			\
						src/matrix34.cpp		\
						src/tester.cpp			\
						src/token.cpp			\
						src/Joint.cpp			\
						src/Ntree.cpp			\
						src/Skeleton.cpp		\
						src/DOF.cpp				\
						src/Point.cpp			\
						src/MDSpace.cpp		\
						src/Vector4D.cpp		\
						src/Color.cpp			\
						src/Material.cpp		\
						src/Light.cpp			\
						src/Vertex.cpp			\
						src/Face.cpp			\
						src/SkinMesh.cpp		\
						src/Vector3D.cpp		\
						src/AnimationClip.cpp\
						src/AnimationPlayer.cpp\
						src/Channel.cpp		\
						src/KeyFrame.cpp		\
						src/Matrix44.cpp		\
						src/Span.cpp
						
OBJ				=	$(SRCS:.cpp=.o)


all				: 	$(OBJ)
	$(CC) $(OBJ) -o $(EXENAME) $(LDFLAGS)

clean				:
	rm -f $(OBJ)

fclean			: clean
	rm -f $(EXENAME)

re					: fclean all
