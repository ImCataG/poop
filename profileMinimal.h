//
// Created by catag on 5/18/2022.
//

#ifndef OOP_PROFILEMINIMAL_H
#define OOP_PROFILEMINIMAL_H


#include <string>
#include <memory>
#include "boost.h"

class profileMinimal {
protected:
    std::string name;
    long long int balance;
    bool shopping;

public:
    [[maybe_unused]] virtual void changeBal(long long int x);
    [[maybe_unused]] void setName(const std::string& s);
    [[maybe_unused]] std::string getName();
    [[maybe_unused]] virtual long long int getBal();
    explicit profileMinimal(const std::string& name_= "untitled", bool shopping_ = true);
    profileMinimal(const std::string &name, long long int balance, bool shopping_ = true);

    profileMinimal& operator=(const profileMinimal& other);

    [[maybe_unused]] virtual float multi ();
    friend std::ostream& operator<<(std::ostream& os, const profileMinimal& p);

    [[maybe_unused]] profileMinimal(const profileMinimal& other);

    virtual ~profileMinimal();
    [[maybe_unused]] virtual char profileType() = 0;
    virtual void addBoost(const boost& b);
    virtual void print(std::ostream& os) const = 0;

    [[nodiscard]] bool canUseShop() const;

    //pointer stuff goes under this

    [[maybe_unused]] [[nodiscard]] virtual std::shared_ptr<profileMinimal> clone() const = 0;

};


#endif //OOP_PROFILEMINIMAL_H
