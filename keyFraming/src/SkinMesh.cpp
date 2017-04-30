#include "SkinMesh.h"

SkinMesh::SkinMesh(Skeleton *sk)
{
	vertices = nullptr;
	outputData = nullptr;
	skeleton = sk;
}

SkinMesh::SkinMesh(const char * filename)
{
	numOfInputFaces = 0;
	numOfInputVertices = 0;
}

SkinMesh::~SkinMesh(){}

void SkinMesh::update()
{
	// Get all the joint's world matrices
    int i = 0;
	for(std::vector<Vertex*>::iterator it = inputVertex.begin(); it != inputVertex.end(); ++it)
	{
		Vector3D vprime(0,0,0);  // v'
		Vector3D nprime(0,0,0);  // n'
		//Vector3D v((*it)->getPosition()); //v
		//Vector3D n((*it)->getNormals());  // n
		Vector3D v(originalVertex.at(i)->getPosition());
	  	Vector3D n(originalVertex.at(i)->getNormals());
		Matrix34 M;
        //v.Print("v");
		int numOfJoints = (*it)->skinweights.size();  // number of attachments in this vertex
		/*
		std::cout<<"----------------------------------------------"<<std::endl;
		std::cout<<"vertex #  "<<(*it)->id<<std::endl;
		v.Print("v");
		n.Print("n");
		*/
		for(int i = 0; i < numOfJoints; i++)
		{
			// Get the Attachment info for joint i
			int joint = (*it)->skinweights.at(i).first; // joint number
			float weight = (*it)->skinweights.at(i).second; //weight
			
			Matrix34 W = skeleton->getWorldMatrix(joint); //Wi
			Matrix34 invB = invBindings.at(joint); //B^(1)i
			M.Dot(W, invB);
			/*	
			std::cout<<"["<<joint<<"] ["<<weight<<"]"<<std::endl;
			W.Print("W");
			invB.Print("B^-1");
			M.Print("M");
			*/
				
			Vector3D temp_v;
			Vector3D temp_n;
			
			M.Transform(v,temp_v);
			M.Transform3x3(n,temp_n);
			temp_n.normalize();
			vprime += temp_v * weight;
			nprime += temp_n * weight;
		}
		nprime.normalize();		
		Vector4D pos(vprime.x, vprime.y, vprime.z,1);
		Vector4D nor(nprime.x, nprime.y, nprime.z,1);
		(*it)->setPosition(pos);
		(*it)->setNormal(nor);
        
        Vector3D vvv((*it)->getPosition());
		/*
		vprime.Print("v'");
		nprime.Print("n'");
		std::cout<<"---------------------------------------------"<<std::endl;
		*/
        i++;
	}
	initMesh();
}

void SkinMesh::load(const char * filename)
{
	Tokenizer token;
	int counter = 0;
	token.Open(filename);
	token.FindToken("positions");
	counter = token.GetFloat();
	numOfInputVertices = counter;
	token.FindToken("{");
	
	// Get Vertices positions
	for(int i = 0; i < counter; i++)
	{
		float x = token.GetFloat();
		float y = token.GetFloat();
		float z = token.GetFloat();

		Vector3D position = Vector3D(x,y,z);
      Vector3D oPosition = Vector3D(x,y,z);
        
		Vertex *ver = new Vertex(position);
      Vertex *oVer = new Vertex(oPosition);
        
		ver->id = i;
      oVer->id = i;
		inputVertex.push_back(ver);
      originalVertex.push_back(oVer);
        
	}
	/*
	for(std::vector<Vertex*>::iterator it = inputVertex.begin();
												  it != inputVertex.end(); ++it)
	{
		(*it)->getPosition().print("");
	}
   */	
	// Get Vertices normals
	token.FindToken("normals");
	counter = token.GetFloat();
	token.FindToken("{");
	for(int i = 0; i < counter; i++)
	{
		float x = token.GetFloat();
		float y = token.GetFloat();
		float z = token.GetFloat();

		Vector4D normals = Vector4D(x,y,z,1);
        Vector4D oNormals = Vector4D(x,y,z,1);

		  normals.normalize();
		  oNormals.normalize();
        
		inputVertex.at(i)->setNormal(normals);
        originalVertex.at(i)->setNormal(oNormals);

	}
	/*	
	for(std::vector<Vertex*>::iterator it = inputVertex.begin();
												  it != inputVertex.end(); ++it)
	{
		(*it)->getNormals().print("");
	}
	*/
	// Get Vertices skinweights
	token.FindToken("skinweights");
	counter = token.GetFloat();
	token.FindToken("{");
	for(int i = 0; i < counter; i++)
	{
		int num_of_attachments = token.GetInt();
		for(int j = 0; j < num_of_attachments; j++)
		{ 
			int first = token.GetInt();
			float second = token.GetFloat();
			std::pair<int, float> p(first,second);
			inputVertex.at(i)->skinweights.push_back(p);
		}

		std::vector<std::pair<int,float>> temp = inputVertex.at(i)->skinweights;
		/*	
		printf("weights :");
		for(std::vector<std::pair<int,float>>::iterator i = temp.begin();
				i != temp.end(); i++)
		{
			std::cout<<i->first<<" "<<i->second<<" ";
		}
		printf("\n");
		*/
	}
	

	// Get triangles
	token.FindToken("triangles");
	counter = token.GetFloat();
	numOfInputFaces = counter;
	token.FindToken("{");
	for(int i = 0; i < counter; i++)
	{
		int x = token.GetInt();
		int y = token.GetInt();
		int z = token.GetInt();
		
		int fv[] = {x,y,z};
		Vector4D color(1,0,0,1);
		Face *f = new Face(fv,color);
		inputFaces.push_back(f);
	}

	/*	
	for(std::vector<Face*>::iterator it = inputFaces.begin();
												  it != inputFaces.end(); ++it)
	{
		std::cout<<(*it)->faceVertexes[0]<<" "<<(*it)->faceVertexes[1]<<" "<<(*it)->faceVertexes[2]<<std::endl;
	}
	*/
	// Get the binding matrix
	token.FindToken("bindings");
	counter = token.GetFloat();
	token.FindToken("{");
	for(int i = 0; i < counter; i++)
	{
		token.FindToken("matrix");
		token.FindToken("{");
		float ax = token.GetFloat(); 
		float ay = token.GetFloat(); 
		float az = token.GetFloat();
		float bx = token.GetFloat(); 
		float by = token.GetFloat(); 
		float bz = token.GetFloat();
		float cx = token.GetFloat(); 
		float cy = token.GetFloat(); 
		float cz = token.GetFloat();
		float dx = token.GetFloat(); 
		float dy = token.GetFloat(); 
		float dz = token.GetFloat();
		/*Matrix34 B(	ax, bx, cx, dx,
						ay, by, cy, dy,
						az, bz, cz, dz
					 );
		*/
		Matrix34 B;
		B.a.x = ax; B.a.y = ay; B.a.z = az;
		B.b.x = bx; B.b.y = by; B.b.z = bz;
		B.c.x = cx; B.c.y = cy; B.c.z = cz;
		B.d.x = dx; B.d.y = dy; B.d.z = dz;
		bindings.push_back(B);
		B.Inverse();
		invBindings.push_back(B);		
	}
	/*
	for(std::vector<Matrix34>::iterator it=bindings.begin(); it!=bindings.end(); ++it)
	{
		it->Print("");
	}
	for(std::vector<Matrix34>::iterator it=invBindings.begin(); it!=invBindings.end(); ++it)
	{
		it->Print("");
	}
	*/
	token.Close();
}

void SkinMesh::initMesh()
{
	int i = 0;
	int faces[3]; //f0, f1, f2;
	Vertex *v[3]; //*v0, *v1, *v2;

	numOfVertices = numOfInputFaces * 3;
	if(!vertices)
	{
		vertices = (Vertex*)malloc(sizeof(Vertex) * numOfVertices);
		outputData = (Data*)malloc(sizeof(Data) * numOfVertices);

	}
	//vertices = (Vertex*)malloc(sizeof(Vertex) * numOfVertices);
	//outputData = (Data*)malloc(sizeof(Data) * numOfVertices);

	for(std::vector<Face*>::iterator it = inputFaces.begin(); it != inputFaces.end(); ++it)
	{
		faces[0] = (*it)->faceVertexes[0];
		faces[1] = (*it)->faceVertexes[1];
		faces[2] = (*it)->faceVertexes[2];

		v[0] = inputVertex[faces[0]];
		v[1] = inputVertex[faces[1]];
		v[2] = inputVertex[faces[2]];
		
		(*it)->setVertexes(*v[0], *v[1], *v[2]);
		//create face normals
		//(*it)->setNormalAvg(v[0]->getNormals(), v[1]->getNormals(), v[2]->getNormals());
		
		// Create output data
		vertices[i] = Vertex(v[0]->getPosition(), (*it)->getColor(), v[0]->getNormals());
		outputData[i] = *vertices[i].getOutputData();
		
		vertices[i+1] = Vertex(v[1]->getPosition(), (*it)->getColor(),v[1]->getNormals());
		outputData[i+1] = *vertices[i+1].getOutputData();
		
		vertices[i+2] = Vertex(v[2]->getPosition(), (*it)->getColor(), v[2]->getNormals());
		outputData[i+2] = *vertices[i+2].getOutputData();
		
		i += 3;
	}
}

void SkinMesh::loopDraw()
{
    int faces[3]; //f0, f1, f2;
    Vertex *v[3]; //*v0, *v1, *v2;
    
    numOfVertices = numOfInputFaces * 3;

    
    for(std::vector<Face*>::iterator it = inputFaces.begin(); it != inputFaces.end(); ++it)
    {
        faces[0] = (*it)->faceVertexes[0];
        faces[1] = (*it)->faceVertexes[1];
        faces[2] = (*it)->faceVertexes[2];
        
        v[0] = inputVertex[faces[0]];
        v[1] = inputVertex[faces[1]];
        v[2] = inputVertex[faces[2]];
   
        
        // Create output data
        Vector3D pos0 = v[0]->getPosition();
        Vector3D nor0 = v[0]->getNormals();
        
        Vector3D pos1 =  v[1]->getPosition();
        Vector3D nor1 = v[1]->getNormals();
    
        Vector3D pos2 = v[2]->getPosition();
        Vector3D nor2 = v[2]->getNormals();

        
        glShadeModel(GL_SMOOTH);
   
        glBegin(GL_TRIANGLES);
            glColor3f(0.1, 0.2, 0.3);
            glNormal3f(nor0.x, nor0.y, nor0.z);
            glVertex3f(pos0.x, pos0.y, pos0.z);
            glNormal3f(nor1.x, nor1.y, nor1.z);
            glVertex3f(pos1.x, pos1.y, pos1.z);
            glNormal3f(nor2.x, nor2.y, nor2.z);
            glVertex3f(pos2.x, pos2.y, pos2.z);
        glEnd();
    }

}

void SkinMesh::draw()
{	
	glLoadIdentity();

    /*
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 12 * sizeof(GLfloat), (GLvoid*)0);
	glColorPointer(3, GL_FLOAT, 12 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	glNormalPointer(GL_FLOAT, 12 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));

    float *dat = getData();
    
	glDrawArrays(GL_TRIANGLES, 0, getNumOfVertices());
    
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
    */
    loopDraw();
}

void SkinMesh::initVBO()
{
	glGenBuffers(1, vboHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Data)*(getNumOfVertices()), (GLfloat*)(getData()),GL_STATIC_DRAW);
}

float * SkinMesh::getData()
{
	return (float*)outputData;
}

int SkinMesh::getNumOfVertices()
{
	return numOfVertices;
}
