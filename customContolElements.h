#ifndef CUSTOMCONTOLELEMENTS_H
#define CUSTOMCONTOLELEMENTS_H

#include <QObject>
#include <QWidget>
#include <QApplication>


#include <QMenu>
#include <QLayout>
#include <QFrame>
#include <QCheckBox>
#include <QLabel>
#include <QScrollArea>
#include <QWidgetAction>
#include <QBitmap>
#include <QScreen>

#include <QDebug>



class CFilterFrame : public QWidget{

    Q_OBJECT

public:

    CFilterFrame(QWidget *parent = nullptr);
    ~CFilterFrame() override;

    void exec(QPoint pos = QPoint(-1, -1));
    void exec(QRect expt, bool vertical = false, QPoint pos = QPoint(-1, -1));

    void hideEvent(QHideEvent *event) override;



signals:



private:

    QFrame *frameSort;
    QVBoxLayout *main_vlayout;
    QVBoxLayout *minorVlayout;
    QCheckBox *showRadPoints;
    QCheckBox *showChemPoints;
    QCheckBox *showBioPoints;

    QRect window_rect;
    int window_height = 0; // 窗口高度，每次打开都更新一次

};

class CMessageItem : public QWidget{

    Q_OBJECT

public:

    CMessageItem(QWidget *parent = nullptr);
    CMessageItem(QWidget *parent = nullptr, QString author = "Unknown", QString txt = "NULL", QString time = "00:00");
    ~CMessageItem();

    //void exec(QPoint pos = QPoint(-1, -1));
    //void exec(QRect expt, bool vertical = false, QPoint pos = QPoint(-1, -1));

    //void hideEvent(QHideEvent *event) override;



signals:



private:

    QVBoxLayout *vLayout;
    QFrame *mainFrame;
    QGridLayout *mainGridLayout;
    QLabel *labelMsgText;
    QLabel *labelAuthor;
    QLabel *labelTime;


//    QRect window_rect;
//    int window_height = 0; // 窗口高度，每次打开都更新一次

};

class CMessageFrame : public QWidget{

    Q_OBJECT

public:

    CMessageFrame(QWidget *parent = nullptr);
    ~CMessageFrame() override;

    void exec(QPoint pos = QPoint(-1, -1));
    void exec(QRect expt, bool vertical = false, QPoint pos = QPoint(-1, -1));

    void hideEvent(QHideEvent *event) override;
    void addMsg(CMessageItem *msg);



signals:



private:

    QVBoxLayout *vLayoutMain;
    QFrame *msgFrame;
    QGridLayout *gridLayout;
    QCheckBox *showMsg;
    QCheckBox *showPoints;
    QCheckBox *showLines;
    QScrollArea *scrollArea;
    QWidget *scrollAreaContents;
    QVBoxLayout *vLayoutMsg;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;


//    QFrame *msgFrame;
//    QScrollArea *scrollArea;
//    QVBoxLayout *main_vlayout;
//    QVBoxLayout *vLayout;
//    QHBoxLayout *hLayout;
//    QCheckBox *showMsg;
//    QCheckBox *showPoints;
//    QCheckBox *showLines;

    QRect window_rect;
    int window_height = 0; // 窗口高度，每次打开都更新一次

};





class CContextMenu : public QWidget{

    Q_OBJECT

public:

    CContextMenu(QWidget *parent = nullptr);
    ~CContextMenu() override;
    void popup(const QPoint &pos, QAction *at = nullptr);

signals:



private:

    QMenu *contextMenu;

//    QCheckBox *checkBoxRad;
//    QCheckBox *checkBoxBio;
//    QCheckBox *checkBoxChem;

//    QWidgetAction *checkableAction1;
//    QWidgetAction *checkableAction2;
//    QWidgetAction *checkableAction3;

    QAction *addAction;
    QAction *deleteAction;
    QAction *sortAction;
    QAction *helpAction;




};

class CPopupNotification : public QWidget{

    Q_OBJECT

public:

    CPopupNotification(QWidget *parent = nullptr);
    ~CPopupNotification() override;

    void exec(QPoint pos = QPoint(-1, -1));
    void exec(QRect expt, bool vertical = false, QPoint pos = QPoint(-1, -1));

signals:



private:


    QGridLayout *gridLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *labelTopic;
    QLabel *label;
    QLabel *labelTextCont;
    QLabel *labelTimeNot;

    QRect window_rect;
    int window_height = 0; // 窗口高度，每次打开都更新一次


};


#endif // CUSTOMCONTOLELEMENTS_H
