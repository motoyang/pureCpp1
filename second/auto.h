#ifndef AUTO_H
#define AUTO_H


class Auto
{
    std::string m_brand;
    int m_mileage;
    double m_hours;
    int m_fuel;

public:
    Auto();
    virtual ~Auto();

    void drive(const std::string& driver, int mileage, double hours);
    void fuel(int quantity);
    int maintain(const std::string& something);
    std::tuple<std::string, int, float, int> check() const;
};

class Car: public Auto
{
public:
    Car();
    virtual ~Car();

    double music(const std::string& song);
    bool navi(const std::string& address);
};

#endif // AUTO_H
