#ifndef FLOOR_H
#define FLOOR_H


class Floor
{
private:
    static int index;
    int fID;

    bool requestUp;
    bool requestDown;

public:
    Floor();
    Floor(int);
    ~Floor();

    int getFID();

    void setRequestingUp(bool);
    void setRequestingDown(bool);

    bool isRequestingUp();
    bool isRequestingDown();


};

#endif // FLOOR_H
