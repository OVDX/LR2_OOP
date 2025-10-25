#include "Publication.h"

Publication::Publication()
    : id_(0), title_("Untitled"), category_("General"), price_(0),
    rating_(0), publisher_("Unknown"), issue_number_(0) {
    std::cout << "Publication() called\n";
}

Publication::Publication(int id, std::string title, std::string category,
    double price, double rating, int issue,
    std::string publisher)
    : id_(id), title_(title), category_(category), price_(price),
    rating_(rating), publisher_(publisher), issue_number_(issue) {
    std::cout << "Publication(params) called\n";
}

Publication::~Publication() {
    std::cout << "~Publication() called\n";
}

void Publication::PrintInfo() const {
    std::cout << "Publication: " << title_ << " (" << category_
        << ") Rating: " << rating_ << " Price: " << price_ << std::endl;
}

void Publication::AddReview(const std::string& text) { reviews_.push_back(text); }

double Publication::GetPrice() const { return price_; }
double Publication::GetRating() const { return rating_; }
