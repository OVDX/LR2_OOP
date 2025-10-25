#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <iostream>
#include <string>
#include <vector>

class Publication {
protected:
    int id_;
    std::string title_;
    std::string category_;
    double price_;
    double rating_;
    std::string publisher_;
    int issue_number_;
    std::vector<std::string> reviews_;

public:
    Publication();
    Publication(int id, std::string title, std::string category, double price,
        double rating, int issue, std::string publisher);
    virtual ~Publication();

    virtual void PrintInfo() const;
    void AddReview(const std::string& text);
    double GetPrice() const;
    double GetRating() const;
};

#endif
