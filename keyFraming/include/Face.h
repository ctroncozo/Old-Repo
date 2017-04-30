#ifndef CRISTIAN_TRONCOSO_FACE_H
#define CRISTIAN_TRONCOSO_FACE_H
#include <cmath>
#include "Vertex.h"

/*!
 * \brief   Contains all model's faces information.
 */
class Face
{
   protected:
   Vector3D normal;
   Vector4D color;
   Vertex vertexes[3];
    
    
	public:
  	int id;               	/**< The id is the input order according to the input file (.OFF or .OBJ) */
   int faceVertexes[3];		/**< Vertex index according to the input file */
   
	/*!
    * \Brief   : Constructor, default.
    */
 	Face();
	/*!
    * \Brief   : Constructor,Initializes a Face based on Vertex index (from input file) and color.
    */
	Face(int *fVertexes, Vector4D inColor);
 	/*!
    * \Brief   : Constructor, Initializes using position, normal and color.
    */
	Face(Vector3D *vertices, Vector3D normal, Vector4D color);
	/*!
    * \Brief   : Constructor, Initializes using position and normal.
    */
	Face(Vector3D *Vertices, Vector3D normal);
	/*!
    * \Brief   : Constructor, Initialize using position.
    */
	Face(Vector3D *vertices);
	/*!
     * \Brief   : Destructor.
     */
	~Face();
	/*!
     * \Brief   : Sets the face's Vertexes (3) based on input information
	  *			   From input file.
     */
	void setVertexes(Vertex A, Vertex B, Vertex C);
	/*!
     * \Brief   : Calculates an set the Face's normal.
     */
	void setNormal();
	/*!
	 * \Brief	 : Calculate the normal as the average of the normal on each vertex.
	 */
	void setNormalAvg(Vector3D n0, Vector3D n1, Vector3D n2);
	/*!
     * \Brief   : Sets the face's color.
     */
	void setFaceColor(float *inColor);
	/*!
     * \Brief   : Return face's normal vector.
     */
	Vector3D getNormal();
	/*!
     * \Brief   : Return the face's color.
     */
	Vector4D getColor();
};
#endif // CRISTIAN_TRONCOSO_FACE_H
