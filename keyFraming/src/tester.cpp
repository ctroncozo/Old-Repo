////////////////////////////////////////
// tester.cpp
////////////////////////////////////////

#include "tester.h"

#define WINDOWTITLE	"Spinning Cube"

////////////////////////////////////////////////////////////////////////////////


static Tester *TESTER;
static void animate(int value);


int Joint::counter = 0;
time_t AnimationPlayer::START = clock();

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    TESTER = new Tester(argc,argv);
    glutTimerFunc(1000/100, animate, 0);
    glutMainLoop();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

// These are really HACKS to make glut call member functions instead of static functions
static void display()									{TESTER->Draw();}
static void idle()										{TESTER->Update();}
static void resize(int x,int y)							{TESTER->Resize(x,y);}
static void keyboard(unsigned char key,int x,int y)		{TESTER->Keyboard(key,x,y);}
static void mousebutton(int btn,int state,int x,int y)	{TESTER->MouseButton(btn,state,x,y);}
static void mousemotion(int x, int y)					{TESTER->MouseMotion(x,y);}

////////////////////////////////////////////////////////////////////////////////

void animate(int value)
{
    TESTER->Update();
    glutPostRedisplay();
    glutTimerFunc(1000/100, animate, 0);
}

Tester::Tester(int argc,char **argv) {
    WinX=640;
    WinY=480;
    LeftDown=MiddleDown=RightDown=false;
    MouseX=MouseY=0;
    jointId = 0;
    // Create the window
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( WinX, WinY );
    glutInitWindowPosition( 0, 0 );
    WindowHandle = glutCreateWindow( WINDOWTITLE );
    glutSetWindowTitle( WINDOWTITLE );
    glutSetWindow( WindowHandle );
    
    // Background color
    glClearColor( 0., 0., 0., 1. );
    
    // Callbacks
    glutDisplayFunc( display );
    //glutIdleFunc( idle );
    glutKeyboardFunc( keyboard );
    glutMouseFunc( mousebutton );
    glutMotionFunc( mousemotion );
    glutPassiveMotionFunc( mousemotion );
    glutReshapeFunc( resize );
    
    
    
    // Initialize components
    Cam.SetAspect(float(WinX)/float(WinY));
    sk = new Skeleton();
    skin = new SkinMesh(sk);
    player = new AnimationPlayer(sk);
    
    //setLights();
    
    if(argc > 1)
    {
        sk->load(argv[1]);
    }
    else
    {
        sk->load("./animation/wasp/wasp.skel");
        //sk->load("/Users/camel/Dropbox/CSE169/Projects/Project_3/animation/wasp/wasp.skel");
    }
    
    if(argc > 2)
    {
        skin->load(argv[2]);
        skin->initMesh();
        //skin->initVBO();
    }
    else
    {
        skin->load("./animation/wasp/wasp.skin");
        //skin->load("/Users/camel/Dropbox/CSE169/Projects/Project_3/animation/wasp/wasp.skin");
        skin->initMesh();
    }
    if(argc > 3)
    {
        player->setClip(argv[3]);
    }
    else
    {
        player->setClip("./animation/wasp/wasp_walk.anim");
        //player->setClip("/Users/camel/Dropbox/CSE169/Projects/Project_3/animation/wasp/wasp_walk.anim");
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    setLights();
}

////////////////////////////////////////////////////////////////////////////////

Tester::~Tester() {
    glFinish();
    glutDestroyWindow(WindowHandle);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Update() {
    // Update the components in the world
    Cam.Update();
    //Cube.Update();
    //sk->update(jointId, pose, j); // j is joint that we want to modify.
    sk->update2();
    skin->update();
    player->update();
    // Tell glut to re-display the scene
    glutSetWindow(WindowHandle);
    glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Reset() {
    Cam.Reset();
    Cam.SetAspect(float(WinX)/float(WinY));
    
    //Cube.Reset();
    sk->reset();
}
////////////////////////////////////////////////////////////////////////////////

void Tester::renderBitmapString(float x, float y, float z, void *font, char *string)
{
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 0, 0);
    char *c;
    glRasterPos3f(x,y,z);
    for (c=string; *c != '\0'; c++)
        glutBitmapCharacter(font,*c);
    
    glEnable(GL_LIGHTING);
}

void Tester::restorePerspectiveProjection()
{
    glMatrixMode(GL_PROJECTION);
    // restore previous projection matrix
    glPopMatrix();
    // get back to model view
    glMatrixMode(GL_MODELVIEW);
}

void Tester::setOrthographicProjection()
{
    // Swtich to projection mode
    glMatrixMode(GL_PROJECTION);
    
    // Save previus matrix that contains the setting for the perspective projection
    glPushMatrix();
    
    // reset matrix
    glLoadIdentity();
    
    // set a 2D orthographic projection
    gluOrtho2D(0,WinX, WinY, 0);
    
    // siwitch back to model view
    glMatrixMode(GL_MODELVIEW);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::setLights()
{
    
    glEnable(GL_LIGHTING);
    //Material m0;
    l0 = new Light(0, Vector4D(1,1,1,1));
    l1 = new Light(1, Vector4D(-1,1,-0.5,1));
    glShadeModel(GL_SMOOTH);
    //m0.apply();
    l0->bind(0);
    l1->bind(1);
}

void Tester::unsetLights()
{
    l0->unbind();
    l1->unbind();
    glDisable(GL_LIGHTING);
}


////////////////////////////////////////////////////////////////////////////////
void Tester::Draw() {
    
    // Begin drawing scene
    glViewport(0, 0, WinX, WinY);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw components
    Cam.Draw();		// Sets up projection & viewing matrices
    //Cube.Draw();
    //sk->draw();
    skin->draw();
    
    
    Vector3D p = j.getPose();
    Joint *jj = sk->jointsArr.at(jointId);
    //sprintf(s, "Joint : %s  <%f, %f, %f>",jj->jname.c_str(),jj->dofx.phi, jj->dofy.phi, jj->dofz.phi);
    // compute the frames per second
    frame ++;
    elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    if(elapsedTime - timebase > 1000)
    {
        sprintf(s, "Timer - FPS: %4.2f", frame*1000.0f/(elapsedTime - timebase));
        timebase = elapsedTime;
        frame = 0;
    }
    
    
    // Change projection to show the string
    setOrthographicProjection();
    glPushMatrix();
    glLoadIdentity();
    renderBitmapString(5,30,0,GLUT_BITMAP_HELVETICA_18,s);
    glPopMatrix();
    // reset back to perspective projection
    restorePerspectiveProjection();
    
    // Finish drawing scene
    glFinish();
    glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Quit() {
    glFinish();
    glutDestroyWindow(WindowHandle);
    exit(0);
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Resize(int x,int y) {
    WinX = x;
    WinY = y;
    Cam.SetAspect(float(WinX)/float(WinY));
}

////////////////////////////////////////////////////////////////////////////////

void Tester::Keyboard(int key,int x,int y) {
    switch(key) {
        case 0x1b:		// Escape
            Quit();
            break;
        case 'r':
            Reset();
            break;
        case 'n':
            jointId += 1;
            break;
        case 'p':
            jointId -= 1;
            break;
        case 'x':
            sk->jointsArr.at(jointId)->dofx.phi -= 0.2;
            break;
        case 'X':
            sk->jointsArr.at(jointId)->dofx.phi += 0.2;
            break;
        case 'y':
            sk->jointsArr.at(jointId)->dofy.phi -= 0.2 ;
            break;
        case 'Y':
            sk->jointsArr.at(jointId)->dofy.phi += 0.2;
            break;
        case 'z':
            sk->jointsArr.at(jointId)->dofz.phi -= 0.2;
            break;
        case 'Z':
            sk->jointsArr.at(jointId)->dofz.phi += 0.2;
            break;
        case '1':
            setLights();
            break;
        case '2':
            unsetLights();
            break;
    }
    pose.x = 0; pose.y= 0; pose.z = 0;
}

////////////////////////////////////////////////////////////////////////////////

void Tester::MouseButton(int btn,int state,int x,int y) {
    if(btn==GLUT_LEFT_BUTTON) {
        LeftDown = (state==GLUT_DOWN);
    }
    else if(btn==GLUT_MIDDLE_BUTTON) {
        MiddleDown = (state==GLUT_DOWN);
    }
    else if(btn==GLUT_RIGHT_BUTTON) {
        RightDown = (state==GLUT_DOWN);
    }
}

////////////////////////////////////////////////////////////////////////////////

void Tester::MouseMotion(int nx,int ny) {
    int dx = nx - MouseX;
    int dy = -(ny - MouseY);
    
    MouseX = nx;
    MouseY = ny;
    
    // Move camera
    // NOTE: this should really be part of Camera::Update()
    if(LeftDown) {
        const float rate=1.0f;
        Cam.SetAzimuth(Cam.GetAzimuth()+dx*rate);
        Cam.SetIncline(Cam.GetIncline()-dy*rate);
    }
    if(RightDown) {
        const float rate=0.01f;
        Cam.SetDistance(Cam.GetDistance()*(1.0f-dx*rate));
    }
}

////////////////////////////////////////////////////////////////////////////////
