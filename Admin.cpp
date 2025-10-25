#include "Admin.h"
#include <iostream>

Admin::Admin() : BaseUser(), blocked_users_(0) {
    std::cout << "Admin() called\n";
}

Admin::Admin(int id, std::string name, std::string email,
    std::string role, double balance, std::string password)
    : BaseUser(id, name, email, role, balance, password), blocked_users_(0) {
    std::cout << "Admin(params) called\n";
}

Admin::~Admin() { std::cout << "~Admin() called\n"; }

void Admin::AddReader(const Reader& r) { monitored_readers_.push_back(r); }

void Admin::ShowAllReaders() const {
    std::cout << "Admin monitoring:\n";
    for (auto& r : monitored_readers_) r.PrintBasicInfo();
}

void Admin::BlockReader(int id) {
    blocked_users_++;
    std::cout << "Reader " << id << " blocked. Total blocked: " << blocked_users_
        << std::endl;
}
