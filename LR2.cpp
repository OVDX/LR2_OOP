#include "Publication.h"
#include "Reader.h"
#include <iostream>

// --- Функції поза класом ---
void AnalyzeReader(const Reader& r) {
    std::cout << "[Func by value] Total = " << r.CalculateTotal() << std::endl;
}

void AnalyzeReader(const Reader* r) {
    std::cout << "[Func by pointer] Total = " << r->CalculateTotal(true)
        << std::endl;
}

// --- Функція, яка повертає об’єкт класу ---
Publication CreatePublication() {
    Publication p(5, "Forbes", "Business", 120, 4.8, 44, "Forbes Media");
    return p;
}

int main() {
    srand(time(nullptr));

    // 1️ Демонстрація створення різними конструкторами
    Publication p1;
    Publication p2(1, "Tech Today", "IT", 99.9, 4.6, 120, "TechGroup");
    Publication p3 = p2;  // копіювання
    int subs = 10;
    Publication p4(2, "Nature", "Science", 150, 4.9, 10, "Nature Ltd", subs);

    // 2️ Статичне поле
    std::cout << "Total publications: " << Publication::GetPublicationCount()
        << std::endl;

    // 3️ Об'єкти класу Reader
    Reader r1(1, "Erik", "erik@mail.com", 500);
    Reader* r2 = new Reader(2, "Max", "max@mail.com", 300);
    r1.Subscribe(p2);
    r1.Subscribe(p4);

    // 4️ Функції поза класом
    AnalyzeReader(r1);
    AnalyzeReader(r2);

    // 5️ Функція, що повертає об’єкт
    Publication new_pub = CreatePublication();
    new_pub.PrintInfo();

    // 6️ Використання динамічної пам'яті
    r2->AllocateRandomValues(8);

    // 7️ Масиви об’єктів
    Reader readers_static[2] = { r1, *r2 };
    Reader* readers_dynamic = new Reader[2];

    // 8️ Взаємодія — Асоціація
    std::cout << "Association: Reader subscribes publication\n";
    r1.Subscribe(p1);

    // 9️ Агрегація
    std::cout << "Aggregation: Reader references external publication\n";
    Publication& ref_pub = p4;
    ref_pub.UpdateRating(5.0);

    // 10 Композиція (Reader містить Publication у векторі)
    std::cout << "Composition: Reader owns publications\n";
    r1.PrintInfo();

    delete[] readers_dynamic;
    delete r2;

    return 0;
}
