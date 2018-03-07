#ifndef _ModelUtilities_HG_
#define _ModelUtilities_HG_

#include <fstream>
#include <string>
#include <vector>
#include "cMesh.h"

class cVAOMeshManager;
class cLight;

// Only "function signature"
void ReadFileToToken( std::ifstream &file, std::string token );

// Note the & symbol which is "by reference" which means
//	it's NOT a copy, but referring to the original object.
// ALSO note that this is a C++ thing (& isn't a thing in C)
bool LoadPlyFileIntoMesh( std::string filename, cMesh &theMesh );
bool LoadPlyFileIntoMeshWithNormals( std::string filename, cMesh &theMesh );

bool LoadLightsAttributesFromFile(std::string& fileName, std::vector<cLight>& theLights);
bool Load3DModelsFromModelFile(int shaderID, cVAOMeshManager* pVAOManager, std::string &error);
bool LoadSceneFromFile(std::string& fileName);
bool mapTexturesToProperObjects();
bool loadTexturesFromFile(std::string& fileName);
#endif
