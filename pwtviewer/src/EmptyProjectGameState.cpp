
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
  EmptyProjectGameState::EmptyProjectGameState( const Ogre::String &helpDescription,
                                                const std::string fin ) :
    TutorialGameState( helpDescription ), mWTNode(0), filepath(fin)
  {
  }
  //-----------------------------------------------------------------------------------
  void EmptyProjectGameState::createScene01(void)
  {
    mCameraController = new CameraController( mGraphicsSystem, false );

    Ogre::SceneManager *sceneManager = mGraphicsSystem->getSceneManager();

    DataAccessor* acc = openFileAccessor(filepath.c_str());
    PWT* pwt = pwt_extract(acc);
    pwt_print(pwt);
    PWT_Frame* rootframe = pwt->frames;

    Ogre::SceneNode *rootNode = sceneManager->getRootSceneNode( Ogre::SCENE_DYNAMIC );

    mWTNode = createStaticMesh(rootframe, rootNode);

    //setWireframe(true);

    Ogre::Light *light = sceneManager->createLight();
    Ogre::SceneNode *lightNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject( light );
    //light->setPowerScale( Ogre::Math::PI ); //Since we don't do HDR, counter the PBS' division by PI
    light->setType( Ogre::Light::LT_DIRECTIONAL );
    light->setDirection( Ogre::Vector3( -1, -1, -1 ).normalisedCopy() );

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

  Ogre::SceneNode* EmptyProjectGameState::createStaticMesh(
                                         PWT_Frame* modelFrame, Ogre::SceneNode *ogreNode)
  {
    Ogre::SceneNode *sceneNode = ogreNode->createChildSceneNode( Ogre::SCENE_DYNAMIC );

    if(modelFrame->has_visuals && modelFrame->visuals->vcount){
      PWT_Visuals *visuals = modelFrame->visuals;
      //float minx, miny, minz;
      float maxx, maxy, maxz;
      float maxradius;

      Ogre::VaoManager *vaoManager = mGraphicsSystem->getRoot()->getRenderSystem()->getVaoManager();

      //Create the mesh
      Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual("My StaticMesh",
                                   Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );

      //Create one submesh
      Ogre::SubMesh *subMesh = mesh->createSubMesh();

      //Vertex declaration
      Ogre::VertexElement2Vec vertexElements;
      vertexElements.push_back( Ogre::VertexElement2( Ogre::VET_FLOAT3, Ogre::VES_POSITION ) );
      vertexElements.push_back( Ogre::VertexElement2( Ogre::VET_FLOAT3, Ogre::VES_NORMAL ) );
      vertexElements.push_back( Ogre::VertexElement2( Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES ) );

      #define VENTRYSIZE 8

      //For immutable buffers, it is mandatory that cubeVertices is not a null pointer.
      //Vertex and Normal count should be the same. TODO: Check!
      float *vertices = reinterpret_cast<float*>( OGRE_MALLOC_SIMD(
                                                 sizeof(float) * VENTRYSIZE * visuals->vertex_count,
                                                 Ogre::MEMCATEGORY_GEOMETRY ) );

      //Fill the data.
      for(int vertexid = 0; vertexid < visuals->vertex_count; vertexid++){
        auto &vertex = visuals->vertices[vertexid];
        vertices[(vertexid*VENTRYSIZE) + 0] = vertex.X;
        vertices[(vertexid*VENTRYSIZE) + 1] = vertex.Y;
        vertices[(vertexid*VENTRYSIZE) + 2] = vertex.Z;
        vertices[(vertexid*VENTRYSIZE) + 3] = visuals->normals[vertexid].X;
        vertices[(vertexid*VENTRYSIZE) + 4] = visuals->normals[vertexid].Y;
        vertices[(vertexid*VENTRYSIZE) + 5] = visuals->normals[vertexid].Z;
        vertices[(vertexid*VENTRYSIZE) + 6] = visuals->texmapU[vertexid];
        vertices[(vertexid*VENTRYSIZE) + 7] = visuals->texmapV[vertexid];

        //if(vertexid == 0 || vertex.X < minx) minx = vertex.X;
        //if(vertexid == 0 || vertex.Y < miny) miny = vertex.Y;
        //if(vertexid == 0 || vertex.Z < minz) minz = vertex.Z;
        if(vertexid == 0 || vertex.X > maxx) maxx = vertex.X;
        if(vertexid == 0 || vertex.Y > maxy) maxy = vertex.Y;
        if(vertexid == 0 || vertex.Z > maxz) maxz = vertex.Z;
        float vectorlen = Ogre::Math::Sqrt((vertex.X*vertex.X) +
                                           (vertex.Y*vertex.Y) +
                                           (vertex.Z*vertex.Z));
        if(vertexid == 0 || maxradius < vectorlen) maxradius = vectorlen;

      }

      Ogre::VertexBufferPacked *vertexBuffer = 0;
      try
        {
          //Create the actual vertex buffer.
          vertexBuffer = vaoManager->createVertexBuffer( vertexElements, visuals->vertex_count,
                                                         Ogre::BT_IMMUTABLE, vertices, true );
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
                                                       Ogre::BT_IMMUTABLE, indices, true );
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
      //printf("MIN BOUNDS %f %f %f\n", minx, miny, minz);
      printf("MAX BOUNDS %f %f %f\n", maxx, maxy, maxz);
      printf("Radius %f\n", maxradius);
      mesh->_setBounds( Ogre::Aabb::newFromExtents(Ogre::Vector3(visuals->bboxmin.X,
                                                                 visuals->bboxmin.Y,
                                                                 visuals->bboxmin.Z),
                                                   //Ogre::Vector3( minx, miny, minz ),
                                                   Ogre::Vector3( maxx, maxy, maxz )), false );
      mesh->_setBoundingSphereRadius( maxradius );

      Ogre::Item *item = mGraphicsSystem->getSceneManager()->createItem( mesh, Ogre::SCENE_DYNAMIC );
      sceneNode->attachObject( item );
    }

    //TODO apply matrix transform
    Ogre::Matrix4 projMat();

    for(int subframeindex = 0; subframeindex < modelFrame->subframe_count; subframeindex++){
      EmptyProjectGameState::createStaticMesh(modelFrame->subframes[subframeindex], sceneNode);
    }

    return sceneNode;
  }

  void EmptyProjectGameState::setWireframe(bool wireframe) {
    Ogre::HlmsManager* hlmsmanager = mGraphicsSystem->getRoot()->getHlmsManager();
    Ogre::Hlms* hlms = hlmsmanager->getHlms(Ogre::HlmsTypes::HLMS_PBS);
    Ogre::Hlms::HlmsDatablockMap::const_iterator itor = hlms->getDatablockMap().begin();
    Ogre::Hlms::HlmsDatablockMap::const_iterator end  = hlms->getDatablockMap().end();
    while( itor != end )
    {
      Ogre::HlmsPbsDatablock *datablock = static_cast<Ogre::HlmsPbsDatablock*>(itor->second.datablock);
      Ogre::HlmsMacroblock macroblock = *datablock->getMacroblock();
      macroblock.mPolygonMode = wireframe ? Ogre::PM_WIREFRAME : Ogre::PM_SOLID;
      const Ogre::HlmsMacroblock* finalMacroblock = hlmsmanager->getMacroblock( macroblock );
      datablock->setMacroblock( finalMacroblock );

      ++itor;
    }
  }

}
