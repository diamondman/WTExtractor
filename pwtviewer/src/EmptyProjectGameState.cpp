
#include "EmptyProjectGameState.h"
#include "CameraController.h"
#include "GraphicsSystem.h"

#include "OgreMeshManager.h"
#include "OgreMeshManager2.h"
#include "OgreMesh2.h"

#include "OgreCamera.h"
#include "OgreRenderWindow.h"

#include "OgreHlmsPbsDatablock.h"
#include "OgreHlmsSamplerblock.h"

#include "OgreRoot.h"
#include "OgreHlmsManager.h"
#include "OgreHlmsTextureManager.h"
#include "OgreHlmsPbs.h"

#include "dataaccessors.h"

using namespace Demo;

namespace Demo
{
  EmptyProjectGameState::EmptyProjectGameState( const Ogre::String &helpDescription ) :
    TutorialGameState( helpDescription ), mWTNode(0)
  {
  }
  //-----------------------------------------------------------------------------------
  void EmptyProjectGameState::createScene01(void)
  {
    mCameraController = new CameraController( mGraphicsSystem, false );

    Ogre::SceneManager *sceneManager = mGraphicsSystem->getSceneManager();

    DataAccessor* acc = openFileAccessor("/home/diamondman/src/WTExtractor/sample_files/sample.pwt");
    PWT* pwt = pwt_extract(acc);
    mWTNode = createStaticMesh(pwt);
    /*Ogre::Item *item = sceneManager->createItem( mModel, Ogre::SCENE_DYNAMIC );
    Ogre::SceneNode *sceneNode = sceneManager->getRootSceneNode( Ogre::SCENE_DYNAMIC )->
      createChildSceneNode( Ogre::SCENE_DYNAMIC );
    sceneNode->attachObject( item );*/

    Ogre::Item *item2 = sceneManager->createItem("Cube_d.mesh");
    Ogre::SceneNode* mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    mSceneNode->attachObject(item2);
    mSceneNode->setPosition( -6, 0, 0 );
    mSceneNode->

    TutorialGameState::createScene01();
  }
  //-----------------------------------------------------------------------------------
  void EmptyProjectGameState::destroyScene(void){
    //mModel.setNull();
  }
  //-----------------------------------------------------------------------------------
  void EmptyProjectGameState::update( float timeSinceLast )
  {
    TutorialGameState::update( timeSinceLast );
  }
  //-----------------------------------------------------------------------------------
  void EmptyProjectGameState::generateDebugText( float timeSinceLast, Ogre::String &outText )
  {
    TutorialGameState::generateDebugText( timeSinceLast, outText );
  }
  //-----------------------------------------------------------------------------------
  void EmptyProjectGameState::keyReleased( const SDL_KeyboardEvent &arg )
  {
    if( (arg.keysym.mod & ~(KMOD_NUM|KMOD_CAPS)) != 0 )
      {
        TutorialGameState::keyReleased( arg );
        return;
      }

    TutorialGameState::keyReleased( arg );
  }

  Ogre::SceneNode* EmptyProjectGameState::createStaticMesh(PWT* pwt)
  {
    PWT_Frame* frames = pwt->frames;
    //PWT_Fra **subframes = frames->subframes;
    PWT_Visuals *visuals = frames->visuals;
    pwt_print(pwt);

    Ogre::Root *root = mGraphicsSystem->getRoot();
    Ogre::RenderSystem *renderSystem = root->getRenderSystem();
    Ogre::VaoManager *vaoManager = renderSystem->getVaoManager();

    //Create the mesh
    Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual("My StaticMesh",
                               Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );

    //Create one submesh
    Ogre::SubMesh *subMesh = mesh->createSubMesh();

    //Vertex declaration
    Ogre::VertexElement2Vec vertexElements;
    vertexElements.push_back( Ogre::VertexElement2( Ogre::VET_FLOAT3, Ogre::VES_POSITION ) );
    vertexElements.push_back( Ogre::VertexElement2( Ogre::VET_FLOAT3, Ogre::VES_NORMAL ) );

    //For immutable buffers, it is mandatory that cubeVertices is not a null pointer.
    /*CubeVertices *cubeVertices = reinterpret_cast<CubeVertices*>( OGRE_MALLOC_SIMD(
                                                  sizeof(CubeVertices) * 8,
                                                  Ogre::MEMCATEGORY_GEOMETRY ) );*/
    //Vertex and Normal count should be the same. TODO: Check!
    float *vertices = reinterpret_cast<float*>( OGRE_MALLOC_SIMD(
                                            sizeof(float) * 6 * visuals->vertex_count,
                                            Ogre::MEMCATEGORY_GEOMETRY ) );

    //Fill the data.
    for(int vertexid = 0; vertexid < visuals->vertex_count; vertexid++){
      vertices[(vertexid*6) + 0] = visuals->vertices[vertexid].X;
      vertices[(vertexid*6) + 1] = visuals->vertices[vertexid].Y;
      vertices[(vertexid*6) + 2] = visuals->vertices[vertexid].Z;
      vertices[(vertexid*6) + 3] = visuals->normals[vertexid].X;
      vertices[(vertexid*6) + 4] = visuals->normals[vertexid].Y;
      vertices[(vertexid*6) + 5] = visuals->normals[vertexid].Z;
    }
    /*memcpy( cubeVertices, c_originalVertices, sizeof(CubeVertices) * 8 );*/

    Ogre::VertexBufferPacked *vertexBuffer = 0;
    try
      {
        //Create the actual vertex buffer.
        vertexBuffer = vaoManager->createVertexBuffer( vertexElements, visuals->vertex_count,
                                                       Ogre::BT_IMMUTABLE,
                                                       vertices, true );
      }
    catch( Ogre::Exception &e )
      {
        OGRE_FREE_SIMD( vertexBuffer, Ogre::MEMCATEGORY_GEOMETRY );
        vertexBuffer = 0;
        throw e;
      }

    //Now the Vao. We'll just use one vertex buffer source (multi-source not working yet)
    Ogre::VertexBufferPackedVec vertexBuffers;
    vertexBuffers.push_back( vertexBuffer );
    /////////////////////////////
    //Ogre::IndexBufferPacked *indexBuffer = createIndexBuffer(); //Create the actual index buffer

    Ogre::IndexBufferPacked *indexBuffer = 0;

    Ogre::uint16 *indices = reinterpret_cast<Ogre::uint16*>( OGRE_MALLOC_SIMD(
                                                     sizeof(Ogre::uint16) * 3 * visuals->fcount,
                                                     Ogre::MEMCATEGORY_GEOMETRY ) );

    for(int faceindex = 0; faceindex < visuals->fcount; faceindex++) {
      //memcpy( indices, c_indexData, sizeof( c_indexData ) );
      indices[(faceindex * 3) + 0] = visuals->faces[faceindex][0];
      indices[(faceindex * 3) + 1] = visuals->faces[faceindex][1];
      indices[(faceindex * 3) + 2] = visuals->faces[faceindex][2];
    }

    try
      {
        indexBuffer = vaoManager->createIndexBuffer( Ogre::IndexBufferPacked::IT_16BIT,
                                                     3 * visuals->fcount,
                                                     Ogre::BT_IMMUTABLE,
                                                     indices, true );
      }
    catch( Ogre::Exception &e )
      {
        // When keepAsShadow = true, the memory will be freed when the index buffer is destroyed.
        // However if for some weird reason there is an exception raised, the memory will
        // not be freed, so it is up to us to do so.
        // The reasons for exceptions are very rare. But we're doing this for correctness.
        OGRE_FREE_SIMD( indexBuffer, Ogre::MEMCATEGORY_GEOMETRY );
        indexBuffer = 0;
        throw e;
      }

    /////////////////////////////
    Ogre::VertexArrayObject *vao = vaoManager->createVertexArrayObject(
                                               vertexBuffers, indexBuffer, Ogre::OT_TRIANGLE_LIST );

    //Each Vao pushed to the vector refers to an LOD level.
    //Must be in sync with mesh->mLodValues & mesh->mNumLods if you use more than one level
    subMesh->mVao[Ogre::VpNormal].push_back( vao );
    //Use the same geometry for shadow casting.
    subMesh->mVao[Ogre::VpShadow].push_back( vao );

    //Set the bounds to get frustum culling and LOD to work correctly.
    mesh->_setBounds( Ogre::Aabb( Ogre::Vector3::ZERO, Ogre::Vector3::UNIT_SCALE ), false );
    mesh->_setBoundingSphereRadius( 1.732f );

    Ogre::SceneManager *sceneManager = mGraphicsSystem->getSceneManager();
    Ogre::Item *item = sceneManager->createItem( mesh, Ogre::SCENE_DYNAMIC );
    Ogre::SceneNode *sceneNode = sceneManager->getRootSceneNode( Ogre::SCENE_DYNAMIC )->
      createChildSceneNode( Ogre::SCENE_DYNAMIC );
    sceneNode->attachObject( item );




    return sceneNode;
  }

}
