//
// SkinMesh.h
//
// Created by Cristian Troncoso on 04/08;16
// Copyright © 2016 Cristian Troncoso. All rights reserved.
//

#ifndef CRISTIAN_TRONCOSO_SKINMESH_H
#define CRISTIAN_TRONCOSO_SKINMESH_H

#if defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Face.h"
#include "token.h"
#include "Skeleton.h"
/*!
 * \Brief	: SkinMesh class 
 */
class SkinMesh
{
	protected:
	Vertex *vertices;			// Stores all skin vertices.
	Data * outputData;		// Raw data passed to opengl ( position, colors, and normals ).
	int numOfVertices;		// Total number of vertices after parsing input file.
	int numOfInputVertices;	// Number of vertices on input file. In this case same as total numOfVer.
	int numOfInputFaces;		// Number of triangles on input file.
	 
	std::vector<Face*> 	 inputFaces; // Triangles from input file
	std::vector<Vertex*> inputVertex; // Vertices from input file.
    std::vector<Vertex*> originalVertex;
	std::vector<float*> skinweights;
	GLuint vboHandle[1];	// Vertex buffer array handler.
	Skeleton *skeleton;
	std::vector<Matrix34> bindings;
	std::vector<Matrix34> invBindings;
	public:
    void loopDraw();
	/*!
	 * \Brief	: Default constructor.  */
	SkinMesh(Skeleton *sk);
	/*
	 * \Brief	: Skin file name constructor.
	 * \Param	: Filen mame
	 */
	SkinMesh(const char * filename);
	/*!
	 * \Brief	: Destructor.
	 */
	 ~SkinMesh();
	/*!
	 * \Brief	: Load and parse the .skin file
	 */
	void load(const char * filename);
	/*!
	 * \Brief	: Initializes the triangle mesh. Generate mesh faces and vertices.
	 */
	void initMesh();
	/*!
	 * \Brief	: update
	 */
	 void update();
	/*!
	 * \Brief	: Draws the skin into opengl
	 */
	void draw();
	/*!
	 * \Brief	: Initializes the vertex buffer array.
	 */
	void initVBO();
	/*!
	 * \Brief 	: Return the Data buffer.
	 * \Return	: Pointer to a Data buffer object containing vertices color, normal and position.
	 */
	float * getData();
	/*!
	 * \Brief	: Gets the total numbert of vertices.
	 * \Returns	: int 
	 */
	int getNumOfVertices(); 
};
#endif //CRISTIAN_TRONCOSO_SKINMESH_H
