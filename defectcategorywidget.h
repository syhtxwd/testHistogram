#ifndef DEFECTCATEGORYWIDGET_H
#define DEFECTCATEGORYWIDGET_H
/*
 * 类名：HistogramBaseWidget
 * 说明：本小类绘制直方图
 * ******************************************************/
#include <QWidget>
#include <QMap>
#include <QColor>
#include <QStringList>
class HistogramBaseWidget: public QWidget
{
    Q_OBJECT
public:
    explicit HistogramBaseWidget(QWidget * parent = nullptr);
    bool OninitData(const QMap<QString, QStringList> & m_dataMap);
    bool SetTitle(QString  title);
    bool SetHoriTitle( QString horiTitle);
    bool SetVeriTitle( QString veriTitle);
    bool SetDataColorList(const QList<QColor> &m_colorList) ;
    bool SetVeriColor( QColor m_veriColor = QColor(Qt::blue));
    bool SetHoriColor( QColor m_horiColor = QColor(Qt::blue));
    //设置柱状之间的间隔
    bool SetVeriColumnarInterval(const int m_space = 50);
    inline int  VeriColumnarInterval()const
    {
        return m_space;
    }
    //设置纵坐标的刻度值和起始值
    bool SetVerticalScale(const int m_verticalScale,  int m_verticalStartScale = 0);
    //设置纵坐标刻度值对应的像素
    bool SetVerticalScaleToPixel( int m_verticalToPixel = 50);
    //设置柱的宽度
    bool SetHoricalWidth(const int m_columnarWidth);
    inline int  HoricalWidth()const
    {
        return m_columnarWidth;
    }
    //设置图表的边框宽度
    bool SetChartMargin(const int m_margin = 50);
    inline int ChartMargin()const
    {
        return m_margin;
    }
    //设置坐标系刻度字体
    bool SetCoordinateFont(const QFont &m_font);
    //设置横坐标刻度
    bool SetHorizonScaleValue(const QStringList &m_horizonlist);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QMap<QString, QStringList> m_dataMap;
    QString m_title, m_horiTitle, m_veriTitle;
    QList<QColor> m_colorList;
    QColor       m_veriColor = Qt::blue;
    QColor m_horiColor = Qt::blue;
    QFont  m_font;
    QStringList m_horizonlist;
    int    m_space = 50;
    int    m_verticalScale = 50, m_verticalStartScale = 0;
    int    m_columnarWidth = 50;
    int    m_margin = 50;
    int    m_verticalToPixel = 50;
};


#endif // DEFECTCATEGORYWIDGET_H
