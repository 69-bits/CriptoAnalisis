#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CesarEncryption.h"
#include "AsciiBinary.h"
#include "DES.h"
#include "XORE.h"
#include "Vigenere.h"

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
    XOREncoder encryptionXORE;
    Vignere encryptionVigenere;


private slots:
    void abrirArchivo();
    void cifrarTexto();
    void guardarArchivo();
    void comboBox(const QString &texto);
    void cifrarOpcion();
    void decifrarOpcion();
};
#endif // MAINWINDOW_H
