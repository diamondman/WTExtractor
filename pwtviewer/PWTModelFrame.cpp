#include "PWTModelFrame.h"
#include <QtWidgets/QApplication>
#include <QResizeEvent>
#include <OgreTextureManager.h>
#include <Compositor/OgreCompositorManager2.h>

#include <OgreMeshManager2.h>
#include <OgreMesh2.h>
#include <OgreSubMesh2.h>
#include <OgreItem.h>

#include <Hlms/Pbs/OgreHlmsPbsDatablock.h>
#include <Hlms/Pbs/OgreHlmsPbs.h>
#include <Hlms/Unlit/OgreHlmsUnlit.h>
#include <OgreHlmsSamplerblock.h>
#include <OgreHlms.h>
#include <OgreArchiveManager.h>
#include <OgreQuaternion.h>
#include <OgreMath.h>
#include <OgreVector3.h>

#include <iostream>
#include <stdio.h>

#include <OgreWindowEventUtilities.h>

PWTModelFrame::PWTModelFrame(QWidget* parent) :
  QWidget(parent), mRoot(0), mRenderWindow(0), mWTNode(0), pwt(0),
  mUpdatePending(false), mIsAnimating(true), leftMouseDragging(false) {

  setAttribute(Qt::WA_OpaquePaintEvent); //No partial redraw. No need for blanking widget.
  setAttribute(Qt::WA_PaintOnScreen); //No double buffering (handled by GL)
}

PWTModelFrame::~PWTModelFrame(){
  if(mRoot)
    delete mRoot;
}

void PWTModelFrame::resizeEvent(QResizeEvent *event) {
  QWidget::resizeEvent(event);
  if(event->isAccepted() && mRoot) {
    mRenderWindow->windowMovedOrResized();
    //#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
    mRenderWindow->resize(width(), height());
    this->update(); //Not sure if this does anything.
    renderNow();
  }
}

void PWTModelFrame::showEvent(QShowEvent *event) {
  QWidget::showEvent(event);
  if(isVisible())
    renderNow();
}

void PWTModelFrame::renderNow() {
  if(!isVisible())
    return;

  if(mRoot == NULL)
    initialize();

  if(pwt && !mWTNode)
    createScene();

  render();

  if (mIsAnimating)
    renderLater();
}

void PWTModelFrame::renderLater() {
  /*
    This function forces QWindow to keep rendering. Omitting this causes the renderNow() function to
    only get called when the window is resized, moved, etc. as opposed to all of the time; which is
    generally what we need.
  */
  if (!mUpdatePending) {
    mUpdatePending = true;
    QApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
  }
}

void PWTModelFrame::initialize() {
  mRoot = OGRE_NEW Ogre::Root( "", "" );

  //mRoot->loadPlugin("/usr/local/lib/OGRE/RenderSystem_GL3Plus");
  mRoot->loadPlugin((QCoreApplication::applicationDirPath() + "/RenderSystem_GL3Plus").toStdString());
  //mRoot->loadPlugin("./RenderSystem_GL3Plus_d");
  //mRoot->unloadPlugin("./RenderSystem_GL3Plus_d");

  const Ogre::RenderSystemList& rsList = mRoot->getAvailableRenderers();
  Ogre::RenderSystem* rs = rsList[0];

  QString dimensions = QString("%1 x %2").arg(this->width()).arg(this->height());
  rs->setConfigOption("Video Mode", dimensions.toStdString());
  rs->setConfigOption("Full Screen", "No");
  rs->setConfigOption("VSync", "No");
  mRoot->setRenderSystem(rs);
  mRoot->initialise(false);

  Ogre::NameValuePairList parameters;
  parameters["currentGLContext"] = Ogre::String("false");
  parameters["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned long)(this->winId()));
  parameters["parentWindowHandle"] = Ogre::StringConverter::toString((unsigned long)(this->winId()));

  mRenderWindow = mRoot->createRenderWindow("QT Window", this->width(), this->height(),
                                            false, &parameters);
  mRenderWindow->setVisible(true);

  const size_t numThreads = std::max<int>(1, Ogre::PlatformInformation::getNumLogicalCores());
  Ogre::InstancingThreadedCullingMethod threadedCullingMethod = Ogre::INSTANCING_CULLING_SINGLETHREAD;
  if (numThreads > 1)threadedCullingMethod = Ogre::INSTANCING_CULLING_THREADED;
  mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, numThreads, threadedCullingMethod);

  mCamera = mSceneManager->createCamera("MainCamera");
  // Position it at 500 in Z direction
  mCamera->setPosition( Ogre::Vector3( 0, 5, 15 ) );
  // Look back along -Z
  mCamera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
  mCamera->setNearClipDistance( 0.2f );
  mCamera->setFarClipDistance( 1000.0f );

  //COMPOSITOR
  Ogre::CompositorManager2* compMan = mRoot->getCompositorManager2();
  const Ogre::String workspaceName = "default scene workspace";
  const Ogre::IdString workspaceNameHash = workspaceName;
  compMan->createBasicWorkspaceDef(workspaceName, Ogre::ColourValue( 0.2f, 0.4f, 0.6f ));
  compMan->addWorkspace(mSceneManager, mRenderWindow, mCamera, workspaceNameHash, true);

  //mCamera->setAspectRatio(Ogre::Real(mRenderWindow->getWidth())/
  //                        Ogre::Real(mRenderWindow->getHeight()));
  mCamera->setAutoAspectRatio(true);

  mCamera->detachFromParent();
  mCameraNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
  mCameraNode->attachObject(mCamera);

  //HLMS
  Ogre::String hlmsFolder = QCoreApplication::applicationDirPath().toStdString();

  auto hlmsManager = mRoot->getHlmsManager();

  //Define the shader library to use for HLMS
  auto library = Ogre::ArchiveVec();

  library.push_back(Ogre::ArchiveManager::getSingleton().load
                    (hlmsFolder + "/Hlms/Common/GLSL", "FileSystem", true));
  library.push_back(Ogre::ArchiveManager::getSingleton().load
                    (hlmsFolder + "/Hlms/Common/Any", "FileSystem", true));

  auto archiveUnlitAny = Ogre::ArchiveManager::getSingleton().load
    (hlmsFolder + "/Hlms/Unlit/Any", "FileSystem", true);
  library.push_back(archiveUnlitAny);
  auto archiveUnlit = Ogre::ArchiveManager::getSingleton().load
    (hlmsFolder + "/Hlms/Unlit/GLSL", "FileSystem", true);
  auto hlmsUnlit = OGRE_NEW Ogre::HlmsUnlit(archiveUnlit, &library);
  hlmsManager->registerHlms(hlmsUnlit);

  library.pop_back();
  auto archivePbsAny = Ogre::ArchiveManager::getSingleton().load
    (hlmsFolder + "/Hlms/Pbs/Any", "FileSystem", true);
  library.push_back(archivePbsAny);
  auto archivePbs = Ogre::ArchiveManager::getSingleton().load
    (hlmsFolder + "/Hlms/Pbs/GLSL", "FileSystem", true);
  auto hlmsPbs = OGRE_NEW Ogre::HlmsPbs(archivePbs, &library);
  hlmsManager->registerHlms(hlmsPbs);

  //Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups(true);
};

void PWTModelFrame::createScene() {
  Ogre::SceneNode *rootNode = mSceneManager->getRootSceneNode( Ogre::SCENE_DYNAMIC );

  printf("About to create with pwt %p\n", pwt);

  mWTNode = createPWTMesh(pwt->frames, rootNode);

  //setWireframe(true);

  Ogre::Light *light = mSceneManager->createLight();
  Ogre::SceneNode *lightNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
  lightNode->attachObject( light );
  //light->setPowerScale( Ogre::Math::PI ); //Since we don't do HDR, counter the PBS' division by PI
  light->setType( Ogre::Light::LT_DIRECTIONAL );
  light->setDirection( Ogre::Vector3( -1, -1, -1 ).normalisedCopy() );
}

void PWTModelFrame::setModel(PWT* pwt) {
  this->pwt = pwt;
}

void PWTModelFrame::render() {
  /*
    How we tied in the render function for OGre3D with QWindow's render function. This is what gets call
    repeatedly. Note that we don't call this function directly; rather we use the renderNow() function
    to call this method as we don't want to render the Ogre3D scene unless everything is set up first.
    That is what renderNow() does.

    Theoretically you can have one function that does this check but from my experience it seems better
    to keep things separate and keep the render function as simple as possible.
  */
  Ogre::WindowEventUtilities::messagePump();
  mRoot->renderOneFrame();
  //std::cout << "RENDERING" << std::endl << std::endl;
}

bool PWTModelFrame::event(QEvent *event) {
  /*
    QWindow's "message pump". The base method that handles all QWindow events. As you will see there
    are other methods that actually process the keyboard/other events of Qt and the underlying OS.

    Note that we call the renderNow() function which checks to see if everything is initialized, etc.
    before calling the render() function.
  */

  switch (event->type())
    {
    case QEvent::UpdateRequest:
      mUpdatePending = false;
      renderNow();
      return true;

    default:
      return QWidget::event(event);
    }
}

void PWTModelFrame::mousePressEvent(QMouseEvent *event){
  if(event->button() == Qt::LeftButton){
    leftMouseDragging = true;
    lastMouseX = event->x();
    lastMouseY = event->y();
  }
}


void PWTModelFrame::mouseMoveEvent(QMouseEvent *event){
  if((event->buttons() & Qt::LeftButton) && leftMouseDragging){
    int deltaX = event->x() - lastMouseX;
    int deltaY = event->y() - lastMouseY;

    //Rotate the mouse movement vector 90 degrees ccw. deltaY inverted because of Qt's coordinate space.
    Ogre::Vector3 axis = Ogre::Vector3(deltaY, deltaX, 0);
    axis.normalise();

    Ogre::Real distance = Ogre::Math::Sqrt((deltaX * deltaX) + (deltaY * deltaY));

    mWTNode->rotate(Ogre::Quaternion(Ogre::Degree(distance), axis),
                    Ogre::Node::TransformSpace::TS_WORLD);

    lastMouseX = event->x();
    lastMouseY = event->y();
  }
}

void PWTModelFrame::mouseReleaseEvent(QMouseEvent *event){
  if(event->button() == Qt::LeftButton){
    leftMouseDragging = false;
  }
}

Ogre::SceneNode* PWTModelFrame::createPWTMesh(PWT_Frame* modelFrame, Ogre::SceneNode *ogreNode)
{
  Ogre::SceneNode *sceneNode = ogreNode->createChildSceneNode( Ogre::SCENE_DYNAMIC );

  if(modelFrame->has_visuals && modelFrame->visuals->vcount){
    PWT_Visuals *visuals = modelFrame->visuals;
    //float minx, miny, minz;
    float maxx, maxy, maxz;
    float maxradius;

    Ogre::VaoManager *vaoManager = mRoot->getRenderSystem()->getVaoManager();

    //Create the mesh
    Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton()\
      .createManual("My StaticMesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );

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
    float *vertices = reinterpret_cast<float*>( OGRE_MALLOC_SIMD
                                                (sizeof(float) * VENTRYSIZE * visuals->vertex_count,
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

    Ogre::uint16 *indices = reinterpret_cast<Ogre::uint16*>
      ( OGRE_MALLOC_SIMD(
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
    Ogre::VertexArrayObject *vao = vaoManager->createVertexArrayObject
      (vertexBuffers, indexBuffer, Ogre::OT_TRIANGLE_LIST );

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
    printf("Boundaries set\n");

    printf("scenemanager %p\n", mSceneManager);

    Ogre::Item *item = mSceneManager->createItem( mesh, Ogre::SCENE_DYNAMIC );
    printf("Item created\n");
    sceneNode->attachObject( item );
  }

  //TODO apply matrix transform
  Ogre::Matrix4 projMat();

  for(int subframeindex = 0; subframeindex < modelFrame->subframe_count; subframeindex++){
    createPWTMesh(modelFrame->subframes[subframeindex], sceneNode);
  }

  return sceneNode;
}

void PWTModelFrame::setWireframe(bool wireframe) {
  Ogre::HlmsManager* hlmsmanager = mRoot->getHlmsManager();
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
