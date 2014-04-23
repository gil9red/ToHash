#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui
{
    class About;
}

//! Класс, реализующий виджет "О программе".
class About: public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private:
    Ui::About * ui; //!< Форма UI.
};

#endif // PAGE_ABOUT_H
