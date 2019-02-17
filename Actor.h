#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(StudentWorld *world, int initHP, int imageID, double startX, double startY,
          int startDirection, int depth)
    : GraphObject(imageID, startX, startY,
                  startDirection, depth)
    {
        m_world = world;
        m_HP = initHP;
    }
    
    bool stillAlive() const {
        return (m_HP > 0);
    }
    void setDead() {
        m_HP = 0;
    }
    void decHealth() {
        m_HP--;
    }
    
    virtual void doSomething() = 0;
    // Unsure about these
   
    //virtual bool getDestroyed() = 0;
    virtual bool canBlock() const = 0;
    virtual bool canOverlap() const = 0;
    virtual bool canMove() const = 0;
    virtual bool notZombie() const = 0;
protected:
    StudentWorld* getWorld() const {
        return m_world;
    }
private:
    int m_HP;
    StudentWorld *m_world;
};

class Movers: public Actor
{
public:
    Movers(StudentWorld *world, int initHP, int imageID, double startX, double startY,
          int startDirection, int depth)
    : Actor(world, initHP, imageID, startX, startY,
            startDirection, depth)
    {}
    virtual bool canBlock() const {
        return true;
    }
    virtual bool canOverlap() const {
        return true;
    }
    virtual bool canMove() const {
        return true;
    }
};

class Human: public Movers
{
public:
    Human(StudentWorld *world, int imageID, double startX, double startY,
          int startDirection, int depth)
    : Movers(world, 1, imageID, startX, startY,
            startDirection, depth)
    {
        m_infected = false;
        m_infectLvl = 0;
    }
    virtual bool notZombie() const {
        return true;
    }
    bool isInfected() const {
        return m_infected;
    }
    void getInfected() {
        m_infected = true;
    }
    void zombify() {
        m_infectLvl++;
    }
    bool isZombieNow() const {
        return (m_infectLvl >= 500);
    }
private:
    bool m_infected;
    int m_infectLvl;
};

class Penelope: public Human
{
public:
    Penelope(StudentWorld *world, double startX, double startY);
    virtual void doSomething();
    //virtual bool getDestroyed();
    int getlm() const {
        return m_landmines;
    }
    int getfl() const {
        return m_flames;
    }
    int getvacc() const {
        return m_vaccines;
    }
    
    // POTENTIALLY, SOMETHING ABOUT ESCAPING
private:
    int m_landmines;
    int m_flames;
    int m_vaccines;
};

class Wall: public Actor
{
public:
    Wall(double startX, double startY)
    : Actor(nullptr, 1, IID_WALL, startX, startY, right, 0)
    {}
    virtual void doSomething() {}
    virtual bool canBlock() const {
        return true;
    }
    virtual bool canOverlap() const {
        return false;
    }
    virtual bool canMove() const {
        return false;
    }
    virtual bool notZombie() const {
        return true;
    }
};
#endif // ACTOR_H_
