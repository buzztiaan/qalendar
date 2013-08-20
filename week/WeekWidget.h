#ifndef WEEKWIDGET_H
#define WEEKWIDGET_H

#include <QWidget>

#include <QDate>
#include <QDateTime>
#include <QMouseEvent>
#include <QPainter>

#include <CComponent.h>

#include <vector>
#include <map>

#include "ComponentInstance.h"
#include "WeekProfile.h"
#include "WeekHintProfile.h"

namespace Metrics
{
    namespace WeekWidget
    {
        const int NumWeekdays = 7;
        const int TimeWidth = 62;
        const int SwipeThold = 140;
    }
}

class WeekWidget : public QWidget
{
    Q_OBJECT

    // Allow the component widget to drectly emit signals from this class to
    // reduce the number of signal-slot connections, which otherwise could
    // be very high
    friend class ComponentWidget;

    // Allow week hint widgets to access hint profiles
    friend class WeekHintWidget;

public:
    WeekWidget(QWidget *parent = 0);
    ~WeekWidget();

    QSize sizeHint() const;

    void setDate(QDate date);
    QDate firstDate();
    QDate lastDate();

signals:
    void swipedPrev();
    void swipedNext();

private:
    QDate date;

    int allDaySlots;
    WeekProfile weekProfile;
    WeekHintProfile hintProfile;

    QDateTime pressedDate;
    QPoint pressedPoint;
    bool pressedAllDay;

    void cleanup();
    void reload();
    void populateAllDay();
    void populate();

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    QDateTime mapToDate(const QPoint &pos);
    bool inAllDay(const QPoint &pos);
    void forgetPress();

    int allDayRowHeight() const;

    void renderRow(int hour, int baseY, QPainter &painter);

    vector<CComponent*> components;
    vector<CComponent*> allDayComponents;
    vector<ComponentInstance*> instances;
    vector<ComponentInstance*> allDayInstances;
    vector<ComponentWidget*> componentWidgets;
    map<int,int> palette;
};

#endif // WEEKWIDGET_H
