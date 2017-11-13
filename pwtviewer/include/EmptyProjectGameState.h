
#ifndef _Demo_EmptyProjectGameState_H_
#define _Demo_EmptyProjectGameState_H_

#include "OgrePrerequisites.h"
#include "TutorialGameState.h"

#include "OgreSceneManager.h"
#include "OgreItem.h"

#include "OgreMesh2.h"
#include "OgreMeshManager2.h"
#include "OgreSubMesh2.h"

#include "pwt_decode.h"

namespace Demo
{
  class EmptyProjectGameState : public TutorialGameState
  {
    Ogre::SceneNode* mWTNode;

    virtual void generateDebugText( float timeSinceLast, Ogre::String &outText );

    Ogre::SceneNode* createStaticMesh( PWT* pwt );

  public:
    EmptyProjectGameState( const Ogre::String &helpDescription );

    virtual void createScene01(void);
    virtual void destroyScene(void);

    virtual void update( float timeSinceLast );

    virtual void keyReleased( const SDL_KeyboardEvent &arg );
  };
}

#endif
