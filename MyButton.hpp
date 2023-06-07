#pragma once
#include <QMouseEvent>
#include <QPushButton>

class MyButton : public QPushButton {
    // Allows detection of right mouse button press in comparison to regular QPushButton
    Q_OBJECT

public:
    explicit MyButton(QWidget *parent = nullptr);

signals:
    void leftButtonClicked();
    void rightButtonClicked();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
};
