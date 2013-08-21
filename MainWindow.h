#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMenu>

#include <QDate>

#include "MonthPlug.h"
#include "WeekPlug.h"
#include "AgendaPlug.h"
#include "TodosPlug.h"
#include "JournalsPlug.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.nokia.calendar")

public:
    MainWindow(bool runInBackground);

    void setPlug(Plug *plug);

public slots:
    Q_SCRIPTABLE void top_application();

private:
    QMenu *windowMenu;

    MonthPlug *monthPlug;
    WeekPlug *weekPlug;
    AgendaPlug *agendaPlug;
    TodosPlug *todosPlug;
    JournalsPlug *journalsPlug;

    Plug *currentPlug;

    QAction *monthAction;
    QAction *weekAction;
    QAction *agendaAction;
    QAction *todosAction;
    QAction *journalsAction;
    QAction *settingsAction;

    QActionGroup *plugGroup;

    QLayout *mainLayout;

    bool runInBackground;

    void closeEvent(QCloseEvent *e);
    void changeEvent(QEvent *e);

    void deleteOldComponents();

private slots:
    void showMonth();
    void showWeek(QDate date = QDate());
    void showAgenda();
    void showTodos();
    void showJournals();

    void openSettings();
};

#endif // MAINWINDOW_H
