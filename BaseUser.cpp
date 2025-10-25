#include "BaseUser.h"
#include <iostream>

BaseUser::BaseUser()
    : id_(0), name_("Unknown"), email_("none"), role_("Guest"),
    balance_(0.0), password_("1234"), active_(true), warnings_(0),
    login_attempts_(0) {
    std::cout << "BaseUser() called\n";
}

BaseUser::BaseUser(int id, std::string name, std::string email,
    std::string role, double balance, std::string password)
    : id_(id), name_(name), email_(email), role_(role),
    balance_(balance), password_(password), active_(true), warnings_(0),
    login_attempts_(0) {
    std::cout << "BaseUser(params) called\n";
}

BaseUser::~BaseUser() {
    std::cout << "~BaseUser() called\n";
}

void BaseUser::PrintBasicInfo() const {
    std::cout << "User: " << name_ << " (" << email_ << ") | Role: " << role_
        << " | Balance: " << balance_ << std::endl;
}

void BaseUser::IncreaseBalance(double amount) { balance_ += amount; }

void BaseUser::BlockUser() {
    active_ = false;
    std::cout << "User blocked.\n";
}

void BaseUser::ProtectedAction() {
    std::cout << "Protected action executed by: " << name_ << std::endl;
}

void BaseUser::ResetLoginAttempts() { login_attempts_ = 0; }

void BaseUser::PrivateMethod() {
    std::cout << "Private method of BaseUser\n";
}
