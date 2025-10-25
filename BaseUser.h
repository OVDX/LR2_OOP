#ifndef BASEUSER_H
#define BASEUSER_H

#include <iostream>
#include <string>

class BaseUser {
private:
    int id_;                 // private
    std::string password_;   // private
    double balance_;         // private

protected:
    std::string email_;      // protected
    std::string role_;       // protected
    int login_attempts_;     // protected

public:
    std::string name_;       // public
    bool active_;            // public
    int warnings_;           // public

    // Конструктори
    BaseUser();
    BaseUser(int id, std::string name, std::string email,
        std::string role, double balance, std::string password);

    // Віртуальний деструктор
    virtual ~BaseUser();

    // Методи
    void PrintBasicInfo() const;              // публічний метод
    void IncreaseBalance(double amount);      // публічний метод
    void BlockUser();                         // публічний метод

protected:
    void ProtectedAction();                   // захищений метод
    void ResetLoginAttempts();                // protected
private:
    void PrivateMethod();                     // private
};

#endif
