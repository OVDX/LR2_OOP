#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <iostream>
#include <string>
#include <vector>

class Publication {
private:
    int id_;
    std::string title_;
    std::string category_;
    double price_;
    double rating_;
    int issue_number_;
    std::vector<std::string> reviews_;
    int subscribers_count_;

    static int publication_count_;  // спільне поле (для всіх об’єктів)

public:
    const std::string publisher_;  // константне поле
    int& reference_to_subs_;       // посилання на лічильник підписників

    // --- Конструктори ---
    Publication();  // без параметрів
    Publication(int id, std::string title, std::string category, double price,
        double rating, int issue_number, std::string publisher);
    Publication(const Publication& other);  // копіювання
    Publication(int id, std::string title, std::string category, double price,
        double rating, int issue_number, std::string publisher,
        int& ref_subs);  // список ініціалізації
    ~Publication();  // деструктор

    // --- Методи ---
    void AddReview(const std::string& review);
    void UpdateRating(double new_rating);
    void PrintInfo() const;
    double CalculateDiscount(int percent) const;
    double CalculateDiscount(double percent, bool special_offer) const;  // перевантаження
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);
    static int GetPublicationCount();  // статичний метод
};

#endif
