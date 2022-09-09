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


#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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

class CColorPallete : public QWidget{

    Q_OBJECT

public:

    CColorPallete(QWidget *parent = nullptr);
    ~CColorPallete() override;



signals:


public:

    QGridLayout *gridLayout_6;
    QFrame *leftMenuFrame;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer;
    QFrame *topBarFrame;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QFrame *appFrame;
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_3;
    QFrame *frame_4;
    QGridLayout *gridLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_4;
    QFrame *frame;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QCheckBox *checkBox;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpinBox *spinBox;
    QSlider *horizontalSlider;
    QTextEdit *textEdit;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_3;
    QWidget *tab_2;
    QGridLayout *gridLayout_5;
    QTableWidget *tableWidget;
    QWidget *page_2;




};


/*

    colorDial->exec();

    switch(index){

        case 0:    mainColor = colorDial->currentColor(); ui->frameColor->setStyleSheet("background:"+QVariant(mainColor).toString()+";"); break;
        case 1:    secondColor = colorDial->currentColor(); ui->frameColor_2->setStyleSheet("background:"+QVariant(secondColor).toString()+";"); break;
        case 2:    ButtonColor  = colorDial->currentColor(); ui->frameColor_3->setStyleSheet("background:"+QVariant(ButtonColor ).toString()+";"); break;
        case 3:    ButtonPressed  = colorDial->currentColor(); ui->frameColor_4->setStyleSheet("background:"+QVariant(ButtonPressed ).toString()+";"); break;
        case 4:    ButtonFocus  = colorDial->currentColor(); ui->frameColor_5->setStyleSheet("background:"+QVariant(ButtonFocus ).toString()+";"); break;
        case 5:    ButtonHover  = colorDial->currentColor(); ui->frameColor_6->setStyleSheet("background:"+QVariant(ButtonHover ).toString()+";"); break;
        case 6:    ButtonGRPressed  = colorDial->currentColor(); ui->frameColor_7->setStyleSheet("background:"+QVariant(ButtonGRPressed ).toString()+";"); break;
        case 7:    ButtonGRHover  = colorDial->currentColor(); ui->frameColor_8->setStyleSheet("background:"+QVariant(ButtonGRHover ).toString()+";"); break;
        case 8:    TabColor  = colorDial->currentColor(); ui->frameColor_9->setStyleSheet("background:"+QVariant(TabColor ).toString()+";"); break;
        case 9:    TabPane  = colorDial->currentColor(); ui->frameColor_10->setStyleSheet("background:"+QVariant(TabPane ).toString()+";"); break;
        case 10:   TabSelected  = colorDial->currentColor(); ui->frameColor_11->setStyleSheet("background:"+QVariant(TabSelected ).toString()+";"); break;
        case 11:   TableViewAlt  = colorDial->currentColor(); ui->frameColor_12->setStyleSheet("background:"+QVariant(TableViewAlt ).toString()+";"); break;
        case 12:   GridLineColor  = colorDial->currentColor(); ui->frameColor_13->setStyleSheet("background:"+QVariant(GridLineColor ).toString()+";"); break;
        case 13:   TableItemSelected  = colorDial->currentColor(); ui->frameColor_14->setStyleSheet("background:"+QVariant(TableItemSelected ).toString()+";"); break;
        case 14:   HeaderViewSection  = colorDial->currentColor(); ui->frameColor_15->setStyleSheet("background:"+QVariant(HeaderViewSection ).toString()+";"); break;
        case 15:   HeaderViewSectionBorder  = colorDial->currentColor(); ui->frameColor_16->setStyleSheet("background:"+QVariant(HeaderViewSectionBorder ).toString()+";"); break;
        case 16:   ScrollBarBG  = colorDial->currentColor(); ui->frameColor_17->setStyleSheet("background:"+QVariant(ScrollBarBG ).toString()+";"); break;
        case 17:   ScrollBarHandle  = colorDial->currentColor(); ui->frameColor_18->setStyleSheet("background:"+QVariant(ScrollBarHandle ).toString()+";"); break;
        case 18:   ProgressBarBG  = colorDial->currentColor(); ui->frameColor_19->setStyleSheet("background:"+QVariant(ProgressBarBG ).toString()+";"); break;
        case 19:   ProgressBarChunk  = colorDial->currentColor(); ui->frameColor_20->setStyleSheet("background:"+QVariant(ProgressBarChunk ).toString()+";"); break;
        case 20:   SpinBoxSection  = colorDial->currentColor(); ui->frameColor_21->setStyleSheet("background:"+QVariant(SpinBoxSection ).toString()+";"); break;
        case 21:   MenuBackground  = colorDial->currentColor(); ui->frameColor_22->setStyleSheet("background:"+QVariant(MenuBackground ).toString()+";"); break;
        case 22:   MenuSelected  = colorDial->currentColor(); ui->frameColor_23->setStyleSheet("background:"+QVariant(MenuSelected ).toString()+";"); break;
        case 23:   MenuBorder  = colorDial->currentColor(); ui->frameColor_24->setStyleSheet("background:"+QVariant(MenuBorder ).toString()+";"); break;
        case 24:    break;
        case 25:    break;
    default: break;


    }
*/
#endif // CUSTOMCONTOLELEMENTS_H
