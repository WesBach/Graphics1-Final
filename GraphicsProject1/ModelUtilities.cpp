#include "ModelUtilities.h" 
#include "cVAOMeshManager.h"
#include "cMesh.h"
#include <sstream>
#include "cGameObject.h"
#include "cLightManager.h"
#include "inc\glm\vec3.hpp"
#include "inc\glm\glm.hpp"
#include "globalOpenGL_GLFW.h"

extern glm::vec3 g_cameraXYZ;
extern std::vector<cGameObject*> g_vecGameObjects;


void ReadFileToToken( std::ifstream &file, std::string token )
{
	bool bKeepReading = true;
	std::string garbage;
	do
	{
		file >> garbage;		// Title_End??
		if ( garbage == token )
		{
			return;
		}
	}while( bKeepReading );
	return;
}



// Takes a file name, loads a mesh
bool LoadPlyFileIntoMesh( std::string filename, cMesh &theMesh )
{
	// Load the vertices
	// c_str() changes a string to a "c style char* string"
	std::ifstream plyFile( filename.c_str() );

	if ( ! plyFile.is_open() )
	{	// Didn't open file, so return
		return false;
	}
	// File is open, let's read it

	ReadFileToToken( plyFile, "vertex" );
//	int numVertices = 0;
	plyFile >> theMesh.numberOfVertices;

	ReadFileToToken( plyFile, "face" );
//	int numTriangles = 0;
	plyFile >> theMesh.numberOfTriangles;		

	ReadFileToToken( plyFile, "end_header" );

	// Allocate the appropriate sized array (+a little bit)
	//theMesh.pVertices = new cVertex_xyz_rgb_n[theMesh.numberOfVertices];
	theMesh.pVertices = new sVertex_xyz_rgba_n_uv2_bt[theMesh.numberOfVertices];
	theMesh.pTriangles = new cTriangle[theMesh.numberOfTriangles];

	// Read vertices
	for ( int index = 0; index < theMesh.numberOfVertices; index++ )
	{
		//end_header
		//-0.0312216 0.126304 0.00514924 0.850855 0.5 		
		float x, y, z;//, confidence, intensity;

		plyFile >> x;
		plyFile >> y;
		plyFile >> z;
//		plyFile >> confidence;
//		plyFile >> intensity;

		theMesh.pVertices[index].x = x;	// vertices[index].x = x;
		theMesh.pVertices[index].y = y;	// vertices[index].y = y;
		theMesh.pVertices[index].z = z; 
		theMesh.pVertices[index].r = 1.0f;	// vertices[index].g = 1.0f;
		theMesh.pVertices[index].g = 1.0f;	// vertices[index].b = 1.0f;
		theMesh.pVertices[index].b = 1.0f;	// vertices[index].r = 1.0f;
	}

	// Load the triangle (or face) information, too
	for ( int count = 0; count < theMesh.numberOfTriangles; count++ )
	{
		// 3 164 94 98 
		int discard = 0;
		plyFile >> discard;									// 3
		plyFile >> theMesh.pTriangles[count].vertex_ID_0;	// 164
		plyFile >> theMesh.pTriangles[count].vertex_ID_1;	// 94
		plyFile >> theMesh.pTriangles[count].vertex_ID_2;	// 98
	}

	theMesh.CalculateNormals();

	return true;
}

// Takes a file name, loads a mesh
bool LoadPlyFileIntoMeshWithNormals( std::string filename, cMesh &theMesh )
{
	// Load the vertices
	// c_str() changes a string to a "c style char* string"
	std::string file = "assets\\models\\" + filename;
	std::ifstream plyFile(file.c_str());

	if ( ! plyFile.is_open() )
	{	// Didn't open file, so return
		return false;
	}
	// File is open, let's read it

	ReadFileToToken( plyFile, "vertex" );
//	int numVertices = 0;
	plyFile >> theMesh.numberOfVertices;

	ReadFileToToken( plyFile, "face" );
//	int numTriangles = 0;
	plyFile >> theMesh.numberOfTriangles;		

	ReadFileToToken( plyFile, "end_header" );

	// Allocate the appropriate sized array (+a little bit)
	//theMesh.pVertices = new cVertex_xyz_rgb_n[theMesh.numberOfVertices];
	theMesh.pVertices = new sVertex_xyz_rgba_n_uv2_bt[theMesh.numberOfVertices];
	theMesh.pTriangles = new cTriangle[theMesh.numberOfTriangles];

	// Read vertices
	for ( int index = 0; index < theMesh.numberOfVertices; index++ )
	{
		//end_header
		//-0.0312216 0.126304 0.00514924 0.850855 0.5 		
		float x, y, z, nx, ny, nz;//, confidence, intensity;

		plyFile >> x;
		plyFile >> y;
		plyFile >> z;
		plyFile >> nx >> ny >> nz;
//		plyFile >> confidence;
//		plyFile >> intensity;

		theMesh.pVertices[index].x = x;	// vertices[index].x = x;
		theMesh.pVertices[index].y = y;	// vertices[index].y = y;
		theMesh.pVertices[index].z = z; 
		theMesh.pVertices[index].r = 1.0f;	// vertices[index].g = 1.0f;
		theMesh.pVertices[index].g = 1.0f;	// vertices[index].b = 1.0f;
		theMesh.pVertices[index].b = 1.0f;	// vertices[index].r = 1.0f;
		theMesh.pVertices[index].nx = nx;	// vertices[index].g = 1.0f;
		theMesh.pVertices[index].ny = ny;	// vertices[index].b = 1.0f;
		theMesh.pVertices[index].nz = nz;	// vertices[index].r = 1.0f;
	}

	// Load the triangle (or face) information, too
	for ( int count = 0; count < theMesh.numberOfTriangles; count++ )
	{
		// 3 164 94 98 
		int discard = 0;
		plyFile >> discard;									// 3
		plyFile >> theMesh.pTriangles[count].vertex_ID_0;	// 164
		plyFile >> theMesh.pTriangles[count].vertex_ID_1;	// 94
		plyFile >> theMesh.pTriangles[count].vertex_ID_2;	// 98
	}

//	theMesh.CalculateNormals();

	return true;
}

// Takes a file name, loads a mesh
bool LoadPlyFileIntoMeshWith_Normals_and_UV( std::string filename, cMesh &theMesh )
{
	// Load the vertices
	std::string file = "assets\\models\\" + filename;
	// c_str() changes a string to a "c style char* string"
	std::ifstream plyFile(file.c_str() );

	if ( ! plyFile.is_open() )
	{	// Didn't open file, so return
		return false;
	}
	// File is open, let's read it

	ReadFileToToken( plyFile, "vertex" );
//	int numVertices = 0;
	plyFile >> theMesh.numberOfVertices;

	ReadFileToToken( plyFile, "face" );
//	int numTriangles = 0;
	plyFile >> theMesh.numberOfTriangles;		

	ReadFileToToken( plyFile, "end_header" );

	// Allocate the appropriate sized array (+a little bit)
	//theMesh.pVertices = new cVertex_xyz_rgb_n[theMesh.numberOfVertices];
	theMesh.pVertices = new sVertex_xyz_rgba_n_uv2_bt[theMesh.numberOfVertices];
	theMesh.pTriangles = new cTriangle[theMesh.numberOfTriangles];

	// Read vertices
	for ( int index = 0; index < theMesh.numberOfVertices; index++ )
	{
		//end_header
		//-0.0312216 0.126304 0.00514924 0.850855 0.5 		
		float x, y, z, nx, ny, nz;
		// Added
		float u, v;		// Model now has texture coordinate

		// Typical vertex is now... 
		// 29.3068 -5e-006 24.3079 -0.949597 0.1875 -0.251216 0.684492 0.5

		plyFile >> x >> y >> z;
		plyFile >> nx >> ny >> nz;
		// 
		plyFile >> u >> v;			// ADDED
			

		theMesh.pVertices[index].x = x;	// vertices[index].x = x;
		theMesh.pVertices[index].y = y;	// vertices[index].y = y;
		theMesh.pVertices[index].z = z; 
		theMesh.pVertices[index].r = 1.0f;	// vertices[index].g = 1.0f;
		theMesh.pVertices[index].g = 1.0f;	// vertices[index].b = 1.0f;
		theMesh.pVertices[index].b = 1.0f;	// vertices[index].r = 1.0f;
		theMesh.pVertices[index].nx = nx;	// vertices[index].g = 1.0f;
		theMesh.pVertices[index].ny = ny;	// vertices[index].b = 1.0f;
		theMesh.pVertices[index].nz = nz;	// vertices[index].r = 1.0f;

		// Only store the 1st UV.
		theMesh.pVertices[index].u1 = u;
		theMesh.pVertices[index].v1 = v;
	}

	// Load the triangle (or face) information, too
	for ( int count = 0; count < theMesh.numberOfTriangles; count++ )
	{
		// 3 164 94 98 
		int discard = 0;
		plyFile >> discard;									// 3
		plyFile >> theMesh.pTriangles[count].vertex_ID_0;	// 164
		plyFile >> theMesh.pTriangles[count].vertex_ID_1;	// 94
		plyFile >> theMesh.pTriangles[count].vertex_ID_2;	// 98
	}

//	theMesh.CalculateNormals();

	return true;
}

bool Load3DModelsIntoMeshManager(int shaderID, cVAOMeshManager* pVAOManager, std::string &error)
{
	std::stringstream ssError;
	bool bAllGood = true;

	{
		cMesh testMesh;
		testMesh.name = "mountain";
		if ( !LoadPlyFileIntoMeshWith_Normals_and_UV( "mount.blend.ply", testMesh ) )
		{ 
			//std::cout << "Didn't load model" << std::endl;
			ssError << "Didn't load model >" << testMesh.name << "<" << std::endl;
			bAllGood = false;
		}
		if ( ! pVAOManager->loadMeshIntoVAO( testMesh, shaderID ) )
		{
			//std::cout << "Could not load mesh into VAO" << std::endl;
			ssError << "Could not load mesh >" << testMesh.name << "< into VAO" << std::endl;
			bAllGood = false;
		}
	}
	//birch_tree1.ply

	{
		cMesh testMesh;
		testMesh.name = "house";
		if (!LoadPlyFileIntoMeshWith_Normals_and_UV("Big_Old_House.ply", testMesh))
		{
			//std::cout << "Didn't load model" << std::endl;
			ssError << "Didn't load model >" << testMesh.name << "<" << std::endl;
			bAllGood = false;
		}
		if (!pVAOManager->loadMeshIntoVAO(testMesh, shaderID))
		{
			//std::cout << "Could not load mesh into VAO" << std::endl;
			ssError << "Could not load mesh >" << testMesh.name << "< into VAO" << std::endl;
			bAllGood = false;
		}
	}

	{
		cMesh testMesh;
		testMesh.name = "birch";
		if (!LoadPlyFileIntoMeshWith_Normals_and_UV("birch_tree1.ply", testMesh))
		{
			//std::cout << "Didn't load model" << std::endl;
			ssError << "Didn't load model >" << testMesh.name << "<" << std::endl;
			bAllGood = false;
		}
		if (!pVAOManager->loadMeshIntoVAO(testMesh, shaderID))
		{
			//std::cout << "Could not load mesh into VAO" << std::endl;
			ssError << "Could not load mesh >" << testMesh.name << "< into VAO" << std::endl;
			bAllGood = false;
		}
	}

	{
		cMesh testMesh;
		testMesh.name = "house1";
		if (!LoadPlyFileIntoMeshWith_Normals_and_UV("houseA.ply", testMesh))
		{
			//std::cout << "Didn't load model" << std::endl;
			ssError << "Didn't load model >" << testMesh.name << "<" << std::endl;
			bAllGood = false;
		}
		if (!pVAOManager->loadMeshIntoVAO(testMesh, shaderID))
		{
			//std::cout << "Could not load mesh into VAO" << std::endl;
			ssError << "Could not load mesh >" << testMesh.name << "< into VAO" << std::endl;
			bAllGood = false;
		}
	}

	{
		cMesh testMesh;
		testMesh.name = "lamp";
		if (!LoadPlyFileIntoMeshWith_Normals_and_UV("Exterior_lamp.ply", testMesh))
		{
			//std::cout << "Didn't load model" << std::endl;
			ssError << "Didn't load model >" << testMesh.name << "<" << std::endl;
			bAllGood = false;
		}
		if (!pVAOManager->loadMeshIntoVAO(testMesh, shaderID))
		{
			//std::cout << "Could not load mesh into VAO" << std::endl;
			ssError << "Could not load mesh >" << testMesh.name << "< into VAO" << std::endl;
			bAllGood = false;
		}
	}

	{
		cMesh testMesh;
		testMesh.name = "lamp";
		if (!LoadPlyFileIntoMeshWith_Normals_and_UV("Exterior_lamp.ply", testMesh))
		{
			//std::cout << "Didn't load model" << std::endl;
			ssError << "Didn't load model >" << testMesh.name << "<" << std::endl;
			bAllGood = false;
		}
		if (!pVAOManager->loadMeshIntoVAO(testMesh, shaderID))
		{
			//std::cout << "Could not load mesh into VAO" << std::endl;
			ssError << "Could not load mesh >" << testMesh.name << "< into VAO" << std::endl;
			bAllGood = false;
		}
	}
	

	{
		cMesh testMesh;
		testMesh.name = "SmoothSphereRadius1InvertedNormals";
		if (!LoadPlyFileIntoMeshWith_Normals_and_UV("SmoothSphere_Inverted_Normals_xyz_n_uv.ply", testMesh))
		{
			//std::cout << "Didn't load model" << std::endl;
			ssError << "Didn't load model >" << testMesh.name << "<" << std::endl;
			bAllGood = false;
		}
		if (!pVAOManager->loadMeshIntoVAO(testMesh, shaderID))
		{
			//std::cout << "Could not load mesh into VAO" << std::endl;
			ssError << "Could not load mesh >" << testMesh.name << "< into VAO" << std::endl;
			bAllGood = false;
		}
	}
	if ( ! bAllGood ) 
	{
		// Copy the error string stream into the error string that
		//	gets "returned" (through pass by reference)
		error = ssError.str();
	}

	return bAllGood;
}

bool LoadLightsAttributesFromFile(std::string& fileName, std::vector<cLight>& theLights) {
	//open the file
	std::ifstream modelAndSceneFile(fileName.c_str());
	cMesh* testMesh;
	int numLights = 0;

	if (!modelAndSceneFile.is_open())
	{	// Didn't open file, so return
		return false;
	}

	ReadFileToToken(modelAndSceneFile, "NUM_LIGHTS_TO_LOAD");
	modelAndSceneFile >> numLights;

	ReadFileToToken(modelAndSceneFile, "LIGHTS_BEGIN");

	std::string tempType;
	for (int i = 0; i < numLights; i++)
	{
		
		modelAndSceneFile >> theLights[i].position.x;
		modelAndSceneFile >> theLights[i].position.y;
		modelAndSceneFile >> theLights[i].position.z;
		modelAndSceneFile >> theLights[i].attenuation.x;
		modelAndSceneFile >> theLights[i].attenuation.y;
		modelAndSceneFile >> theLights[i].attenuation.z;
		modelAndSceneFile >> theLights[i].diffuse.r;
		modelAndSceneFile >> theLights[i].diffuse.g;
		modelAndSceneFile >> theLights[i].diffuse.b;
		modelAndSceneFile >> tempType;
		if (tempType == "DIRECTIONAL")
			theLights[i].setLightParamType(cLight::POINT);
		else if (tempType == "SPOT")
		{
			theLights[i].setLightParamType(cLight::SPOT);
			theLights[i].direction = glm::vec3(0.0f, -1.0f, 0.0f);
			theLights[i].setLightParamSpotPrenumAngleInner(glm::radians(15.0f));
			theLights[i].setLightParamSpotPrenumAngleOuter(glm::radians(25.0f));
		}

	}

	//close the file stream
	modelAndSceneFile.close();
	return 0;
}

bool Load3DModelsFromModelFile(int shaderID, cVAOMeshManager* pVAOManager, std::string &error)
{
	std::string fileName = "modelsAndScene.txt";
	std::ifstream modelNameFile(fileName.c_str());
	//cMesh* testMesh;

	std::stringstream ssError;
	bool bAnyErrors = false;
	std::string tempString;
	int numModels = 0;
	int numModelsUV;

	if (!modelNameFile.is_open())
	{	// Didn't open file, so return
		return false;
	}


	//ReadFileToToken(modelNameFile, "NUM_MODELS");
	//modelNameFile >> numModels;
	//ReadFileToToken(modelNameFile, "MODEL_NAME_START");

	//for (int i = 0; i < numModels; i++)
	//{
	//	modelNameFile >> tempString;
	//	cMesh* testMesh;
	//	testMesh = new cMesh();
	//	testMesh->name = tempString;
	//	if (!LoadPlyFileIntoMeshWithNormals(tempString, *testMesh))
	//	{
	//		//std::cout << "Didn't load model" << std::endl;
	//		ssError << "Didn't load model >" << testMesh->name << "<" << std::endl;
	//		bAnyErrors = true;
	//	}
	//	if (!pVAOManager->loadMeshIntoVAO(*testMesh, shaderID))
	//	{
	//		//std::cout << "Could not load mesh into VAO" << std::endl;
	//		ssError << "Could not load mesh >" << testMesh->name << "< into VAO" << std::endl;
	//		bAnyErrors = true;
	//	}
	//	//if (testMesh->name == "Mountain_landscape_xyz_n_.ply" || testMesh->name == "Mountain_landscape_xyz_n.ply")
	//	//{
	//	//	testMesh->GeneratePhysicsTriangles();
	//	//	g_GameTerrain = testMesh;
	//	//}

	//	tempString = "";
	//}

	ReadFileToToken(modelNameFile, "NUM_MODELS_UV");
	modelNameFile >> numModelsUV;
	ReadFileToToken(modelNameFile, "MODEL_NAME_UV_START");

	for (int i = 0; i < numModelsUV; i++)
	{
		modelNameFile >> tempString;
		cMesh* testMesh;
		testMesh = new cMesh();
		testMesh->name = tempString;

		if (testMesh->name == "SmoothSphere_Inverted_Normals_xyz_n.ply")
		{
			if (!LoadPlyFileIntoMeshWithNormals(tempString, *testMesh))
			{
				//std::cout << "Didn't load model" << std::endl;
				ssError << "Didn't load model >" << testMesh->name << "<" << std::endl;
				bAnyErrors = true;
			}

		}
		else
		{
			if (!LoadPlyFileIntoMeshWith_Normals_and_UV(tempString, *testMesh))
			{
				//std::cout << "Didn't load model" << std::endl;
				ssError << "Didn't load model >" << testMesh->name << "<" << std::endl;
				bAnyErrors = true;
			}
		}

		
		
		if (!pVAOManager->loadMeshIntoVAO(*testMesh, shaderID))
		{
			//std::cout << "Could not load mesh into VAO" << std::endl;
			ssError << "Could not load mesh >" << testMesh->name << "< into VAO" << std::endl;
			bAnyErrors = true;
		}

		tempString = "";
	}

	if (!bAnyErrors)
	{
		error = ssError.str();
	}

	return bAnyErrors;
}

bool loadTexturesFromFile(std::string& fileName) {
	std::ifstream modelAndSceneFile(fileName.c_str());
	int numTextures = 0;
	if (!modelAndSceneFile.is_open())
	{	// Didn't open file, so return
		return false;
	}

	ReadFileToToken(modelAndSceneFile, "NUM_TEXTURES");
	modelAndSceneFile >> numTextures;

	ReadFileToToken(modelAndSceneFile, "TEXTURE_NAMES");
	for (int i = 0; i < numTextures; i++)
	{
		std::string temp = "";
		modelAndSceneFile >> temp;
		//load the textures into the texture manager
		g_pTextureManager->Create2DTextureFromBMPFile(temp,true);
		temp = "";
	}
	return true;
}

bool mapTexturesToProperObjects() {

	//Big_Old_House.ply
	//birch_tree.ply
	//Exterior_lamp.ply
	//houseA.ply
	//mount.blend.ply
	//SmoothSphere_Inverted_Normals_xyz_n_uv.ply

	//mountain
	//pTempGO->textureNames.push_back(std::pair<std::string,float>("ground_grass.bmp",0.5f));
	//pTempGO->textureNames.push_back(std::pair<std::string, float>("terrain.bmp", 0.5f));;

	//lamp
	//pTempGO->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 0.5f));

	//birch
	//pTempGO->textureNames.push_back(std::pair<std::string, float>("leaves.bmp", 0.5f));

	//houseA
	//pTempGO->textureNames.push_back(std::pair<std::string, float>("houseA.bmp", 0.5f));

	//BigHouse
	//pTempGO->textureNames.push_back(std::pair<std::string, float>("Big_Old_House_C.bmp", 0.5f));

	//skybox
	//g_pSkyBoxObject->textureNames.push_back(std::pair<std::string,float>("TropicalSunnyDayBack2048.bmp", 1.0f));

	for (int i = 1; i < g_vecGameObjects.size(); i++)
	{
		if (g_vecGameObjects[i]->meshName == "mount.blend.ply")
		{
			g_vecGameObjects[i]->textureNames.push_back(std::pair<std::string, float>("ground_grass.bmp", 0.5f));
			g_vecGameObjects[i]->textureNames.push_back(std::pair<std::string, float>("terrain.bmp", 0.5f));
		}
		else if (g_vecGameObjects[i]->meshName == "Exterior_lamp.ply")
		{
			g_vecGameObjects[i]->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 1.0f));
		}
		else if (g_vecGameObjects[i]->meshName == "Ship_Pack_WIP_mod-gas-harvester_xyz_n_uv.ply")
		{
			g_vecGameObjects[i]->textureNames.push_back(std::pair<std::string, float>("rust.bmp", 1.0f));
		}
		else if (g_vecGameObjects[i]->meshName == "birch_tree.ply")
		{
			g_vecGameObjects[i]->textureNames.push_back(std::pair<std::string, float>("leaves.bmp", 0.40f));
			g_vecGameObjects[i]->textureNames.push_back(std::pair<std::string, float>("treeTrunk.bmp", 0.6f));
		}
		else if (g_vecGameObjects[i]->meshName == "houseA.ply")
		{
			g_vecGameObjects[i]->textureNames.push_back(std::pair<std::string, float>("houseA.bmp", 1.0f));
		}
		else if (g_vecGameObjects[i]->meshName == "Big_Old_House.ply")
		{
			g_vecGameObjects[i]->textureNames.push_back(std::pair<std::string, float>("Big_Old_House_C.bmp", 0.25f));
			g_vecGameObjects[i]->textureNames.push_back(std::pair<std::string, float>("Big_Old_House_S.bmp", 0.75f));

			//Big_Old_House_S.bmp
		}
		else if (g_vecGameObjects[i]->meshName == "SmoothSphere_Inverted_Normals_xyz_n.ply")
		{
			g_vecGameObjects[i]->textureNames.push_back(std::pair<std::string, float>("space", 1.0f));
			g_vecGameObjects[i]->bIsSkyBoxObject = true;
		}

	}

	return true;
}

bool LoadSceneFromFile(std::string& fileName) {
	//open the file
	std::ifstream modelAndSceneFile(fileName.c_str());
	int numModels = 0;
	int numModelsUV = 0;
	if (!modelAndSceneFile.is_open())
	{	// Didn't open file, so return
		return false;
	}
	ReadFileToToken(modelAndSceneFile, "CAMERA_POSITION");
	modelAndSceneFile >> g_cameraXYZ.x;
	modelAndSceneFile >> g_cameraXYZ.y;
	modelAndSceneFile >> g_cameraXYZ.z;


	//models with normal and uv
	ReadFileToToken(modelAndSceneFile, "MODELS_BEGIN");
	ReadFileToToken(modelAndSceneFile, "NUMBER_OF_MODELS_WITH_UV");
	modelAndSceneFile >> numModelsUV;
	ReadFileToToken(modelAndSceneFile, "MODELS_WITH_UV_FOR_DRAWING");
	cGameObject* pTempGO;
	for (int i = 0; i < numModelsUV; i++)
	{
		std::string tempString = "";
		pTempGO = new cGameObject();
		float tempFloat = 0.0f;
		modelAndSceneFile >> pTempGO->meshName;
		modelAndSceneFile >> pTempGO->position.x;
		modelAndSceneFile >> pTempGO->position.y;
		modelAndSceneFile >> pTempGO->position.z;
		modelAndSceneFile >> pTempGO->scale;
		modelAndSceneFile >> pTempGO->vel.x;
		modelAndSceneFile >> pTempGO->vel.y;
		modelAndSceneFile >> pTempGO->vel.z;
		modelAndSceneFile >> pTempGO->radius;
		modelAndSceneFile >> pTempGO->diffuseColour.x;
		modelAndSceneFile >> pTempGO->diffuseColour.y;
		modelAndSceneFile >> pTempGO->diffuseColour.z;
		modelAndSceneFile >> pTempGO->diffuseColour.a;
		modelAndSceneFile >> pTempGO->bIsWireFrame;
		modelAndSceneFile >> pTempGO->orientation.x;
		modelAndSceneFile >> pTempGO->orientation.y;
		modelAndSceneFile >> pTempGO->orientation.z;
		modelAndSceneFile >> tempFloat;
		pTempGO->orientation2.x = glm::radians(tempFloat);
		modelAndSceneFile >> tempFloat;
		pTempGO->orientation2.y = glm::radians(tempFloat);
		modelAndSceneFile >> tempFloat;
		pTempGO->orientation2.z = glm::radians(tempFloat);
		modelAndSceneFile >> pTempGO->bIsUpdatedInPhysics;
		modelAndSceneFile >> tempString;
		modelAndSceneFile >> pTempGO->bHasAABB;
		modelAndSceneFile >> pTempGO->hasTexture;

		g_vecGameObjects.push_back(pTempGO);

		if (tempString == "UNKNOWN")
		{
			pTempGO->typeOfObject = eTypeOfObject::UNKNOWN;
		}
		else if (tempString == "SPHERE")
		{
			pTempGO->typeOfObject = eTypeOfObject::SPHERE;
			//g_theBomb = pTempGO;
		}
		else
		{
			pTempGO->typeOfObject = eTypeOfObject::PLANE;
		}

	}


	////models with normals
	//ReadFileToToken(modelAndSceneFile, "NUMBER_OF_MODELS_TO_DRAW");
	//modelAndSceneFile >> numModels;

	//ReadFileToToken(modelAndSceneFile, "MODELS_FOR_DRAWING");
	//for (int i = 0; i < numModels; i++)
	//{
	//	std::string tempString = "";
	//	pTempGO = new cGameObject();
	//	modelAndSceneFile >> pTempGO->meshName;
	//	modelAndSceneFile >> pTempGO->position.x;
	//	modelAndSceneFile >> pTempGO->position.y;
	//	modelAndSceneFile >> pTempGO->position.z;
	//	modelAndSceneFile >> pTempGO->scale;
	//	modelAndSceneFile >> pTempGO->vel.x;
	//	modelAndSceneFile >> pTempGO->vel.y;
	//	modelAndSceneFile >> pTempGO->vel.z;
	//	modelAndSceneFile >> pTempGO->radius;
	//	modelAndSceneFile >> pTempGO->diffuseColour.x;
	//	modelAndSceneFile >> pTempGO->diffuseColour.y;
	//	modelAndSceneFile >> pTempGO->diffuseColour.z;
	//	modelAndSceneFile >> pTempGO->bIsWireFrame;
	//	modelAndSceneFile >> pTempGO->orientation.x;
	//	modelAndSceneFile >> pTempGO->orientation.y;
	//	modelAndSceneFile >> pTempGO->orientation.z;
	//	modelAndSceneFile >> pTempGO->orientation2.x;
	//	modelAndSceneFile >> pTempGO->orientation2.y;
	//	modelAndSceneFile >> pTempGO->orientation2.z;
	//	modelAndSceneFile >> pTempGO->bIsUpdatedInPhysics;
	//	modelAndSceneFile >> tempString;
	//	modelAndSceneFile >> pTempGO->bHasAABB;

	//	g_vecGameObjects.push_back(pTempGO);

	//	if (tempString == "UNKNOWN")
	//	{
	//		pTempGO->typeOfObject = eTypeOfObject::UNKNOWN;
	//	}
	//	else if (tempString == "SPHERE")
	//	{
	//		pTempGO->typeOfObject = eTypeOfObject::SPHERE;
	//		//g_theBomb = pTempGO;
	//	}
	//	else
	//	{
	//		pTempGO->typeOfObject = eTypeOfObject::PLANE;
	//	}

	//}

	//close the file stream
	modelAndSceneFile.close();
	return 0;
}
