#include "Reader.h"
#include <algorithm>
#include <fstream>
#include <iostream>

int Reader::reader_count_ = 0;

Reader::Reader() {
    id_ = 0;
    name_ = "Unknown";
    email_ = "none";
    balance_ = 0.0;
    warnings_ = 0;
    blacklisted_ = false;
    random_values_ = nullptr;
    reader_count_++;
    std::cout << "Reader() called\n";
}

Reader::Reader(int id, std::string name, std::string email, double balance)
    : id_(id), name_(name), email_(email), balance_(balance) {
    warnings_ = 0;
    blacklisted_ = false;
    random_values_ = nullptr;
    reader_count_++;
    std::cout << "Reader(params) called\n";
}

Reader::Reader(const Reader& other)
    : id_(other.id_),
    name_(other.name_),
    email_(other.email_),
    subscriptions_(other.subscriptions_),
    balance_(other.balance_),
    warnings_(other.warnings_),
    blacklisted_(other.blacklisted_) {
    random_values_ = nullptr;
    reader_count_++;
    std::cout << "Reader(copy) called\n";
}

Reader::~Reader() {
    delete[] random_values_;
    std::cout << "~Reader() called\n";
}

void Reader::Subscribe(const Publication& pub) { subscriptions_.push_back(pub); }

void Reader::Pay(double amount) { balance_ -= amount; }

void Reader::PrintInfo() const {
    std::cout << "Reader: " << name_ << " (" << email_ << ") Balance: " << balance_
        << std::endl;
}

double Reader::CalculateTotal() const {
    double total = 0;
    for (const auto& p : subscriptions_) total += p.CalculateDiscount(0);
    return total;
}

double Reader::CalculateTotal(bool include_discount) const {
    double total = 0;
    for (const auto& p : subscriptions_)
        total += include_discount ? p.CalculateDiscount(10) : p.CalculateDiscount(0);
    return total;
}

void Reader::AllocateRandomValues(int count) {
    random_values_count_ = count;
    random_values_ = new int[count];
    for (int i = 0; i < count; i++) random_values_[i] = rand() % 100;
    std::sort(random_values_, random_values_ + count);
}

void Reader::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    file << name_ << "\n" << email_ << "\n" << balance_ << std::endl;
}

void Reader::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    file >> name_ >> email_ >> balance_;
}

int Reader::GetReaderCount() { return reader_count_; }
