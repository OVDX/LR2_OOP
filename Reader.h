#ifndef READER_H
#define READER_H

#include "BaseUser.h"
#include "Publication.h"
#include <vector>

// Reader наслідує BaseUser через public
class Reader : public BaseUser {
private:
    std::vector<Publication> subscriptions_;
    bool blacklisted_;
    double total_spent_;

public:
    Reader();
    Reader(int id, std::string name, std::string email, std::string role,
        double balance, std::string password);
    ~Reader();

    void Subscribe(const Publication& pub);
    void ShowSubscriptions() const;
    void Pay(double amount);
    void AccessBaseActions();
};

#endif
