/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qboxset.h"
#include "qboxset_p.h"
#include "charthelpers_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    Constructs QBoxSet with parent of \a parent
*/
QBoxSet::QBoxSet(QObject *parent)
    : QObject(parent),
      d_ptr(new QBoxSetPrivate(this))
{
}

QBoxSet::QBoxSet(qreal value1, qreal value2, qreal value3, qreal value4, qreal value5, QObject *parent)
    : QObject(parent),
      d_ptr(new QBoxSetPrivate(this))
{
    d_ptr->append(value1);
    d_ptr->append(value2);
    d_ptr->append(value3);
    d_ptr->append(value4);
    d_ptr->append(value5);
}

/*!
    Destroys the boxset
*/
QBoxSet::~QBoxSet()
{
    // NOTE: d_ptr destroyed by QObject
}

/*!
    Appends new value \a value to the end of set.
*/
void QBoxSet::append(const qreal value)
{
    int index = d_ptr->m_values.count();
    d_ptr->append(value);

    emit valuesAdded(index, 1);
}

/*!
    Appends a list of reals to set. Works like append with single real value. The \a values in list
    are appended to end of boxset
    \sa append()
*/
void QBoxSet::append(const QList<qreal> &values)
{
    int index = d_ptr->m_values.count();
    d_ptr->append(values);
    emit valuesAdded(index, values.count());
}

/*!
    Sets new value \a value as the lower extreme for the set.
*/
void QBoxSet::setLowerExtreme(const qreal value)
{
    d_ptr->replace(QBoxSetPrivate::PosLowerExtreme, value);
    emit valueChanged(QBoxSetPrivate::PosLowerExtreme);
}

/*!
    Returns the lower extreme value of the set.
*/
qreal QBoxSet::lowerExtreme()
{
    return d_ptr->m_values.at(QBoxSetPrivate::PosLowerExtreme);
}

/*!
    Sets new value \a value as the lower quartile for the set.
*/
void QBoxSet::setLowerQuartile(const qreal value)
{
    d_ptr->replace(QBoxSetPrivate::PosLowerQuartile, value);
    emit valueChanged(QBoxSetPrivate::PosLowerQuartile);
}

/*!
    Returns the lower quartile value of the set.
*/
qreal QBoxSet::lowerQuartile()
{
    return d_ptr->m_values.at(QBoxSetPrivate::PosLowerQuartile);
}

/*!
    Sets new value \a value as the median for the set.
*/
void QBoxSet::setMedian(const qreal value)
{
    d_ptr->replace(QBoxSetPrivate::PosMedian, value);
    emit valueChanged(QBoxSetPrivate::PosMedian);
}

/*!
    Returns the median value of the set.
*/
qreal QBoxSet::median()
{
    return d_ptr->m_values.at(QBoxSetPrivate::PosMedian);
}

/*!
    Sets new value \a value as the upper quartile for the set.
*/
void QBoxSet::setUpperQuartile(const qreal value)
{
    d_ptr->replace(QBoxSetPrivate::PosUpperQuartile, value);
    emit valueChanged(QBoxSetPrivate::PosUpperQuartile);
}

/*!
    Returns the upper quartile value of the set.
*/
qreal QBoxSet::upperQuartile()
{
    return d_ptr->m_values.at(QBoxSetPrivate::PosUpperQuartile);
}

/*!
    Sets new value \a value as the upper extreme for the set.
*/
void QBoxSet::setUpperExtreme(const qreal value)
{
    d_ptr->replace(QBoxSetPrivate::PosUpperQuartile, value);
    emit valueChanged(QBoxSetPrivate::PosUpperQuartile);
}

/*!
    Returns the upper extreme value of the set.
*/
qreal QBoxSet::upperExtreme()
{
    return d_ptr->m_values.at(QBoxSetPrivate::PosUpperExtreme);
}

/*!
    Convenience operator. Same as append, with real \a value.
    \sa append()
*/
QBoxSet &QBoxSet::operator << (const qreal &value)
{
    append(value);
    return *this;
}

/*!
    Inserts new \a value on the \a index position.
    The value that is currently at this postion is moved to postion index + 1
    \sa remove()
*/
void QBoxSet::insert(const int index, const qreal value)
{
    d_ptr->insert(index, value);
    emit valuesAdded(index, 1);
}

/*!
    Removes \a count number of values from the set starting at \a index.
    \sa insert()
*/
void QBoxSet::remove(const int index, const int count)
{
    int removedCount = d_ptr->remove(index, count);
    if (removedCount > 0)
        emit valuesRemoved(index, removedCount);
    return;
}

/*!
    Sets a new value \a value to set, indexed by \a index
*/
void QBoxSet::replace(const int index, const qreal value)
{
    if (index >= 0 && index < d_ptr->m_values.count()) {
        d_ptr->replace(index, value);
        emit valueChanged(index);
    }
}


/*!
    Returns value of set indexed by \a index.
    If the index is out of bounds 0.0 is returned.
*/
qreal QBoxSet::at(const int index) const
{
    if (index < 0 || index >= d_ptr->m_values.count())
        return 0;
    return d_ptr->m_values.at(index);
}

/*!
    Returns value of set indexed by \a index.
    If the index is out of bounds 0.0 is returned.
*/
qreal QBoxSet::operator [](const int index) const
{
    return at(index);
}

/*!
    Returns count of values in set.
*/
int QBoxSet::count() const
{
    return d_ptr->m_values.count();
}

/*!
    Sets pen for set. Boxes of this set are drawn using \a pen
*/
void QBoxSet::setPen(const QPen &pen)
{
    if (d_ptr->m_pen != pen) {
        d_ptr->m_pen = pen;
        emit d_ptr->updatedBox();
        emit penChanged();
    }
}

/*!
    Returns pen of the set.
*/
QPen QBoxSet::pen() const
{
    return d_ptr->m_pen;
}

/*!
    Sets brush for the set. Boxes of this set are drawn using \a brush
*/
void QBoxSet::setBrush(const QBrush &brush)
{
    if (d_ptr->m_brush != brush) {
        d_ptr->m_brush = brush;
        emit d_ptr->updatedBox();
        emit brushChanged();
    }
}

/*!
    Returns brush of the set.
*/
QBrush QBoxSet::brush() const
{
    return d_ptr->m_brush;
}

/*!
    Returns the color of the brush of boxset.
*/
QColor QBoxSet::color()
{
    return brush().color();
}

/*!
    Sets the \a color of brush for this boxset
*/
void QBoxSet::setColor(QColor color)
{
    QBrush b = brush();
    if ((b.color() != color) || (b.style() == Qt::NoBrush)) {
        b.setColor(color);
        if (b.style() == Qt::NoBrush) {
            // Set tyle to Qt::SolidPattern. (Default is Qt::NoBrush)
            // This prevents theme to override color defined in QML side:
            // BoxSet { label: "Bob"; color:"red"; values: [1,2,3] }
            // The color must be obeyed, since user wanted it.
            b.setStyle(Qt::SolidPattern);
        }
        setBrush(b);
        emit colorChanged(color);
    }
}

/*!
    Returns the color of pen of this boxset
*/
QColor QBoxSet::borderColor()
{
    return pen().color();
}

/*!
    Sets the color of pen for this boxset
*/
void QBoxSet::setBorderColor(QColor color)
{
    QPen p = pen();
    if (p.color() != color) {
        p.setColor(color);
        setPen(p);
        emit borderColorChanged(color);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBoxSetPrivate::QBoxSetPrivate(QBoxSet *parent) : QObject(parent),
    q_ptr(parent),
    m_pen(QPen(Qt::NoPen)),
    m_brush(QBrush(Qt::NoBrush))
{
}

QBoxSetPrivate::~QBoxSetPrivate()
{
}

void QBoxSetPrivate::append(qreal value)
{
    if (isValidValue(value)) {
        m_values.append(value);
        emit restructuredBox();
    }
}

void QBoxSetPrivate::append(QList<qreal> values)
{
    for (int i = 0; i < values.count(); i++) {
        if (isValidValue(values.at(i)))
            m_values.append(values.at(i));
    }
    emit restructuredBox();
}

void QBoxSetPrivate::insert(const int index, const qreal value)
{
    if (isValidValue(value)) {
        m_values.insert(index, value);
        emit restructuredBox();
    }
}

int QBoxSetPrivate::remove(const int index, const int count)
{
    int removeCount = count;

    if ((index < 0) || (m_values.count() == 0))
        return 0; // Invalid index or not values in list, remove nothing.
    else if ((index + count) > m_values.count())
        removeCount = m_values.count() - index; // Trying to remove more items than list has. Limit amount to be removed.

    int c = 0;
    while (c < removeCount) {
        m_values.removeAt(index);
        c++;
    }
    emit restructuredBox();
    return removeCount;
}

void QBoxSetPrivate::replace(const int index, const qreal value)
{
    m_values.replace(index, value);
    emit updatedLayout();
}

qreal QBoxSetPrivate::value(const int index)
{
    if (index < 0 || index >= m_values.count())
        return 0;
    return m_values.at(index);
}

#include "moc_qboxset.cpp"
#include "moc_qboxset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE