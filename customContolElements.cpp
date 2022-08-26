#include <customContolElements.h>


//--------------------------------------------------------------------------------------------------------
//  CONTEXT MENU
//--------------------------------------------------------------------------------------------------------
CContextMenu::CContextMenu(QWidget *parent) : QWidget(parent)
{

    //Context menu for PointTable
    contextMenu = new QMenu(this);

    //copy styleSheet from parrent
    //if parent wasnt given as arg - it causes crash, so we checking if parent has styleSheet
    if(!parent->styleSheet().isEmpty())
        contextMenu->setStyleSheet(parent->styleSheet());
    /*
    //adding sorting checkboxes
    checkBoxRad = new QCheckBox(contextMenu);
    checkBoxBio = new QCheckBox(contextMenu);
    checkBoxChem = new QCheckBox(contextMenu);

    checkBoxRad->setText("\nРадіаційна небезпека\n");
    checkBoxBio->setText("\nХімічна небезпека\n");
    checkBoxChem->setText("\nБіологічна небезпека\n");


    //checkbleAction to place it in QMenu
    checkableAction1 = new QWidgetAction(contextMenu);
    checkableAction2 = new QWidgetAction(contextMenu);
    checkableAction3 = new QWidgetAction(contextMenu);

    checkableAction1->setDefaultWidget(checkBoxRad);
    checkableAction2->setDefaultWidget(checkBoxBio);
    checkableAction3->setDefaultWidget(checkBoxChem);





//    //connect actions to functions
//    connect(addAction, &QAction::triggered,
//          this, &MainWindow::addActionFunc);
//    connect(addAction, &QAction::triggered,
//          this, &MainWindow::deleteActionFunc);
//    connect(addAction, &QAction::triggered,
//          this, &MainWindow::sortActionFunc);
//    connect(addAction, &QAction::triggered,
//          this, &MainWindow::helpActionFunc);


    //adding checkboxes and other elements
    contextMenu->addAction(checkableAction1);
    contextMenu->addAction(checkableAction2);
    contextMenu->addAction(checkableAction3);
   */
    //Actions for Context menu
    addAction = new QAction("Додати");
    deleteAction = new QAction("Видалити");
    sortAction = new QAction("Сортувати");
    helpAction = new QAction("Допомога");

    contextMenu->addSeparator();
    contextMenu->addAction(addAction);
    contextMenu->addAction(deleteAction);
    contextMenu->addAction(sortAction);

    contextMenu->addSeparator();
    contextMenu->addAction(helpAction);
}

CContextMenu::~CContextMenu()
{

}

void CContextMenu::popup(const QPoint &pos, QAction *at)
{
    contextMenu->popup(pos);
}


//--------------------------------------------------------------------------------------------------------
//  FILTER FRAME
//--------------------------------------------------------------------------------------------------------
CFilterFrame::CFilterFrame(QWidget *parent)
{
    this->setObjectName("customFrameWindow");
    this->setStyleSheet(parent->styleSheet());

    setWindowFlag(Qt::Popup, true);
    setAttribute(Qt::WA_StyledBackground);
    //setAttribute(Qt::WA_DeleteOnClose, true);
    setFocusPolicy(Qt::StrongFocus);
    setAutoFillBackground(false);

    //For adjust size window
    QScreen *screen = QGuiApplication::primaryScreen();
    window_rect = screen->availableGeometry();
    window_height = window_rect.height();

    //create Frame to show and layout
    main_vlayout  = new QVBoxLayout(parent);
    //properties
    //main_vlayout->setSpacing(0);
    main_vlayout->setMargin(5);

    frameSort = new QFrame(parent);

    showRadPoints = new QCheckBox("\nРадіаційна небезпека\n", frameSort);
    showChemPoints = new QCheckBox("\nХімічна небезпека\n", frameSort);
    showBioPoints = new QCheckBox("\nБіологічна небезпека\n", frameSort);

    main_vlayout ->addWidget(showRadPoints);
    main_vlayout ->addWidget(showChemPoints);
    main_vlayout ->addWidget(showBioPoints);

    setLayout(main_vlayout);

}

CFilterFrame::~CFilterFrame()
{
    //connectin closing event for save checkbox state
    qDebug() << "CFilterFrame destroyed";
}

void CFilterFrame::exec(QPoint pos)
{
    if (pos == QPoint(-1,-1))
         pos = QCursor::pos();
     QPoint originPos = pos; // 不包含像素偏移的原始点
     main_vlayout->setEnabled(true);
     main_vlayout->activate(); // 先调整所有控件大小
     this->adjustSize();

     // setAttribute(Qt::WA_DontShowOnScreen); // 会触发 setMouseGrabEnabled 错误
     // show();
     // hide(); // 直接显示吧
     // setAttribute(Qt::WA_DontShowOnScreen, false);

     int x = pos.x() + 1;
     int y = pos.y() + 1;
     int w = width() + 1;
     int h = height() + 1;
     QRect avai = window_rect; // 屏幕大小

     // 如果超过范围，则调整位置
     if (x + w > avai.right())
         x = avai.right() - w;
     if (y + h > avai.bottom())
         y = avai.bottom() - h;
     if (x >= w && pos.x() + w > avai.right())
         x = originPos.x() - w;
     if (y >= h && pos.y() + h > avai.bottom())
         y = originPos.y() - h;

     // 移动窗口
     move(QPoint(x, y));

     QWidget::show();
     setFocus();
}

void CFilterFrame::hideEvent(QHideEvent *event)
{
    qDebug() << "CFilterFrame hide event";
}


//--------------------------------------------------------------------------------------------------------
//  MESSAGE FRAME
//--------------------------------------------------------------------------------------------------------
CMessageFrame::CMessageFrame(QWidget *parent)
{
    //parent->resize(800, 800);


    this->setObjectName("customFrameWindow");
    this->setStyleSheet(parent->styleSheet());

    setWindowFlag(Qt::Popup, true);

    //For adjust size window
    QScreen *screen = QGuiApplication::primaryScreen();
    window_rect = screen->availableGeometry();
    window_height = window_rect.height();

    parent->resize(452, 478);
    vLayoutMain = new QVBoxLayout(parent);
    vLayoutMain->setSpacing(0);
    vLayoutMain->setObjectName(QString::fromUtf8("verticalLayout"));
    vLayoutMain->setContentsMargins(0, 0, 0, 0);
    msgFrame = new QFrame(parent);
    msgFrame->setObjectName(QString::fromUtf8("mFrame"));
    msgFrame->setFrameShape(QFrame::StyledPanel);
    msgFrame->setFrameShadow(QFrame::Raised);
    gridLayout = new QGridLayout(msgFrame);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    showMsg = new QCheckBox("\n  Повідомлення  \n", msgFrame);
    showMsg->setObjectName(QString::fromUtf8("checkBox"));

    gridLayout->addWidget(showMsg, 0, 0, 1, 1);

    showPoints = new QCheckBox("\n  Точки  \n", msgFrame);
    showPoints->setObjectName(QString::fromUtf8("checkBox_2"));

    gridLayout->addWidget(showPoints, 0, 1, 1, 1);

    showLines = new QCheckBox("\n  Рубежі  \n", msgFrame);
    showLines->setObjectName(QString::fromUtf8("checkBox_3"));

    gridLayout->addWidget(showLines, 0, 2, 1, 1);

    scrollArea = new QScrollArea(msgFrame);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setWidgetResizable(true);
    scrollAreaContents = new QWidget();
    scrollAreaContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
    scrollAreaContents->setGeometry(QRect(0, 0, 426, 423));
    vLayoutMsg = new QVBoxLayout(scrollAreaContents);
    vLayoutMsg->setObjectName(QString::fromUtf8("verticalLayout_2"));


    scrollArea->setWidget(scrollAreaContents);

    gridLayout->addWidget(scrollArea, 1, 0, 1, 3);


    vLayoutMain->addWidget(msgFrame);

/*
    setWindowFlag(Qt::Popup, true);
    setAttribute(Qt::WA_StyledBackground);
    //setAttribute(Qt::WA_DeleteOnClose, true);
    setFocusPolicy(Qt::StrongFocus);
    setAutoFillBackground(false);

    //For adjust size window
    QScreen *screen = QGuiApplication::primaryScreen();
    window_rect = screen->availableGeometry();
    window_height = window_rect.height();




    vLayoutMain = new QVBoxLayout(parent);
    vLayoutMain->setSpacing(0);
    vLayoutMain->setContentsMargins(0, 0, 0, 0);

    msgFrame = new QFrame(parent);
    msgFrame->setFrameShape(QFrame::StyledPanel);
    msgFrame->setFrameShadow(QFrame::Raised);
    //msgFrame->setGeometry(0,0,400,800);
    //msgFrame->setMinimumSize(400,800);

    gridLayout = new QGridLayout(msgFrame);

    showMsg = new QCheckBox("\n  Повідомлення  \n", msgFrame);
    showPoints = new QCheckBox("\n  Точки  \n", msgFrame);
    showLines = new QCheckBox("\n  Рубежі  \n", msgFrame);

    gridLayout->addWidget(showMsg,    0, 0, 1, 1);
    gridLayout->addWidget(showPoints, 0, 1, 1, 1);
    gridLayout->addWidget(showLines,  0, 2, 1, 1);

    scrollArea = new QScrollArea(msgFrame);
    scrollArea->setWidgetResizable(true);
    scrollAreaContents = new QWidget();
    scrollAreaContents->setGeometry(QRect(0, 0, 400, 800));

    vLayoutMsg = new QVBoxLayout(scrollAreaContents);

    gridLayout->addWidget(scrollArea, 1, 0, 1, 3);


    scrollArea->setWidget(scrollAreaContents);

    gridLayout->addWidget(scrollArea, 1, 0, 1, 3);

    */
    //vLayoutMain->addWidget(msgFrame);


    /*
    //Vlayout of main frame that containts all elements
    main_vlayout = new QVBoxLayout(parent);
    //properties
    //main_vlayout->setSpacing(0);
    main_vlayout->setMargin(5);

    //main frame
    msgFrame = new QFrame(parent);


    //container of Frame
    vLayout = new QVBoxLayout(msgFrame);
    //container of Checkboxes
    hLayout = new QHBoxLayout(msgFrame);

    showMsg = new QCheckBox("\n  Повідомлення  \n", msgFrame);
    showPoints = new QCheckBox("\n  Точки  \n", msgFrame);
    showLines = new QCheckBox("\n  Рубежі  \n", msgFrame);

    //main_vlayout->addWidget(msgFrame);
    hLayout->addWidget(showMsg);
    hLayout->addWidget(showPoints);
    hLayout->addWidget(showLines);

    main_vlayout->addItem(hLayout);
    main_vlayout->addWidget(scrollArea);

    scrollArea->setGeometry(10, 10, 200,600);
    scrollArea->setLayout(vLayout);


    CMessageItem *msgLable1 = new CMessageItem(msgFrame,"Kiev","\tIf you don't know which release to download, you probably will want"
                                                               "\n to download the BL3SaveEditor-Portable.zip. Then if that doesn't work, "
                                                               "\nyou should try the BL3SaveEditor.zip version of the release.","12:00");
    CMessageItem *msgLable2 = new CMessageItem(msgFrame,"Odessa","\tClick Open, then you can select either a profile (profile.sav) \nor a game save ([NUMBERS].sav).","12:01");
    CMessageItem *msgLable3 = new CMessageItem(msgFrame,"Bravo","\tYou can now edit your profile or game save to your hearts content!","12:02");
    CMessageItem *msgLable4 = new CMessageItem(msgFrame,"Charlie","\tNow save your profile/save! Profit!!!","12:03");

    vLayout->addWidget(msgLable1);
    vLayout->addWidget(msgLable2);
    vLayout->addWidget(msgLable3);
    vLayout->addWidget(msgLable4);
    */

    setLayout(gridLayout);

}

CMessageFrame::~CMessageFrame()
{

}

void CMessageFrame::exec(QPoint pos)
{
    if (pos == QPoint(-1,-1))
         pos = QCursor::pos();
     QPoint originPos = pos; // 不包含像素偏移的原始点
     vLayoutMain->setEnabled(true);
     vLayoutMain->activate(); // 先调整所有控件大小
     this->adjustSize();

     // setAttribute(Qt::WA_DontShowOnScreen); // 会触发 setMouseGrabEnabled 错误
     // show();
     // hide(); // 直接显示吧
     // setAttribute(Qt::WA_DontShowOnScreen, false);

     int x = pos.x() + 1;
     int y = pos.y() + 1;
     int w = width() + 1;
     int h = height() + 1;
     QRect avai = window_rect; // 屏幕大小

     // 如果超过范围，则调整位置
     if (x + w > avai.right())
         x = avai.right() - w;
     if (y + h > avai.bottom())
         y = avai.bottom() - h;
     if (x >= w && pos.x() + w > avai.right())
         x = originPos.x() - w;
     if (y >= h && pos.y() + h > avai.bottom())
         y = originPos.y() - h;

     // 移动窗口
     move(QPoint(x, y));

     QWidget::show();
     setFocus();
}

void CMessageFrame::hideEvent(QHideEvent *event)
{

}

void CMessageFrame::addMsg(CMessageItem *msg)
{
    vLayoutMsg->addWidget(msg);
}

//--------------------------------------------------------------------------------------------------------
//  MESSAGE ITEM
//--------------------------------------------------------------------------------------------------------
CMessageItem::CMessageItem(QWidget *parent)
{

}

CMessageItem::CMessageItem(QWidget *parent, QString author, QString txt, QString time)
{

    this->setObjectName("customFrameWindowMsg");
    this->setStyleSheet(parent->styleSheet());



    vLayout = new QVBoxLayout(parent);
    vLayout->setSpacing(5);
    vLayout->setMargin(5);

    mainFrame = new QFrame(parent);
    mainFrame->setMinimumHeight(100);

    mainGridLayout = new QGridLayout(mainFrame);
    mainGridLayout->setSpacing(5);
    mainGridLayout->setMargin(5);

    labelMsgText = new QLabel(txt, mainFrame);
    mainGridLayout->addWidget(labelMsgText, 1, 0, 1, 2);

    labelAuthor = new QLabel(author, mainFrame);
    labelAuthor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    mainGridLayout->addWidget(labelAuthor, 0, 0, 1, 1);

    labelTime = new QLabel(time, mainFrame);
    mainGridLayout->addWidget(labelTime, 0, 1, 1, 1);
    labelTime->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

    vLayout->addWidget(mainFrame);

    setLayout(vLayout);
}

CMessageItem::~CMessageItem()
{

}

//--------------------------------------------------------------------------------------------------------
//  POPUP NOTIFICATION
//--------------------------------------------------------------------------------------------------------

CPopupNotification::CPopupNotification(QWidget *parent)
{
    this->setObjectName("customFrameWindowMsg");
    this->setStyleSheet(parent->styleSheet());

    setWindowFlag(Qt::Popup, true);

    //For adjust size window
    QScreen *screen = QGuiApplication::primaryScreen();
    window_rect = screen->availableGeometry();
    window_height = window_rect.height();

    gridLayout = new QGridLayout(parent);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    frame = new QFrame(parent);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    gridLayout_2 = new QGridLayout(frame);
    gridLayout_2->setHorizontalSpacing(40);
    gridLayout_2->setVerticalSpacing(0);
    gridLayout_2->setContentsMargins(20, 0, 0, 0);

    labelTopic = new QLabel("Topic",frame);
    labelTopic->setObjectName(QString::fromUtf8("label_2"));

    gridLayout_2->addWidget(labelTopic, 0, 1, 1, 1);

    label = new QLabel("ico",frame);
    label->setObjectName(QString::fromUtf8("label"));
    label->setMinimumSize(QSize(50, 50));
    label->setMaximumSize(QSize(50, 50));

    gridLayout_2->addWidget(label, 1, 0, 1, 1);

    labelTextCont = new QLabel("Content\nSAdasfsdfsfsdfsdfs fsdfdfvsfdfvsfvsfsdfsf",frame);
    labelTextCont->setObjectName(QString::fromUtf8("labelTextCont"));

    gridLayout_2->addWidget(labelTextCont, 1, 1, 1, 1);

    labelTimeNot = new QLabel("Time",frame);
    labelTimeNot->setObjectName(QString::fromUtf8("labelTimeNot"));

    gridLayout_2->addWidget(labelTimeNot, 2, 1, 1, 1);


    gridLayout->addWidget(frame, 0, 0, 1, 1);

    setLayout(gridLayout);
}

CPopupNotification::~CPopupNotification()
{

}

void CPopupNotification::exec(QPoint pos)
{
    if (pos == QPoint(-1,-1))
         pos = QCursor::pos();
     QPoint originPos = pos; // 不包含像素偏移的原始点
     gridLayout->setEnabled(true);
     gridLayout->activate(); // 先调整所有控件大小
     this->adjustSize();

     // setAttribute(Qt::WA_DontShowOnScreen); // 会触发 setMouseGrabEnabled 错误
     // show();
     // hide(); // 直接显示吧
     // setAttribute(Qt::WA_DontShowOnScreen, false);

     int x = pos.x() + 1;
     int y = pos.y() + 1;
     int w = width() + 1;
     int h = height() + 1;
     QRect avai = window_rect; // 屏幕大小

     // 如果超过范围，则调整位置
     if (x + w > avai.right())
         x = avai.right() - w;
     if (y + h > avai.bottom())
         y = avai.bottom() - h;
     if (x >= w && pos.x() + w > avai.right())
         x = originPos.x() - w;
     if (y >= h && pos.y() + h > avai.bottom())
         y = originPos.y() - h;

     // 移动窗口
     move(QPoint(x, y));

     QWidget::show();
     setFocus();
}
