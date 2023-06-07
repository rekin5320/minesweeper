// TODO split to header and source files; temporarily for convenience it's together
#include <QMouseEvent>
#include <QPushButton>


class MyButton : public QPushButton {
    // Allows detection of right mouse button press in comparison to regular QPushButton
    Q_OBJECT

public:
    explicit MyButton(QWidget *parent = nullptr) : QPushButton(parent) {}

signals:
    void leftButtonClicked();
    void rightButtonClicked();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override {
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
};
