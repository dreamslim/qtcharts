/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef BOXWHISKERS_H
#define BOXWHISKERS_H

#include <private/boxwhiskersdata_p.h>
#include <QtCharts/QChartGlobal>
#include <private/abstractdomain_p.h>
#include <QtCharts/QBoxSet>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsLineItem>
#include <QtWidgets/QGraphicsLayoutItem>
#include <QtGui/QPainterPath>

QT_CHARTS_BEGIN_NAMESPACE

class QBarSet;

class BoxWhiskers : public QGraphicsObject
{
    Q_OBJECT

public:
    BoxWhiskers(QBoxSet *set, AbstractDomain *domain, QGraphicsObject *parent);
    ~BoxWhiskers();

    void setBrush(const QBrush &brush);
    void setPen(const QPen &pen);
    void setLayout(const BoxWhiskersData &data);
    void setBoxOutlined(const bool outlined) { m_boxOutlined = outlined; }
    void setBoxWidth(const qreal width);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    void updateGeometry(AbstractDomain *domain);
protected:
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void setGeometry(const QRectF &rect);

Q_SIGNALS:
    void clicked(QBoxSet *boxset);
    void hovered(bool status, QBoxSet *boxset);

private:
    friend class BoxPlotChartItem;
    friend class BoxPlotAnimation;

    QBoxSet *m_boxSet;
    AbstractDomain *m_domain;
    QPainterPath    m_boxPath;
    QRectF m_boundingRect;
    bool m_hovering;
    bool m_validData;
    QBrush  m_brush;
    QPen m_pen;
    QPen m_medianPen;
    QPen m_outlinePen;
    bool m_boxOutlined;
    qreal m_boxWidth;
    BoxWhiskersData m_data;
    QSizeF m_domainSize;
    QRectF m_middleBox;
    qreal m_geometryMedian;
    qreal m_geometryLeft;
    qreal m_geometryRight;
};

QT_CHARTS_END_NAMESPACE

#endif // BOXWHISKERS_H