//
//  Mesh.hpp
//  Mesh_Editor_Xcode
//
//  Created by Cristian Troncoso on 2/10/16.
//  Copyright © 2016 Cristian Troncoso. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

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

#define DEBUG 3
#if defined(DEBUG) && DEBUG > 0
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
__FILE__, __LINE__, __func__, ##args)
#else
#define printf //
#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif


/*!
 * \brief   : Mesh class
 */
class Mesh
{
protected:
    Vertex *vertices;            /**< Stores "all" model's vertices */
    
    Data* outputData;            /**< Raw data from all vertices, with interleaving location, color and normal */
    
    int numOfVertices;           /**< Total number of vertices after face parsing (ouput number of vertices) */
    
    int numOfInputVertices;      /**< Num of vertices on input file */
    int numOFinputFaces;         /**< Num of faces on input file */
    
    std::vector<Face*> inputFaces;      /**< Contains original vertices from input file */
    std::vector<Vertex*> inputVertex;   /**< Contains original faces from input file */
	 GLuint vboHandle[1];			/**< VBO that contains interleaved positions, color and Normals */   
public:
    /*!
     * \brief   Mesh constructor.
     */
    Mesh(std::string filename);
    /*!
     * \brief   Mesh Destructor.
     */
    ~Mesh(void);
    /*!
     * \brief   Loads input file and parse it. It generates inputFaces and InputVertex.
     * \param   Path to the input file
     */
    void loadObject(const std::string filename);
    /*!
     * \brief   It traverses the inputFace and inputVertex vectors to generate all model's vertices
     */
    void initMesh();
    /*!
     * \brief   It generates a buffer with all vertex information, color, normals and what not.
     *          It uses the faces values (x,y,z) as a vertex id.
     */
    void createVertexBuffer();
    /*!
     * \brief   TODO - Draw is not implemented.
     */
    void draw();
	 /*!
	  * \brief	 Initialize the VBO
	  */
	  void initVBO();
    /*!
     * \brief   I gets the raw data buffer. The buffer that is loaded onto the gpu
     *          with interleaving position, color and normal.
     * \return  Data buffer.
     */
    double* getVertexData();
    /*!
     * \brief   Returns the total number of vertices in the model.
     * \Return  Number of vertices in model.
     */
    int getNumOfVertices();
     /*!
     * \brief   Split lines from input file for parsing purposes.
     *          http://stackoverflow.com/questions/236129/split-a-string-in-c
     */
    std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
    /*!
     * \brief   It populates the Data objec in each vertex, based on the face information
     *          collected from file plus normal and color assigned to each face.
     */
    void createData(int i, Face *f);
};

#endif /* Mesh_hpp */
