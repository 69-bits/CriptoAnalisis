#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CesarEncryption.h"
#include "AsciiBinary.h"
#include "DES.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CaesarEncryption encryptionCesar;
    AsciiBinary encryptionAscii;
    DES encryptionDES;

private slots:
    void abrirArchivo();
    void cifrarTexto();
    void guardarArchivo();
};
#endif // MAINWINDOW_H
