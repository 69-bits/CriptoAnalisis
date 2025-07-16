#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QButtonGroup>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnAbrir, &QPushButton::clicked, this, &MainWindow::abrirArchivo);
    connect(ui->btnCifrar, &QPushButton::clicked, this, &MainWindow::cifrarTexto);
    connect(ui->btnGuardar, &QPushButton::clicked, this, &MainWindow::guardarArchivo);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::comboBox);

    connect(ui->btcifrar, &QPushButton::toggled, this, &MainWindow::cifrarOpcion);
    connect(ui->btDescifrar, &QPushButton::toggled, this, &MainWindow::decifrarOpcion);

    ui->textOriginal->setReadOnly(true);
    ui->textResultado->setReadOnly(true);

    ui->textOriginal->setPlaceholderText("No hay ningun archivo .txt para visualizar");
    ui->textResultado->setPlaceholderText("Esperando arhivo txt");

    ui->btnCifrar->setEnabled(false);
    ui->btnGuardar->setEnabled(false);

    this->setFixedSize(this->size());

    ui->comboBox->addItem("Cifrado César");
    ui->comboBox->addItem("Cifrado ASCII to Binary");
    ui->comboBox->addItem("Cifrado DES");
    ui->comboBox->addItem("Cifrado XOREncoder");
    ui->comboBox->addItem("Cifrado Vigenere");

    ui->btcifrar->setCheckable(true);
    ui->btDescifrar->setCheckable(true);
    ui->btcifrar->setChecked(true); // Por defecto está activo Cifrar

    ui->btcifrar->setStyleSheet("QPushButton:checked { background-color: #4CAF50; color: white; }");
    ui->btDescifrar->setStyleSheet("QPushButton:checked { background-color: #4CAF50; color: white; }");

    QButtonGroup *modoGrupo = new QButtonGroup(this);
    modoGrupo->addButton(ui->btcifrar);
    modoGrupo->addButton(ui->btDescifrar);
    modoGrupo->setExclusive(true);


    ui->textEdit->hide();
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

    int userSelection = ui->comboBox->currentIndex();
    QString plainText;
    std::string cypherText;

    if(ui->btcifrar->isChecked())
    {
        switch (userSelection) {
        case 0:
            // Cifrado César
            plainText = ui->textOriginal->toPlainText();
            cypherText = encryptionCesar.EncryptionCaesar(plainText.toStdString(), 4);
            ui->textResultado->setPlainText(QString::fromStdString(cypherText));
            ui->btnGuardar->setEnabled(true);
            break;

        case 1:
            // ASCII a binario
            plainText = ui->textOriginal->toPlainText();
            cypherText = encryptionAscii.stringToBinary(plainText.toStdString());
            ui->textResultado->setPlainText(QString::fromStdString(cypherText));
            ui->btnGuardar->setEnabled(true);
            break;

        case 2: {
            // Cifrado DES con clave fija
            qDebug() << "Cifrado DES seleccionado";

            // Clave fija (64 bits)
            std::bitset<64> claveBits("0001001100110100010101110111100110011011101111001101111111110001");
            DES des(claveBits);

            // Obtener texto a cifrar
            QString textoQt = ui->textOriginal->toPlainText();
            std::string mensaje = textoQt.toStdString();

            // Padding para que sea múltiplo de 8
            while (mensaje.size() % 8 != 0) {
                mensaje += '\0';
            }

            // Cifrar por bloques de 8 bytes
            QString resultadoHex;
            for (size_t i = 0; i < mensaje.size(); i += 8) {
                std::string bloque = mensaje.substr(i, 8);
                std::bitset<64> bloqueBits = des.stringToBitset64(bloque);
                std::bitset<64> cifrado = des.encode(bloqueBits);

                QString hex = QString::number(cifrado.to_ullong(), 16).rightJustified(16, '0');
                resultadoHex += hex.toUpper() + " ";
            }

            ui->textResultado->setPlainText(resultadoHex.trimmed());
            ui->btnGuardar->setEnabled(true);
            break;
        }
        case 3: {
            qDebug() << "Cifrado XOR seleccionado";

            // Obtener texto y clave desde el UI
            QString plainText = ui->textOriginal->toPlainText();
            QString clave = ui->textEdit->toPlainText();

            // Convertir a std::string
            std::string mensaje = plainText.toStdString();
            std::string claveStr = clave.toStdString();

            // Verificar que la clave no esté vacía
            if (claveStr.empty()) {
                QMessageBox::warning(this, "Error", "Por favor, ingresa una clave para el cifrado XOR.");
                break;
            }

            // Cifrar usando XOR
            std::string cifrado = encryptionXORE.encode(mensaje, claveStr);

            std::stringstream hexStream;
            for (unsigned char c : cifrado) {
                hexStream << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
            }
            ui->textResultado->setPlainText(QString::fromStdString(hexStream.str()));


            ui->btnGuardar->setEnabled(true);

            break;
        }
        case 4: {
            qDebug() << "Cifrado Vigenere seleccionado";

            // Obtener texto y clave desde el UI
            QString plainText = ui->textOriginal->toPlainText();
            QString clave = ui->textEdit->toPlainText();

            std::string mensaje = plainText.toStdString();
            std::string claveStr = clave.toStdString();

            // Verificar que la clave no esté vacía
            if (claveStr.empty()) {
                QMessageBox::warning(this, "Error", "Por favor, ingresa una clave para el cifrado Vigenere.");
                break;
            }

            try {
                Vignere vigenere(claveStr);
                std::string cifrado = vigenere.encode(mensaje);

                // Mostrar resultado
                ui->textResultado->setPlainText(QString::fromStdString(cifrado));
                ui->btnGuardar->setEnabled(true);
            }
            catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", e.what());
            }

            break;
        }
    }
  }
    else if (ui->btDescifrar->isChecked()){
        switch (userSelection) {
        case 0:
            // Descifrado César
            qDebug() << "Descifrado CESAR seleccionado";

            plainText = ui->textOriginal->toPlainText();
            cypherText = encryptionCesar.DecodeCaesar(plainText.toStdString(), 4);
            ui->textResultado->setPlainText(QString::fromStdString(cypherText));
            ui->btnGuardar->setEnabled(true);
            break;

        case 1:
            // Binario a ASCII
            plainText = ui->textOriginal->toPlainText();
            cypherText = encryptionAscii.binaryToString(plainText.toStdString());
            ui->textResultado->setPlainText(QString::fromStdString(cypherText));
            ui->btnGuardar->setEnabled(true);
            break;

        case 2: {
            // Descifrado DES
            qDebug() << "Descifrado DES seleccionado";

            std::bitset<64> claveBits("0001001100110100010101110111100110011011101111001101111111110001");
            DES des(claveBits);

            QString textoCifrado = ui->textOriginal->toPlainText();
            std::string input = textoCifrado.toStdString();

            std::stringstream ss(input);
            std::string hexBlock;
            std::string mensaje;

            while (ss >> hexBlock) {
                uint64_t valor = std::stoull(hexBlock, nullptr, 16);
                std::bitset<64> bloque(valor);
                std::bitset<64> descifrado = des.decode(bloque); // <-- usa tu función decode

                std::string bloqueDescifrado = des.bitset64ToString(descifrado);
                mensaje += bloqueDescifrado;
            }
            mensaje.erase(mensaje.find_last_not_of('\0') + 1);

            ui->textResultado->setPlainText(QString::fromStdString(mensaje));
            ui->btnGuardar->setEnabled(true);
            break;
        }

        case 3: {
            qDebug() << "Descifrado XOR seleccionado";

            QString inputHex = ui->textOriginal->toPlainText();
            QString clave = ui->textEdit->toPlainText();

            std::string claveStr = clave.toStdString();
            std::string input = inputHex.toStdString();

            if (claveStr.empty()) {
                QMessageBox::warning(this, "Error", "Por favor, ingresa una clave para descifrar con XOR.");
                break;
            }

            std::istringstream iss(input);
            std::string hex;
            std::string bytes;
            while (iss >> hex) {
                unsigned char byte = static_cast<unsigned char>(std::stoi(hex, nullptr, 16));
                bytes.push_back(byte);
            }

            std::string descifrado = encryptionXORE.encode(bytes, claveStr); // XOR encode = decode
            ui->textResultado->setPlainText(QString::fromStdString(descifrado));
            ui->btnGuardar->setEnabled(true);
            break;
        }

        case 4: {
            qDebug() << "Descifrado Vigenere seleccionado";

            QString plainText = ui->textOriginal->toPlainText();
            QString clave = ui->textEdit->toPlainText();

            std::string mensaje = plainText.toStdString();
            std::string claveStr = clave.toStdString();

            if (claveStr.empty()) {
                QMessageBox::warning(this, "Error", "Por favor, ingresa una clave para el descifrado Vigenere.");
                break;
            }

            try {
                Vignere vigenere(claveStr);
                std::string descifrado = vigenere.decode(mensaje);
                ui->textResultado->setPlainText(QString::fromStdString(descifrado));
                ui->btnGuardar->setEnabled(true);
            }
            catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", e.what());
            }

            break;
        }
        }

  }
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

void MainWindow::comboBox(const QString &texto){
    if(texto == "Cifrado XOREncoder" || texto == "Cifrado Vigenere"){
        ui->textEdit->show();
    }
    else{
       ui->textEdit->hide();
    }
}

void MainWindow::cifrarOpcion(){
    ui->btnCifrar->setText("Pulsa para Cifrar");
    ui->groupBox_3->setTitle("Una vez tenga su archivo, pulse en el botón para cifrar.");
}

void MainWindow::decifrarOpcion(){
    ui->btnCifrar->setText("Pulsa para Descifrar");
    ui->groupBox_3->setTitle("Una vez tenga su archivo, pulse en el botón para descifrar.");

}


