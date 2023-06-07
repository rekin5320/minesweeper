#include "MyButton.hpp"

MyButton::MyButton(QWidget *parent) : QPushButton(parent) {}

void MyButton::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit leftButtonClicked();
    }
    else if (event->button() == Qt::RightButton) {
        emit rightButtonClicked();
    }
    else {
        QPushButton::mouseReleaseEvent(event);
    }
}
