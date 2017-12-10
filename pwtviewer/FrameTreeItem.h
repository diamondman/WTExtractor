// Based heavily on http://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html

#include <QList>
#include <QVariant>
#include "pwt_decode.h"

class FrameTreeItem {
 public:
  FrameTreeItem(PWT* pwt);
  FrameTreeItem(const PWT_Frame* frame, const FrameTreeItem* parent = 0);
  ~FrameTreeItem();

  FrameTreeItem* child(int row);
  int childCount() const;
  int columnCount() const;
  QVariant data(int column) const;
  int row() const;
  const FrameTreeItem* parentItem();
  const PWT_Frame* getFrame();

 private:
  const FrameTreeItem* parentFrame;
  QList<FrameTreeItem*> children;
  const PWT_Frame* frame;
};
