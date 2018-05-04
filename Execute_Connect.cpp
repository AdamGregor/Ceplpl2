/**
 *@file Execute_Connect.cpp
 *@author Adam Gregor (xgrego18)
 *@author Zdenìk Jelínek (xjelin47)
 *@brief  Zdrojový soubor pro to tøídy obsluhujicí Run/Step/Reset/Remove a konektivitu blokù
 */

#include "Blocks.h"
#include "SupportClasses.h"
#include "Arenas.h"
#include "Execute.h"
#include "mainwindow.h"
#include <iostream>
#include <typeinfo>
#include <string>
#define HIGHEST_EFFECT 1.0
#define LOWEST_EFFECT -0.5
using namespace  std;

//globalni promenna, jedinacek
extern Execute Program;
extern MainWindow* MyWindow;

Execute::Execute() {
    this->Blocks = new Blocklist;
    Block_count = 0;
    Done = 0;
    NotReadyInRow = 0;
    Completed = false;
}



void Connect::Disconnect(int which){
    if(which == 0){ //chci mazat IN block
        if(out_name=="COMBAT"){
            Combat* tmp = (Combat*) out;
            tmp->Combat::Disconnect(this);
        }
        else if(out_name=="REST"){
            Rest* tmp = (Rest*) out;
            tmp->Rest::Disconnect(this);
        }
        else if(out_name=="ARENASELECT"){
            ArenaSelect* tmp = (ArenaSelect*) out;
            tmp->ArenaSelect::Disconnect(this);
        }
        else if(out_name=="DICETHROW"){
            DiceThrow* tmp = (DiceThrow*) out;
            tmp->DiceThrow::Disconnect(this);
        }
        else if(out_name=="ITEMAPPLY"){
            ItemApply* tmp = (ItemApply*) out;
            tmp->ItemApply::Disconnect(this);
        }
    }


    if(which == 1){ //chci mazat OUT block
        if(in_name=="COMBAT"){
            Combat* tmp = (Combat*) in;
            tmp->Combat::Disconnect(this);
        }
        else if(in_name=="REST"){
            Rest* tmp = (Rest*) in;
            tmp->Rest::Disconnect(this);
        }
        else if(in_name=="ARENASELECT"){
            ArenaSelect* tmp = (ArenaSelect*) in;
            tmp->ArenaSelect::Disconnect(this);
        }
        else if(in_name=="DICETHROW"){
            DiceThrow* tmp = (DiceThrow*) in;
            tmp->DiceThrow::Disconnect(this);
        }
        else if(in_name=="ITEMAPPLY"){
            ItemApply* tmp = (ItemApply*) in;
            tmp->ItemApply::Disconnect(this);
        }
    }

}

void SubscribeList::InsertItem(Connect *data) {
    ListItemLogic *neu = new ListItemLogic;
    ListItemLogic *first = this->getFirst();
    neu->data = data;
    neu->next = first;
    this->first = neu;
    this->listLenght++;
}

void SubscribeList::RemoveItem(Connect *data){
    ListItemLogic* blok = getFirst();
    ListItemLogic* prev;
    if(blok->data == data){
        first = blok->next;
        listLenght-=1;
        return;
    }
    else{
        while(1){
            prev = blok;
            blok=blok->next;
            if(blok->data == data){
                prev->next=blok->next;
                listLenght-=1;
                return;
            }
        }
    }

}

Connect::Connect(Block* Blok1, Block *Blok2, bool* ok) {
    this->transfered = false;
    this->value = -1;
    this->name = "None";

    this->Data_type = Blok1->getOut();
    this->in_name = Blok1->getType();
    this->reaction = Blok2->tryConnect(this->Data_type,this);
    if (reaction->init != nullptr) {
        Blok1->setSubscribe(this);
        this->in = Blok1;
        this->out = Blok2;
        this->out_name = reaction->blockType;
        *ok = true;
    }
    else {
        *ok = false;
    }

}


void Connect::DistributeResult(void* value,double power, string name){
    transfered = true;
    this->value=power;
    this->name = name;

    *(reaction->init) = true;
    if (this->in->getOut() == "Gods") {
        Gods **tmp = (Gods**)reaction->value;
        *tmp = (Gods*)value;
    }
    else if (this->in->getOut() == "Arena") {
        Arena **tmp = (Arena**)reaction->value;
        *tmp = (Arena*)value;
    }
    else if (this->in->getOut() == "Accessories") {
        Accessories **tmp = (Accessories**)reaction->value;
        *tmp = (Accessories*)value;
    }


}

void Blocklist::addItem(Block *data) {
    BlocklistElem *tmp = new BlocklistElem;
    tmp->Data = data;
    tmp->next = this->first;
    this->first = tmp;
}

void Execute::AddBlock(Block* blok) {
    this->Blocks->addItem(blok);
    this->Block_count += 1;
}

void Execute::Run() {
    bool Ready;
    BlocklistElem * data = this->Blocks->getFirst();
    while (1) {
        if(Completed){
            MyWindow->printReset();
            Completed = true;
            return;
        }
        if (Done == this->Block_count) {
            Completed = true;
            return;
        }

        Ready = data->Data->askReady();
        if (Ready) {
            data->Data->eval();
            Done +=1 ;
            NotReadyInRow = 0;
        }
        else {
            NotReadyInRow += 1;
            if (NotReadyInRow == this->Block_count) {
                Completed = true;
                MyWindow->printCycle();
                return;
            }
            data = data->next;
            if (data == nullptr)
                data = this->Blocks->getFirst();
        }
    }
}

void Execute::Step() {
    bool Ready;
    BlocklistElem * data = this->Blocks->getFirst();

    while (1) {
        if (Done == this->Block_count || Completed) {
            MyWindow->printReset();
            Completed = true;
            return;
        }
        Ready = data->Data->askReady();
        if (Ready) {
            data->Data->eval();
            Done += 1;
            NotReadyInRow = 0;
            if (Done == this->Block_count || Completed) {
                //MyWindow->printReset();
                Completed = true;
                return;
            }
            //jsou jeste bloky k udelani
            return;

        }
        else {
            NotReadyInRow += 1;
            if (NotReadyInRow == this->Block_count) {
                MyWindow->printCycle();
                Completed = true;
                return;
            }
            data = data->next;
            if (data == nullptr)
                data = this->Blocks->getFirst();
        }
    }
}

void Execute::Reset() {
    Done = 0;
    NotReadyInRow = 0;
    Completed = 0;
    BlocklistElem *Blok = this->Blocks->getFirst();
    while (Blok != nullptr) {
        Blok->Data->Reset();
        Blok = Blok->next;
    }

}

void Execute::Remove(Block* block_to_remove){
    BlocklistElem* block = Blocks->getFirst();
    if(block->Data == block_to_remove){
        Blocks->first=block->next;
        Block_count--;
        return;
    }
    else {
        while(1){
            BlocklistElem* prev = block;
            block = block->next;
            if(block->Data == block_to_remove){
                prev->next=block->next;
                Block_count--;
                return;
            }
        }

    }



}