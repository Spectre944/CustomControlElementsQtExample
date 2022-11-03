#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QCheckBox>
#include <QWidgetAction>

#include <QBitmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //call menu by rignt click on table
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(ui->tableWidget, &QMenu::customContextMenuRequested,
                this, &MainWindow::on_tableWidget_customContextMenuRequested);
/*
    QCheckBox *checkBox1 = new QCheckBox(contextMenu);
    QCheckBox *checkBox2 = new QCheckBox(contextMenu);
    QCheckBox *checkBox3 = new QCheckBox(contextMenu);

    QWidgetAction *checkableAction1 = new QWidgetAction(contextMenu);
    QWidgetAction *checkableAction2 = new QWidgetAction(contextMenu);
    QWidgetAction *checkableAction3 = new QWidgetAction(contextMenu);

    checkBox1->setText("\nРадіаційна небезпека\n");
    checkBox2->setText("\nХімічна небезпека\n");
    checkBox3->setText("\nБіологічна небезпека\n");


    checkableAction1->setDefaultWidget(checkBox1);
    checkableAction2->setDefaultWidget(checkBox2);
    checkableAction3->setDefaultWidget(checkBox3);


    //Actions for Context menu
    addAction = new QAction("Додати");
    deleteAction = new QAction("Видалити");
    sortAction = new QAction("Сортувати");
    helpAction = new QAction("Допомога");

//    addAction->setCheckable(true);
//    deleteAction->setCheckable(true);
//    sortAction->setCheckable(true);

    //Context menu for PointTable
    contextMenu = new QMenu(ui->centralwidget);

    //adding checkboxes
    contextMenu->addAction(checkableAction1);
    contextMenu->addAction(checkableAction2);
    contextMenu->addAction(checkableAction3);

    contextMenu->addSeparator();
    contextMenu->addAction(addAction);
    contextMenu->addAction(deleteAction);
    contextMenu->addAction(sortAction);

    contextMenu->addSeparator();
    contextMenu->addAction(helpAction);
*/

    //creating custom menu from class and copy stylesheet giving centralWidget to arg
    cMenu = new CContextMenu(ui->centralwidget);

    //create filter frame
    cFilter = new CFilterFrame(ui->centralwidget);
    //cFilter->setAttribute(Qt::WA_DeleteOnClose, true);

    cMessage = new CMessageFrame(ui->centralwidget);

    cPopup = new CPopupNotification(ui->centralwidget);

    cColor = new CColorPallete(ui->centralwidget);

    cLoading = new CLoadingScreen(ui->centralwidget);

    cColorPicker = new CColorPicker(ui->centralwidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addActionFunc()
{
    qDebug() << "Add action triggered";
}

void MainWindow::deleteActionFunc()
{

}

void MainWindow::sortActionFunc()
{

}

void MainWindow::helpActionFunc()
{

}


void MainWindow::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index=ui->tableWidget->indexAt(pos);


    qDebug() << index;

    cMenu->popup(ui->tableWidget->viewport()->mapToGlobal(pos));
    //contextMenu->popup(ui->tableWidget->viewport()->mapToGlobal(pos));
}


void MainWindow::on_pushButton_clicked()
{

    //get coordinates of mouse to show new windows on this cooridnates
    int x = ui->pushButton->cursor().pos().x();
    int y = ui->pushButton->cursor().pos().y();

    cFilter->exec(QPoint(x,y));
    //cFilter->exec(QRect(x, y, 200,200));
    //cFilter->showFilterFrame(QRect(x, y, 200,200));

    /*
    //create Frame to show and layout
    frameSort = new QFrame(ui->stackedWidget);
    vLayout = new QVBoxLayout(frameSort);

    //connectin closing event for save checkbox state
    connect(frameSort, &QFrame::destroyed,
            this, &MainWindow::saveState);

    showRadPoints = new QCheckBox("\nРадіаційна небезпека\n");
    showChemPoints = new QCheckBox("\nХімічна небезпека\n");
    showBioPoints = new QCheckBox("\nБіологічна небезпека\n");

    vLayout->addWidget(showRadPoints);
    vLayout->addWidget(showChemPoints);
    vLayout->addWidget(showBioPoints);

    //frameSort->setAttribute(Qt::WA_StyledBackground);
    frameSort->setAttribute(Qt::WA_DeleteOnClose, true);
    frameSort->setWindowFlag(Qt::Popup, true);

    frameSort->setGeometry(x, y, 200,200);
    frameSort->show();
    */
}

void MainWindow::saveState()
{

}

void MainWindow::on_pushButton_3_clicked()
{
    //get coordinates of mouse to show new windows on this cooridnates
    int x = ui->pushButton->cursor().pos().x();
    int y = ui->pushButton->cursor().pos().y();

    cMessage->exec(QPoint(x,y));
}


void MainWindow::on_pushButton_2_clicked()
{
    CMessageItem *msgLable4 = new CMessageItem(this,"Charlie","\tNow save your profile/save! Profit!!!","12:03");

    cMessage->addMsg(msgLable4);
}


void MainWindow::on_pushButton_4_clicked()
{
    //get coordinates of mouse to show new windows on this cooridnates
    int x = ui->pushButton->cursor().pos().x();
    int y = ui->pushButton->cursor().pos().y();

    cPopup->exec(QPoint(x,y));
    cColor->show();
}


void MainWindow::on_pushButton_5_clicked()
{
    cLoading->exec();
}


void MainWindow::on_pushButton_6_clicked()
{
    cColorPicker->exec();
}

