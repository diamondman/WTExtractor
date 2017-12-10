// Based heavily on http://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "pwt_decode.h"

class FrameTreeItem;

class FrameTreeModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  explicit FrameTreeModel(PWT* pwt, QObject *parent = 0);
  ~FrameTreeModel();

  QVariant data(const QModelIndex &index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  FrameTreeItem* recursiveFindSelection(const QModelIndex& current);
  const PWT_Frame* getFrameFromTreeSelection(const QModelIndex& current);

 private:
  FrameTreeItem *rootItem;
};
