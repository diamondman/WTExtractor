// Based heavily on http://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html

#include "FrameTreeItem.h"

FrameTreeItem::FrameTreeItem(PWT* pwt)
  : frame(0), parentFrame(0) {
  children.append(new FrameTreeItem(pwt->frames, this));
}

FrameTreeItem::FrameTreeItem(const PWT_Frame* frame, const FrameTreeItem* parent)
  : frame(frame), parentFrame(parent) {
  for(int i = 0; i < frame->subframe_count; i++)
    children.append(new FrameTreeItem(frame->subframes[i], this));
}

FrameTreeItem::~FrameTreeItem(){
  qDeleteAll(children);
}

FrameTreeItem* FrameTreeItem::child(int row){
  return children.value(row);
}

int FrameTreeItem::childCount() const {
  return children.count();
}

int FrameTreeItem::columnCount() const {
  return 3;
}

QVariant FrameTreeItem::data(int column) const{
  switch(column){
  case 0:
    return QString((frame? (frame->name?frame->name:"<null>"):"Name"));
  case 1:
    return QString((frame? (frame->has_visuals?"yes":"no"):"Visuals"));
  case 2:
    return QString((frame? (frame->has_animation?"yes":"no"):"Animation"));
  default:
    return "UNK";
  }
}

int FrameTreeItem::row() const {
  if(parentFrame)
    return parentFrame->children.indexOf(const_cast<FrameTreeItem*>(this));
  return 0;
}

const FrameTreeItem* FrameTreeItem::parentItem(){
  return parentFrame;
}

const PWT_Frame* FrameTreeItem::getFrame(){
  return frame;
}
