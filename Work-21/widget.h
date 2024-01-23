#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_button_gen_csr_clicked();

private:
    const int NUM_LINES = 6;
    QWidget*     widget;

    QVBoxLayout* mainLayot;
    QVBoxLayout* v_layot;
    QHBoxLayout* h_layot;

    QComboBox* combo_box_encrypt;
    QComboBox* combo_box_hash;
    QLabel*    cb_encrypt;
    QLabel*    cb_hash;

    QLabel* country_name;
    QLabel* state;
    QLabel* local;
    QLabel* org_name;
    QLabel* org_unit;
    QLabel* common_name;

    QLineEdit** lines  = new QLineEdit*[NUM_LINES];
    QLabel**    labels = new QLabel*[NUM_LINES];

    QPushButton* button_gen_csr;

    QTextEdit*   text_output_csr;

};


#endif // WIDGET_H
