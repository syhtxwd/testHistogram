#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./defectcategorywidget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_HisWidget = new HistogramBaseWidget(this);


    QFont font;
    font.setPointSize(11);
    m_HisWidget->SetCoordinateFont(font);
    m_HisWidget->SetVeriTitle("纵坐标");
    m_HisWidget->SetHoriTitle("横坐标");
    m_HisWidget->SetTitle(QString("直方图"));


    QList<QColor> m_colorList;
    m_colorList << QColor(Qt::blue) << QColor(Qt::red) << QColor(Qt::yellow)\
                << QColor(Qt::gray) << QColor(Qt::blue) << QColor(Qt::red);
    m_HisWidget->SetDataColorList(m_colorList);



    QMap<QString, QStringList>  m_dataMap;
    QStringList    m_list, m_list2, m_list3, m_list4, m_list5, m_list6;
    m_list << "50" ;
    m_list2 << "50" ;
    m_list3 << "50" ;
    m_list4 << "50" ;
    m_list5 << "50" ;
    m_list6 << "150" ;

    m_dataMap.insert("1", m_list);
    m_dataMap.insert("2", m_list2);
    m_dataMap.insert("3", m_list3);
    m_dataMap.insert("4", m_list4);
    m_dataMap.insert("5", m_list5);
    m_dataMap.insert("6", m_list6);
    m_HisWidget->OninitData(m_dataMap);

    QStringList m_listt;
    m_listt << "1" << "2" << "3" << "4" << "5" << "6";
    m_HisWidget->SetHorizonScaleValue(m_listt);

    setCentralWidget(m_HisWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}
