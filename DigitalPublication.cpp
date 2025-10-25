#include "DigitalPublication.h"
#include <iostream>

DigitalPublication::DigitalPublication()
    : Publication(), file_size_(0), format_("pdf"), url_("none"), ratings_() {
    std::cout << "DigitalPublication() called\n";
}

DigitalPublication::DigitalPublication(int id, std::string title,
    std::string category, double price,
    double rating, int issue,
    std::string publisher, double file_size,
    std::string format, std::string url)
    : Publication(id, title, category, price, rating, issue, publisher),
    file_size_(file_size),
    format_(format),
    url_(url),
    ratings_() {
    std::cout << "DigitalPublication(params) called\n";
}

DigitalPublication::~DigitalPublication() {
    std::cout << "~DigitalPublication() called\n";
}

void DigitalPublication::PrintInfo() const {
    Publication::PrintInfo();
    std::cout << "  [Digital] format=" << format_ << ", size=" << file_size_
        << "MB, url=" << url_ << "\n";
}

void DigitalPublication::Download() {
    std::cout << "Downloading \"" << /* assuming Publication has title_ protected */ "\"... (url: " << url_ << ")\n";
}

// --- Реалізація доданих методів ---
void DigitalPublication::DisplayInfo() const {
    // Більш детальна інформація для демонстрації у main
    PrintInfo();
    std::cout << "  URL: " << url_ << ", File size: " << file_size_
        << " MB, Format: " << format_ << "\n";
    std::cout << "  Ratings count: " << ratings_.size() << "\n";
}

void DigitalPublication::AddRating(int stars, const std::string& comment) {
    ratings_.push_back({ stars, comment });
    // Для простоти можна оновити середній рейтинг (якщо Publication має метод чи поле)
    // Якщо Publication має захищений rating_ — ми могли б оновити його тут; але залишимо окремо
    std::cout << "Added rating " << stars << " (" << comment << ") to digital publication.\n";
}

void DigitalPublication::ShowRatings() const {
    std::cout << "Ratings for digital publication:\n";
    for (const auto& r : ratings_) {
        std::cout << "  - " << r.first << " stars: " << r.second << "\n";
    }
    if (ratings_.empty()) std::cout << "  (no ratings)\n";
}
