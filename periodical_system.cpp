#include "periodical_system.h"

#include <fstream>
#include <algorithm>
#include <string>
#include <random>
#include <sstream>

// -------------------- Periodical реалізація --------------------

Periodical::Periodical()
    : id(0),
    title(""),
    price_per_issue(0.0),
    publisher_("Unknown"),
    frequency_("Monthly"),
    rating_sum_(0.0),
    rating_count_(0),
    issues_per_year_(12),
    discount_rate_(0.0) {
}

Periodical::Periodical(int id, const std::string& title, double price)
    : id(id),
    title(title),
    price_per_issue(price),
    publisher_("Default Publisher"),
    frequency_("Monthly"),
    rating_sum_(0.0),
    rating_count_(0),
    issues_per_year_(12),
    discount_rate_(0.0) {
}

// AddReview з трьома параметрами (перевантаження) - використовується reviewer
void Periodical::AddReview(const std::string& reviewer, int rating, const std::string& text) {
    // використовуємо приватні поля rating_sum_, rating_count_, reviews_
    rating_sum_ += rating;
    ++rating_count_;
    std::ostringstream oss;
    oss << "[" << rating << "] " << text;
    reviews_.push_back({ reviewer, oss.str() });
}

// AddReview з двома параметрами (перевантаження)
void Periodical::AddReview(int rating, const std::string& text) {
    rating_sum_ += rating;
    ++rating_count_;
    reviews_.push_back({ "Anonymous", text });
}

double Periodical::CalculateAverageRating() const {
    if (rating_count_ == 0) return 0.0;
    return rating_sum_ / rating_count_;
}

// Метод, що приймає об'єкт класу Reader і робить просту перевірку (п.4)
void Periodical::RateByReader(const Reader& r, int rating) {
    // Адже ми forward-declared Reader, тут ми тільки читаємо публічні поля r.name
    AddReview(r.name, rating, "Оцінка від читача (через RateByReader)");
}

// Clone повертає об'єкт класу (повертає Periodical) (п.4)
Periodical Periodical::Clone() const {
    Periodical copy = *this;
    // модифікуємо, щоб вказати, що це клон
    copy.title = title + " (клон)";
    return copy;
}

void Periodical::PrintInfo() const {
    std::cout << "Periodical{id=" << id << ", title=\"" << title
        << "\", price=" << price_per_issue
        << ", publisher=\"" << publisher_ << "\", freq=" << frequency_
        << ", avg_rating=" << CalculateAverageRating()
        << "}\n";
}

void Periodical::DebugShowAllFields() const {
    std::cout << "=== Debug Periodical ===\n";
    std::cout << "id: " << id << "\n";
    std::cout << "title: " << title << "\n";
    std::cout << "price_per_issue: " << price_per_issue << "\n";
    std::cout << "publisher_: " << publisher_ << "\n";
    std::cout << "frequency_: " << frequency_ << "\n";
    std::cout << "rating_sum_: " << rating_sum_ << "\n";
    std::cout << "rating_count_: " << rating_count_ << "\n";
    std::cout << "issues_per_year_: " << issues_per_year_ << "\n";
    std::cout << "discount_rate_: " << discount_rate_ << "\n";
    std::cout << "reviews_ size: " << reviews_.size() << "\n";
    std::cout << "=========================\n";
}

// Файлові операції: простий текстовий формат (п.5)
bool Periodical::SaveToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) return false;
    ofs << id << "\n";
    ofs << title << "\n";
    ofs << price_per_issue << "\n";
    ofs << publisher_ << "\n";
    ofs << frequency_ << "\n";
    ofs << rating_sum_ << "\n";
    ofs << rating_count_ << "\n";
    ofs << issues_per_year_ << "\n";
    ofs << discount_rate_ << "\n";
    // збережемо відгуки як кількість рядків + пари
    ofs << reviews_.size() << "\n";
    for (const auto& r : reviews_) {
        ofs << r.first << "\n" << r.second << "\n";
    }
    return true;
}

Periodical Periodical::LoadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    Periodical p;
    if (!ifs) return p;
    ifs >> p.id;
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(ifs, p.title);
    ifs >> p.price_per_issue;
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(ifs, p.publisher_);
    std::getline(ifs, p.frequency_);
    ifs >> p.rating_sum_;
    ifs >> p.rating_count_;
    ifs >> p.issues_per_year_;
    ifs >> p.discount_rate_;
    size_t reviews_n = 0;
    ifs >> reviews_n;
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    p.reviews_.clear();
    for (size_t i = 0; i < reviews_n; ++i) {
        std::string reviewer, text;
        std::getline(ifs, reviewer);
        std::getline(ifs, text);
        p.reviews_.push_back({ reviewer, text });
    }
    return p;
}

// -------------------- Reader реалізація --------------------

Reader::Reader()
    : id(0),
    name(""),
    balance(0.0),
    email_("unknown"),
    phone_(""),
    is_blacklisted_(false),
    active_subscription_months_(0),
    total_paid_(0) {
}

Reader::Reader(int id, const std::string& name, double balance)
    : id(id),
    name(name),
    balance(balance),
    email_(name + "@example.com"),
    phone_("000-000-000"),
    is_blacklisted_(false),
    active_subscription_months_(0),
    total_paid_(0) {
}

// Subscribe (1) — підписка на видання (використовує підписки_ який містить об'єкти Periodical)
// Це реалізує пункт 3: розміщення об'єкта одного класу в іншому (Reader містить Periodical)
void Reader::Subscribe(Periodical& p) {
    // додамо один місяць підписки за ціну однієї копії
    if (is_blacklisted_) {
        std::cout << "Reader " << name << " is blacklisted; cannot subscribe.\n";
        return;
    }
    if (balance < p.price_per_issue) {
        std::cout << "Insufficient funds for " << name << " to subscribe to " << p.title << "\n";
        return;
    }
    balance -= p.price_per_issue;
    subscriptions_.push_back(p);  // тут копіюється об'єкт Periodical (зв'язок)
    active_subscription_months_ += 1;
    total_paid_ += static_cast<int>(p.price_per_issue);
    std::cout << name << " subscribed to " << p.title << " for 1 month.\n";
}

// Subscribe (2) перевантажений — підписка на months місяців
void Reader::Subscribe(Periodical& p, int months) {
    if (is_blacklisted_) {
        std::cout << "Reader " << name << " is blacklisted; cannot subscribe.\n";
        return;
    }
    double total_cost = p.price_per_issue * months;
    // застосуємо просту знижку якщо months >= 12
    if (months >= 12) {
        total_cost *= 0.9;  // 10% знижка
    }
    if (balance < total_cost) {
        std::cout << "Insufficient funds for " << name << " to subscribe to " << p.title << " for "
            << months << " months.\n";
        return;
    }
    balance -= total_cost;
    subscriptions_.push_back(p);  // додаємо одне видання як підписку (для простоти)
    active_subscription_months_ += months;
    total_paid_ += static_cast<int>(total_cost);
    std::cout << name << " subscribed to " << p.title << " for " << months << " months. Paid: "
        << total_cost << "\n";
}

// LeaveReview — залишає відгук на Periodical (приймає об'єкт) (п.4)
void Reader::LeaveReview(Periodical& p, int rating, const std::string& text) {
    // додаємо відгук через публічний інтерфейс Periodical
    p.AddReview(name, rating, text);
    my_reviews_.push_back({ rating, text });
    std::cout << name << " left a review for " << p.title << "\n";
}

// Duplicate повертає копію Reader (п.4)
Reader Reader::Duplicate() const {
    Reader copy = *this;
    copy.name = name + " (duplicate)";
    // не копіюємо підписки у глибину — але в цьому прикладі копіювання допустиме
    return copy;
}

bool Reader::PayForSubscription(Periodical& p, int months) {
    double total = p.price_per_issue * months;
    if (balance < total) return false;
    balance -= total;
    total_paid_ += static_cast<int>(total);
    active_subscription_months_ += months;
    subscriptions_.push_back(p);
    return true;
}

void Reader::PrintInfo() const {
    std::cout << "Reader{id=" << id << ", name=\"" << name
        << "\", balance=" << balance << ", email=" << email_
        << ", blacklisted=" << (is_blacklisted_ ? "yes" : "no")
        << ", subscriptions=" << subscriptions_.size()
        << ", total_paid=" << total_paid_ << "}\n";
}

// Файлові операції для Reader (п.5)
bool Reader::SaveToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) return false;
    ofs << id << "\n";
    ofs << name << "\n";
    ofs << balance << "\n";
    ofs << email_ << "\n";
    ofs << phone_ << "\n";
    ofs << is_blacklisted_ << "\n";
    ofs << active_subscription_months_ << "\n";
    ofs << total_paid_ << "\n";
    // збережемо кількість підписок та їх id + title
    ofs << subscriptions_.size() << "\n";
    for (const auto& p : subscriptions_) {
        ofs << p.id << "\n";
        ofs << p.title << "\n";
        ofs << p.price_per_issue << "\n";
    }
    // збережемо відгуки
    ofs << my_reviews_.size() << "\n";
    for (const auto& r : my_reviews_) {
        ofs << r.first << "\n";
        ofs << r.second << "\n";
    }
    return true;
}

Reader Reader::LoadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    Reader r;
    if (!ifs) return r;
    ifs >> r.id;
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(ifs, r.name);
    ifs >> r.balance;
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(ifs, r.email_);
    std::getline(ifs, r.phone_);
    ifs >> r.is_blacklisted_;
    ifs >> r.active_subscription_months_;
    ifs >> r.total_paid_;
    size_t subs_n = 0;
    ifs >> subs_n;
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    r.subscriptions_.clear();
    for (size_t i = 0; i < subs_n; ++i) {
        Periodical p;
        ifs >> p.id;
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(ifs, p.title);
        ifs >> p.price_per_issue;
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        r.subscriptions_.push_back(p);
    }
    size_t reviews_n = 0;
    ifs >> reviews_n;
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    r.my_reviews_.clear();
    for (size_t i = 0; i < reviews_n; ++i) {
        int rating;
        std::string text;
        ifs >> rating;
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(ifs, text);
        r.my_reviews_.push_back({ rating, text });
    }
    return r;
}

// Метод-додаток: виділення динамічної пам'яті та сортування (п.12)
void Reader::AllocateAndSortRandomInts() {
    // генерація випадкового розміру (від 5 до 15)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> size_dist(5, 15);
    int n = size_dist(gen);

    int* arr = new int[n];  // виділення динамічної пам'яті

    // наповнення випадковими значеннями (0..99)
    std::uniform_int_distribution<> val_dist(0, 99);
    for (int i = 0; i < n; ++i) {
        arr[i] = val_dist(gen);
    }

    std::cout << "Reader " << name << " allocated array of size " << n << ": ";
    for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
    std::cout << "\n";

    // сортування (вбудований алгоритм)
    std::sort(arr, arr + n);

    std::cout << "Sorted: ";
    for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
    std::cout << "\n";

    delete[] arr;  // звільнення пам'яті
}

// Метод, що працює з покажчиком (використовується в main) (п.11)
void Reader::IncreaseBalanceByPointer(double amount) {
    balance += amount;
}