#pragma once
#include "Node.h"
#include "ZY_Graph.h"
class BloodHearts :
    public Node
{
public:
    BloodHearts();
    BloodHearts(int health, int h, int w, const wstring& fileName);
    ~BloodHearts();

    virtual void drawSelf(HDC hdc)override;

    void setHealth(int h) { _health = h; }
    int getHealth() { return _health; }
    void setMaxHealth(int h) { _maxHealth = h; }
    void setWH(int w, int h) { _wsum = w, _hsum = h; }
    void setOX(int x) { _oX = x; }
    void setOY(int y) { _oY = y; }
    void setClear(float c) { _clearance = c; }
    void setGraph(const wstring& fileName);
private:
    int _wsum;
    int _hsum;
    int _health;
    int _maxHealth;
    int _oX;
    int _oY;
    float _clearance;
    int _cellW;
    int _cellH;
    T_Graph _graph;
};

