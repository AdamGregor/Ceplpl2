/**
 *@file mainwindow.cpp
 *@author Zdenek Jelinek (xjelin47), Adam Gregor (xgrego18)
 *@brief mainwindow of app
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mylabel.h"
#include "connection.h"
#include "Execute.h"
#include "SupportClasses.h"

#include <QPushButton>
#include <QThread>
#include <QDesktopWidget>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPen>
#include <QGraphicsLineItem>
#include <QDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QTimer>

#include <iostream>
#include <fstream>
#include <string>

Execute Program;
MainWindow* MyWindow;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    this->setWindowTitle("BlockEditor");
    MyWindow = this;

    scene = new QGraphicsScene;
    QRect tmp = QApplication::desktop()->screenGeometry();
    this->setFixedSize(tmp.width() *0.9, tmp.height()*0.9);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   // ui->graphicsView->setEnabled(false);

    QGraphicsLineItem* item = new QGraphicsLineItem;
    item->setLine(0,0,0.01,0.01);
    scene->addItem(item);

    pen = new QPen;
    pen->setWidth(4);

    blocks_ID = 1;
    active_connection = nullptr;
    filename = QString();
    this->blocks = new BlockList;
    this->listConn = new blockConnect;
    this->Spawn_x = 12;
    this->Spawn_y = 67;

    connect(this, SIGNAL(resized()), this, SLOT(doResized()));
    connect(ui->actionCombat, SIGNAL(triggered()), this, SLOT(addCombat()));
    connect(ui->actionDice_throw, SIGNAL(triggered()), this, SLOT(addDice_throw()));
    connect(ui->actionArena_select, SIGNAL(triggered()), this, SLOT(addArena_select()));
    connect(ui->actionItem_apply, SIGNAL(triggered()), this, SLOT(addItem_apply()));
    connect(ui->actionRest, SIGNAL(triggered()), this, SLOT(addRest()));
    connect(ui->actionRun, SIGNAL(triggered()), this, SLOT(run()));
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(printHelp()));
    connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(load()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(save_as()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newScheme()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(quickSave()));
    connect(ui->actionReset, SIGNAL(triggered()), this, SLOT(resetIt()));
    connect(ui->actionStep, SIGNAL(triggered()), this, SLOT(stepIt()));

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::addCombat(){
    MyLabel* block = new MyLabel(this);
    block->setID(blocks_ID);
    block->setType(COMBAT);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    connect(block, SIGNAL(deleteSig(MyLabel*)), this, SLOT(deleteSlot(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);
    QPixmap pixmap(":combat.gif");
    block->setPixmap(pixmap);

    MyLabel* tmp = new MyLabel(this);
    block->setIDlabel(tmp);
    tmp->setGeometry(Spawn_x, Spawn_y +5, 35, 15);
    QString id = QString::number(blocks_ID);
    tmp->setText(id);
    tmp->setAlignment(Qt::AlignCenter);
    tmp->show();

    block->show();
    blocks->insert(block);

    block->setLogicblock(new Combat(block->getID()));

    Spawn_x +=10;
    Spawn_y +=10;
    blocks_ID++;
}

void MainWindow::addDice_throw(){
    MyLabel* block = new MyLabel(this);
    block->setID(blocks_ID);
    block->setType(DICE);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    connect(block, SIGNAL(deleteSig(MyLabel*)), this, SLOT(deleteSlot(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);

    QPixmap pixmap(":dice.png");
    block->setPixmap(pixmap);

    MyLabel* tmp = new MyLabel(this);
    block->setIDlabel(tmp);
    tmp->setGeometry(Spawn_x, Spawn_y +5, 35, 15);
    QString id = QString::number(blocks_ID);
    tmp->setText(id);
    tmp->setAlignment(Qt::AlignCenter);
    tmp->show();

    block->show();
    blocks->insert(block);
    block->setLogicblock(new DiceThrow(block->getID()));
    Spawn_x +=10;
    Spawn_y +=10;
    blocks_ID++;
}

void MainWindow::addItem_apply(){
    MyLabel* block = new MyLabel(this);
    block->setID(blocks_ID);
    block->setType(ITEM);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    connect(block, SIGNAL(deleteSig(MyLabel*)), this, SLOT(deleteSlot(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);

    QPixmap pixmap(":itemSelect.gif");
    block->setPixmap(pixmap);
    MyLabel* tmp = new MyLabel(this);
    block->setIDlabel(tmp);
    tmp->setGeometry(Spawn_x, Spawn_y +5, 35, 15);
    QString id = QString::number(blocks_ID);
    tmp->setText(id);
    tmp->setAlignment(Qt::AlignCenter);
    tmp->show();
    block->show();
    blocks->insert(block);
    block->setLogicblock(new ItemApply(block->getID()));
    Spawn_x +=10;
    Spawn_y +=10;
    blocks_ID++;
}

void MainWindow::addArena_select(){
    MyLabel* block = new MyLabel(this);
    block->setID(blocks_ID);
    block->setType(ARENA);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    connect(block, SIGNAL(deleteSig(MyLabel*)), this, SLOT(deleteSlot(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);

    QPixmap pixmap(":arenaSelect.gif");
    block->setPixmap(pixmap);
    MyLabel* tmp = new MyLabel(this);
    block->setIDlabel(tmp);
    tmp->setGeometry(Spawn_x, Spawn_y +5, 35, 15);
    QString id = QString::number(blocks_ID);
    tmp->setText(id);
    tmp->setAlignment(Qt::AlignCenter);
    tmp->show();
    block->show();
    blocks->insert(block);
    block->setLogicblock(new ArenaSelect(block->getID()));
    Spawn_x +=10;
    Spawn_y +=10;
    blocks_ID++;
}

void MainWindow::addRest(){
    MyLabel* block = new MyLabel(this);
    block->setID(blocks_ID);
    block->setType(REST);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    connect(block, SIGNAL(deleteSig(MyLabel*)), this, SLOT(deleteSlot(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);

    QPixmap pixmap(":rest.gif");
    block->setPixmap(pixmap);
    MyLabel* tmp = new MyLabel(this);
    block->setIDlabel(tmp);
    tmp->setGeometry(Spawn_x, Spawn_y +5, 35, 15);
    QString id = QString::number(blocks_ID);
    tmp->setText(id);
    tmp->setAlignment(Qt::AlignCenter);
    tmp->show();
    block->show();
    blocks->insert(block);
    block->setLogicblock(new Rest(block->getID()));
    Spawn_x +=10;
    Spawn_y +=10;
    blocks_ID++;
}


void MainWindow::mouseRelease(MyLabel* block){
    if(ui->actionDelete->isChecked())
        return;

    QPoint place;
    place = this->mapFromGlobal(QCursor::pos());
    int x = place.x();
    int y = place.y();
    x -= 50;
    y -= 50;
    checkPlacement(&x, &y);
    block->setCoords(x, y);
    block->setGeometry(x,y,100,100);
    MyLabel* tmp = block->getIDlabel();
    tmp->setGeometry(x, y+5, 35, 15);

    connectionList* out = block->getOutList();
    connectionList* in = block->getInList();

    if(out->getListLenght() != 0){               // posuny spoju s out porty
        ListItem* out_port = out->getFirst();
        for(int i = 0; i < out->getListLenght(); i++){
            block->getCoords(&x, &y);
            out_port->data->setOutcoords(&x, &y);
            out_port->data->getOutcoords(&x, &y);
            int g, h;
            out_port->data->getIncoords(&g, &h);
            out_port->data->setLine(x ,y, g, h);
            out_port = out_port->next;
        }
    }

    if(in->getListLenght() != 0){                   // posuny spoju s in porty
        ListItem* in_port = in->getFirst();
        for(int i = 0; i < in->getListLenght(); i++){
            int g, h;
            block->getCoords(&g, &h);
            in_port->data->setIncoords(&g, &h);
            in_port->data->getIncoords(&g, &h);
            in_port->data->getOutcoords(&x, &y);
            in_port->data->setLine(x, y, g, h);
            in_port = in_port->next;
        }
    }
}


void MainWindow::checkPlacement(int* x, int* y){
    if(*x < 12){         //12 -> hranice povoleneho okna
        *x = 12;
    }
    else if(*x+110 > this->size().width())
        *x = this->size().width() - 111;

    if(*y < 67){
        *y = 67;
    }
    else if(*y+110 > this->size().height()){
        *y = this->size().height() - 111;
    }

    return;
}

void MainWindow::resizeEvent(QEvent* event){
    emit resized();
}

void* MainWindow::getGod(unsigned int ID){

    Listblock* bloc = blocks->getFirst();
    for(int i = 0; i < blocks->getListLenght(); i++){
        if(bloc->data->getID() == ID){
            bloc->data->setStyleSheet("QLabel { background-color : blue;}");
            break;
        }
        bloc = bloc->next;
    }

    bool ok;
    QString zeus = "Zeus";
    QString odin = "Odin";
    QString athena = "Athena";
    QString njord = "Njord";
    QString poseidon = "Poseidon";
    QString mimir = "Mimir";
    QString id = QString::number(ID);

    QString god = QInputDialog::getText(this, "Block ID: " + id, "Enter a god:\n-> Zeus\n-> Odin\n-> Athena\n-> Njord\n-> Poseidon\n-> Mimir\n", QLineEdit::Normal, "Zeus", &ok);
    bloc->data->setStyleSheet("QLabel { background-color : ;}");

    if(!ok){
        return nullptr;
    }

    if(god.isEmpty()){
        return nullptr;
    }
    else if(QString::compare(god, zeus, Qt::CaseInsensitive) == 0){
        Zeus* tmp = new Zeus;
        return (void*)tmp;
    }
    else if(QString::compare(god, odin, Qt::CaseInsensitive) == 0){
        Odin* tmp = new Odin;
        return (void*)tmp;
    }
    else if(QString::compare(god, athena, Qt::CaseInsensitive) == 0){
        Athena* tmp = new Athena;
        return (void*)tmp;
    }
    else if(QString::compare(god, njord, Qt::CaseInsensitive) == 0){
        Njord* tmp = new Njord;
        return (void*)tmp;
    }
    else if(QString::compare(god, poseidon, Qt::CaseInsensitive) == 0){
        Poseidon* tmp = new Poseidon;
        return (void*)tmp;
    }
    else if(QString::compare(god, mimir, Qt::CaseInsensitive) == 0){
        Mimir* tmp = new Mimir;
        return (void*)tmp;
    }
    else{
        return nullptr;
    }

    return nullptr;

}

void* MainWindow::getArena(unsigned int ID){
    Listblock* bloc = blocks->getFirst();
    for(int i = 0; i < blocks->getListLenght(); i++){
        if(bloc->data->getID() == ID){
            bloc->data->setStyleSheet("QLabel { background-color : blue;}");
            break;
        }
        bloc = bloc->next;
    }

    bool ok;
    QString olymp = "Olymp";
    QString aegean = "Aegean sea";
    QString library = "Library of Alexandria";
    QString asgard = "Asgardt";
    QString norwegian = "Norwegian sea";
    QString alfheim = "Alfheim";
    QString valley = "Valley of the kings";
    QString id = QString::number(ID);
    QString place = QInputDialog::getText(this, "Block ID: " + id, "Enter arena:\n-> Olymp\n-> Aegean sea\n-> Library of Alexandria\n-> Asgartd\n-> Norwegian sea\n-> Alfheim\n-> Valley of the kings\n",
                                         QLineEdit::Normal, "Olymp", &ok);
    bloc->data->setStyleSheet("QLabel { background-color : ;}");

    if(place.isEmpty())
        return nullptr;

    if(place.isEmpty()){
        return nullptr;
    }
    else if(QString::compare(place, olymp, Qt::CaseInsensitive) == 0){
        Olymp* tmp = new Olymp;
        return (void*)tmp;
    }
    else if(QString::compare(place, aegean, Qt::CaseInsensitive) == 0){
        AegeanSea* tmp = new AegeanSea;
        return (void*)tmp;
    }
    else if(QString::compare(place, library, Qt::CaseInsensitive) == 0){
        LibraryOfAlexandria* tmp = new LibraryOfAlexandria;
        return (void*)tmp;
    }
    else if(QString::compare(place, asgard, Qt::CaseInsensitive) == 0){
        Asgartd* tmp = new Asgartd;
        return (void*)tmp;
    }
    else if(QString::compare(place, norwegian, Qt::CaseInsensitive) == 0){
        NorwegianSea* tmp = new NorwegianSea;
        return (void*)tmp;
    }
    else if(QString::compare(place, alfheim, Qt::CaseInsensitive) == 0){
        Alfheim* tmp = new Alfheim;
        return (void*)tmp;
    }
    else if(QString::compare(place, valley, Qt::CaseInsensitive) == 0){
        ValleyOfTheKings* tmp = new ValleyOfTheKings;
        return (void*)tmp;
    }

    else{
        return nullptr;
    }

    return nullptr;
}

void* MainWindow::getItem(unsigned int ID){
    Listblock* bloc = blocks->getFirst();
    for(int i = 0; i < blocks->getListLenght(); i++){
        if(bloc->data->getID() == ID){
            bloc->data->setStyleSheet("QLabel { background-color : blue;}");
            break;
        }
        bloc = bloc->next;
    }

    bool ok;
    QString axe = "Leviathan Axe";
    QString curse = "Curse";
    QString scroll = "Scroll of wisdom";
    QString piety = "Piety";
    QString impiety = "Impiety";
    QString id = QString::number(ID);

    QString item = QInputDialog::getText(this, "Block ID: " + id, "Enter item:\n-> Leviathan Axe\n-> Curse\n-> Scroll of wisdom\n-> Piety\n-> Impiety\n",
                                         QLineEdit::Normal, "Curse", &ok);
    bloc->data->setStyleSheet("QLabel { background-color : ;}");

    if(!ok){
        return nullptr;
    }
    if(item.isEmpty())
        return nullptr;

    else if(QString::compare(item, axe, Qt::CaseInsensitive) == 0){
        LeviathanAxe* tmp = new LeviathanAxe;
        return (void*)tmp;
    }
    else if(QString::compare(item, curse, Qt::CaseInsensitive) == 0){
        Curse* tmp = new Curse;
        return (void*)tmp;
    }
    else if(QString::compare(item, scroll, Qt::CaseInsensitive) == 0){
        ScrollOfWisdom* tmp = new ScrollOfWisdom;
        return (void*)tmp;
    }
    else if(QString::compare(item, piety, Qt::CaseInsensitive) == 0){
        Piety* tmp = new Piety;
        return (void*)tmp;
    }
    else if(QString::compare(item, impiety, Qt::CaseInsensitive) == 0){
        Impiety* tmp = new Impiety;
        return (void*)tmp;
    }
    else{
        return nullptr;
    }

    return nullptr;
}

void MainWindow::highlightBlock(unsigned int ID){
    Listblock* block = blocks->getFirst();
    for(int i = 0; i < blocks->getListLenght(); i++){
        if(block->data->getID() == ID)
            break;
        block = block->next;
    }

    block->data->setStyleSheet("QLabel { background-color : blue;}");
    return;
}

void MainWindow::unhighlightBlock(unsigned int ID){
    Listblock* block = blocks->getFirst();
    for(int i = 0; i < blocks->getListLenght(); i++){
        if(block->data->getID() == ID)
            break;
        block = block->next;
    }

    block->data->setStyleSheet("QLabel { background-color : ;}");
    return;
}

void MainWindow::printResult(int typ, unsigned int ID, void *data){
    QMessageBox msg;

    if(typ == 0){
        Gods* buh = (Gods*)data;
        std::string name = buh->getName();
        double strenght = buh->getStrenght();
        QString tmpname = QString::fromStdString(name);
        QString tmpstrenght = QString::number(strenght);
        QString id = QString::number(ID);

        msg.setText("Result of block with ID: " + id +" is God:\nName: " + tmpname + "\nStrenght: " + tmpstrenght + "\n");
        msg.exec();
    }
    else if(typ == 1){
        Arena* aren = (Arena*)data;
        std::string name = aren->getName();
        double strenght = aren->getEffect();
        QString tmpname = QString::fromStdString(name);
        QString tmpstrenght = QString::number(strenght);
        QString id = QString::number(ID);

        msg.setText("Result of block with ID: " + id +" is Arena:\nName: " + tmpname + "\nEffect: " + tmpstrenght + "\n");
        msg.exec();
    }
    else{
        Accessories* buh = (Accessories*)data;
        std::string name = buh->getName();
        double strenght = buh->getEffect();
        QString tmpname = QString::fromStdString(name);
        QString tmpstrenght = QString::number(strenght);
        QString id = QString::number(ID);

        msg.setText("Result of block with ID: " + id +" is Item:\nName: " + tmpname + "\nEffect: " + tmpstrenght + "\n");
        msg.exec();
    }

    return;

}

void MainWindow::printCycle(){
    QMessageBox msg;
    msg.setText("ERROR: Cycles detected! Remove some of your blocks.\n");
    msg.exec();

}


void MainWindow::mousePress(MyLabel *block){
    int x;
    int y;

    if(active_connection){
        if(active_connection->getNumOfClicks() == 2){
            active_connection = new connection;
            active_connection->setOutblock(block);
            block->getCoords(&x, &y);
            active_connection->setOutcoords(&x, &y);
            active_connection->incNumOfClicks();

        }
        else{
            if(block == active_connection->getOutBlock())       //nelze vytvorit spojeni na jednom bloku
                return;

            blockConn* tmp = listConn->getFirst();
            if(tmp != nullptr){
                for(int i = 0; i < listConn->getListlenght(); i++){   // staci jedno stejne spojeni
                    if(active_connection->getOutBlock()->getID() == tmp->first_ID && block->getID() == tmp->second_ID){
                        active_connection = nullptr;
                        return;
                    }
                }
            }
            MyLabel* temp = active_connection->getOutBlock();

            bool ok;
            Connect* novespojeni = new Connect(temp->getLogicblock(), block->getLogicblock(), &ok);
            if(ok)
                temp->setLogicconnect(novespojeni);
            else{
                delete novespojeni;
                delete active_connection;
                active_connection = nullptr;
                QMessageBox msg;
                msg.setText("This connection can not be made.\nEither full input ports of second block or incompatible I/O types.\n");
                msg.exec();
                return;
            }

            active_connection->setInblock(block);
            connectionList* in = block->getInList();

            connectionList* out = temp->getOutList();
            int g,h;
            active_connection->getOutcoords(&g,&h);
            block->getCoords(&x, &y);
            active_connection->setPen(*pen);
            active_connection->setIncoords(&x, &y);
            active_connection->getIncoords(&x, &y);
            active_connection->setLine(g,h, x, y);
            scene->addItem(active_connection);
            active_connection->incNumOfClicks();
            in->insert(active_connection);
            out->insert(active_connection);
            listConn->insert(active_connection->getOutBlock()->getID(), active_connection->getInBlock()->getID());
        }
    }

    else{
        active_connection = new connection();
        active_connection->setOutblock(block);
        block->getCoords(&x, &y);
        active_connection->setOutcoords(&x, &y);
        active_connection->incNumOfClicks();
    }
}

void MainWindow::deleteSlot(MyLabel *block){
    if(ui->actionDelete->isChecked()){
        active_connection = nullptr;
        connectionList* out_list = block->getOutList();
        connectionList* in_list = block->getInList();
        ListItem* item = out_list->getFirst();
        MyLabel* other_block;
        delete block->getIDlabel();

        for(int i = 0; i < out_list->getListLenght(); i++){
            other_block = item->data->getInBlock();
            other_block->getInList()->deleteConnection(block->getID(), true);
            item = item->next;
            listConn->deleteConn(block->getID(), other_block->getID());
        }

        item = in_list->getFirst();
        for(int i = 0; i < in_list->getListLenght(); i++){
            other_block = item->data->getOutBlock();
            other_block->getOutList()->deleteConnection(block->getID(), false);
            item = item->next;
            listConn->deleteConn(other_block->getID(), block->getID());
        }

        blocks->deleteBlock(block->getID());
    }

    else{
        return;
    }
}

void MainWindow::run(){
    Program.Run();
}

void MainWindow::stepIt(){
    Program.Step();
}

void MainWindow::newScheme(){
    this->Spawn_x = 12;
    this->Spawn_y = 67;
    blocks_ID = 0;
    filename = QString();
    Listblock* tmp = blocks->getFirst();
    int lenght = blocks->getListLenght();
    active_connection = nullptr;

    for(int i = 0; i < lenght; i++){
        connectionList* out_list = tmp->data->getOutList();
        connectionList* in_list = tmp->data->getInList();
        ListItem* item = out_list->getFirst();
        MyLabel* other_block;

        for(int i = 0; i < out_list->getListLenght(); i++){
            other_block = item->data->getInBlock();
            other_block->getInList()->deleteConnection(tmp->data->getID(), true);
            listConn->deleteConn(tmp->data->getID(), other_block->getID());
            item = item->next;
        }

        item = in_list->getFirst();
        for(int i = 0; i < in_list->getListLenght(); i++){
            other_block = item->data->getOutBlock();
            other_block->getOutList()->deleteConnection(tmp->data->getID(), false);
            listConn->deleteConn(other_block->getID(), tmp->data->getID());
            item = item->next;
        }
        delete tmp->data->getIDlabel();
        blocks->deleteBlock(tmp->data->getID());
        tmp = tmp->next;
    }

    delete blocks;
    listConn = new blockConnect;
    blocks = new BlockList;
}

void MainWindow::printHelp(){
    QMessageBox help;
    help.setWindowTitle("Block Editor - Help");
    help.setText(QString("Move a block:\n   - Press, move and release left mouse button\n\n") +
                 QString("Make a connection:\n   - Click on a blocks you want to connect with right mouse button\n\n") +
                 QString("Run editor:\n   - Press Run\n\n") +
                 QString("Enter a God:\n   - Zeus, Odin, Athena, Njord, Mimir, Poseidon\n\n") +
                 QString("Delete block:\n   - Toggle Delete button and press on block you want to delete\n      with left mouse button\n\n"));
    help.exec();
}

void MainWindow::load(){
    filename = QFileDialog::getOpenFileName(this, "Open scheme", "./", "Scheme (*.az)");
    if(filename.isEmpty())
        return;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "Unable to open file", file.errorString());
        return;
    }

    this->Spawn_x = 12;
    this->Spawn_y = 67;
    blocks_ID = 0;
    Listblock* tmp = blocks->getFirst();
    int lenght = blocks->getListLenght();
    active_connection = nullptr;
    for(int i = 0; i < lenght; i++){
        connectionList* out_list = tmp->data->getOutList();
        connectionList* in_list = tmp->data->getInList();
        ListItem* item = out_list->getFirst();
        MyLabel* other_block;

        for(int i = 0; i < out_list->getListLenght(); i++){
            other_block = item->data->getInBlock();
            other_block->getInList()->deleteConnection(tmp->data->getID(), true);
            listConn->deleteConn(tmp->data->getID(), other_block->getID());
            item = item->next;
        }

        item = in_list->getFirst();
        for(int i = 0; i < in_list->getListLenght(); i++){
            other_block = item->data->getOutBlock();
            other_block->getOutList()->deleteConnection(tmp->data->getID(), false);
            listConn->deleteConn(other_block->getID(), tmp->data->getID());
            item = item->next;
        }

        blocks->deleteBlock(tmp->data->getID());
        tmp = tmp->next;
    }

    delete blocks;
    listConn = new blockConnect;
    blocks = new BlockList;

    QTextStream read(&file);
    bool ok;
    int count = 0;
    unsigned int ID;
    int x, y;   //pro nove bloky
    blockType typ;
    QString combat = "COMBAT"; QString dice = "DICE"; QString item = "ITEM";
    QString arena = "ARENA"; QString rest = "REST";

    QString line = read.readLine();
    if(line.isEmpty()){
        file.close();
        return;
    }

    count = line.toInt(&ok, 10);
    for(int i = 0; i < count; i++){
        line = read.readLine();
        QStringList items = line.split(" ");
        for(int j = 0; j < items.size(); j++){
            if(j == 0){
                QString tmp = items.at(j);
                ID = tmp.toUInt(&ok, 10);
                if(blocks_ID <= ID)
                    blocks_ID = ID + 1;
            }
            else if(j == 1){
                QString tmp = items.at(j);
                if(QString::compare(tmp, combat) == 0)
                    typ = COMBAT;
                else if(QString::compare(tmp, dice) == 0)
                    typ = DICE;
                else if(QString::compare(tmp, item) == 0)
                    typ = ITEM;
                else if(QString::compare(tmp, arena) == 0)
                    typ = ARENA;
                else if(QString::compare(tmp, rest) == 0)
                    typ = REST;
            }
            else if(j == 2){
                QString tmp = items.at(j);
                x = tmp.toInt(&ok, 10);
            }
            else if(j == 3){
                QString tmp = items.at(j);
                y = tmp.toInt(&ok, 10);
            }
        }

        MyLabel* newblock = new MyLabel(this);
        newblock->setID(ID);
        newblock->setType(typ);
        checkPlacement(&x, &y);
        newblock->setCoords(x, y);
        newblock->getCoords(&x, &y);
        connect(newblock , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
        connect(newblock, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
        connect(newblock, SIGNAL(deleteSig(MyLabel*)), this, SLOT(deleteSlot(MyLabel*)));
        newblock->setGeometry(x, y, 100, 100);
        if(typ == COMBAT){
            QPixmap pixmap(":combat.gif");
            newblock->setPixmap(pixmap);
        }
        else if(typ == ARENA){
            QPixmap pixmap(":arenaSelect.gif");
            newblock->setPixmap(pixmap);
        }
        else if(typ == DICE){
            QPixmap pixmap(":dice.png");
            newblock->setPixmap(pixmap);
        }
        else if(typ == ITEM){
            QPixmap pixmap(":itemSelect.gif");
            newblock->setPixmap(pixmap);
        }
        else if(typ == REST){
            QPixmap pixmap(":rest.gif");
            newblock->setPixmap(pixmap);
        }

        MyLabel* docasne = new MyLabel(this);
        QString idcko = QString::number(ID);
        newblock->setIDlabel(docasne);
        docasne->setGeometry(x, y +5, 35, 15);
        docasne->setText(idcko);
        docasne->setAlignment(Qt::AlignCenter);
        docasne->show();

        blocks->insert(newblock);
        newblock->show();
    }

    line = read.readLine();
    if(line.isEmpty()){
        file.close();
        return;
    }

    count = line.toInt(&ok, 10);        // nacteni spoju
    QStringList items;
    MyLabel* in_block, * out_block;
    unsigned int in = -1 , out = -1;
    for(int i = 0; i < count; i++){
        line = read.readLine();
        items = line.split(" ");
        for(int j = 0; j < items.size(); j++){
            if(j == 0){
                QString tmp = items.at(j);
                out = tmp.toUInt(&ok, 10);
            }
            else if(j == 1){
                QString tmp = items.at(j);
                in = tmp.toUInt(&ok, 10);
            }
        }
        Listblock* tmp_block = blocks->getFirst();
        for(int j = 0; j < blocks->getListLenght(); j++){
            if(tmp_block->data->getID() == out){
                out_block = tmp_block->data;
            }
            else if(tmp_block->data->getID() == in){
                in_block = tmp_block->data;
            }
            tmp_block = tmp_block->next;
        }

        connection* conn = new connection;
        conn->setInblock(in_block);
        conn->setOutblock(out_block);
        conn->setPen(*pen);
        int k, l, m, n;
        out_block->getCoords(&k, &l);
        in_block->getCoords(&m, &n);
        conn->setIncoords(&m, &n);
        conn->setOutcoords(&k, &l);
        conn->getOutcoords(&k, &l);
        conn->getIncoords(&m, &n);
        conn->setLine(k, l, m, n);
        scene->addItem(conn);
        listConn->insert(conn->getOutBlock()->getID(), conn->getInBlock()->getID());
        out_block->getOutList()->insert(conn);
        in_block->getInList()->insert(conn);
       // connect(conn, SIGNAL(showDat(connection*)), this, SLOT(showData(connection*)));
    }


    file.close();
}

void MainWindow::save_as(){

    filename = QFileDialog::getSaveFileName(this, "Save File", "./untitled.az", "Scheme (*.az)");

    if(filename.isEmpty() == true){
        return;
    }

    QFile file(filename);
    file.open( QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << blocks->getListLenght() << endl;
    Listblock* block = blocks->getFirst();
    for(int i = 0; i < blocks->getListLenght(); i++){
        stream << block->data->getID();
        if(block->data->getType() == COMBAT){
            stream << " COMBAT ";
        }
        else if(block->data->getType() == DICE){
            stream << " DICE ";
        }
        else if (block->data->getType() == ITEM){
            stream << " ITEM ";
        }
        else if (block->data->getType() == REST){
            stream << " REST ";
        }
        else if (block->data->getType() == ARENA){
            stream << " ARENA ";
        }

        int x,y;
        block->data->getCoords(&x, &y);
        stream << x << " " << y << endl;

        block = block->next;
    }

    stream << listConn->getListlenght() << endl;
    blockConn* item = listConn->getFirst();
    for(int i = 0; i < listConn->getListlenght(); i++){
        stream << item->first_ID << " " << item->second_ID << endl;
        item = item->next;
    }

    file.close();
}

void MainWindow::quickSave(){

    if(filename.isEmpty() == true){
        filename = QFileDialog::getSaveFileName(this, "Save File", "./untitled.az", "Scheme (*.az)");
    }

    if(filename.isEmpty() == true){
        return;
    }

    QFile file(filename);
    file.open( QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << blocks->getListLenght() << endl;
    Listblock* block = blocks->getFirst();
    for(int i = 0; i < blocks->getListLenght(); i++){
        stream << block->data->getID();
        if(block->data->getType() == COMBAT){
            stream << " COMBAT ";
        }
        else if(block->data->getType() == DICE){
            stream << " DICE ";
        }
        else if (block->data->getType() == ITEM){
            stream << " ITEM ";
        }
        else if (block->data->getType() == REST){
            stream << " REST ";
        }
        else if (block->data->getType() == ARENA){
            stream << " ARENA ";
        }

        int x,y;
        block->data->getCoords(&x, &y);
        stream << x << " " << y << endl;

        block = block->next;
    }

    stream << listConn->getListlenght() << endl;
    blockConn* item = listConn->getFirst();
    for(int i = 0; i < listConn->getListlenght(); i++){
        stream << item->first_ID << " " << item->second_ID << endl;
        item = item->next;
    }

    file.close();
}


void MainWindow::doResized(){               // zatim deadcode, treba to vyuziju v budoucnu
    Listblock* tmp = blocks->getFirst();
    int x, y, g, h;
    connectionList* list;
    for(int i = 0; i < blocks->getListLenght(); i++){
        tmp->data->getCoords(&x, &y);
        checkPlacement(&x, &y);
        tmp->data->setCoords(x, y);
        tmp->data->setGeometry(x, y, 100, 100);
        tmp = tmp->next;
    }

    blockConn* temp = listConn->getFirst();
    for(int i = 0; i < listConn->getListlenght(); i++){
        unsigned int id_out = temp->first_ID;
        unsigned int id_in = temp->second_ID;
        tmp = blocks->getFirst();
        for(int j = 0; j < blocks->getListLenght(); j++){
            if(id_out == tmp->data->getID()){
                list = tmp->data->getOutList();
                ListItem* docasne = list->getFirst();
                for(int a = 0; a < list->getListLenght(); a++){
                    if(docasne->data->getInBlock()->getID() == id_in){
                        tmp->data->getCoords(&x, &y);
                        docasne->data->getInBlock()->getCoords(&g, &h);
                        docasne->data->setIncoords(&g, &h);
                        docasne->data->setOutcoords(&x, &y);
                        docasne->data->getIncoords(&g, &h);
                        docasne->data->getOutcoords(&x, &y);
                        docasne->data->setLine(x, y, g, h);
                    }
                    docasne = docasne->next;
                }
            }
            tmp = tmp->next;
        }
        temp = temp->next;
    }
}

void MainWindow::resetIt(){
    Program.Reset();
}

