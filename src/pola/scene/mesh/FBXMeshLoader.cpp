/*
 * FBXMeshLoader.cpp
 *
 *  Created on: 2016年8月17日
 *      Author: lijing
 */

#include "pola/scene/mesh/FBXMeshLoader.h"
#include "pola/scene/mesh/Mesh.h"
#include "pola/log/Log.h"

#include <fbxsdk.h>

namespace pola {
namespace scene {

#ifdef IOS_REF
	#undef  IOS_REF
	#define IOS_REF (*(pManager->GetIOSettings()))
#endif

bool InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene)
{
    //The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
    pManager = FbxManager::Create();
    if( !pManager )
    {
        LOGE("Error: Unable to create FBX Manager!");
        return false;
    }
	else LOGD("Autodesk FBX SDK version %s", pManager->GetVersion());

	//Create an IOSettings object. This object holds all import/export settings.
	FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(ios);

	//Load plugins from the executable directory (optional)
	FbxString lPath = FbxGetApplicationDirectory();
	pManager->LoadPluginsDirectory(lPath.Buffer());

    //Create an FBX scene. This object holds most objects imported/exported from/to files.
    pScene = FbxScene::Create(pManager, "My Scene");
	if( !pScene )
    {
		LOGE("Error: Unable to create FBX scene!");
        return false;
    }
	return true;
}

void DestroySdkObjects(FbxManager* pManager, bool pExitStatus)
{
    //Delete the FBX Manager. All the objects that have been allocated using the FBX Manager and that haven't been explicitly destroyed are also automatically destroyed.
    if( pManager ) pManager->Destroy();
	if( pExitStatus ) LOGD("Program Success!");
}

bool LoadScene(FbxManager* pManager, FbxDocument* pScene, FbxStream* stream)
{
    int lFileMajor, lFileMinor, lFileRevision;
    int lSDKMajor,  lSDKMinor,  lSDKRevision;
    //int lFileFormat = -1;
    int i, lAnimStackCount;
    bool lStatus;
    char lPassword[1024];

    // Get the file version number generate by the FBX SDK.
    FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

    // Create an importer.
    FbxImporter* lImporter = FbxImporter::Create(pManager,"");

    // Initialize the importer by providing a filename.
    const bool lImportStatus = lImporter->Initialize(stream, nullptr,-1, pManager->GetIOSettings());
    lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

    if( !lImportStatus )
    {
        FbxString error = lImporter->GetStatus().GetErrorString();
        LOGW("Call to FbxImporter::Initialize() failed.");
        LOGW("Error returned: %s\n", error.Buffer());

        if (lImporter->GetStatus().GetCode() == FbxStatus::eInvalidFileVersion)
        {
        	LOGW("FBX file format version for this FBX SDK is %d.%d.%d", lSDKMajor, lSDKMinor, lSDKRevision);
        	LOGW("FBX file format version is %d.%d.%d\n", lFileMajor, lFileMinor, lFileRevision);
        }

        return false;
    }

    LOGD("FBX file format version for this FBX SDK is %d.%d.%d", lSDKMajor, lSDKMinor, lSDKRevision);

    if (lImporter->IsFBX())
    {
    	LOGD("FBX file format version is %d.%d.%d\n", lFileMajor, lFileMinor, lFileRevision);

        // From this point, it is possible to access animation stack information without
        // the expense of loading the entire file.

    	LOGD("Animation Stack Information");

        lAnimStackCount = lImporter->GetAnimStackCount();

        LOGD("    Number of Animation Stacks: %d", lAnimStackCount);
        LOGD("    Current Animation Stack: \"%s\"", lImporter->GetActiveAnimStackName().Buffer());
        LOGD("\n");

        for(i = 0; i < lAnimStackCount; i++)
        {
            FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

            FBXSDK_printf("    Animation Stack %d\n", i);
            FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
            FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

            // Change the value of the import name if the animation stack should be imported
            // under a different name.
            FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

            // Set the value of the import state to false if the animation stack should be not
            // be imported.
            FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
            FBXSDK_printf("\n");
        }

        // Set the import states. By default, the import states are always set to
        // true. The code below shows how to change these states.
        IOS_REF.SetBoolProp(IMP_FBX_MATERIAL,        true);
        IOS_REF.SetBoolProp(IMP_FBX_TEXTURE,         true);
        IOS_REF.SetBoolProp(IMP_FBX_LINK,            true);
        IOS_REF.SetBoolProp(IMP_FBX_SHAPE,           true);
        IOS_REF.SetBoolProp(IMP_FBX_GOBO,            true);
        IOS_REF.SetBoolProp(IMP_FBX_ANIMATION,       true);
        IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
    }

    // Import the scene.
    lStatus = lImporter->Import(pScene);

    if(lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
    {
        /*FBXSDK_printf("Please enter password: ");

        lPassword[0] = '\0';

        FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
        scanf("%s", lPassword);
        FBXSDK_CRT_SECURE_NO_WARNING_END

        FbxString lString(lPassword);

        IOS_REF.SetStringProp(IMP_FBX_PASSWORD,      lString);
        IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

        lStatus = lImporter->Import(pScene);

        if(lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
        {
            FBXSDK_printf("\nPassword is wrong, import aborted.\n");
        }*/
    }

    // Destroy the importer.
    lImporter->Destroy();

    return lStatus;
}

class MyFbxReader : public FbxStream {
public:
	MyFbxReader(FbxManager* pSdkManager, io::InputStream* is) : mInputStream(is) {
		const char* format = "FBX (*.fbx)";
		mReaderID = pSdkManager->GetIOPluginRegistry()->FindReaderIDByDescription(format);
	}
	virtual EState GetState() {
		return mInputStream->isClosed() ? EState::eClosed : EState::eOpen;
	}
	virtual bool Open(void* pStreamData) {
		mInputStream->seek(0);
		return !mInputStream->isClosed();
	}
	virtual bool Close() {
		return true;
	}
	virtual bool Flush() {
		return true;
	}
	virtual int Write(const void* /*pData*/, int /*pSize*/) {
		return 0;
	}
	virtual int Read(void* pData, int pSize) const {
		if (pSize < 0) return EOF;

		return mInputStream->read(pData, size_t(pSize));
	}
	virtual int GetReaderID() const {
		return mReaderID;
	}
	virtual int GetWriterID() const {
		return -1;
	}
	virtual void Seek(const FbxInt64& pOffset, const FbxFile::ESeekPos& pSeekPos) {
		if (pSeekPos == FbxFile::ESeekPos::eBegin) {
			mInputStream->seek(pOffset);
		} else if (pSeekPos == FbxFile::ESeekPos::eCurrent) {
			mInputStream->skip(pOffset);
		} else if (pSeekPos == FbxFile::ESeekPos::eEnd) {
			ssize_t t = mInputStream->getLength() - pOffset;
			if (t >= 0) {
				mInputStream->seek(t);
			}
		}
	}
	virtual long GetPosition() const {
		return mInputStream->getPosition();
	}
	virtual void SetPosition(long pPosition) {
		mInputStream->seek(pPosition);
	}
	virtual int GetError() const {
		return 0;
	}
	virtual void ClearError() {
	}
private:
	io::InputStream* mInputStream;
	int mReaderID;
};


class NullMesh : public IMesh {
public:
	NullMesh() {
	}
	virtual ~NullMesh() {
	}
	virtual graphic::Geometry* geometry() {
		return nullptr;
	}
};

class FBXProcessor {
public:
	FBXProcessor(FbxManager* fbxManager, MeshLoader::Result* result);

	void process(FbxNode* lNode);
	void process(FbxNode* lNode, MeshLoader::Result* result, int depth);

	MeshLoader::Result* processMesh(FbxNode* node);

	FbxManager* mFbxManager;
	MeshLoader::Result* mResult;

};

FBXProcessor::FBXProcessor(FbxManager* fbxManager, MeshLoader::Result* result) :
		mFbxManager(fbxManager), mResult(result) {
}

void FBXProcessor::process(FbxNode* node) {
	process(node, mResult, 0);
}

void FBXProcessor::process(FbxNode* node, MeshLoader::Result* parent, int depth) {
	FbxNodeAttribute::EType lAttributeType;
	if (node->GetNodeAttribute() == NULL) {
		LOGW("NULL Node Attribute");
	} else {
		lAttributeType = (node->GetNodeAttribute()->GetAttributeType());
		switch (lAttributeType) {
		default:
			break;
		case FbxNodeAttribute::eMesh:
			MeshLoader::Result* result = processMesh(node);
			if (result != nullptr) {
				parent->children.push_back(result);
				parent = result;
			}
			break;
		}
	}
	for (int i = 0; i < node->GetChildCount(); i++) {
		FbxNode* child = node->GetChild(i);
		process(child, parent, depth + 1);
	}
}

MeshLoader::Result* FBXProcessor::processMesh(FbxNode* node) {
	FbxMesh* fbxMesh = node->GetMesh();
	if (fbxMesh == nullptr) return nullptr;
	if (!fbxMesh->IsTriangleMesh()) {
		FbxGeometryConverter converter(mFbxManager);
		fbxMesh = (FbxMesh*) converter.Triangulate(fbxMesh, true);
	}

	MeshLoader::Result* result = new MeshLoader::Result;

	graphic::mat4 m;
	m.compose(graphic::vec3(node->LclTranslation.Get()[0], node->LclTranslation.Get()[2], node->LclTranslation.Get()[1]),
			graphic::vec3(node->LclRotation.Get()[0], node->LclRotation.Get()[2], node->LclRotation.Get()[1]),
			graphic::vec3(node->LclScaling.Get()[0], node->LclScaling.Get()[2], node->LclScaling.Get()[1]));

	IMesh* mesh = new Mesh;
	graphic::Geometry3D* geometry = (graphic::Geometry3D*) mesh->geometry();

	int triangleCount = fbxMesh->GetPolygonCount();
	LOGD("processMesh triangleCount=%d", triangleCount);
	geometry->alloc(triangleCount * 3);
	graphic::vec3* positions = geometry->positions();

	FbxVector4* pCtrlPoint = fbxMesh->GetControlPoints();
	for (int i = 0; i < triangleCount; ++i) {
		int ctrlPointIndex = fbxMesh->GetPolygonVertex(i , 0);
		positions[i * 3] = {pCtrlPoint[ctrlPointIndex][0], pCtrlPoint[ctrlPointIndex][2], pCtrlPoint[ctrlPointIndex][1]};
		m.transformVector(positions[i * 3]);
		ctrlPointIndex = fbxMesh->GetPolygonVertex(i , 2);
		positions[i * 3 + 1] = {pCtrlPoint[ctrlPointIndex][0], pCtrlPoint[ctrlPointIndex][2], pCtrlPoint[ctrlPointIndex][1]};
		m.transformVector(positions[i * 3 + 1]);
		ctrlPointIndex = fbxMesh->GetPolygonVertex(i , 1);
		positions[i * 3 + 2] = {pCtrlPoint[ctrlPointIndex][0], pCtrlPoint[ctrlPointIndex][2], pCtrlPoint[ctrlPointIndex][1]};
		m.transformVector(positions[i * 3 + 2]);
	}
	geometry->computeBoundingBox();

	FbxLayerElementArrayTemplate<int>* pMaterialIndices;
	FbxGeometryElement::EMappingMode   materialMappingMode = FbxGeometryElement::eNone;
	if(fbxMesh->GetElementMaterial()) {
		pMaterialIndices    = &fbxMesh->GetElementMaterial()->GetIndexArray();
		materialMappingMode = fbxMesh->GetElementMaterial()->GetMappingMode();
		if (pMaterialIndices) {
			switch(materialMappingMode) {
			case FbxGeometryElement::eByPolygon: {
				if (pMaterialIndices->GetCount() == triangleCount) {
					for (int triangleIndex = 0; triangleIndex < triangleCount;
							++triangleIndex) {
						int materialIndex = pMaterialIndices->GetAt(
								triangleIndex);
					}
				}
				LOGD("eByPolygon");
				break;
			}
			case FbxGeometryElement::eAllSame: {
				int lMaterialIndex = pMaterialIndices->GetAt(0);
				LOGD("eAllSame");
				break;
			}
			default:
				break;
			}
		}
	}

	int materialCount;
	materialCount = node->GetMaterialCount();
	for(int materialIndex = 0 ; materialIndex < materialCount ; materialIndex++) {
		FbxSurfaceMaterial* pSurfaceMaterial = node->GetMaterial(materialIndex);
		int textureLayerIndex;
		for(textureLayerIndex = 0 ; textureLayerIndex < FbxLayerElement::sTypeTextureCount ; ++textureLayerIndex) {
			FbxProperty pProperty = pSurfaceMaterial->FindProperty(FbxLayerElement::sTextureChannelNames[textureLayerIndex]);
			if (pProperty.IsValid()) {
				int textureCount = pProperty.GetSrcObjectCount(FbxCriteria::ObjectType(FbxFileTexture::ClassId));
				for(int j = 0 ; j < textureCount ; ++j) {
					FbxFileTexture* pTexture = FbxCast<FbxFileTexture>(pProperty.GetSrcObject(FbxCriteria::ObjectType(FbxFileTexture::ClassId), j));
					if (pTexture) {
						LOGD("texture=%s    %s", pTexture->GetFileName(), FbxLayerElement::sTextureChannelNames[textureLayerIndex]);
					}
				}
			}
		}
	}

	result->mesh = mesh;
	return result;
}

FBXMeshLoader::FBXMeshLoader() {
}

FBXMeshLoader::~FBXMeshLoader() {
}

bool FBXMeshLoader::available(io::InputStream* is) {
	return false;
}

pola::utils::sp<MeshLoader::Result> FBXMeshLoader::doLoadMesh(io::InputStream* is) {

	FbxManager* lSdkManager = NULL;
	FbxScene* lScene = NULL;
	bool lResult;

	// Prepare the FBX SDK.
	InitializeSdkObjects(lSdkManager, lScene);
	// Load the scene.

	MyFbxReader fbxReader(lSdkManager, is);
	lResult = LoadScene(lSdkManager, lScene, &fbxReader);
	if (!lResult) {
		DestroySdkObjects(lSdkManager, false);
		return nullptr;
	}

	FbxNode* lNode = lScene->GetRootNode();

	int numStacks = lScene->GetSrcObjectCount(FbxCriteria::ObjectType(FbxAnimStack::ClassId));
	LOGD("numStacks=%d", numStacks);

	// TODO
	IMesh* mesh = new NullMesh;
	pola::utils::sp<MeshLoader::Result> result = new Result;
	result->mesh = mesh;
	FBXProcessor processor(lSdkManager, result.get());
	if (lNode != nullptr) {
		processor.process(lNode);
	}
	DestroySdkObjects(lSdkManager, true);
	if (result->children.empty()) {
		delete mesh;
		return nullptr;
	}
	return result;
}

} /* namespace scene */
} /* namespace pola */
