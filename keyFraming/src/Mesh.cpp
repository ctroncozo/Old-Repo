#include "Mesh.h"
#include <fstream>
#include <sstream>

Mesh::Mesh(std::string filename)
{
    numOFinputFaces     = 0;
    numOfInputVertices  = 0;
    loadObject(filename);
    initMesh();
}

Mesh::~Mesh(){}

double * Mesh::getVertexData()
{
    double *temp = (double*)(&outputData)[0];
    return temp;
}

int Mesh::getNumOfVertices()
{
    return numOfVertices;
}

std::vector<std::string>& Mesh::split(const std::string &s,
                                      char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

void Mesh::loadObject(const std::string filename)
{
    
    FILE * file;
    int faceCounter = 0;
    int vertCounter = 0;
    std::string line;
    Vector4D color;
    
    std::ifstream infile(filename);
    
    std::vector<std::string> tokens;
    std::string token;
    std::vector<std::string> tok;

    const char * c = filename.c_str();
    
    file = fopen(c,"rb");
    
    std::cout << "Starting parse..." << std::endl;

    while (std::getline(infile, line))
    {
        //Split a line into tokens by delimiting it on spaces
        tokens.clear();
        tokens = split(line, ' ', tokens);
        
        //If first token is a v then it gots to be a vertex
        if(tokens.at(0).compare("OFF") == 0)
        {
            std::cout<<"OFF"<< std::endl;
            continue;
        }
        if(numOFinputFaces == 0)
        {
            numOfInputVertices = std::stof(tokens.at(0));
            numOFinputFaces = std::stof(tokens.at(1));
        }
        if(tokens.size() == 3)
        {
            //Parse the vertex line
            float x = std::stof(tokens.at(0));
            float y = std::stof(tokens.at(1));
            float z = std::stof(tokens.at(2));
            
            Vector3D position = Vector3D(x,y,z);
            Vertex *ver = new Vertex(position);
            
            ver->id = vertCounter;
            
            inputVertex.push_back(ver);
            vertCounter++;
            
        }
        if(tokens.size() == 4)
        {
            //generate a random color for each face.
            color[0] = ((double)rand()) / ((double)RAND_MAX) * 1.0 + 0.1;
            color[1] = ((double)rand()) / ((double)RAND_MAX) * 1.0 + 0.1;
            color[2] = ((double)rand()) / ((double)RAND_MAX) * 1.0 + 0.1;
            color[3] = 1;
            
            int x = std::stof(tokens.at(1)) + 1;
            int y = std::stof(tokens.at(2)) + 1;
            int z = std::stof(tokens.at(3)) + 1;
            
            int fv[] = {x,y,z};
            
            Face *f = new Face(fv, color);
            f->id = faceCounter;
            
            inputFaces.push_back(f);
            faceCounter++;
        }
    }
    std::cout << "Done parsing." << std::endl;
}

void Mesh::initVBO()
{
	glGenBuffers(1, vboHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Data)*(getNumOfVertices()), (GLfloat*)(getVertexData()), GL_STATIC_DRAW);
}

void Mesh::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
	// enable vertex array
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 12 * sizeof(GLfloat), (GLvoid*)0);
	glColorPointer(3, GL_FLOAT, 12 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	glNormalPointer(GL_FLOAT, 12 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));

	glDrawArrays(GL_TRIANGLES, 0, getNumOfVertices());
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::createData(int i, Face *f)
{
    //generate a random color for each face.
    Vertex *v0;
    Vertex *v1;
    Vertex *v2;
   
	 /**< Each Face has 3 vertex; vo, v1 and v2.*/
    int f0 = f->faceVertexes[0];
    int f1 = f->faceVertexes[1];
    int f2 = f->faceVertexes[2];
    
    v0 = inputVertex[f0];
    v1 = inputVertex[f1];
    v2 = inputVertex[f2];
    
    vertices[i] = Vertex(v0->getPosition(), f->getColor(), f->getNormal());
    outputData[i] = *vertices[i].getOutputData();
    
    vertices[i+1] = Vertex(v1->getPosition(), f->getColor(), f->getNormal());
    outputData[i+1] = *vertices[i+1].getOutputData();
    
    vertices[i+2] = Vertex(v2->getPosition(), f->getColor(), f->getNormal());
    outputData[i+2] = *vertices[i+2].getOutputData();
}

void Mesh::initMesh()
{
    int i = 0;
    
    int faces[3];//f0, f1, f2;
    Vertex *v[3];//*v0, *v1, *v2;
    
    numOfVertices = numOFinputFaces * 3;
    
    vertices    = (Vertex*)malloc(sizeof(Vertex)* numOfVertices);
    outputData  = (Data*)malloc(sizeof(Data)* numOfVertices);
    
    for(std::vector<Face*>::iterator it=inputFaces.begin(); it != inputFaces.end(); ++it)
    {
        
        /**< Each Face has 3 vertex; vo, v1 and v2.*/
        faces[0] = (*it)->faceVertexes[0];
        faces[1] = (*it)->faceVertexes[1];
        faces[2] = (*it)->faceVertexes[2];
        
        
        v[0] = inputVertex[faces[0]];
        v[1] = inputVertex[faces[1]];
        v[2] = inputVertex[faces[2]];
        
        // Calculate face normals
        (*it)->setVertexes(*v[0],*v[1],*v[2]);
        (*it)->setNormal();
        
        //createData(i,(*it));
		  vertices[i] = Vertex(v[0]->getPosition(), (*it)->getColor(), (*it)->getNormal());
    	  outputData[i] = *vertices[i].getOutputData();
    
        vertices[i+1] = Vertex(v[1]->getPosition(), (*it)->getColor(), (*it)->getNormal());
        outputData[i+1] = *vertices[i+1].getOutputData();
    
        vertices[i+2] = Vertex(v[2]->getPosition(), (*it)->getColor(), (*it)->getNormal());
        outputData[i+2] = *vertices[i+2].getOutputData();
	  
        i += 3;
    }
}



