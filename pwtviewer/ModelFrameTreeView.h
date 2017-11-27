#include <QTreeView>

class ModelFrameTreeView : public QTreeView {
  Q_OBJECT

 public:
  ModelFrameTreeView(QWidget *parent = Q_NULLPTR);

 signals:
  void onSelectedFrameChange(const QModelIndex &current, const QModelIndex &previous);

 protected:
  void currentChanged(const QModelIndex &current, const QModelIndex &previous);
};
