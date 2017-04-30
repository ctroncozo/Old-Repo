//
// Vertex.hpp
//
// Created by Cristian Troncoso 2/15/2016
//

#ifndef Vertex_hpp
#define Vertex_hpp

#if defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "Vector3D.h"
#include "Vector4D.h"
#include <vector>
/*!
 * \brief   Data class helps to organize the Vertex data that needs
 *          to be loaded onto the GPU.
 */
class Data
{
private:
    Vector4D position;              /**< (x,y,z,1) position. */
    Vector4D color;
    Vector4D normal;
    
public:
    /*!
     * \Brief   : Constructor, instantiates using Vetex's position, some default color
     *            and normal (0,0,0,1).
     */
    Data(Vector3D p);
    /*!
     * \Brief   : Constructor, instantiates using Vetex's position, color and normal.
     */
    Data(Vector3D p, Vector4D c, Vector3D n);
    /*!
     * \Brief   : Set the Vertex's normal
     */
    void setNormal(Vector4D n);
	 /*!
	  * \Brief	: Set Position.
	  */
	  void setPosition(Vector4D p);
    /*!
     * \Brief   : Returns the vector's position,used by Vertex class.
     */
    Vector4D getPosition();

	 /*!
	  * \Brief	: Returns vertex's normal 
	  */
	 Vector4D getNormals();
}; //End Class Data

/*!
 * \brief   Class Vertex stores all information of model's vertexes.
 */
class Vertex
{
protected:
    Data *data;                     /**< Contains the raw data (position, color and normal). */
public:
	 std::vector<std::pair<int,float>> skinweights;    
    int id;                         /**< Identify the vertices based on input order (Index). */
    /*!
     * \Brief   : Default constructor.
     */
    Vertex();
    /*!
     * \Brief   : Constructor, Initializes Vertex using position vector.
     */
    Vertex(Vector3D position);
    /*!
     * \Brief   : Constructor, Initializes Vertex using position, color and normal vectors.
     */
    Vertex(Vector3D position, Vector4D color, Vector3D normal);
    /*!
     * \Brief   : Constructor, Initializes Vertex using position and normal vectors.
     */
    Vertex(Vector3D position, Vector3D normal);
    /*!
     * \Brief   : Destructor.
     */
    ~Vertex();
    
    /*!
     * \Brief   : Set the normal vector on each Vertex.
     */
    void setNormal(Vector4D n);
	 /*!
	  * \Brief	: Set position.
	  */
	  void setPosition(Vector4D p);
    /*!
     * \Brief   : Return the (x,y,z) position of a Vertex in space.
     */
    Vector3D getPosition();
	/*!
	 * \Brief	: Return Vector3D(nx,ny,nz)
	 */
	 Vector3D getNormals();
    /*!
     * \Brief   : Returns all Vetex data; position, color and normal. Ready to 
     *            be loaded onto GPU.
     */
    Data* getOutputData();
};

#endif //End Vertex_hpp

