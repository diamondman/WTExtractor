#include "ModelFrameTreeView.h"

#include <QModelIndex>
#include <iostream>

ModelFrameTreeView::ModelFrameTreeView(QWidget *parent) : QTreeView(parent) {}

void ModelFrameTreeView::currentChanged(const QModelIndex &current,
                                        const QModelIndex &previous) {
  QTreeView::currentChanged(current, previous);

  emit onSelectedFrameChange(current, previous);
}
