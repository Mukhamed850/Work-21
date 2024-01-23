#include "widget.h"
#include "ui_widget.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QStringList>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>

Widget::Widget(QWidget *parent) : QWidget(parent) {

    widget  = new QWidget(this);

    //COMBO BOXES
    h_layot = new QHBoxLayout;

    QVBoxLayout* layot_cb_encrypt = new QVBoxLayout;
    QVBoxLayout* layot_cb_hash    = new QVBoxLayout;

    combo_box_encrypt  = new QComboBox;
    combo_box_hash     = new QComboBox;
    cb_encrypt         = new QLabel("Encryption option:");
    cb_hash            = new QLabel("Hash option:");

    layot_cb_encrypt->addWidget(cb_encrypt); layot_cb_encrypt->addWidget(combo_box_encrypt);
    layot_cb_hash->addWidget(cb_hash);       layot_cb_hash->addWidget(combo_box_hash);

    combo_box_encrypt->addItems({"-", "gost2001", "gost2012_256", "gost2012_512"});
    combo_box_hash->addItems({"-", "md_gost94", "md_gost12_256", "md_gost12_512"});

    h_layot->addLayout(layot_cb_encrypt);
    h_layot->addLayout(layot_cb_hash);

    //FIELDS
    v_layot = new QVBoxLayout;

    labels[0] = new QLabel("Country Name:");
    labels[1] = new QLabel("State or Province:");
    labels[2] = new QLabel("Locality:");
    labels[3] = new QLabel("Organization:");
    labels[4] = new QLabel("Organization Unit:");
    labels[5] = new QLabel("Common Name:");

    for(int i = 0; i < NUM_LINES; i++) {
        lines[i] = new QLineEdit(this);
        v_layot->addWidget(labels[i]);
        v_layot->addWidget(lines[i]);
    }

    //BUTTON
    button_gen_csr = new QPushButton("GENERATE CERTIFICATE REQUEST");
    connect(button_gen_csr, &QPushButton::clicked, this, &Widget::on_button_gen_csr_clicked);
    v_layot->addWidget(button_gen_csr);

    //TEXT FIELD
    text_output_csr = new QTextEdit(this);
    v_layot->addWidget(text_output_csr);

    mainLayot = new QVBoxLayout(widget);
    mainLayot->addLayout(h_layot);
    mainLayot->addLayout(v_layot);

    widget->setLayout(mainLayot);
    widget->show();

}

Widget::~Widget() { }

void Widget::on_button_gen_csr_clicked() {
    QString result;
    bool is_all_data = true;

    for(int i = 0; i < NUM_LINES; i++) {
        if(lines[i]->text() == "") {
            is_all_data = false;
            lines[i]->setPlaceholderText("Empty!");
        }
        lines[i]->text() == "" ? labels[i]->setStyleSheet("color: rgb(255, 0, 0)") : labels[i]->setStyleSheet("color: rgb(0, 0, 0)");
    }

    if(!(combo_box_encrypt->currentIndex() && combo_box_hash->currentIndex()))
        is_all_data = false;

    combo_box_encrypt->currentIndex() ? cb_encrypt->setStyleSheet("color: rgb(0, 0, 0)") : cb_encrypt->setStyleSheet("color: rgb(255, 0, 0)");
    combo_box_hash->currentIndex()    ? cb_hash->setStyleSheet("color: rgb(0, 0, 0)")    : cb_hash->setStyleSheet("color: rgb(255, 0, 0)");

    if(lines[0]->text().size() != 2 && lines[0]->text().size() != 0) {
        is_all_data = false;
        lines[0]->clear();
        lines[0]->setPlaceholderText("You need to write 2 letters!");
        labels[0]->setStyleSheet("color: rgb(255, 0, 0)");
    }

    if(!is_all_data)
        qDebug() << "NOT ALL DATA IS ENTERED!";
    else {
        std::string key_file_name    = "private.key";
        std::string certificate_name = "CSR.csr";
        std::string command = "openssl genpkey -algorithm " + combo_box_encrypt->currentText().toStdString() + " -pkeyopt paramset:A -out " + key_file_name;

        if(system(command.c_str())) {
            qDebug() << "ERROR OF GENERATING PRIVATE KEY!";
        }
        else {
            command = "openssl req -x509 -" + combo_box_hash->currentText().toStdString() + " -new -key " + key_file_name + " -out " + certificate_name + " -subj \"" +
                    "/C="  + lines[0]->text().toStdString() +
                    "/ST=" + lines[1]->text().toStdString() +
                    "/L="  + lines[2]->text().toStdString() +
                    "/O="  + lines[3]->text().toStdString() +
                    "/OU=" + lines[4]->text().toStdString() +
                    "/CN=" + lines[5]->text().toStdString() + "\"";
            if(system(command.c_str()))
                qDebug() << "ERROR OF GENERATING SERTIFICATE!";
            else {
                QFile file(QString::fromStdString(certificate_name));
                if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QTextStream in(&file);
                    result = in.readAll();
                    file.close();
                }

                else {
                    qDebug() << "ERROR!";
                }

            }
        }
    text_output_csr->setText(result);


    }







}



















