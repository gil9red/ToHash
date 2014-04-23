#include "about.h"
#include "ui_about.h"

About::About( QWidget * parent )
    : QDialog( parent ),
      ui( new Ui::About )
{
    ui->setupUi( this );
    ui->labelVersion->setText( ui->labelVersion->text().arg( qApp->applicationVersion() ) );
}

About::~About()
{
    delete ui;
}
