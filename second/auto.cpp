#include "precompiled.h"
#include "auto.h"

Auto::Auto()
    : m_brand("Audi!"), m_mileage(0),  m_hours(0), m_fuel(0)
{
    std::cout << "Auto::Auto()" << std::endl;
}

Auto::~Auto()
{
    std::cout << "Auto::~Auto()" << std::endl;
}

void Auto::drive(const std::string& driver, int mileage, double hours)
{
    const int oilConsumptionRate = 6;

    mileage = std::min(m_fuel * oilConsumptionRate, mileage);
    std::cout<< "Drived about " << hours << "hours, and " << mileage << " miles by "
              << driver << std::endl;

    m_mileage += mileage;
    m_fuel -= (mileage / oilConsumptionRate);
    m_hours += hours;
}

void Auto::fuel(int quantity)
{
    m_fuel += quantity;
}

int Auto::maintain(const std::string& something)
{
    std::cout << "maintain with " << something << std::endl;
    return m_mileage * 2 + m_hours * 0.1;
}

std::tuple<std::string, int, float, int> Auto::check() const
{
//    std::cout << m_brand <<", " << m_mileage << ", " << m_hours << ", " << m_fuel << std::endl;
    return std::make_tuple(m_brand, m_mileage, m_hours, m_fuel);
}
