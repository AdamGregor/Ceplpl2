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

// Konstruktory bloku, portum jsou nastaveny pocatecni hodnoty (nullptr, false)

Rest::Rest(unsigned int ID) {
    this->ID_bloku = ID;

    IPort1 = nullptr;
    IPort1_Connected = false;
    IPort1_Initiated = false;
    OPort1 = nullptr;
    OPort1_Connected = false;
    OPort1_Initiated = false;

    Program.AddBlock(this);
}

DiceThrow::DiceThrow(unsigned int ID) {
    this->ID_bloku = ID;

    IPort1 = nullptr;
    IPort1_Connected = false;
    IPort1_Initiated = false;
    OPort1 = nullptr;
    OPort1_Connected = false;
    OPort1_Initiated = false;

    Program.AddBlock(this);
}

Combat::Combat(unsigned int ID) {
    this->ID_bloku = ID;

    IPort1 = nullptr;
    IPort1_Connected = false;
    IPort1_Initiated = false;

    IPort2 = nullptr;
    IPort2_Connected = false;
    IPort2_Initiated = false;

    IPort3 = nullptr;
    IPort3_Connected = false;
    IPort3_Initiated = false;

    OPort1 = nullptr;
    OPort1_Connected = false;
    OPort1_Initiated = false;

    Program.AddBlock(this);
}

ItemApply::ItemApply(unsigned int ID) {
    this->ID_bloku = ID;

    IPort1 = nullptr;
    IPort1_Connected = false;
    IPort1_Initiated = false;
    IPort2 = nullptr;
    IPort2_Connected = false;
    IPort2_Initiated = false;
    OPort1 = nullptr;
    OPort1_Connected = false;
    OPort1_Initiated = false;

    Program.AddBlock(this);
}

ArenaSelect::ArenaSelect(unsigned int ID) {
    this->ID_bloku = ID;

    IPort1 = nullptr;
    IPort1_Connected = false;
    IPort1_Initiated = false;
    IPort2 = nullptr;
    IPort2_Connected = false;
    IPort2_Initiated = false;
    OPort1 = nullptr;
    OPort1_Connected = false;
    OPort1_Initiated = false;

    Program.AddBlock(this);
}



bool Rest::askReady() {
    std::cout << "Plupluplu \n";
    if ((IPort1_Initiated == true || IPort1_Connected == false) && OPort1_Initiated == false)
        return true;
    else
        return false;
}

bool Combat::askReady() {
    if ((IPort1_Initiated == true || IPort1_Connected == false) && (IPort2_Initiated == true || IPort2_Connected == false)
        && (IPort3_Initiated == true || IPort3_Connected == false) && OPort1_Initiated == false)
        return true;
    else
        return false;
}

bool ItemApply::askReady() {
    if ((IPort1_Initiated == true || IPort1_Connected == false) &&
        (IPort2_Initiated == true || IPort2_Connected == false) && OPort1_Initiated == false)
        return true;
    else
        return false;
}

bool DiceThrow::askReady() {
    if ((IPort1_Initiated == true || IPort1_Connected == false) &&	OPort1_Initiated == false)
        return true;
    else
        return false;
}

bool ArenaSelect::askReady() {
    if ((IPort1_Initiated == true || IPort1_Connected == false) &&
        (IPort2_Initiated == true || IPort2_Connected == false) && OPort1_Initiated == false)
        return true;
    else
        return false;
}

PortStuff * Rest::tryConnect(string typ) {
    std::cout << typ << IPort1_Connected;
    PortStuff *ret = new PortStuff;
    if (typ == "Gods" && IPort1_Connected == false) {
        this->IPort1_Connected = true;
        ret->value = &(this->IPort1);
        //std::cout << "taaadddyyy " << ret->value <<" " << &(void*)(this->IPort1) <<"\n";
        ret->init = &(this->IPort1_Initiated);
        return ret;
    }
    else
        ret->value = nullptr;
        ret->init= nullptr;
        return ret;
}

PortStuff *DiceThrow::tryConnect(string typ) {
    PortStuff *ret = new PortStuff;
    if (typ == "Gods" && IPort1_Connected == false) {
        this->IPort1_Connected = true;
        ret->value = &(this->IPort1);
        ret->init = &(this->IPort1_Initiated);
        return ret;
    }
    else
        ret->value = nullptr;
        ret->init = nullptr;
        return ret;
}

PortStuff *Combat::tryConnect(string typ) {
    PortStuff *ret = new PortStuff;
    if (typ == "Gods" && IPort1_Connected == false) {
        this->IPort1_Connected = true;
        ret->value = &(this->IPort1);
        ret->init = &(this->IPort1_Initiated);
        return ret;
    }
    else if (typ == "Gods" && IPort3_Connected == false) {
        this->IPort3_Connected = true;
        ret->value = &(this->IPort3);
        ret->init = &(this->IPort3_Initiated);
        return ret;
    }
    else if (typ == "Arena" && IPort2_Connected == false) {
        ret->value = &(this->IPort2);
        ret->init = &(this->IPort2_Initiated);
        return ret;
    }
    else
        ret->value = nullptr;
        ret->init = nullptr;
        return ret;
}

PortStuff *ItemApply::tryConnect(string typ) {
    PortStuff *ret = new PortStuff;
    if (typ == "Gods" && IPort1_Connected == false) {
        this->IPort1_Connected = true;
        ret->value = &(this->IPort1);
        ret->init = &(this->IPort1_Initiated);
        return ret;
    }
    else
        ret->value = nullptr;
    ret->init = nullptr;
    return ret;
}

PortStuff* ArenaSelect::tryConnect(string typ) {
    PortStuff *ret = new PortStuff;
    if (typ == "Gods" && IPort1_Connected == false) {
        this->IPort1_Connected = true;
        ret->value = &(this->IPort1);
        ret->init = &(this->IPort1_Initiated);
        return ret;
    }
    else if (typ == "Gods" && IPort2_Connected == false) {
        this->IPort2_Connected = true;
        ret->value = &(this->IPort2);
        ret->init = &(this->IPort2_Initiated);
        return ret;
    }
    else
        ret->value = nullptr;
        ret->init = nullptr;
        return ret;
}


//eval bloku REST
void Rest::eval() {
    /**

    */
    while (this->IPort1 == nullptr) {
        IPort1 = MyWindow->getGod(ID_bloku);
    }
    Gods * tmp = (Gods *)IPort1;

    this->OPort1 = tmp->setStrenght(tmp->getOriginalStrenght());
    OPort1_Initiated = true;
    //distribuce vysledku
    ListItemLogic *subscribes = this->subscriptions->getFirst();
    while (subscribes != nullptr) {
        subscribes->data->DistributeResult((void*) this->OPort1);
        subscribes = subscribes->next;
    }
}

//Select areny na zaklade bohu
void ArenaSelect::eval() {
    string name;
    //vypocteni, ci arena se pouzije
    int random = rand() % 2;

    while (this->IPort1 == nullptr) {
        IPort1 = MyWindow->getGod(ID_bloku);
    }
    Gods * tmp1 = (Gods *)IPort1;

    while (this->IPort2 == nullptr) {
        IPort2 = MyWindow->getGod(ID_bloku);
    }
    Gods * tmp2 = (Gods *)IPort2;
    //nastaveni areny podle vylosovaneho boha
    if (random == 0)
        name = tmp1->getName();
    else
        name = tmp2->getName();

    if (name == "Zeus")
        this->OPort1 = new Olymp;
    else if (name == "Poseidon")
        this->OPort1 = new AegeanSea;
    else if (name == "Athena")
        this->OPort1 = new LibraryOfAlexandria;
    else if (name == "Odin")
        this->OPort1 = new Asgartd;
    else if (name == "Njord")
        this->OPort1 = new NorwegianSea;
    else if (name == "Mimir")
        this->OPort1 = new Alfheim;

    OPort1_Initiated = true;
    //distribuce vysledku
    ListItemLogic *subscribes = this->subscriptions->getFirst();
    while (subscribes != nullptr) {
        subscribes->data->DistributeResult((void*) this->OPort1);
        subscribes = subscribes->next;
    }

}

void Combat::eval() {
    while (this->IPort1 == nullptr) {
        IPort1 = MyWindow->getGod(ID_bloku);
    }
    Gods * Buh1 = (Gods *)IPort1;

    while (this->IPort3 == nullptr) {
        IPort3 = MyWindow->getGod(ID_bloku);
    }
    Gods * Buh2 = (Gods *)IPort3;

    while (this->IPort2 == nullptr) {
        IPort2 = MyWindow->getArena(ID_bloku);
    }
    Arena *Bojiste = (Arena*) this->IPort2;

    double effect = Bojiste->getEffect();
    string arena = Bojiste->getName();
    string God1 = Buh1->getName();
    double God1_S = Buh1->getStrenght();

    string God2 = Buh2->getName();
    double God2_S = Buh2->getStrenght();

    //pokud je 1. buh recky a arena take, prida mu cast sily
    if ((arena == "Olymp" || arena == "Aegean Sea" || arena == "Library Of Alexandria") &&
        (God1 == "Zeus" || God1 == "Poseidon" || God1 == "Athena"))
        God1_S += 0.5 * effect;

    //pokud je 1. buh seversky a arena take, prida mu cast sily
    else if ((arena == "Asgartd" || arena == "Norwegian Sea" || arena == "Alfheim") &&
        (God1 == "Odin" || God1 == "Njord" || God1 == "Mimir"))
        God1_S += 0.5 * effect;


    //pokud je 2. buh recky a arena take, prida mu cast sily
    if ((arena == "Olymp" || arena == "Aegean Sea" || arena == "Library Of Alexandria") &&
        (God2 == "Zeus" || God2 == "Poseidon" || God2 == "Athena"))
        God2_S += 0.5 * effect;


    //pokud je 2. buh seversky a arena take, prida mu cast sily
    else if ((arena == "Asgartd" || arena == "Norwegian Sea" || arena == "Alfheim") &&
        (God2 == "Odin" || God2 == "Njord" || God2 == "Mimir"))
        God2_S += 0.5 * effect;

    //bonusy na zaklade lokace pro boha1;
    if(arena == "Olymp" && God1 == "Zeus")
        God1_S += 0.5 * effect;
    else if (arena == "Asgartd" && God1 == "Odin")
        God1_S += 0.5 * effect;
    else if ((arena == "Aegean Sea" || arena == "Norwegian Sea") &&
        (God1 == "Poseidon" || God1 == "Njord"))
        God1_S += 0.5 * effect;
    else if ((arena == "Library Of Alexandria" || arena == "Alfheim") &&
        (God1 == "Athena" || God1 == "Mimir"))
        God1_S += 0.5 * effect;

    //bonusy na zaklade lokace pro boha2;
    if (arena == "Olymp" && God2 == "Zeus")
        God2_S += 0.5 * effect;
    else if (arena == "Asgartd" && God2 == "Odin")
        God2_S += 0.5 * effect;
    else if ((arena == "Aegean Sea" || arena == "Norwegian Sea") &&
        (God2 == "Poseidon" || God2 == "Njord"))
        God2_S += 0.5 * effect;
    else if ((arena == "Library Of Alexandria" || arena == "Alfheim") &&
        (God2 == "Athena" || God2 == "Mimir"))
        God2_S += 0.5 * effect;

    //zvitezi 1. buh
    if (God1_S > God2_S) {
        Buh1->setStrenght(God1_S - God2_S);
        Buh2->setStrenght(0.0);
        this->OPort1 = Buh1;
    }
    //zvitezi 2.buh
    else if (God1_S < God2_S) {
        Buh2->setStrenght(God2_S - God1_S);
        Buh1->setStrenght(0.0);
        this->OPort1 = Buh2;
    }
    //remiza, 'strihnou' si
    else if (God1_S == God2_S) {
        if (rand() % 2 == 1) {
            Buh1->setStrenght(0.01);
            Buh2->setStrenght(0.0);
            this->OPort1 = Buh1;
        }
        else {
            Buh2->setStrenght(0.01);
            Buh1->setStrenght(0.0);
            this->OPort1 = Buh2;
        }
    }
    OPort1_Initiated = true;
    //distribuce vysledku
    ListItemLogic *subscribes = this->subscriptions->getFirst();
    while (subscribes != nullptr) {
        subscribes->data->DistributeResult((void*) this->OPort1);
        subscribes = subscribes->next;
    }
}

void ItemApply::eval() {
    while (this->IPort1 == nullptr) {
        IPort1 = MyWindow->getGod(ID_bloku);
    }
    Gods * buh = (Gods *)IPort1;

    while (this->IPort2 == nullptr) {
        IPort2 = MyWindow->getItem(ID_bloku);
    }
    Accessories * vec = (Accessories*) this->IPort2;


    double effect = vec->getEffect();
    effect *= (double)((rand() % 155) - 25) / 100.0;

    buh->addStrenght(effect);
    if (buh->getStrenght() < 0.0)
        buh->setStrenght(0.0);

    this->OPort1 = buh;
    OPort1_Initiated = true;
    //distribuce vysledku
    ListItemLogic *subscribes = this->subscriptions->getFirst();
    while (subscribes != nullptr) {
        subscribes->data->DistributeResult((void*) this->OPort1);
        subscribes = subscribes->next;
    }

}

//Bohovi bude sebrano 10% zdravi a za to dostane nahodny predmet
void DiceThrow::eval() {
    //nastavi se zivot na 90% stavajiciho
    while (this->IPort1 == NULL) {
        IPort1 = MyWindow->getGod(ID_bloku);
    }
    Gods * Buh = (Gods *)IPort1;

    double strenght = Buh->getStrenght();
    strenght *= 0.9;


    //vybere se nahodny predmet a ten se na nej aplikuje
    int random = rand();
    double boost;
    random = random % ITEM_COUNT;

    if (random == 0) {
        LeviathanAxe *tmp = new LeviathanAxe;
        boost = tmp->getEffect();
        delete tmp;
    }

    else if (random == 1) {
        Curse *tmp = new Curse;
        boost = tmp->getEffect();
        delete tmp;
    }

    else if (random == 2) {
        ScrollOfWisdom *tmp = new ScrollOfWisdom;
        boost = tmp->getEffect();
        delete tmp;
    }

    else if (random == 3) {
        Piety *tmp = new Piety;
        boost = tmp->getEffect();
        delete tmp;
    }

    else if (random == 4) {
        Impiety *tmp = new Impiety;
        boost = tmp->getEffect();
        delete tmp;
    }

    strenght += boost;
    if (strenght < 0.0)
        strenght = 0.0;

    Buh->setStrenght(strenght);

    this->OPort1 = Buh;
    OPort1_Initiated = true;

    //distribuce vysledku
    ListItemLogic *subscribes = this->subscriptions->getFirst();
    while (subscribes != nullptr) {
        subscribes->data->DistributeResult((void*) this->OPort1);
        subscribes = subscribes->next;
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


Connect::Connect(Block* Blok1, Block *Blok2) {
    this->transfered = false;

    this->Data_type = Blok1->getOut();
    std::cout << this->Data_type << "\n";
    this->reaction = Blok2->tryConnect(this->Data_type);
    if (reaction->init != nullptr) {
        Blok1->setSubscribe(this);
        Blok1->OPort1_Connected = true;
        std::cout << "je to fajn \n";
        this->in = Blok1;
        this->out = Blok2;
    }
    else {
        std::cout << "ses posral, ne? ";
    }
        //nejaka chyba

}


void Connect::DistributeResult(void* value){
    transfered = true;
    std::cout<<"\n zdeeeee "<<value << "\n";
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
        if (Done == this->Block_count || Completed) {
            std::cout << "Juch juch";
            Completed = true;
            return;
        }
        Ready = data->Data->askReady();
        std::cout << "moje redy: " << Ready;
        if (Ready) {
            data->Data->eval();
            Done +=1 ;
            NotReadyInRow = 0;
        }
        else {
            NotReadyInRow += 1;
            if (NotReadyInRow == this->Block_count) {
                std::cout << "Nach nach";
                Completed = true;
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
            std::cout << "Juch juch";
            Completed = true;
            return;
        }
        Ready = data->Data->askReady();
        std::cout << "moje redy: " << Ready;
        if (Ready) {
            data->Data->eval();
            Done += 1;
            NotReadyInRow = 0;
            if (Done == this->Block_count || Completed) {
                //byl dodelan posledni blok
                std::cout << "Juch juch\n";
                Completed = true;
                return;
            }
            //jsou jeste bloky k udelani
            std::cout << "Jeste zbyva \n";
            return;

        }
        else {
            NotReadyInRow += 1;
            std::cout<<" " << NotReadyInRow<<" "<< this->Block_count<<"\n";
            if (NotReadyInRow == this->Block_count) {
                std::cout << "Nach nach\n";
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



void Rest::Reset() {
    this->OPort1_Initiated = false;
    this->OPort1 = nullptr;
    this->IPort1_Initiated = false;

    ListItemLogic * Connection = this->subscriptions->getFirst();
    while (Connection != nullptr) {
        Connection->data->transfered = false;
        Connection = Connection->next;
    }
}

void Combat::Reset() {
    this->OPort1_Initiated = false;
    this->OPort1 = nullptr;
    this->IPort2_Initiated = false;
    this->IPort3_Initiated = false;
    this->IPort1_Initiated = false;

    ListItemLogic * Connection = this->subscriptions->getFirst();
    while (Connection != nullptr) {
        Connection->data->transfered = false;
        Connection = Connection->next;
    }
}

void ItemApply::Reset() {
    this->OPort1_Initiated = false;
    this->OPort1 = nullptr;
    this->IPort2_Initiated = false;
    this->IPort1_Initiated = false;

    ListItemLogic * Connection = this->subscriptions->getFirst();
    while (Connection != nullptr) {
        Connection->data->transfered = false;
        Connection = Connection->next;
    }
}

void DiceThrow::Reset() {
    this->OPort1_Initiated = false;
    this->OPort1 = nullptr;
    this->IPort1_Initiated = false;

    ListItemLogic * Connection = this->subscriptions->getFirst();
    while (Connection != nullptr) {
        Connection->data->transfered = false;
        Connection = Connection->next;
    }
}

void ArenaSelect::Reset() {
    this->OPort1_Initiated = false;
    this->OPort1 = nullptr;
    this->IPort2_Initiated = false;
    this->IPort1_Initiated = false;

    ListItemLogic * Connection = this->subscriptions->getFirst();
    while (Connection != nullptr) {
        Connection->data->transfered = false;
        Connection = Connection->next;
    }
}
