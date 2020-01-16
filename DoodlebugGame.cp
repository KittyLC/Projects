#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Organism;
class Doodlebug;
class Ant;

class World {
    friend class Organism;
    friend class Doodlebug;
    friend class Ant;

public:
    World();
    ~World();
    Organism* getAt(int x, int y);
    void setAt(int x, int y, Organism *org);
    void Display();

protected:
    char doodlebugs = 'o';
    char ant = 'X';
    int antbreed = 3;
    int doodlebreed = 8;
    int doodlestarve = 3;
    Organism* grid[20][20];
};

class Organism : public World {
    friend class World;

public:
    Organism();
    Organism(World *world, int x, int y);
    ~Organism();
    virtual void breed() = 0;
    virtual void move() = 0;
    virtual int getType() = 0;
    virtual bool starve() = 0;

protected:
    int x, y;
    int breedTicks;
    World *world;
};

int size = 20;

World::World() {
    for (int i =0; i<size; i++) {
        for (int j=0; j<size; j++) {
            grid[i][j] = NULL;
        }
    }
}

World::~World() {
    for (int i =0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if (grid[i][j] != NULL)
                delete (grid[i][j]);
        }
    }
}

Organism* World::getAt(int x, int y) {
    if ((x >= 0) && (x<size) && (y >=0) && (y<size))
        return grid[x][y];
    return NULL;
}

void World::setAt(int x, int y, Organism *org) {
    if ((x >= 0) && (x<size) && (y >=0) && (y<size)) {
        grid[x][y] = org;
    }
}

void World::Display() {
    for (int i = 0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if (grid[i][j] == NULL)
                cout << "-";
            else if (grid[i][j]->getType() == ant)
                cout << "o";
            else
                cout << "X";
        }
            cout << endl;
    }
}

Organism::Organism() {
    world = NULL;
    breedTicks = 0;
    x = 0;
    y = 0;
}

Organism::Organism(World *wrld, int x, int y) {
    this->world = wrld;
    breedTicks = 0;
    this->x = x;
    this->y = y;
    wrld->setAt(x, y, this);
}

Organism::~Organism() {}

class Ant : public  Organism {
    friend class World;

public:
    Ant();
    Ant(World *world, int x, int y);
    void breed();
    void move();
    int getType();
    bool starve() {
        return false;
    }
};

Ant::Ant() : Organism() {}

Ant::Ant(World *world, int x, int y) : Organism(world, x, y) {}

void Ant::move() {
    int dir = rand() % 4;

    switch (dir) {
        case 0:
            if ((y > 0) && (world->getAt(x, y - 1) != NULL)) {
                world->setAt(x, y - 1, world->getAt(x, y));
                world->setAt(x, y, NULL);
                y--;
            }
        case 1:
            if ((y < size - 1) && (world->getAt(x, y + 1) != NULL)) {
                world->setAt(x, y + 1, world->getAt(x, y));
                world->setAt(x, y, NULL);
                y++;
            }
        case 2:
            if ((x > 0) && (world->getAt(x - 1, y) != NULL)) {
                world->setAt(x - 1, y, world->getAt(x, y));
                world->setAt(x, y, NULL);
                x--;
            }
        case 3:
            if ((x < size - 1) && (world->getAt(x + 1, y) != NULL)) {
                world->setAt(x + 1, y, world->getAt(x, y));
                world->setAt(x, y, NULL);
                x++;
            }
            breedTicks++;
    }
}

int Ant::getType() {
    return ant;
}

void Ant::breed() {
    if (breedTicks==antbreed) {
        breedTicks=0;
        if ((y>0) && (world->getAt(x, y-1)!=NULL)) {
            Ant *newAnt = new Ant(world, x, y-1);
        }
        else if ((y<size-1) && (world->getAt(x, y+1)!=NULL)) {
            Ant *newAnt = new Ant(world, x, y+1);
        }
        else if ((x>0) && (world->getAt(x-1, y) != NULL)) {
            Ant *newAnt = new Ant(world, x-1, y);
        }
        else if ((x<size-1) && (world->getAt(x+1, y) != NULL)) {
            Ant *newAnt = new Ant(world, x+1, y);
        }
    }
}

class Doodlebug : public Organism {
   friend class World;

public:
    Doodlebug();
    Doodlebug(World *world, int x, int y);
    void breed();
    void move();
    int getType();
    bool starve();

private:
    int starveTicks;
};

Doodlebug::Doodlebug() : Organism() {
    starveTicks = 0;
}

Doodlebug::Doodlebug(World *world, int x, int y) : Organism(world, x, y) {
    starveTicks = 0;
}

void Doodlebug::move() {
    if ((y>0) && (world->getAt(x, y-1) != NULL) &&
    (world->getAt(x, y-1)->getType()==ant)) {
        world->setAt(x, y, NULL);
        starveTicks = 0;
        y--;
    }
    else if ((y<size-1) && (world->getAt(x, y+1) != NULL) &&
    world->getAt(x, y+1)->getType() == ant) {
        world->setAt(x, y, NULL);
        starveTicks = 0;
        y++;
    }
    else if ((x>0) && (world->getAt(x-1, y) != NULL) &&
            (world->getAt(x-1, y)->getType()==ant)) {
        world->setAt(x, y, NULL);
        starveTicks = 0;
        x--;
    }
    else if ((x<size-1) && (world->getAt(x+1, y) != NULL) &&
            (world->getAt(x+1, y)->getType()==ant)) {
        world->setAt(x, y, NULL);
        starveTicks = 0;
        x++;
    }

    int dir = rand() % 4;
    switch (dir) {
        case 0:
        if ((y>0) && (world->getAt(x, y-1)!=NULL)) {
            world->setAt(x, y-1, world->getAt(x,y));
            world->setAt(x, y, NULL);
            y--;
        }
        case 1:
        if((y<size-1) && (world->getAt(x, y+1) != NULL)) {
            world->setAt(x, y+1, world->getAt(x,y));
            world->setAt(x, y, NULL);
            y++;
        }
        case 2:
        if ((x>0) && (world->getAt(x-1, y) != NULL)) {
            world->setAt(x-1, y, world->getAt(x,y));
            world->setAt(x, y, NULL);
            x--;
        }
        default:
        if ((x < size - 1) && (world->getAt(x + 1, y) != NULL)) {
            world->setAt(x + 1, y, world->getAt(x, y));
            world->setAt(x, y, NULL);
            x++;
        }
    }
    starveTicks++;
    breedTicks++;
}

int Doodlebug::getType() {
    return doodlebugs;
}

void Doodlebug::breed() {
    if (breedTicks==doodlebreed) {
        breedTicks=0;
        if ((y>0) && (world->getAt(x, y-1)==NULL)) {
            Doodlebug *newDoodle = new Doodlebug(world, x, y-1);
        }
        else if ((y<size-1) && (world->getAt(x, y+1)==NULL)) {
            Doodlebug *newDoodle = new Doodlebug(world, x, y+1);
        }
        else if ((x>0) && (world->getAt(x-1, y) == NULL)) {
            Doodlebug *newDoodle = new Doodlebug(world, x-1, y);
        }
        else {
            Doodlebug *newDoodle = new Doodlebug(world, x+1, y);
        }
    }
}

bool Doodlebug::starve() {
    if (starveTicks>doodlestarve)
        return true;
}

int main() {
    int initialants = 100;
    int initialbugs = 5;
    string input;
    srand(time(NULL));

    World w;
    Organism* bug;

    int antcount = 0;
    while (antcount<initialants) {
        int x = rand() % size;
        int y = rand() % size;
        if (w.getAt(x,y) == NULL) {
            antcount++;
            Ant *a = new Ant(&w, x, y);
        }
    }

    int doodlecount =0;
    while (doodlecount<initialbugs) {
        int x = rand() % size;
        int y = rand() % size;
        if (w.getAt(x,y) == NULL) {
            doodlecount++;
            Doodlebug *d = new Doodlebug(&w, x, y);
        }
    }

    do {
        cout << "Press Enter to continue:\n";
        getline(cin, input);
        w.Display();
        bug->move();
        bug->breed();
        bug->starve();
    } while (input == "\n");

    return 0;
}