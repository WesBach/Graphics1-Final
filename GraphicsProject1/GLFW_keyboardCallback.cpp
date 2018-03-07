#include "globalOpenGL_GLFW.h"
#include "globalGameStuff.h"

#include <iostream>

bool isShiftKeyDown( int mods, bool bByItself = true );
bool isCtrlKeyDown( int mods, bool bByItself = true );
bool isAltKeyDown( int mods, bool bByItself = true );
int objectIndex = 0;
int lightIndex = 0;

extern bool isWorldWithLights;
extern bool isWorldWithTextures;
extern bool isWorldWireFrame;


/*static*/ void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

	if ( key == GLFW_KEY_SPACE   && action == GLFW_PRESS)
	{
//		::g_GameObjects[1]->position.y += 0.01f;
		std::cout << "Object: " + objectIndex << " x:" << ::g_vecGameObjects[objectIndex]->position.x << std::endl;
		std::cout << "Object: " + objectIndex << " y:" << ::g_vecGameObjects[objectIndex]->position.y << std::endl;
		std::cout << "Object: " + objectIndex << " z:" << ::g_vecGameObjects[objectIndex]->position.z << std::endl;
	}

	if (key == GLFW_KEY_ENTER  && action == GLFW_PRESS)
	{
		//		::g_GameObjects[1]->position.y += 0.01f;
		std::cout << "Object: " + lightIndex << " x:" << g_pLightManager->vecLights[lightIndex].attenuation.x << std::endl;
		std::cout << "Object: " + lightIndex << " y:" << g_pLightManager->vecLights[lightIndex].attenuation.y << std::endl;
		std::cout << "Object: " + lightIndex << " z:" << g_pLightManager->vecLights[lightIndex].attenuation.z << std::endl;
		std::cout << "Object: " + lightIndex << " Posx:" << g_pLightManager->vecLights[lightIndex].position.x << std::endl;
		std::cout << "Object: " + lightIndex << " Posy:" << g_pLightManager->vecLights[lightIndex].position.y << std::endl;
		std::cout << "Object: " + lightIndex << " Posz:" << g_pLightManager->vecLights[lightIndex].position.z << std::endl;
	}

	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		if (objectIndex == g_vecGameObjects.size() - 1)
			objectIndex = 0;
		else
			objectIndex++;

		g_cameraTarget_XYZ = g_vecGameObjects[objectIndex]->position;

	}
	
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
	{
		if (lightIndex == g_pLightManager->vecLights.size() - 1)
			lightIndex = 0;
		else
			lightIndex++;

		g_cameraTarget_XYZ = g_pLightManager->vecLights[lightIndex].position;
		g_vecGameObjects[0]->position = g_cameraTarget_XYZ;
	}

	if (key == GLFW_KEY_8 && action == GLFW_PRESS)
	{
		isWorldWireFrame = !isWorldWireFrame;
	}

	if (key == GLFW_KEY_9 && action == GLFW_PRESS)
	{
		isWorldWithLights = !isWorldWithLights;
	}

	if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	{
		isWorldWithTextures = !isWorldWithTextures;
	}
		
	const float CAMERASPEED = 1.0f;
	const float LIGHTSPEED = 0.2f;
	switch (key)
	{
	case GLFW_KEY_UP:
		::g_vecGameObjects[objectIndex]->position.y += 0.1f;
		g_cameraTarget_XYZ.y = ::g_vecGameObjects[objectIndex]->position.y;
		break;

	case GLFW_KEY_DOWN:
		::g_vecGameObjects[objectIndex]->position.y -= 0.1f;
		g_cameraTarget_XYZ.y = ::g_vecGameObjects[objectIndex]->position.y;
		break;

	case GLFW_KEY_LEFT:
		::g_vecGameObjects[objectIndex]->position.x -= 0.1f;
		g_cameraTarget_XYZ.x = ::g_vecGameObjects[objectIndex]->position.x;
		break;

	case GLFW_KEY_RIGHT:
		::g_vecGameObjects[objectIndex]->position.x += 0.1f;
		g_cameraTarget_XYZ.x = ::g_vecGameObjects[objectIndex]->position.x;
		break;

	case GLFW_KEY_RIGHT_SHIFT:
		::g_vecGameObjects[objectIndex]->position.z -= 0.1f;
		g_cameraTarget_XYZ.z = ::g_vecGameObjects[objectIndex]->position.z;
		break;

	case GLFW_KEY_KP_1:
		::g_vecGameObjects[objectIndex]->position.z += 0.1f;
		g_cameraTarget_XYZ.z = ::g_vecGameObjects[objectIndex]->position.z;
		break;

	case GLFW_KEY_I:
		::g_pLightManager->vecLights[lightIndex].position.z += LIGHTSPEED;
		g_vecGameObjects[0]->position.z = g_pLightManager->vecLights[lightIndex].position.z;
		g_cameraTarget_XYZ = g_pLightManager->vecLights[lightIndex].position;
		break;
	case GLFW_KEY_J:
		::g_pLightManager->vecLights[lightIndex].position.x -= CAMERASPEED;
		g_vecGameObjects[0]->position.x = g_pLightManager->vecLights[lightIndex].position.x;
		g_cameraTarget_XYZ = g_pLightManager->vecLights[lightIndex].position;
		break;
	case GLFW_KEY_K:
		::g_pLightManager->vecLights[lightIndex].position.z -= LIGHTSPEED;
		g_vecGameObjects[0]->position.z = g_pLightManager->vecLights[lightIndex].position.z;
		g_cameraTarget_XYZ = g_pLightManager->vecLights[lightIndex].position;
		break;
	case GLFW_KEY_L:
		::g_pLightManager->vecLights[lightIndex].position.x += LIGHTSPEED;
		g_vecGameObjects[0]->position.x = g_pLightManager->vecLights[lightIndex].position.x;
		g_cameraTarget_XYZ = g_pLightManager->vecLights[lightIndex].position;
		break;

	case GLFW_KEY_U:
		::g_pLightManager->vecLights[lightIndex].position.y -= LIGHTSPEED;
		g_vecGameObjects[0]->position.y = g_pLightManager->vecLights[lightIndex].position.y;
		g_cameraTarget_XYZ = g_pLightManager->vecLights[lightIndex].position;
		break;
	case GLFW_KEY_P:
		::g_pLightManager->vecLights[lightIndex].position.y += LIGHTSPEED;
		g_vecGameObjects[0]->position.y = g_pLightManager->vecLights[lightIndex].position.y;
		g_cameraTarget_XYZ = g_pLightManager->vecLights[lightIndex].position;
		break;

	case GLFW_KEY_A:		// Left
//		g_cameraTarget_XYZ.x -= CAMERASPEED;
		if ( isShiftKeyDown(mods, true) )	
		{	::g_pLightManager->vecLights[lightIndex].position.x -= CAMERASPEED;	}
		else								
		{	::g_cameraXYZ.x -= CAMERASPEED;		}
		break;
	case GLFW_KEY_D:		// Right
//		g_cameraTarget_XYZ.x += CAMERASPEED;
		if ( isShiftKeyDown(mods, true) )	
		{	::g_pLightManager->vecLights[lightIndex].position.x += LIGHTSPEED;	}
		else
		{	::g_cameraXYZ.x += CAMERASPEED;	}		
		break;
	case GLFW_KEY_W:		// Forward (along z)
		if ( isShiftKeyDown(mods, true) )	
		{	::g_pLightManager->vecLights[lightIndex].position.z += LIGHTSPEED;	}
		else
		{	::g_cameraXYZ.z += CAMERASPEED;	}
		break;
	case GLFW_KEY_S:		// Backwards (along z)
		if ( isShiftKeyDown(mods, true) )	
		{	::g_pLightManager->vecLights[lightIndex].position.z -= LIGHTSPEED;	}
		else
		{	::g_cameraXYZ.z -= CAMERASPEED;	}
		break;
	case GLFW_KEY_Q:		// "Down" (along y axis)
		if ( isShiftKeyDown(mods, true) )	
		{	::g_pLightManager->vecLights[lightIndex].position.y -= LIGHTSPEED;	}
		else
		{	::g_cameraXYZ.y -= CAMERASPEED;	}
		break;
	case GLFW_KEY_E:		// "Up" (along y axis)
		if ( isShiftKeyDown(mods, true) )	
		{	::g_pLightManager->vecLights[lightIndex].position.y += LIGHTSPEED;	}
		else
		{	::g_cameraXYZ.y += CAMERASPEED;	}
		break;

	case GLFW_KEY_1:
		::g_pLightManager->vecLights[lightIndex].attenuation.y *= 0.99f;	// less 1%
		break;
	case GLFW_KEY_2:
		::g_pLightManager->vecLights[lightIndex].attenuation.y *= 1.01f; // more 1%
		if ( ::g_pLightManager->vecLights[lightIndex].attenuation.y <= 0.0f )
		{
			::g_pLightManager->vecLights[lightIndex].attenuation.y = 0.001f;	// Some really tiny value
		}
		break;
	case GLFW_KEY_3:	// Quad
		::g_pLightManager->vecLights[lightIndex].attenuation.z *= 0.99f;	// less 1%
		break;
	case GLFW_KEY_4:	//  Quad
		::g_pLightManager->vecLights[lightIndex].attenuation.z *= 1.01f; // more 1%
		if ( ::g_pLightManager->vecLights[lightIndex].attenuation.z <= 0.0f )
		{
			::g_pLightManager->vecLights[lightIndex].attenuation.z = 0.001f;	// Some really tiny value
		}
		break;

	}
	// HACK: print output to the console
//	std::cout << "Light[0] linear atten: "
//		<< ::g_pLightManager->vecLights[0].attenuation.y << ", "
//		<< ::g_pLightManager->vecLights[0].attenuation.z << std::endl;
	return;
}



// Helper functions
bool isShiftKeyDown( int mods, bool bByItself /*=true*/ )
{
	if ( bByItself )
	{	// shift by itself?
		if ( mods == GLFW_MOD_SHIFT )	{ return true; }
		else							{ return false; }
	}
	else
	{	// shift with anything else, too
		if ( ( mods && GLFW_MOD_SHIFT ) == GLFW_MOD_SHIFT )	{	return true;	}
		else												{	return false;	}
	}
	// Shouldn't never get here, so return false? I guess?
	return false;
}

//bool isCtrlKeyDown( int mods, bool bByItself = true );
//bool isAltKeyDown( int mods, bool bByItself = true );