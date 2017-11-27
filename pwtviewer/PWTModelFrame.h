#include <QWidget>
#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <QShowEvent>

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

 protected:
  virtual bool event(QEvent *event) override;
  virtual void paintEvent(QPaintEvent *event) override {}; //Prevent flicker.

 private:
  void initialize();
  void renderNow();
  void renderLater();

  Ogre::Root* mRoot;
  Ogre::RenderWindow* mRenderWindow;
  Ogre::SceneManager* mSceneManager;
  Ogre::Camera* mCamera;
  Ogre::SceneNode* mCameraNode;

  bool mUpdatePending;
  bool mIsAnimating;
};
