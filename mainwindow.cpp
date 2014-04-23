#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QHash>
#include <QCryptographicHash>
#include "crc32.h"
#include <QFile>
#include <QFileDialog>
#include <QClipboard>
#include <QTextStream>
#include <QTextCodec>
#include "about.h"

namespace TypeAlgorithm
{
    enum Type
    {
        md4,
        md5,
        sha1,
        hash,
        crc32
    };
}

namespace TypeNumerationSystem
{
    enum Type
    {
        hex = 16
    };
}

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Заполнение списка алгоритмов.
    {
        ui->algorithm->addItem( "crc32", TypeAlgorithm::crc32 );
        ui->algorithm->addItem( "hash", TypeAlgorithm::hash );
        ui->algorithm->addItem( "sha1", TypeAlgorithm::sha1 );
        ui->algorithm->addItem( "md4", TypeAlgorithm::md4 );
        ui->algorithm->addItem( "md5", TypeAlgorithm::md5 );

        ui->algorithm->setCurrentIndex( ui->algorithm->findData( TypeAlgorithm::crc32 ) );
    }
    // Заполнение списка систем счисления.
    {
        ui->numerationSystem->addItem( tr( "hexadecimal" ) + " (16)", TypeNumerationSystem::hex );
        ui->numerationSystem->setCurrentIndex( ui->numerationSystem->findData( TypeNumerationSystem::hex ) );
    }

    // Конвертирование после окончания ввода.
    {
        QTimer * conversionWithDelay = new QTimer( this );
        conversionWithDelay->setSingleShot( true );
        conversionWithDelay->setInterval( 111 );
        QObject::connect( conversionWithDelay, SIGNAL(timeout()), SLOT(sl_convert()) );

        // То, что вызывает конвертирование.
        QObject::connect( ui->input, SIGNAL(textChanged()), conversionWithDelay, SLOT(start()) );
        QObject::connect( ui->algorithm, SIGNAL(currentIndexChanged(int)), conversionWithDelay, SLOT(start()) );
        QObject::connect( ui->numerationSystem, SIGNAL(currentIndexChanged(int)), conversionWithDelay, SLOT(start()) );
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sl_convert()
{
    QString text = ui->input->toPlainText();
    if ( text.isNull() || text.isEmpty() )
    {
        ui->output->setPlainText( "" );
        return;
    }

    QByteArray byteArray = text.toAscii();

    int algorithmIndex = ui->algorithm->currentIndex();
    TypeAlgorithm::Type algorithm = static_cast < TypeAlgorithm::Type > ( ui->algorithm->itemData( algorithmIndex ).toInt() );

    int numerationSystemIndex = ui->numerationSystem->currentIndex();
    int base = ui->numerationSystem->itemData( numerationSystemIndex ).toInt();

    switch ( algorithm )
    {
    case TypeAlgorithm::hash:
    {
        text = QString::number( qHash( text ), base );
        break;
    }

    case TypeAlgorithm::crc32:
    {
        text = QString::number( CRC32::fromString( text ), base );
        break;
    }

    case TypeAlgorithm::sha1:
    {
        QByteArray arr = QCryptographicHash::hash( byteArray, QCryptographicHash::Sha1 );
        text = arr.toHex();

        break;
    }

    case TypeAlgorithm::md4:
    {
        QByteArray arr = QCryptographicHash::hash( byteArray, QCryptographicHash::Md4 );
        text = arr.toHex();

        break;
    }

    case TypeAlgorithm::md5:
    {
        QByteArray arr = QCryptographicHash::hash( byteArray, QCryptographicHash::Md5 );
        text = arr.toHex();

        break;
    }

    default:
        text = "";
        break;
    }

    if ( text.isNull() || text.isEmpty() )
    {
        ui->output->setPlainText( "" );
        return;
    }

    if ( base == TypeNumerationSystem::hex )
        text.insert( 0, "0x" );

    ui->output->setPlainText( text );
}

void MainWindow::on_actionFromClipboard_triggered()
{
    ui->input->setPlainText( qApp->clipboard()->text() );
}
void MainWindow::on_actionFromFile_triggered()
{
    const QString & fileName = QFileDialog::getOpenFileName( this );
    if ( fileName.isNull() )
        return;

    QFile file( fileName );
    if ( !file.open( QIODevice::ReadOnly ) )
        return;

    QTextStream in( &file );
    in.setCodec( QTextCodec::codecForName( "utf8" ) );

    ui->input->setPlainText( in.readAll() );
}
void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}
void MainWindow::on_actionAbout_triggered()
{
    About * about = new About();
    about->exec();
}
