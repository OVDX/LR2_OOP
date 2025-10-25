#include "Publication.h"
#include <fstream>

int Publication::publication_count_ = 0;

// Конструктор без параметрів
Publication::Publication()
    : publisher_("Unknown"), reference_to_subs_(subscribers_count_) {
    id_ = 0;
    title_ = "Untitled";
    category_ = "General";
    price_ = 0.0;
    rating_ = 0.0;
    issue_number_ = 0;
    subscribers_count_ = 0;
    publication_count_++;
    std::cout << "Publication() called\n";
}

// Конструктор з параметрами
Publication::Publication(int id, std::string title, std::string category,
    double price, double rating, int issue_number,
    std::string publisher)
    : id_(id),
    title_(title),
    category_(category),
    price_(price),
    rating_(rating),
    issue_number_(issue_number),
    publisher_(publisher),
    reference_to_subs_(subscribers_count_) {
    subscribers_count_ = 0;
    publication_count_++;
    std::cout << "Publication(params) called\n";
}

// Конструктор копіювання
Publication::Publication(const Publication& other)
    : id_(other.id_),
    title_(other.title_),
    category_(other.category_),
    price_(other.price_),
    rating_(other.rating_),
    issue_number_(other.issue_number_),
    reviews_(other.reviews_),
    subscribers_count_(other.subscribers_count_),
    publisher_(other.publisher_),
    reference_to_subs_(subscribers_count_) {
    publication_count_++;
    std::cout << "Publication(copy) called\n";
}

// Конструктор зі списком ініціалізації
Publication::Publication(int id, std::string title, std::string category,
    double price, double rating, int issue_number,
    std::string publisher, int& ref_subs)
    : id_(id),
    title_(title),
    category_(category),
    price_(price),
    rating_(rating),
    issue_number_(issue_number),
    publisher_(publisher),
    reference_to_subs_(ref_subs) {
    subscribers_count_ = ref_subs;
    publication_count_++;
    std::cout << "Publication(init list) called\n";
}

// Деструктор
Publication::~Publication() { std::cout << "~Publication() called\n"; }

// Методи
void Publication::AddReview(const std::string& review) {
    reviews_.push_back(review);
}

void Publication::UpdateRating(double new_rating) { rating_ = new_rating; }

void Publication::PrintInfo() const {
    std::cout << "Publication: " << title_ << " (" << category_
        << ") Price: " << price_ << " Rating: " << rating_
        << " Publisher: " << publisher_ << std::endl;
}

double Publication::CalculateDiscount(int percent) const {
    return price_ - price_ * percent / 100.0;
}

double Publication::CalculateDiscount(double percent, bool special_offer) const {
    double disc = price_ - price_ * percent / 100.0;
    return special_offer ? disc * 0.9 : disc;
}

void Publication::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    file << title_ << "\n"
        << category_ << "\n"
        << price_ << "\n"
        << rating_ << "\n"
        << publisher_ << std::endl;
}

void Publication::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    file >> title_ >> category_ >> price_ >> rating_;
}

int Publication::GetPublicationCount() { return publication_count_; }
