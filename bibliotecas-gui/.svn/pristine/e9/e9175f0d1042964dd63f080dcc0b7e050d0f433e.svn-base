#ifndef GREETER_H
#define GREETER_H

#include <QWidget>

class Greeter : public QWidget {
    Q_OBJECT
public:
    explicit Greeter(QWidget *parent = 0);
private:
    void updateGreetings();
private slots:
    // Utilizo el MOC (metaobject compiler) de qt para autoconectar funciones
    // Firma de las funciones: on_<objeto>_<signal>()
    void on_buttonGreet_clicked();
};

#endif // GREETER_H
