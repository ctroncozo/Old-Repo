////////////////////////////////////////
// tester.h
////////////////////////////////////////

#ifndef CSE169_TESTER_H
#define CSE169_TESTER_H

#include "core.h"
#include "camera.h"
#include "cube.h"
#include "Skeleton.h"
#include "SkinMesh.h"
#include "Vector3D.h"
#include "Joint.h"
#include "Light.h"
#include "Material.h"
#include "AnimationPlayer.h"

////////////////////////////////////////////////////////////////////////////////

class Tester {
public:
    Tester(int argc,char **argv);
    ~Tester();
    
    void Update();
    void Reset();
    void Draw();
    
    void Quit();
    
    // Event handlers
    void Resize(int x,int y);
    void Keyboard(int key,int x,int y);
    void MouseButton(int btn,int state,int x,int y);
    void MouseMotion(int x,int y);
    
    
    void renderBitmapString(float x, float y, float z, void *font, char *string);
    void restorePerspectiveProjection();
    void setOrthographicProjection();
    
    
private:
    // Window management
    int WindowHandle;
    int WinX,WinY;
    int jointId;
    Joint j;
    Vector3D pose;
    char s[50];
    Light *l0;
    Light *l1;
    long elapsedTime;
    long timebase;
    int frame;
    
    
    // Input
    bool LeftDown,MiddleDown,RightDown;
    int MouseX,MouseY;
    
    // Components
    Camera Cam;
    //SpinningCube Cube;
    Skeleton *sk;
    SkinMesh *skin;
    AnimationPlayer *player;
    void setLights();
    void unsetLights();
};

////////////////////////////////////////////////////////////////////////////////

/*
 The 'Tester' is a simple top level application class. It creates and manages a
 window with the GLUT extension to OpenGL and it maintains a simple 3D scene
 including a camera and some other components.
 */

#endif
