// Include glad and GLFW in correct order
#include "globalOpenGL_GLFW.h"


#include <iostream>			// C++ cin, cout, etc.
//#include "linmath.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


#include <stdlib.h>
#include <stdio.h>
// Add the file stuff library (file stream>
#include <fstream>
#include <sstream>		// "String stream"
#include <string>
#include <algorithm>

#include <vector>		//  smart array, "array" in most languages
#include "Utilities.h"
#include "ModelUtilities.h"
#include "cMesh.h"
#include "cShaderManager.h" 
#include "cGameObject.h"
#include "cVAOMeshManager.h"

#include "Physics.h"	// Physics collision detection functions

#include "cLightManager.h"

// Include all the things that are accessed in other files
#include "globalGameStuff.h"
#include "DebugRenderer.h"
#include "cEmitter.h"

DebugRenderer*	g_pTheDebugrender;

// Forward declaration of the function
void DrawObject(cGameObject* pTheGO);

void LoadUniformLocationsIfNeeded(unsigned int id);
void LoadModelsIntoScene(void);
bool Load3DModelsIntoMeshManager(int shaderID, cVAOMeshManager* pVAOManager, std::string &error);
// Used by the light drawing thingy
// Will draw a wireframe sphere at this location with this colour
void DrawDebugSphere(glm::vec3 location, glm::vec4 colour, float scale);
cGameObject* g_pTheDebugSphere;
cGameObject* g_pSkyBoxObject = NULL;
//	static const int MAXNUMBEROFGAMEOBJECTS = 10;
//	cGameObject* g_GameObjects[MAXNUMBEROFGAMEOBJECTS];

// Remember to #include <vector>...
std::vector< cGameObject* >  g_vecGameObjects;

glm::vec3 g_cameraXYZ = glm::vec3(-131.699, 50.1f, -171.201f);	// 5 units "down" z   
glm::vec3 g_cameraTarget_XYZ = glm::vec3(3.69998, -5.40004, -78.7994);

cVAOMeshManager* g_pVAOManager = 0;		// or NULL, or nullptr

//cShaderManager	g_ShaderManager;			// Stack (no new)
cShaderManager*		g_pShaderManager = 0;		// Heap, new (and delete)
cLightManager*		g_pLightManager = 0;

cBasicTextureManager*	g_pTextureManager = 0;

cEmitter* g_pParticleEmitter;
std::vector< cParticle* > g_vecParticlesToDraw;

// Other uniforms:
GLint uniLoc_materialDiffuse = -1;
GLint uniLoc_materialAmbient = -1;
GLint uniLoc_ambientToDiffuseRatio = -1; 	// Maybe	// 0.2 or 0.3
GLint uniLoc_materialSpecular = -1;  // rgb = colour of HIGHLIGHT only
							// w = shininess of the 
GLint uniLoc_bIsDebugWireFrameObject = -1;
GLint uniloc_bIsSkyBox = -1;
GLint uniLoc_eyePosition = -1;	// Camera position
GLint uniLoc_mModel = -1;
GLint uniLoc_mView = -1;
GLint uniLoc_mProjection = -1;
GLint uniLoc_bIsASkyBox = -1;

//for render modes
bool isWorldWireFrame = false;;
bool isWorldWithLights = true;
bool isWorldWithTextures = true;

GLint uniloc_bIsWorldWireframe;
GLint uniloc_bIsWorldWithLights;
GLint uniloc_bIsWorldWithTextures;

/////////////////
//	TEXTURE ids	//
/////////////////

GLint texSamp2D00_LocID = -1;
GLint texSamp2D01_LocID = -1;
GLint texSamp2D02_LocID = -1;
GLint texSamp2D03_LocID = -1;
GLint texSamp2D04_LocID = -1;
GLint texSamp2D05_LocID = -1;
GLint texSamp2D06_LocID = -1;
GLint texSamp2D07_LocID = -1;

GLint texBlend00_LocID = -1;
GLint texBlend01_LocID = -1;
GLint texBlend02_LocID = -1;
GLint texBlend03_LocID = -1;
GLint texBlend04_LocID = -1;
GLint texBlend05_LocID = -1;
GLint texBlend06_LocID = -1;
GLint texBlend07_LocID = -1;

// Cube map textures
GLint texSampCube00_LocID = -1;
GLint texSampCube01_LocID = -1;
GLint texSampCube02_LocID = -1;
GLint texSampCube03_LocID = -1;

GLint texCubeBlend00_LocID = -1;
GLint texCubeBlend01_LocID = -1;
GLint texCubeBlend02_LocID = -1;
GLint texCubeBlend03_LocID = -1;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}


bool getCloserObject(cGameObject*p1, cGameObject*p2) {
	float distance1 = glm::distance(g_cameraXYZ, p1->position);
	float distance2 = glm::distance(g_cameraXYZ, p2->position);
	return distance1 > distance2;
}

// HACK
cGameObject* pTP0 = 0;

int main(void)
{

	GLFWwindow* window;
	//    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	GLint mvp_location;	// , vpos_location, vcol_location;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	int height = 480;	/* default */
	int width = 640;	// default
	std::string title = "OpenGL Rocks";

	loadConfigFile(width,height,title);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// C++ string
	// C no strings. Sorry. char    char name[7] = "Michael\0";
	window = glfwCreateWindow(width, height,
		title.c_str(),
		NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	std::cout << glGetString(GL_VENDOR) << " "
		<< glGetString(GL_RENDERER) << ", "
		<< glGetString(GL_VERSION) << std::endl;
	std::cout << "Shader language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	::g_pShaderManager = new cShaderManager();

	cShaderManager::cShader vertShader;
	cShaderManager::cShader fragShader;


	vertShader.fileName = "simpleVert.glsl";
	fragShader.fileName = "simpleFrag.glsl";

	::g_pShaderManager->setBasePath("assets//shaders//");

	// Shader objects are passed by reference so that
	//	we can look at the results if we wanted to. 
	if (!::g_pShaderManager->createProgramFromFile(
		"mySexyShader", vertShader, fragShader))
	{
		std::cout << "Oh no! All is lost!!! Blame Loki!!!" << std::endl;
		std::cout << ::g_pShaderManager->getLastError() << std::endl;
		// Should we exit?? 
		return -1;
		//		exit(
	}
	std::cout << "The shaders comipled and linked OK" << std::endl;


	// Load models
	::g_pVAOManager = new cVAOMeshManager();

	GLint sexyShaderID = ::g_pShaderManager->getIDFromFriendlyName("mySexyShader");
	std::string error;

	if (!Load3DModelsFromModelFile(sexyShaderID, ::g_pVAOManager, error))
	{
		std::cout << "Not all models were loaded..." << std::endl;
		std::cout << error << std::endl;
	}

	//if ( ! Load3DModelsIntoMeshManager(sexyShaderID, ::g_pVAOManager, error ) )
	//{
	//	std::cout << "Not all models were loaded..." << std::endl;
	//	std::cout << error << std::endl;
	//}
	std::string modelsAndScene = "modelsAndScene.txt";
	LoadSceneFromFile(modelsAndScene);


	//LoadModelsIntoScene();

	g_pTheDebugrender = new DebugRenderer();
	if (!::g_pTheDebugrender->initialize(error))
	{
		std::cout << "Warning: couldn't init the debug renderer." << std::endl;
	}

	GLint currentProgID = ::g_pShaderManager->getIDFromFriendlyName("mySexyShader");

	// Get the uniform locations for this shader
	mvp_location = glGetUniformLocation(currentProgID, "MVP");		// program, "MVP");
	uniLoc_materialDiffuse = glGetUniformLocation(currentProgID, "materialDiffuse");
	uniLoc_materialAmbient = glGetUniformLocation(currentProgID, "materialAmbient");
	uniLoc_ambientToDiffuseRatio = glGetUniformLocation(currentProgID, "ambientToDiffuseRatio");
	uniLoc_materialSpecular = glGetUniformLocation(currentProgID, "materialSpecular");

	uniLoc_bIsDebugWireFrameObject = glGetUniformLocation(currentProgID, "bIsDebugWireFrameObject");
	uniLoc_bIsASkyBox = glGetUniformLocation(currentProgID, "isASkyBox");

	uniLoc_eyePosition = glGetUniformLocation(currentProgID, "eyePosition");

	uniLoc_mModel = glGetUniformLocation(currentProgID, "mModel");
	uniLoc_mView = glGetUniformLocation(currentProgID, "mView");
	uniLoc_mProjection = glGetUniformLocation(currentProgID, "mProjection");

	uniloc_bIsWorldWireframe = glGetUniformLocation(currentProgID, "isWorldWireFrame");
	uniloc_bIsWorldWithLights = glGetUniformLocation(currentProgID, "isWorldWithLights");
	uniloc_bIsWorldWithTextures = glGetUniformLocation(currentProgID, "isWorldWithTextures");


	::g_pLightManager = new cLightManager();

	::g_pLightManager->CreateLights(20);	// There are 10 lights in the shader
	::g_pLightManager->LoadShaderUniformLocations(currentProgID);
	LoadLightsAttributesFromFile(modelsAndScene, g_pLightManager->vecLights);

	// Texture 
	::g_pTextureManager = new cBasicTextureManager();
	::g_pTextureManager->SetBasePath("assets/textures");
	loadTexturesFromFile(modelsAndScene);

	::g_pTextureManager->SetBasePath("assets/textures/skybox");
	if (!::g_pTextureManager->CreateCubeTextureFromBMPFiles(
		"space",
		"SpaceBox_right1_posX.bmp",
		"SpaceBox_left2_negX.bmp",
		"SpaceBox_top3_posY.bmp",
		"SpaceBox_bottom4_negY.bmp",
		"SpaceBox_front5_posZ.bmp",
		"SpaceBox_back6_negZ.bmp", true, true))
	{
		std::cout << "Didn't load skybox" << std::endl;
	}

	mapTexturesToProperObjects();

	LoadUniformLocationsIfNeeded(currentProgID);

	glEnable(GL_DEPTH);

	::g_pParticleEmitter = new cEmitter();
	::g_pParticleEmitter->position = glm::vec3(-128.699, -25.3f, -163.202f);

	//int numParticles, int maxParticleCreatedPerStep,
	//	glm::vec3 minInitVel, glm::vec3 maxInitVel,
	//	float minLife, float maxLife,
	//	glm::vec3 minRangeFromEmitter,
	//	glm::vec3 maxRangeFromEmitter,
	//	glm::vec3 acceleration )
	::g_pParticleEmitter->init(200, 200,
		glm::vec3(0.1f, 0.1f, 0.1f),	// Min init vel
		glm::vec3(0.5f, 3.0f, 0.5f),	// max init vel
		5.0f, 10.0f,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f));

	// Gets the "current" time "tick" or "step"
	double lastTimeStep = glfwGetTime();
	std::vector<cGameObject*> tempVec = g_vecGameObjects;

	// Main game or application loop
	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		//        glm::mat4x4 m, p, mvp;			//  mat4x4 m, p, mvp;
		glm::mat4x4 p, mvp;			//  mat4x4 m, p, mvp;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);

		// Clear colour AND depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glEnable(GL_DEPTH_TEST);

		//        glUseProgram(program);
		::g_pShaderManager->useShaderProgram("mySexyShader");
		GLint shaderID = ::g_pShaderManager->getIDFromFriendlyName("mySexyShader");

		// Update all the light uniforms...
		// (for the whole scene)
		::g_pLightManager->CopyLightInformationToCurrentShader();

		// Projection and view don't change per scene (maybe)
		p = glm::perspective(0.6f,			// FOV
			ratio,		// Aspect ratio
			0.1f,			// Near (as big as possible)
			1000.0f);	// Far (as small as possible)

// View or "camera" matrix
		glm::mat4 v = glm::mat4(1.0f);	// identity

		//glm::vec3 cameraXYZ = glm::vec3( 0.0f, 0.0f, 5.0f );	// 5 units "down" z
		v = glm::lookAt(g_cameraXYZ,						// "eye" or "camera" position
			g_cameraTarget_XYZ,		// "At" or "target" 
			glm::vec3(0.0f, 1.0f, 0.0f));	// "up" vector

		glUniformMatrix4fv(uniLoc_mView, 1, GL_FALSE,
			(const GLfloat*)glm::value_ptr(v));
		glUniformMatrix4fv(uniLoc_mProjection, 1, GL_FALSE,
			(const GLfloat*)glm::value_ptr(p));

		// Enable blend ("alpha") transparency for the scene
		// NOTE: You "should" turn this OFF, then draw all NON-Transparent objects
		//       Then turn ON, sort objects from far to near ACCORDING TO THE CAMERA
		//       and draw them
		glEnable(GL_BLEND);		// Enables "blending"
								//glDisable( GL_BLEND );
								// Source == already on framebuffer
								// Dest == what you're about to draw
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		// Draw all the particles
		int particles = ::g_pParticleEmitter->getLivingParticles(::g_vecParticlesToDraw);

		//sort the particles based on disatnce from camera;

		std::vector<cGameObject*> tempObjectVec;
		for (int index = 0; index < particles; index++)
		{
			// Draw whatever object we want...
			// HACK:
			cGameObject* pParticleMesh = ::g_vecGameObjects[0];
			glm::vec3 oldPos = pParticleMesh->position;
			float rand = getRandInRange(0.0, 1.0);
			pParticleMesh->diffuseColour.a = rand;
			pParticleMesh->scale = 0.25;
			pParticleMesh->position = ::g_vecParticlesToDraw[index]->pos;
			//tempObjectVec.push_back(pParticleMesh);
			DrawObject(pParticleMesh);

			pParticleMesh->position = oldPos;
		}

		//sort the object by distance closest to camera
		std::sort(tempVec.begin(), tempVec.end(), getCloserObject);

		// Draw the scene
		unsigned int sizeOfVector = (unsigned int)tempVec.size();	//*****//
		for (int index = 0; index != sizeOfVector; index++)
		{
			cGameObject* pTheGO = tempVec[index];

			DrawObject(pTheGO);

			//			}// if ( ::g_pVAOManager->lookupVAOFromName(

		}//for ( int index = 0...

		std::stringstream ssTitle;
		ssTitle << "Camera (xyz): "
			<< g_cameraXYZ.x << ", "
			<< g_cameraXYZ.y << ", "
			<< g_cameraXYZ.z;
		glfwSetWindowTitle(window, ssTitle.str().c_str());

		// "Presents" what we've drawn
		// Done once per scene 
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Essentially the "frame time"
		// Now many seconds that have elapsed since we last checked
		double curTime = glfwGetTime();
		double deltaTime = curTime - lastTimeStep;

		g_pTheDebugrender->RenderDebugObjects(v, p, deltaTime);

		PhysicsStep(deltaTime);

		::g_pParticleEmitter->Update((float)deltaTime);

		lastTimeStep = curTime;

	}// while ( ! glfwWindowShouldClose(window) )


	glfwDestroyWindow(window);
	glfwTerminate();

	// 
	delete ::g_pShaderManager;
	delete ::g_pVAOManager;

	//    exit(EXIT_SUCCESS);
	return 0;
}



// Used by the light drawing thingy
// Will draw a wireframe sphere at this location with this colour
void DrawDebugSphere(glm::vec3 location, glm::vec4 colour,
	float scale)
{
	//// TODO: the magic
	//glm::vec3 oldPosition = ::g_pTheDebugSphere->position;
	//glm::vec4 oldDiffuse = ::g_pTheDebugSphere->diffuseColour;
	//bool bOldIsWireFrame = ::g_pTheDebugSphere->bIsWireFrame;

	//::g_pTheDebugSphere->position = location;
	//::g_pTheDebugSphere->diffuseColour = colour;
	//::g_pTheDebugSphere->bIsWireFrame = true;
	//::g_pTheDebugSphere->scale = scale;

	//DrawObject( ::g_pTheDebugSphere );

	//::g_pTheDebugSphere->position = oldPosition;
	//::g_pTheDebugSphere->diffuseColour = oldDiffuse;
	//::g_pTheDebugSphere->bIsWireFrame = bOldIsWireFrame;

	//return;
}

// Draw a single object
void DrawObject(cGameObject* pTheGO)
{
	// Is there a game object? 
	if (pTheGO == 0)	//if ( ::g_GameObjects[index] == 0 )
	{	// Nothing to draw
		return;		// Skip all for loop code and go to next
	}

	// Was near the draw call, but we need the mesh name
	std::string meshToDraw = pTheGO->meshName;		//::g_GameObjects[index]->meshName;

	sVAOInfo VAODrawInfo;
	if (::g_pVAOManager->lookupVAOFromName(meshToDraw, VAODrawInfo) == false)
	{	// Didn't find mesh
		std::cout << "WARNING: Didn't find mesh " << meshToDraw << " in VAO Manager" << std::endl;
		return;
	}

	if (pTheGO->bHasAABB)
	{
		cMesh* tempMesh = new cMesh();
		g_pVAOManager->lookupMeshFromName(pTheGO->meshName, *tempMesh);
		pTheGO->theBoundingBox = new AABB_Center_Radius(tempMesh, pTheGO->position, pTheGO->scale);
		pTheGO->theBoundingBox->buildBoundingBox(pTheGO->scale);
	}

	// 'model' or 'world' matrix
	glm::mat4x4 mModel = glm::mat4x4(1.0f);	//		mat4x4_identity(m);

	glm::mat4 matRreRotZ = glm::mat4x4(1.0f);
	matRreRotZ = glm::rotate(matRreRotZ, pTheGO->orientation.z,
		glm::vec3(0.0f, 0.0f, 1.0f));
	mModel = mModel * matRreRotZ;

	glm::mat4 trans = glm::mat4x4(1.0f);
	trans = glm::translate(trans,
		pTheGO->position);
	mModel = mModel * trans;

	glm::mat4 matPostRotZ = glm::mat4x4(1.0f);
	matPostRotZ = glm::rotate(matPostRotZ, pTheGO->orientation2.z,
		glm::vec3(0.0f, 0.0f, 1.0f));
	mModel = mModel * matPostRotZ;

	//			::g_vecGameObjects[index]->orientation2.y += 0.01f;

	glm::mat4 matPostRotY = glm::mat4x4(1.0f);
	matPostRotY = glm::rotate(matPostRotY, pTheGO->orientation2.y,
		glm::vec3(0.0f, 1.0f, 0.0f));
	mModel = mModel * matPostRotY;


	glm::mat4 matPostRotX = glm::mat4x4(1.0f);
	matPostRotX = glm::rotate(matPostRotX, pTheGO->orientation2.x,
		glm::vec3(1.0f, 0.0f, 0.0f));
	mModel = mModel * matPostRotX;
	// TODO: add the other rotation matrix (i.e. duplicate code above)

	float finalScale = pTheGO->scale;

	glm::mat4 matScale = glm::mat4x4(1.0f);
	matScale = glm::scale(matScale,
		glm::vec3(finalScale,
			finalScale,
			finalScale));
	mModel = mModel * matScale;



	glUniformMatrix4fv(uniLoc_mModel, 1, GL_FALSE,
		(const GLfloat*)glm::value_ptr(mModel));

	glm::mat4 mWorldInTranpose = glm::inverse(glm::transpose(mModel));


	glUniform4f(uniLoc_materialDiffuse,
		pTheGO->diffuseColour.r,
		pTheGO->diffuseColour.g,
		pTheGO->diffuseColour.b,
		pTheGO->diffuseColour.a);
	//...and all the other object material colours

	if (pTheGO->bIsWireFrame)
	{
		glUniform1f(uniLoc_bIsDebugWireFrameObject, 1.0f);	// TRUE
	}
	else
	{
		glUniform1f(uniLoc_bIsDebugWireFrameObject, 0.0f);	// FALSE
	}

	GLuint texture00Unit = 0;
	//set textures for individual object

	if (pTheGO->bIsSkyBoxObject)
	{
		std::string textureName = pTheGO->textureNames[0].first;
		GLuint texture00Number = ::g_pTextureManager->getTextureIDFromName(textureName);
		glActiveTexture(GL_TEXTURE0 + texture00Number);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture00Number);

		glUniform1i(texSampCube00_LocID, texture00Number);
	}
	else {
		for (int i = 0; i < pTheGO->textureNames.size(); i++)
		{
			std::string textureName = pTheGO->textureNames[i].first;
			GLuint texture00Number = ::g_pTextureManager->getTextureIDFromName(textureName);
			glActiveTexture(i + GL_TEXTURE0);		// GL_TEXTURE0 = 33984
			glBindTexture(GL_TEXTURE_2D, texture00Number);

			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, ::g_pTextureManager->getTextureIDFromName(pTheGO->textureNames[i].first));

			if (i == 0)
			{
				glUniform1f(texBlend00_LocID, pTheGO->textureNames[i].second);
			}
			else if (i == 1)
			{
				glUniform1f(texBlend01_LocID, pTheGO->textureNames[i].second);
			}
		}
	}

	if (isWorldWithTextures)
	{
		glUniform1f(uniloc_bIsWorldWithTextures, GL_TRUE);	// TRUE
	}
	else {
		glUniform1f(uniloc_bIsWorldWithTextures, GL_FALSE);	// TRUE
	}

	if (isWorldWithLights)
	{
		glUniform1f(uniloc_bIsWorldWithLights, GL_TRUE);	// TRUE
	}
	else {
		glUniform1f(uniloc_bIsWorldWithLights, GL_FALSE);	// TRUE
	}

	if (pTheGO->bIsSkyBoxObject)
	{
		glUniform1f(uniLoc_bIsASkyBox, GL_TRUE);	// TRUE
		glDisable(GL_DEPTH);
	}
	else
		glUniform1f(uniLoc_bIsASkyBox, GL_FALSE);	// TRUE


	if (isWorldWireFrame)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Default
		//		glEnable(GL_DEPTH_TEST);		// Test for z and store in z buffer
		glDisable(GL_CULL_FACE);
		glUniform1f(uniloc_bIsWorldWireframe, GL_TRUE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// Default
		glEnable(GL_DEPTH_TEST);		// Test for z and store in z buffer
		glEnable(GL_CULL_FACE);
		glUniform1f(uniloc_bIsWorldWireframe, GL_FALSE);

	}

	glCullFace(GL_BACK);


	glBindVertexArray(VAODrawInfo.VAO_ID);

	glDrawElements(GL_TRIANGLES,
		VAODrawInfo.numberOfIndices,		// testMesh.numberOfTriangles * 3,	// How many vertex indices
		GL_UNSIGNED_INT,					// 32 bit int 
		0);
	// Unbind that VAO
	glBindVertexArray(0);

	return;
}



void LoadUniformLocationsIfNeeded(unsigned int shaderID)
{

	texSamp2D00_LocID = glGetUniformLocation(shaderID, "myAmazingTexture00");
	texSamp2D01_LocID = glGetUniformLocation(shaderID, "myAmazingTexture01");

	texBlend00_LocID = glGetUniformLocation(shaderID, "textureBlend00");
	texBlend01_LocID = glGetUniformLocation(shaderID, "textureBlend01");

	texSampCube00_LocID = glGetUniformLocation(shaderID, "texSampCube00");
	//texSampCube01_LocID = glGetUniformLocation(shaderID, "texSampCube01");
	//texSampCube02_LocID = glGetUniformLocation(shaderID, "texSampCube02");

	//texCubeBlend00_LocID = glGetUniformLocation(shaderID, "texCubeBlend00");
	//texCubeBlend01_LocID = glGetUniformLocation(shaderID, "texCubeBlend01");
	//texCubeBlend02_LocID = glGetUniformLocation(shaderID, "texCubeBlend02");
	return;
}// void LoadUniformLocationsIfNeeded()