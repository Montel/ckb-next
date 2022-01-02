#ifndef CLICKEVENTPUSHBUTTON_H
#define CLICKEVENTPUSHBUTTON_H

#include <QToolButton>
#include <QDebug>

class ClickEventPushButton : public QToolButton{
    Q_OBJECT
public:
    explicit ClickEventPushButton(QWidget* parent = nullptr) : QToolButton(parent) {}
    inline bool isClickedByMouse() {
        bool temp = clickedByMouse;
        clickedByMouse = false;
        return temp;
    }
protected:
    void mouseReleaseEvent(QMouseEvent* e) override;
private:
    bool clickedByMouse = false;
};
#endif // CLICKEVENTPUSHBUTTON_H
