#include "Reader.h"
#include <iostream>

Reader::Reader()
    : BaseUser(), blacklisted_(false), total_spent_(0) {
    std::cout << "Reader() called\n";
}

Reader::Reader(int id, std::string name, std::string email, std::string role,
    double balance, std::string password)
    : BaseUser(id, name, email, role, balance, password),
    blacklisted_(false), total_spent_(0) {
    std::cout << "Reader(params) called\n";
}

Reader::~Reader() { std::cout << "~Reader() called\n"; }

void Reader::Subscribe(const Publication& pub) {
    subscriptions_.push_back(pub);
    total_spent_ += pub.GetPrice();
}

void Reader::ShowSubscriptions() const {
    std::cout << "Subscriptions of " << name_ << ":\n";
    for (auto& p : subscriptions_) p.PrintInfo();
}

void Reader::Pay(double amount) { IncreaseBalance(-amount); }

void Reader::AccessBaseActions() {
    ProtectedAction();   // доступ через protected
    BaseUser::BlockUser();  // оператор глобального доступу
}
