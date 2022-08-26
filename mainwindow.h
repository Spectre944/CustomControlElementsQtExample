#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLayout>
#include <QFrame>
#include <QCheckBox>

#include <customContolElements.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addActionFunc();
    void deleteActionFunc();
    void sortActionFunc();
    void helpActionFunc();

    void saveState();

private slots:
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;

    QMenu *contextMenu;

    QAction *addAction;
    QAction *deleteAction;
    QAction *sortAction;
    QAction *helpAction;

    QFrame *frameSort;
    QVBoxLayout *vLayout;
    QCheckBox *showRadPoints;
    QCheckBox *showChemPoints;
    QCheckBox *showBioPoints;

    CContextMenu *cMenu;
    CFilterFrame *cFilter;
    CMessageFrame *cMessage;
    CPopupNotification *cPopup;

};
#endif // MAINWINDOW_H
