#include "PWTModelFrame.h"
#include <QtWidgets/QApplication>
#include <QResizeEvent>
#include <OgreTextureManager.h>
#include <Compositor/OgreCompositorManager2.h>
#include <iostream>

#include <OgreWindowEventUtilities.h>

PWTModelFrame::PWTModelFrame(QWidget* parent) :
  QWidget(parent), mRoot(0), mRenderWindow(0), mUpdatePending(false), mIsAnimating(true) {

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

  //Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  //mRoot.initialiseAllResourceGroups();

};

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
