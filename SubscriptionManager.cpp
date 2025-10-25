#include "SubscriptionManager.h"
#include <iostream>

SubscriptionManager::SubscriptionManager()
    : Reader(), DigitalPublication(), manager_id_("M-000") {
    std::cout << "SubscriptionManager() called\n";
}

SubscriptionManager::SubscriptionManager(std::string id, int rid,
    std::string name, std::string email,
    std::string role, double balance,
    std::string password)
    : Reader(rid, name, email, role, balance, password),
    DigitalPublication(),
    manager_id_(id) {
    std::cout << "SubscriptionManager(params) called\n";
}

SubscriptionManager::~SubscriptionManager() {
    std::cout << "~SubscriptionManager() called\n";
}

void SubscriptionManager::ManageSubscription() {
    std::cout << "Manager " << manager_id_
        << " manages digital subscriptions for user " << name_ << std::endl;
}

void SubscriptionManager::CreateSubscription(Reader& reader, const Publication& pub) {
    std::cout << "SubscriptionManager: creating subscription for reader " << reader.name_ << "\n";
    reader.Subscribe(pub);
    std::cout << "Subscription created for '" << reader.name_ << "' on publication.\n";
}
