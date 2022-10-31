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

    //Checkboxes for sorting
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
    scrollArea->setMinimumSize(QSize(400, 600));
    scrollArea->setWidgetResizable(true);
    scrollAreaContents = new QWidget();
    scrollAreaContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
    scrollAreaContents->setGeometry(QRect(0, 0, 426, 423));
    vLayoutMsg = new QVBoxLayout(scrollAreaContents);
    vLayoutMsg->setObjectName(QString::fromUtf8("verticalLayout_2"));


    scrollArea->setWidget(scrollAreaContents);

    gridLayout->addWidget(scrollArea, 1, 0, 1, 3);


    vLayoutMain->addWidget(msgFrame);

    //add vSpacer to push all messages to top
    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    vLayoutMsg->addItem(verticalSpacer);



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
    //vLayoutMsg->addWidget(msg);
    vLayoutMsg->insertWidget(0, msg);
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
    mainFrame->setMaximumHeight(100);

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


//--------------------------------------------------------------------------------------------------------
//  COLOR PALLETE
//--------------------------------------------------------------------------------------------------------

CColorPallete::CColorPallete(QWidget *parent)
{

    if (parent->objectName().isEmpty())
                parent->setObjectName(QString::fromUtf8("centralWidget"));

    this->setStyleSheet(parent->styleSheet());
    this->resize(787, 642);
    gridLayout_6 = new QGridLayout(this);
    gridLayout_6->setSpacing(0);
    gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
    gridLayout_6->setContentsMargins(0, 0, 0, 0);
    leftMenuFrame = new QFrame(this);
    leftMenuFrame->setObjectName(QString::fromUtf8("leftMenuFrame"));
    leftMenuFrame->setMinimumSize(QSize(70, 0));
    leftMenuFrame->setMaximumSize(QSize(70, 16777215));
    leftMenuFrame->setFrameShape(QFrame::StyledPanel);
    leftMenuFrame->setFrameShadow(QFrame::Raised);
    verticalLayout = new QVBoxLayout(leftMenuFrame);
    verticalLayout->setSpacing(5);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    pushButton = new QPushButton(leftMenuFrame);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setMinimumSize(QSize(70, 70));
    pushButton->setMaximumSize(QSize(70, 70));

    verticalLayout->addWidget(pushButton);

    pushButton_2 = new QPushButton(leftMenuFrame);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setMinimumSize(QSize(70, 70));
    pushButton_2->setMaximumSize(QSize(70, 70));

    verticalLayout->addWidget(pushButton_2);

    pushButton_3 = new QPushButton(leftMenuFrame);
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
    pushButton_3->setMinimumSize(QSize(70, 70));
    pushButton_3->setMaximumSize(QSize(70, 70));

    verticalLayout->addWidget(pushButton_3);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);


    gridLayout_6->addWidget(leftMenuFrame, 0, 0, 2, 1);

    topBarFrame = new QFrame(this);
    topBarFrame->setObjectName(QString::fromUtf8("topBarFrame"));
    topBarFrame->setMinimumSize(QSize(0, 70));
    topBarFrame->setMaximumSize(QSize(16777215, 70));
    topBarFrame->setFrameShape(QFrame::StyledPanel);
    topBarFrame->setFrameShadow(QFrame::Raised);
    horizontalLayout_4 = new QHBoxLayout(topBarFrame);
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    label_2 = new QLabel(topBarFrame);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout_4->addWidget(label_2);

    pushButton_6 = new QPushButton(topBarFrame);
    pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
    pushButton_6->setMinimumSize(QSize(50, 50));
    pushButton_6->setMaximumSize(QSize(50, 50));

    horizontalLayout_4->addWidget(pushButton_6);

    pushButton_5 = new QPushButton(topBarFrame);
    pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
    pushButton_5->setMinimumSize(QSize(50, 50));
    pushButton_5->setMaximumSize(QSize(50, 50));

    horizontalLayout_4->addWidget(pushButton_5);


    gridLayout_6->addWidget(topBarFrame, 0, 1, 1, 1);

    appFrame = new QFrame(this);
    appFrame->setObjectName(QString::fromUtf8("appFrame"));
    appFrame->setFrameShape(QFrame::StyledPanel);
    appFrame->setFrameShadow(QFrame::Raised);
    gridLayout_2 = new QGridLayout(appFrame);
    gridLayout_2->setSpacing(0);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    gridLayout_2->setContentsMargins(0, 0, 0, 0);
    stackedWidget = new QStackedWidget(appFrame);
    stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
    page = new QWidget();
    page->setObjectName(QString::fromUtf8("page"));
    gridLayout_3 = new QGridLayout(page);
    gridLayout_3->setSpacing(0);
    gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
    gridLayout_3->setContentsMargins(0, 0, 0, 0);
    frame_4 = new QFrame(page);
    frame_4->setObjectName(QString::fromUtf8("frame_4"));
    frame_4->setFrameShape(QFrame::StyledPanel);
    frame_4->setFrameShadow(QFrame::Raised);
    gridLayout = new QGridLayout(frame_4);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    frame_2 = new QFrame(frame_4);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    frame_2->setFrameShape(QFrame::StyledPanel);
    frame_2->setFrameShadow(QFrame::Raised);
    horizontalLayout_3 = new QHBoxLayout(frame_2);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    label = new QLabel(frame_2);
    label->setObjectName(QString::fromUtf8("label"));

    horizontalLayout_3->addWidget(label);


    gridLayout->addWidget(frame_2, 0, 0, 1, 1);

    tabWidget = new QTabWidget(frame_4);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    gridLayout_4 = new QGridLayout(tab);
    gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    pushButton_4 = new QPushButton(tab);
    pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
    pushButton_4->setMinimumSize(QSize(100, 50));

    horizontalLayout_2->addWidget(pushButton_4);

    frame = new QFrame(tab);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    horizontalLayout_2->addWidget(frame);

    groupBox = new QGroupBox(tab);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));

    horizontalLayout_2->addWidget(groupBox);


    gridLayout_4->addLayout(horizontalLayout_2, 0, 0, 1, 2);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    radioButton = new QRadioButton(tab);
    radioButton->setObjectName(QString::fromUtf8("radioButton"));

    horizontalLayout->addWidget(radioButton);

    checkBox = new QCheckBox(tab);
    checkBox->setObjectName(QString::fromUtf8("checkBox"));

    horizontalLayout->addWidget(checkBox);

    comboBox = new QComboBox(tab);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));

    horizontalLayout->addWidget(comboBox);


    gridLayout_4->addLayout(horizontalLayout, 1, 0, 1, 2);

    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    label_3 = new QLabel(tab);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    horizontalLayout_5->addWidget(label_3);

    spinBox = new QSpinBox(tab);
    spinBox->setObjectName(QString::fromUtf8("spinBox"));

    horizontalLayout_5->addWidget(spinBox);

    horizontalSlider = new QSlider(tab);
    horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
    horizontalSlider->setMaximumSize(QSize(200, 16777215));
    horizontalSlider->setOrientation(Qt::Horizontal);

    horizontalLayout_5->addWidget(horizontalSlider);


    gridLayout_4->addLayout(horizontalLayout_5, 2, 0, 1, 2);

    textEdit = new QTextEdit(tab);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));

    gridLayout_4->addWidget(textEdit, 3, 0, 1, 1);

    scrollArea = new QScrollArea(tab);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setWidgetResizable(true);
    scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 308, 1022));
    verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    frame_3 = new QFrame(scrollAreaWidgetContents);
    frame_3->setObjectName(QString::fromUtf8("frame_3"));
    frame_3->setMinimumSize(QSize(0, 1000));
    frame_3->setFrameShape(QFrame::StyledPanel);
    frame_3->setFrameShadow(QFrame::Raised);

    verticalLayout_2->addWidget(frame_3);

    scrollArea->setWidget(scrollAreaWidgetContents);

    gridLayout_4->addWidget(scrollArea, 3, 1, 1, 1);

    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    gridLayout_5 = new QGridLayout(tab_2);
    gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
    tableWidget = new QTableWidget(tab_2);
    if (tableWidget->columnCount() < 12)
        tableWidget->setColumnCount(12);
    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
    QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
    QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
    QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
    QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
    QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
    QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
    QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
    QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
    QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
    QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
    QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(11, __qtablewidgetitem11);
    if (tableWidget->rowCount() < 9)
        tableWidget->setRowCount(9);
    QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
    tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem12);
    QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
    tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem13);
    QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
    tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem14);
    QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
    tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem15);
    QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
    tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem16);
    QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
    tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem17);
    QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
    tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem18);
    QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
    tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem19);
    QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
    tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem20);
    tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

    gridLayout_5->addWidget(tableWidget, 0, 0, 1, 1);

    tabWidget->addTab(tab_2, QString());

    gridLayout->addWidget(tabWidget, 1, 0, 1, 1);


    gridLayout_3->addWidget(frame_4, 1, 0, 1, 1);

    stackedWidget->addWidget(page);
    page_2 = new QWidget();
    page_2->setObjectName(QString::fromUtf8("page_2"));
    stackedWidget->addWidget(page_2);

    gridLayout_2->addWidget(stackedWidget, 0, 0, 1, 1);


    gridLayout_6->addWidget(appFrame, 1, 1, 1, 1);


    stackedWidget->setCurrentIndex(0);
    tabWidget->setCurrentIndex(0);

    parent->setWindowTitle(QCoreApplication::translate("centralWidget", "Form", nullptr));
    pushButton->setText(QString());
    pushButton_2->setText(QString());
    pushButton_3->setText(QString());
    label_2->setText(QCoreApplication::translate("centralWidget", "Name", nullptr));
    pushButton_6->setText(QString());
    pushButton_5->setText(QString());
    label->setText(QCoreApplication::translate("centralWidget", "Page", nullptr));
    pushButton_4->setText(QCoreApplication::translate("centralWidget", "PushButton", nullptr));
    groupBox->setTitle(QCoreApplication::translate("centralWidget", "GroupBox", nullptr));
    radioButton->setText(QCoreApplication::translate("centralWidget", "RadioButton", nullptr));
    checkBox->setText(QCoreApplication::translate("centralWidget", "CheckBox", nullptr));
    label_3->setText(QCoreApplication::translate("centralWidget", "TextLabel", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("centralWidget", "Tab 1", nullptr));
    QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
    ___qtablewidgetitem->setText(QCoreApplication::translate("centralWidget", "New Column", nullptr));
    QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
    ___qtablewidgetitem1->setText(QCoreApplication::translate("centralWidget", "New Column", nullptr));
    QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
    ___qtablewidgetitem2->setText(QCoreApplication::translate("centralWidget", "New Column", nullptr));
    QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
    ___qtablewidgetitem3->setText(QCoreApplication::translate("centralWidget", "New Column", nullptr));
    QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
    ___qtablewidgetitem4->setText(QCoreApplication::translate("centralWidget", "New Column", nullptr));
    QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
    ___qtablewidgetitem5->setText(QCoreApplication::translate("centralWidget", "New Column", nullptr));
    QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
    ___qtablewidgetitem6->setText(QCoreApplication::translate("centralWidget", "New Column", nullptr));
    QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
    ___qtablewidgetitem7->setText(QCoreApplication::translate("centralWidget", "New Column", nullptr));
    QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
    ___qtablewidgetitem8->setText(QCoreApplication::translate("centralWidget", "New Column", nullptr));
    QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
    ___qtablewidgetitem9->setText(QCoreApplication::translate("centralWidget", "New Column", nullptr));
    QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
    ___qtablewidgetitem10->setText(QCoreApplication::translate("centralWidget", "New Column", nullptr));
    QTableWidgetItem *___qtablewidgetitem11 = tableWidget->horizontalHeaderItem(11);
    ___qtablewidgetitem11->setText(QCoreApplication::translate("centralWidget", "New Column", nullptr));
    QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(0);
    ___qtablewidgetitem12->setText(QCoreApplication::translate("centralWidget", "New Row", nullptr));
    QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(1);
    ___qtablewidgetitem13->setText(QCoreApplication::translate("centralWidget", "New Row", nullptr));
    QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(2);
    ___qtablewidgetitem14->setText(QCoreApplication::translate("centralWidget", "New Row", nullptr));
    QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(3);
    ___qtablewidgetitem15->setText(QCoreApplication::translate("centralWidget", "New Row", nullptr));
    QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(4);
    ___qtablewidgetitem16->setText(QCoreApplication::translate("centralWidget", "New Row", nullptr));
    QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(5);
    ___qtablewidgetitem17->setText(QCoreApplication::translate("centralWidget", "New Row", nullptr));
    QTableWidgetItem *___qtablewidgetitem18 = tableWidget->verticalHeaderItem(6);
    ___qtablewidgetitem18->setText(QCoreApplication::translate("centralWidget", "New Row", nullptr));
    QTableWidgetItem *___qtablewidgetitem19 = tableWidget->verticalHeaderItem(7);
    ___qtablewidgetitem19->setText(QCoreApplication::translate("centralWidget", "New Row", nullptr));
    QTableWidgetItem *___qtablewidgetitem20 = tableWidget->verticalHeaderItem(8);
    ___qtablewidgetitem20->setText(QCoreApplication::translate("centralWidget", "New Row", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("centralWidget", "Tab 2", nullptr));

       setLayout(gridLayout);
}

CColorPallete::~CColorPallete()
{

}

CLoadingScreen::CLoadingScreen(QWidget *parent)
{

    this->setObjectName("customFrameWindowMsg");
    this->setStyleSheet(parent->styleSheet());

    //setWindowFlag(Qt::Popup, true);

    //For adjust size window
    QScreen *screen = QGuiApplication::primaryScreen();
    window_rect = screen->availableGeometry();
    window_height = window_rect.height();

    this->setMinimumSize(QSize(940, 400));


    this->setLayoutDirection(Qt::LeftToRight);
    this->setStyleSheet(QString::fromUtf8("background-image: url(:/Sun.jpg);"));

    gridLayout = new QGridLayout(parent);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setHorizontalSpacing(0);
    gridLayout->setVerticalSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    labelInfo = new QLabel(parent);
    labelInfo->setObjectName(QString::fromUtf8("labelIco"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(labelInfo->sizePolicy().hasHeightForWidth());
    labelInfo->setSizePolicy(sizePolicy);
    labelInfo->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                              "font: 16pt \"Segoe UI\";"));
    labelInfo->setAlignment(Qt::AlignBottom|Qt::AlignRight|Qt::AlignTrailing);
    labelInfo->setText("...Завантаження");

    gridLayout->addWidget(labelInfo, 0, 0, 1, 1);



    progressBar = new QProgressBar(parent);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
    progressBar->setValue(24);

    gridLayout->addWidget(progressBar, 2, 0, 1, 1);


    //set main layout to form window
    setLayout(gridLayout);
}

CLoadingScreen::~CLoadingScreen()
{

}

void CLoadingScreen::exec(QPoint pos)
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
