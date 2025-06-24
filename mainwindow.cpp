#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <set>
#include <QPropertyAnimation>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setPlaceholderText("Введите ваш код...");
    ui->openFile->setCursor(Qt::PointingHandCursor);
    ui->execute->setCursor(Qt::PointingHandCursor);
    this->setStyleSheet(R"(
        QMainWindow {
            background-color: #f0f0f0;
        }

        QPushButton {
            background-color: #4CAF50;
            color: white;
            border-radius: 5px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #5BCE60;
        }

        QPushButton:pressed {
            background-color: #378D3A;
        }

        QTextEdit {
            background-color: #B9B9B9;
            border-radius: 5px;
            padding: 5px;
            color: #434343;
            font-weight: bold;
            border: 3px solid #9F9F9F;
        }

        QTextEdit::placeholder {
            font-weight: bold;
        }

        QTextBrowser {
            background-color: #B9B9B9;
            border-radius: 5px;
            font-weight: bold;
            padding: 5px;
            color: black;
            border: 3px solid #9F9F9F;
        }

    )");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Открыть текстовый файл"),
        QDir::homePath(),
        tr("Текстовые файлы (*.txt)")
    );

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось открыть файл"));
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    ui->textEdit->setPlainText(content);
}


void MainWindow::on_execute_clicked()
{
    QString allText = ui->textEdit->toPlainText();

    if (allText.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Пустой текст");
        return;
    }

    vector<QString> code = search_id(allText.toStdString());

    set<QString> result = create_set(code);

    for(QString line : result) {
        ui->textBrowser->append(line);
    }
}

