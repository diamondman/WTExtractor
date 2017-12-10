#include <QWidget>
#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <QShowEvent>

#include "OgreSceneManager.h"

#include "pwt_decode.h"

class PWTModelFrame : public QWidget {
  Q_OBJECT;

 public:
  PWTModelFrame(QWidget* parent);
  ~PWTModelFrame();

  virtual void resizeEvent(QResizeEvent * event) override;
  virtual void showEvent(QShowEvent *event) override;
  //Avoid "QWidget::paintEngine: Should no longer be called"
  virtual QPaintEngine *paintEngine() const override {return NULL;}

  virtual void render(QPainter *painter) {Q_UNUSED(painter);} //Suggested. IDK why.
  virtual void render();

  void createScene();
  void setWireframe(bool wireframe);
  void setModel(PWT* pwt);

 protected:
  virtual bool event(QEvent *event) override;
  virtual void paintEvent(QPaintEvent *event) override {}; //Prevent flicker.
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;

  Ogre::SceneNode* createPWTMesh(PWT_Frame* modelFrame, Ogre::SceneNode *ogreNode);

 private:
  void initialize();
  void renderNow();
  void renderLater();

  Ogre::Root* mRoot;
  Ogre::RenderWindow* mRenderWindow;
  Ogre::SceneManager* mSceneManager;
  Ogre::Camera* mCamera;
  Ogre::SceneNode* mCameraNode;

  Ogre::SceneNode* mWTNode;

  PWT* pwt;

  bool mUpdatePending;
  bool mIsAnimating;
  bool leftMouseDragging;
  bool rightMouseDragging;
  int lastMouseX;
  int lastMouseY;

  //Initializing the Ogre widget in QT causes render to be called
  //several times before it should, and then not at all once the
  //widget is ready. This results in a black screen until user
  //interaction causes render to be called again. To handle this,
  //requiredRedrawCount holds the number of extra frames to
  //render. This number's default should be high enough to handle the
  //random calls to renderand still have at least one frame to render
  //once the widget it ready. This is a hack, and a better solution is
  //welcome.
  unsigned int requiredRedrawCount;
};
