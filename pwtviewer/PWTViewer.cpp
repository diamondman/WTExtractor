#include "PWTViewer.hpp"

PWTViewer::PWTViewer(char* thing)
{
  std::cout << thing << std::endl;
	m_pOgreHeadNode		= 0;
	m_pOgreHeadEntity		= 0;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

PWTViewer::~PWTViewer()
{
       delete OgreFramework::getSingletonPtr();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PWTViewer::startDemo()
{
	new OgreFramework();
	if(!OgreFramework::getSingletonPtr()->initOgre
	   ("PWTViewer v1.0", this, 0))
	  return;

	m_bShutdown = false;

	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Demo initialized!");

	setupDemoScene();
	runDemo();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PWTViewer::setupDemoScene()
{
  //OgreFramework::getSingletonPtr()->m_pSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

  OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("Light")->setPosition(75, 75, 75);

  m_pOgreHeadEntity = OgreFramework::getSingletonPtr()->m_pSceneMgr->createEntity("OgreHeadEntity", "ogrehead.mesh");
  m_pOgreHeadNode = OgreFramework::getSingletonPtr()->m_pSceneMgr->getRootSceneNode()->createChildSceneNode("OgreHeadNode");
  m_pOgreHeadNode->attachObject(m_pOgreHeadEntity);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PWTViewer::runDemo()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Start main loop...");

	double timeSinceLastFrame = 0;
	double startTime = 0;

      OgreFramework::getSingletonPtr()->m_pRenderWnd->resetStatistics();

	while(!m_bShutdown && !OgreFramework::getSingletonPtr()->isOgreToBeShutDown())
	{
		if(OgreFramework::getSingletonPtr()->m_pRenderWnd->isClosed())m_bShutdown = true;

		Ogre::WindowEventUtilities::messagePump();

		if(OgreFramework::getSingletonPtr()->m_pRenderWnd->isActive())
		{
			startTime = OgreFramework::getSingletonPtr()->m_pTimer->getMillisecondsCPU();

			OgreFramework::getSingletonPtr()->m_pKeyboard->capture();
			OgreFramework::getSingletonPtr()->m_pMouse->capture();

			OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);
			OgreFramework::getSingletonPtr()->m_pRoot->renderOneFrame();

			timeSinceLastFrame = OgreFramework::getSingletonPtr()->m_pTimer->getMillisecondsCPU() - startTime;
		}
		else
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
		}
	}

	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Main loop quit");
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Shutdown OGRE...");
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PWTViewer::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_F))
	{
		 //do something
	}

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PWTViewer::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||
