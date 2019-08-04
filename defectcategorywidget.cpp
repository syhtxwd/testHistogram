#include "defectcategorywidget.h"
#include <QPainter>
#include <QDebug>

HistogramBaseWidget::HistogramBaseWidget(QWidget * parent  ):
    QWidget(parent)
{
    m_font.setFamily("Ubuntu");
    m_font.setPointSize(8);
    m_font.setLetterSpacing(QFont::AbsoluteSpacing, 2);
}
bool HistogramBaseWidget::OninitData(const QMap<QString, QStringList> & m_dataMap)
{
    this->m_dataMap = m_dataMap;
}

bool HistogramBaseWidget::SetTitle( QString  title)
{
    this->m_title = title;
    qDebug() << m_title;
    return true;
}
bool HistogramBaseWidget::SetHoriTitle( QString horiTitle)
{
    this->m_horiTitle = horiTitle;
    return true;
}
bool HistogramBaseWidget::SetVeriTitle( QString veriTitle)
{
    this->m_veriTitle = veriTitle;
    return true;
}
bool HistogramBaseWidget::SetDataColorList(const QList<QColor> &m_colorList)
{
    this->m_colorList = m_colorList;
}
bool HistogramBaseWidget::SetVeriColor( QColor m_veriColor)
{
    this->m_veriColor = m_veriColor;
}
bool HistogramBaseWidget::SetHoriColor( QColor m_horiColor)
{
    this->m_horiColor = m_horiColor;
}
bool HistogramBaseWidget::SetVeriColumnarInterval(const int m_space)
{
    this->m_space = m_space;
}
bool HistogramBaseWidget::SetVerticalScale(const int m_verticalScale,  int m_verticalStartScale )
{
    this->m_verticalScale = m_verticalScale;
    this->m_verticalStartScale = m_verticalStartScale;
}
bool HistogramBaseWidget::SetVerticalScaleToPixel( int m_verticalToPixel)
{
    this->m_verticalToPixel = m_verticalToPixel;
}
bool HistogramBaseWidget::SetHoricalWidth(const int m_columnarWidth)
{
    this->m_columnarWidth = m_columnarWidth;
}

bool HistogramBaseWidget::SetChartMargin(const int m_margin )
{
    this->m_margin = m_margin;
}
bool HistogramBaseWidget::SetCoordinateFont(const QFont &m_font)
{
    this->m_font = m_font;
}
bool HistogramBaseWidget::SetHorizonScaleValue(const QStringList &m_horizonlist)
{
    this->m_horizonlist = m_horizonlist;
}
void HistogramBaseWidget::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    //绘制坐标系
    int temp = m_margin;
    if(temp >= 200)
        temp = 50;
    //横坐标--坐标轴
    paint.setPen(m_veriColor);
    paint.drawLine(QPoint(m_margin, this->height() - m_margin), QPoint(this->width() - m_margin, this->height() - m_margin));
    paint.drawLine(QPoint(this->width() - m_margin, this->height() - m_margin), QPoint(this->width() - m_margin - temp * 0.5, this->height() - 50 - temp * 0.2));
    paint.drawLine(QPoint(this->width() - m_margin, this->height() - m_margin), QPoint(this->width() - m_margin - temp * 0.5, this->height() - 50 + temp * 0.2));
    //纵坐标--坐标轴
    paint.setPen(m_horiColor);
    paint.drawLine(QPoint(m_margin, this->height() - m_margin), QPoint(m_margin, m_margin));
    paint.drawLine(QPoint(m_margin, m_margin), QPoint(m_margin - temp * 0.2, m_margin + temp * 0.5));
    paint.drawLine(QPoint(m_margin, m_margin), QPoint(m_margin + temp * 0.2, m_margin + temp * 0.5));

    //绘制刻度值
    paint.setFont(m_font);
    //横坐标
    for(int i = 0; i < m_horizonlist.size(); i++)
    {
        if(m_margin + i * (m_columnarWidth + m_space) > this->width() - m_margin - temp * 0.5 - m_margin)
            break;
        paint.drawText(QRectF(QPoint(m_margin + i * (m_columnarWidth + m_space), this->height() - m_margin), \
                              QPoint(m_margin + i * (m_columnarWidth + m_space) + m_columnarWidth, this->height() )), \
                       Qt::AlignHCenter, m_horizonlist.at(i));
    }

    //纵坐标
    int height = this->height() - m_margin;
    int i = 0;

    while(height > m_margin + temp * 0.5 + m_verticalScale)
    {
        paint.drawText(QRectF(QPoint(0, this->height() - m_margin - i * (m_verticalToPixel))\
                              , QPoint(m_margin, this->height() - m_margin - i * (m_verticalToPixel) + m_verticalToPixel))
                       , Qt::AlignHCenter, QString("%1").arg(m_verticalStartScale + i * m_verticalScale));
        height -= m_verticalToPixel;
        i++;
    }

    //绘制坐标表示
    //横坐标
    paint.drawText(QRectF(QPointF(this->width() - m_margin - temp * 0.5, this->height() - m_margin), \
                          QPointF(this->width() - m_margin - temp * 0.5 - m_margin, this->height())), Qt::AlignHCenter, m_horiTitle);
    //纵坐标
    paint.drawText(QRectF(QPointF(m_margin, m_margin + temp * 0.5), QPointF(0, m_margin + temp * 0.5 + 100)),
                   Qt::AlignHCenter, m_veriTitle);
    //绘制标题
    paint.drawText(QRectF(QPointF(0, 0), QPointF(this->width(), m_margin)),
                   Qt::AlignHCenter | Qt::AlignVCenter, m_title);
    qDebug() << m_horiTitle;
    //绘制数值
    int j = 0, num = 0;
    for(auto iter = m_dataMap.begin(); iter != m_dataMap.end(); iter++, j++)
    {
        if(iter.value().size() == 1)
            paint.setBrush(m_colorList.at(j));
        num = 0;
        for(int i = 0; i < iter.value().size(); i++)
        {
            if(m_margin + j * (m_space + m_columnarWidth) > this->width() - m_margin - m_margin - 0.5 * temp)
                break;
            if(iter.value().size() > 1)
                paint.setBrush(m_colorList.at(i));

            paint.drawRect(m_margin + j * (m_space + m_columnarWidth), this->height() - m_margin - num\
                           , m_columnarWidth, 0 - iter.value().at(i).toInt());
            num += iter.value().at(i).toInt();
        }
    }
}

