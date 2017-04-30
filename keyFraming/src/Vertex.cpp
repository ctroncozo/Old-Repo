#include "Vertex.h"
Data::Data(Vector3D p)
{
    position[0] = p[0];
    position[1] = p[1];
    position[2] = p[2];
    position[3] = 1;
    
    color[0] = 0.5;
    color[1] = 0.5;
    color[2] = 0.5;
    color[3] = 1;
    
    normal[0] = 0;
    normal[1] = 0;
    normal[2] = 0;
    normal[3] = 1;
}
    
Data::Data(Vector3D p, Vector4D c, Vector3D n)
{
    position[0] = p[0];
    position[1] = p[1];
    position[2] = p[2];
    position[3] = 1;
    
    color[0] = c[0];
    color[1] = c[1];
    color[2] = c[2];
    color[3] = c[3];
    
    normal[0] = n[0];
    normal[1] = n[1];
    normal[2] = n[2];
    normal[3] = 1;
}

void Data::setNormal(Vector4D n)
{
    normal = Vector4D(n);
}

void Data::setPosition(Vector4D p)
{
	position = Vector4D(p);
}

Vector4D Data::getPosition()
{
    return position;
}

Vector4D Data::getNormals()
{
	return normal;
}

Vertex::Vertex(){}

Vertex::Vertex(Vector3D position)
{
    data = new Data(position);
}

Vertex::Vertex(Vector3D position, Vector4D color, Vector3D normal)
{
    data = new Data(position, color, normal);
}

Vertex::Vertex(Vector3D position, Vector3D normal)
{
    Vector4D color = Vector4D(0.5,0.5,0.5,1);
    data = new Data(position, color, normal);
}

Vertex::~Vertex(){}


void Vertex::setNormal(Vector4D n)
{
    data->setNormal(n);
}

void Vertex::setPosition(Vector4D p)
{
	data->setPosition(p);
}

Vector3D Vertex::getPosition()
{
    Vector4D position(data->getPosition());
    return (Vector3D(position.x, position.y, position.z));
}

Vector3D Vertex::getNormals()
{
	Vector4D normals(data->getNormals());
	return (Vector3D(normals.x, normals.y, normals.z));
}

Data* Vertex::getOutputData()
{
    return data;
}
        


