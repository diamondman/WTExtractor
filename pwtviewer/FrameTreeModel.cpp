// Based heavily on http://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html

#include "FrameTreeItem.h"
#include "FrameTreeModel.h"

FrameTreeModel::FrameTreeModel(PWT* pwt, QObject *parent) :
  QAbstractItemModel(parent), rootItem(new FrameTreeItem(pwt)) {}

FrameTreeModel::~FrameTreeModel() {
  delete rootItem;
}

int FrameTreeModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return static_cast<FrameTreeItem*>(parent.internalPointer())->columnCount();
  else
    return rootItem->columnCount();
}

QVariant FrameTreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (role != Qt::DisplayRole)
    return QVariant();

  FrameTreeItem *item = static_cast<FrameTreeItem*>(index.internalPointer());

  return item->data(index.column());
}

Qt::ItemFlags FrameTreeModel::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return 0;

  return QAbstractItemModel::flags(index);
}

QVariant FrameTreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return rootItem->data(section);

  return QVariant();
}

QModelIndex FrameTreeModel::index(int row, int column, const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  FrameTreeItem *parentItem;

  if (!parent.isValid())
    parentItem = rootItem;
  else
    parentItem = static_cast<FrameTreeItem*>(parent.internalPointer());

  FrameTreeItem *childItem = parentItem->child(row);
  if (childItem)
    return createIndex(row, column, (void*)childItem);
  else
    return QModelIndex();
}

QModelIndex FrameTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid())
    return QModelIndex();

  FrameTreeItem *childItem = static_cast<FrameTreeItem*>(index.internalPointer());
  const FrameTreeItem *parentItem = childItem->parentItem();

  if (parentItem == rootItem)
    return QModelIndex();

  return createIndex(parentItem->row(), 0, (void*)parentItem);
}

int FrameTreeModel::rowCount(const QModelIndex &parent) const {
  FrameTreeItem *parentItem;
  if (parent.column() > 0)
    return 0;

  if (!parent.isValid())
    parentItem = rootItem;
  else
    parentItem = static_cast<FrameTreeItem*>(parent.internalPointer());

  return parentItem->childCount();
}

FrameTreeItem* FrameTreeModel::recursiveFindSelection(const QModelIndex& current){
  if(current.parent() == QModelIndex()) {
    //std::cout << "ROOT " << current.row() << std::endl;
    return rootItem->child(current.row());
  }

  //std::cout << "NODE " << current.row() << std::endl;
  return recursiveFindSelection(current.parent())->child(current.row());
}

const PWT_Frame* FrameTreeModel::getFrameFromTreeSelection(const QModelIndex& current){
  FrameTreeItem* item = recursiveFindSelection(current);
  return item->getFrame();
}
