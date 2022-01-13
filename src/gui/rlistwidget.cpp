#include <QUuid>
#include "rlistwidget.h"

RListWidget::RListWidget(QWidget *parent) :
    QListWidget(parent)
{
    setDragDropMode(QAbstractItemView::InternalMove);
    setMovement(QListView::Snap);

    reorderTimer.setSingleShot(true);
    reorderTimer.setInterval(100);
    connect(&reorderTimer, &QTimer::timeout, this, &RListWidget::timerTick);

    connect(this, &QListWidget::itemEntered, this, &RListWidget::enter);
    connect(this, &QListWidget::itemChanged, this, &RListWidget::change);
}

void RListWidget::timerTick(){
    bool reordered = false;
    QListWidgetItem* reselect = nullptr;
    QList<QVariant> newItems;
    // Scan the item list to see if they changed
    int c = count();
    for(int i = 0; i < c; i++){
        QListWidgetItem* itm = item(i);
        QVariant itmdata = itm->data(DATA_ROLE);
        newItems.append(itmdata);
        if(i >= previousItems.count() || itmdata != previousItems[i])
            reordered = true;
        // Re-select the dragged item (if any)
        if(itmdata == dragged)
            reselect = itm;
    }
    if(previousItems.length() != newItems.length())
        return;
    if(reordered){
        previousItems = newItems;
        Q_EMIT orderChanged();
        if(reselect){
            reselect->setSelected(true);
            setCurrentItem(reselect);
            dragged = QVariant();
        }
    }
}

void RListWidget::enter(QListWidgetItem* item){
    rescanItems();
    // Check for drag+drop setup
    if(item)
        dragged = item->data(DATA_ROLE);
}

void RListWidget::change(QListWidgetItem* item){
    reorderTimer.stop();
    reorderTimer.start();
}

void RListWidget::rescanItems(){
    QList<QVariant> newItems;
    int c = count();
    for(int i = 0; i < c; i++){
        QVariant itmdata = this->item(i)->data(DATA_ROLE);
        if(itmdata.isNull()){
            // Generate the ID for this item if it doesn't already exist
            itmdata = QUuid::createUuid();
            this->item(i)->setData(DATA_ROLE, itmdata);
        }
        newItems.append(itmdata);
    }
    previousItems = newItems;
}
