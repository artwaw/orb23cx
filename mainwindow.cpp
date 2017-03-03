#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->bar->setValue(0);
    lines = 0;
    ui->bar->setMinimum(0);
    connect(ui->sourceBrowse,SIGNAL(clicked(bool)),this,SLOT(sourceBrowseClick()));
    connect(ui->destBrowse,SIGNAL(clicked(bool)),this,SLOT(destBrowseClick()));
    connect(ui->startBtn,SIGNAL(clicked(bool)),this,SLOT(startClick()));
}

QString MainWindow::browseClick(bool dir) {
    if (dir) {
        return QFileDialog::getSaveFileName(this,"Select destination XML file name and location:",".","XML file (*.xml)");
    } else {
        return QFileDialog::getOpenFileName(this,"Select CSV file:",".","Comma separated values (*.csv);;All files (*.*)");
    };
}

void MainWindow::sourceBrowseClick() {
    lines = 0;
    ui->infoLabel->setText("Waiting for file name");
    ui->sourceEdit->setText(browseClick(false));
    QFile insrc(ui->sourceEdit->text());
    if (ui->destEdit->text().isEmpty()) {
        ui->destEdit->setText(ui->sourceEdit->text().replace(".csv",".xml"));
    };
    if (!insrc.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this,"Ooops!","Can not open file for reading!",QMessageBox::Ok);
        return;
    };
    QTextStream in(&insrc);
    ui->infoLabel->setText("Munching file... Please wait.");
    while (!in.atEnd()) {
        in.readLine();
        lines++;
    };
    insrc.close();
    ui->bar->setMaximum(lines);
    ui->infoLabel->setText("File checked! "+QString::number(lines)+" lines detected.");
}

void MainWindow::destBrowseClick() {
    ui->destEdit->setText(browseClick(true));
}

void MainWindow::startClick() {
    QFile insrc(ui->sourceEdit->text());
    QFile outsrc(ui->destEdit->text());
    if (!insrc.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this,"Ooops!","Can not open file for reading!",QMessageBox::Ok);
        return;
    };
    if (!outsrc.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this,"Ooops!","Can not open file for writing!",QMessageBox::Ok);
        insrc.close();
        return;
    };
    QTextStream in(&insrc);
    QTextStream out(&outsrc);
    out << "<TenantProperties>\n";
    QString cxs,tmp;
    QStringList tmpl;
    int cx = -1;
    in.readLine(); //skipping headers line
    while (!in.atEnd()) {
        cx++;
        tmpl = in.readLine().split(",");
        tmp = tmpl.at(0);
        if (tmp.contains("&")) {
            tmpl.replace(0,tmp.remove("&"));
        };
        out << "  <TenantProperty>\n";
        cxs=QString::number(cx);
        out << "    <name>BILL_"+cxs+"</name>\n    <description>\n    </description>\n    <type>String</type>\n";
        out << "    <value n=\""+tmpl.at(0)+"\" p=\""+tmpl.at(1)+"\" r=\""+tmpl.at(2)+"\" />\n";
        out << "  </TenantProperty>\n";
        ui->bar->setValue(cx);
    };
    out << "</TenantProperties>\n";
    insrc.close();
    outsrc.close();
    ui->bar->setValue(lines);
    QMessageBox::information(this,"OK","Task completed without errors. You may now upload XML file to the 3CX.",QMessageBox::Ok);
    ui->bar->setValue(0);
    lines = 0;
    ui->sourceEdit->setText("");
    ui->destEdit->setText("");
    ui->infoLabel->setText("Waiting for file name");
}

void MainWindow::helpClick() {
    QMessageBox::information(this,"Quick info","This tool converts Orbtalks call rates CSV file into 3CX XML file ready to be upload into CDR prefixes cost settings.\n Just select source file, program will automatically fill in destination file option (but one can change that) and press start.\n Conersion make take some time depending on the size of the source file.",QMessageBox::Ok);
}

MainWindow::~MainWindow()
{
    delete ui;
}
