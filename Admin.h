#ifndef ADMIN_H
#define ADMIN_H

#include "BaseUser.h"
#include "Reader.h"
#include <vector>

class Admin : private BaseUser {
private:
    std::vector<Reader> monitored_readers_;
    int blocked_users_;

public:
    Admin();
    Admin(int id, std::string name, std::string email,
        std::string role, double balance, std::string password);
    ~Admin();

    void AddReader(const Reader& r);
    void ShowAllReaders() const;
    void BlockReader(int id);
};

#endif
