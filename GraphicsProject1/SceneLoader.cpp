// This file is used to laod the models
#include "cGameObject.h"
#include <vector>
#include "Utilities.h"		// getRandInRange()
#include <glm/glm.hpp>
#include "globalGameStuff.h"

extern std::vector< cGameObject* >  g_vecGameObjects;
extern cGameObject* g_pTheDebugSphere;

extern cGameObject* g_pSkyBoxObject;	// (theMain.cpp)

//const float SURFACEOFGROUND = -10.0f;
//const float RIGHTSIDEWALL = 15.0f;
//const float LEFTSIDEWALL = -15.0f;

void LoadModelsIntoScene(void)
{

	{	// Teapot #1
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 1.0f;
		pTempGO->position.y = 10.0f;
		pTempGO->meshName = "SmoothSphereRadius1InvertedNormals";		// Was teapot
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bIsWireFrame = true;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Teapot #1
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 5.0f;
		pTempGO->position.y = -5.0f;
		pTempGO->orientation2.x = glm::radians(-90.0f);
		pTempGO->meshName = "mountain";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string,float>("ground_grass.bmp",0.5f));
		pTempGO->textureNames.push_back(std::pair<std::string, float>("terrain.bmp",0.5f));;
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}


	{	// lamp #1

		//x:-122.699		bject : y : -34.5001		bject : z : -170.802
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->position.x = -122.699f;
		pTempGO->position.y = -34.5001f;
		pTempGO->position.z = -167.802f;
		pTempGO->orientation2.y = glm::radians(90.0f);
		pTempGO->meshName = "lamp";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Lamp #2

		//-34.1001	z:-184.302
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->position.x = -132.699f;
		pTempGO->position.y = -34.1001f;
		pTempGO->position.z = -184.302;
		pTempGO->orientation2.y = glm::radians(180.0f);
		pTempGO->meshName = "lamp";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));
		//pTempGO->textureNames.push_back(std::pair<std::string, float>("GuysOnSharkUnicorn.bmp", 0.0f));;
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTP0 = pTempGO;
		pTempGO->bHasAABB = true;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Lamp #3
		// x:-122.699	y:-34.5001		z : -171.202
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->position.x = -122.699f;
		pTempGO->position.y = -34.5001f;
		pTempGO->position.z = -170.602f;
		pTempGO->orientation2.y = glm::radians(90.0f);
		pTempGO->meshName = "lamp";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Lamp #4
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->orientation2.y = glm::radians(90.0f);
		pTempGO->position.x = -122.699f;
		pTempGO->position.y = -34.5001f;
		pTempGO->position.z = -176.802f;
		pTempGO->meshName = "lamp";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}


	//x:-122.699 y:-34.5001	z : -159.501
	{	// Lamp #5
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->position.x = -122.699f;
		pTempGO->position.y = -34.5001f;
		pTempGO->position.z = -159.501f;
		pTempGO->orientation2.y = glm::radians(90.0f);
		pTempGO->meshName = "lamp";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));
		//pTempGO->textureNames.push_back(std::pair<std::string, float>("GuysOnSharkUnicorn.bmp", 0.0f));;
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}



















	{	// Lamp #6
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->position.x = -137.009f;
		pTempGO->position.y = -34.1001f;
		pTempGO->position.z = -184.302f;
		pTempGO->orientation2.y = glm::radians(180.0f);
		pTempGO->meshName = "lamp";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));
		//pTempGO->textureNames.push_back(std::pair<std::string, float>("GuysOnSharkUnicorn.bmp", 0.0f));;
		pTempGO->hasTexture = true;
		pTempGO->bHasAABB = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Lamp #7
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;

		//-138.199	-34.3001	- 177.202
		pTempGO->position.x = -138.199f;
		pTempGO->position.y = -34.3001f;
		pTempGO->position.z = -177.202f;
		pTempGO->orientation2.y = glm::radians(-90.0f);
		pTempGO->meshName = "lamp";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));
		//pTempGO->textureNames.push_back(std::pair<std::string, float>("GuysOnSharkUnicorn.bmp", 0.0f));;
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Lamp #8

		//:-138.199		:-34.3001		: -170.001
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->position.x = -138.199f;
		pTempGO->position.y = -34.3001f;
		pTempGO->position.z = -170.001f;
		pTempGO->orientation2.y = glm::radians(-90.0f);
		pTempGO->meshName = "lamp";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));
		//pTempGO->textureNames.push_back(std::pair<std::string, float>("GuysOnSharkUnicorn.bmp", 0.0f));;
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Lamp #9

		//-138.199		-34.3001			- 167.401
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->position.x = -138.199f;
		pTempGO->position.y = -34.3001f;
		pTempGO->position.z = -167.401f;
		pTempGO->orientation2.y = glm::radians(-90.0f);
		pTempGO->meshName = "lamp";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));
		//pTempGO->textureNames.push_back(std::pair<std::string, float>("GuysOnSharkUnicorn.bmp", 0.0f));;
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Lamp #10
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->position.x = -138.199f;
		pTempGO->position.y = -34.3001f;
		pTempGO->position.z = -159.6f;
		pTempGO->orientation2.y = glm::radians(-90.0f);
		pTempGO->meshName = "lamp";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));
		//pTempGO->textureNames.push_back(std::pair<std::string, float>("GuysOnSharkUnicorn.bmp", 0.0f));;
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}


	{	// Lamp #11
		//-132.999		-34.3001			- 158.1
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->position.x = -132.998f;
		pTempGO->position.y = -34.3001f;
		pTempGO->position.z = -158.1f;
		pTempGO->meshName = "lamp";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));
		//pTempGO->textureNames.push_back(std::pair<std::string, float>("GuysOnSharkUnicorn.bmp", 0.0f));;
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Lamp #12

		//-127.998		-34.3001			- 158.1
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->position.x = -127.998f;
		pTempGO->position.y = -34.3001f;
		pTempGO->position.z = -158.1f;
		pTempGO->meshName = "lamp";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));
		//pTempGO->textureNames.push_back(std::pair<std::string, float>("GuysOnSharkUnicorn.bmp", 0.0f));;
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

//x:-93.9991
//	bject : y : -40.3
//	bject : z : -180.603

	{	// Teapot #1
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->position.x = -93.9991f;
		pTempGO->position.y = -40.3f;
		pTempGO->position.z = -180.603f;		
		pTempGO->meshName = "birch";		// Was teapot
		pTempGO->diffuseColour.a = 0.5f;
		pTempGO->textureNames.push_back(std::pair<std::string, float>("leaves.bmp", 0.5f));
		//pTempGO->textureNames.push_back(std::pair<std::string, float>("GuysOnSharkUnicorn.bmp", 0.0f));;
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Teapot #1
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.2f;
		pTempGO->position.x = -100.699f;
		pTempGO->position.y = -40.9f;
		pTempGO->position.z = -170.802f;		pTempGO->meshName = "birch";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("leaves.bmp", 0.5f));
		//pTempGO->textureNames.push_back(std::pair<std::string, float>("GuysOnSharkUnicorn.bmp", 0.0f));;
		pTempGO->hasTexture = true;
		pTempGO->bHasAABB = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}


	{	// Teapot #1
		cGameObject* pTempGO = new cGameObject();

		//done
		//ject:  x:-106.699 ject:  y:-40.9 ject : z : -175.802
		pTempGO->scale = 1.0f;
		pTempGO->position.x = -106.699f;
		pTempGO->position.y = -40.9f;
		pTempGO->position.z = -175.802f;		
		pTempGO->meshName = "birch";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("leaves.bmp", 0.5f));
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}


	{	// Teapot #1
		cGameObject* pTempGO = new cGameObject();
		//done
		pTempGO->scale = 1.0f;
		pTempGO->position.x = -110.399f;
		pTempGO->position.y = -40.5f;
		pTempGO->position.z = -162.201f;
		pTempGO->meshName = "birch";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("leaves.bmp", 0.5f));
		pTempGO->hasTexture = true;
		pTempGO->bHasAABB = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Teapot #1
		cGameObject* pTempGO = new cGameObject();
		// x:-118.399	ject:  y:-40.5 ject : z : -167.201
		pTempGO->scale = 2.0f;
		pTempGO->position.x = -118.399f;
		pTempGO->position.y = -40.5f;
		pTempGO->position.z = -167.201f;
		pTempGO->meshName = "birch";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("leaves.bmp", 0.5f));
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Teapot #1
		// x:-49.8998bject:  y:7.7bject:  z:0
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 1.0f;
		pTempGO->position.x = -49.8998f;
		pTempGO->position.y = 7.7f;
		pTempGO->position.z = 0.0f;
		pTempGO->meshName = "birch";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("leaves.bmp", 0.5f));
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// Teapot #1
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 1.0f;
		//x:9.8bject:  y:5.2bject:  z:-33.5001
		pTempGO->position.x = 9.8f;
		pTempGO->position.y = 5.2f;
		pTempGO->position.z = -33.5f;
		pTempGO->meshName = "birch";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("leaves.bmp", 0.5f));
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;		
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}

	{	// smalle house
		//:-131.699 y : -32.7001 z : -171.201
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 1.0f;
		pTempGO->position.x = 3.69998f;
		pTempGO->position.y = -5.40004f;
		pTempGO->position.z = -78.7994f;
		pTempGO->meshName = "house";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("Big_Old_House_C.bmp", 0.5f));
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}


	{	//big house
		//3.69998 y:-5.40004 z:-78.7994
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 1.0f;
		pTempGO->position.x = -131.699f;
		pTempGO->position.y = -32.7001f;
		pTempGO->position.z = -171.201f;
		pTempGO->meshName = "house1";		// Was teapot
		pTempGO->textureNames.push_back(std::pair<std::string, float>("houseA.bmp", 0.5f));
		pTempGO->hasTexture = true;
		pTempGO->bIsUpdatedInPhysics = false;
		pTempGO->bHasAABB = true;
		pTP0 = pTempGO;
		::g_vecGameObjects.push_back(pTempGO);		// Fastest way to add
	}
	
	{
		//cGameObject* pTempGO = new cGameObject();
		::g_pSkyBoxObject = new cGameObject();
		g_pSkyBoxObject->scale = 500.0f;
		g_pSkyBoxObject->position.y = -4.0f;
		g_pSkyBoxObject->diffuseColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		g_pSkyBoxObject->meshName = "SmoothSphereRadius1InvertedNormals";
		g_pSkyBoxObject->bIsUpdatedInPhysics = false;
		g_pSkyBoxObject->textureNames.push_back(std::pair<std::string,float>("TropicalSunnyDayBack2048.bmp", 1.0f));
		g_pSkyBoxObject->bIsSkyBoxObject = true;
		::g_vecGameObjects.push_back(::g_pSkyBoxObject);		// Fastest way to add
	}
	return;
}
