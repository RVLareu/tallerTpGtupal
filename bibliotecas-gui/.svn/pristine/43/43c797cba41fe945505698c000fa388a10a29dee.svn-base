#include "Greeter.h"
// Cargo el archivo generado por uic, leer el CMakelist.txt para mas info
#include "ui_Greeter.h"
// Incluyo el archivo creado por el moc para que cmake lo detecte y compile
#include "moc_Greeter.cpp"

Greeter::Greeter(QWidget *parent) : QWidget(parent) {
    // Instancio la configuracion generada por el designer y uic
    Ui::Greeter greeter;
    // Configuro este widget para use esa configuracion
    greeter.setupUi(this);
}

void Greeter::updateGreetings() {
    QLineEdit* inputName = findChild<QLineEdit*>("inputName");
    QLabel* labelOut = findChild<QLabel*>("labelOut");
    QString name = inputName->text();
    QString greetings = QString("Hola %1").arg(name);
    labelOut->setText(greetings);
}

// Este evento es autoconectado por el moc
void Greeter::on_buttonGreet_clicked() {
    updateGreetings();
}
