#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnAbrir, &QPushButton::clicked, this, &MainWindow::abrirArchivo);
    connect(ui->btnCifrar, &QPushButton::clicked, this, &MainWindow::cifrarTexto);
    connect(ui->btnGuardar, &QPushButton::clicked, this, &MainWindow::guardarArchivo);


    ui->textOriginal->setReadOnly(true);
    ui->textResultado->setReadOnly(true);

    ui->textOriginal->setPlaceholderText("No hay ningun archivo .txt para visualizar");
    ui->textResultado->setPlaceholderText("Esperando arhivo txt para cifrar");

    ui->btnCifrar->setEnabled(false);
    ui->btnGuardar->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::abrirArchivo() {

    qDebug() << "Botón abrir presionado";

    QString ruta = QFileDialog::getOpenFileName(this, "Abrir archivo", "", "Text Files (*.txt)");
    if(!ruta.isEmpty()) {

        qDebug() << "Archivo seleccionado:" << ruta;

        QFile archivo(ruta);
        if(archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&archivo);
            QString contenido = in.readAll();
            archivo.close();

            ui->textOriginal->setPlainText(contenido);

            ui->textResultado->clear();
            ui->btnCifrar->setEnabled(true);
            ui->btnGuardar->setEnabled(false);
        }
    }
    else {
        qDebug() << "No se seleccionó archivo.";
    }

}

void MainWindow::cifrarTexto() {

    qDebug() << "Vamos a echarnos unos cifrados";

    QString plainText = ui->textOriginal->toPlainText();

    std::string cypherText = encryption.EncryptionCaesar(plainText.toStdString(), 3);

    ui->textResultado->setPlainText(QString::fromStdString(cypherText));

    ui->btnGuardar->setEnabled(true);
}

void MainWindow::guardarArchivo() {
    qDebug() << "Aqui te voy a guardar tu archivo";

    QString ruta = QFileDialog::getSaveFileName(this, "Guardar Archivo Cifrado", "", "Text Files (*.txt)");

    if(!ruta.isEmpty()){
        QFile archivo(ruta);
        if(archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&archivo);
            QString cypherText = ui->textResultado->toPlainText();

            out << cypherText;

            archivo.close();
        }
    }

}


