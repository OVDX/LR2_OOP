#ifndef DIGITALPUBLICATION_H
#define DIGITALPUBLICATION_H

#include "Publication.h"
#include <string>
#include <vector>
#include <utility>

class DigitalPublication : public Publication {
private:
    double file_size_;
    std::string format_;
    std::string url_;
    // додаткове поле для рейтингів/відгуків (композиція)
    std::vector<std::pair<int, std::string>> ratings_;  // <rating, comment>

public:
    DigitalPublication();
    DigitalPublication(int id, std::string title, std::string category,
        double price, double rating, int issue,
        std::string publisher, double file_size,
        std::string format, std::string url);
    ~DigitalPublication();

    void PrintInfo() const override;
    void Download();

    // --- Додані методи (виправлення помилок) ---
    void DisplayInfo() const;                             // показати детальну інфу
    void AddRating(int stars, const std::string& comment); // додати рейтинг/відгук
    void ShowRatings() const;                             // показати всі рейтинги
};

#endif
