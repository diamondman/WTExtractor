//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef OGRE_PWTVIEWER_HPP
#define OGRE_PWTVIEWER_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

//#include "TutorialConfig.h"
#include "OgreFramework.hpp"
#include "pwt_decode.h"
#include "dataaccessors.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

class PWTViewer : public OIS::KeyListener
{
public:
  PWTViewer(char*);
  ~PWTViewer();

  void startDemo();

  bool keyPressed(const OIS::KeyEvent &keyEventRef);
  bool keyReleased(const OIS::KeyEvent &keyEventRef);

private:
  void setupDemoScene();
  void runDemo();

  Ogre::SceneNode*			m_pOgreHeadNode;
  Ogre::Entity*				m_pOgreHeadEntity;

  bool					m_bShutdown;

  char*                                 pwtfile;

  DataAccessor*                         acc;
  PWT*                                  pwt;

};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||