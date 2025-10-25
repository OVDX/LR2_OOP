#ifndef SUBSCRIPTIONMANAGER_H
#define SUBSCRIPTIONMANAGER_H

#include "Reader.h"
#include "DigitalPublication.h"
#include <string>

class SubscriptionManager : public Reader, public DigitalPublication {
private:
    std::string manager_id_;

public:
    SubscriptionManager();
    SubscriptionManager(std::string id, int rid, std::string name,
        std::string email, std::string role, double balance,
        std::string password);
    ~SubscriptionManager();

    void ManageSubscription();

    void CreateSubscription(Reader& reader, const Publication& pub);
};

#endif
