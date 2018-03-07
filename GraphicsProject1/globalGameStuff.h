#ifndef _globalGameStuff_HG_
#define _globalGameStuff_HG_

// This is all the global 'game' stuff, so:
// - not OpenGL rendering stuff (unless we can't help it)
// - just 'engine' or game play stuff

#include "cGameObject.h"
#include <vector>
#include <glm/vec3.hpp>
#include "cLightManager.h"

// Remember to #include <vector>...
extern std::vector< cGameObject* >  g_vecGameObjects;


extern glm::vec3 g_cameraXYZ;				// (theMain.cpp)
extern glm::vec3 g_cameraTarget_XYZ;		// (theMain.cpp)


extern cLightManager*	g_pLightManager;	// (theMain.cpp)

// Super basic physics update function
void PhysicsStep( double deltaTime );

// The teapots
extern cGameObject* pTP0;



#endif
