#include "periodical_system.h"

#include <iostream>
#include <memory>  // для smart pointers (демонстрація)
#include <array>

int main() {
    std::cout << "=== Demo: Система Періодичних Видань ===\n";

    // --------------------------
    // ПУНКТ 6: 5 об'єктів у статичній пам'яті
    // (п'ять статичних об'єктів Periodical і Reader)
    Periodical p1(1, "Tech Monthly", 5.0);
    Periodical p2(2, "Nature Weekly", 3.0);
    Periodical p3(3, "History Quarterly", 7.5);
    Periodical p4(4, "Cooking Daily", 1.0);
    Periodical p5(5, "Science Today", 6.0);

    Reader r1(1, "Ivan", 50.0);
    Reader r2(2, "Olena", 20.0);
    Reader r3(3, "Mykola", 5.0);
    Reader r4(4, "Kateryna", 100.0);
    Reader r5(5, "Oleg", 0.0);

    // --------------------------
    // ПУНКТ 6: 5 об'єктів у динамічній пам'яті
    Periodical* dp1 = new Periodical(10, "Dynamic Tech", 4.0);
    Periodical* dp2 = new Periodical(11, "Dynamic Nature", 2.5);
    Periodical* dp3 = new Periodical(12, "Dynamic History", 8.0);
    Periodical* dp4 = new Periodical(13, "Dynamic Cooking", 1.2);
    Periodical* dp5 = new Periodical(14, "Dynamic Science", 5.5);

    Reader* dr1 = new Reader(10, "Diana", 40.0);
    Reader* dr2 = new Reader(11, "Taras", 30.0);
    Reader* dr3 = new Reader(12, "Sasha", 12.0);
    Reader* dr4 = new Reader(13, "Lina", 200.0);
    Reader* dr5 = new Reader(14, "Bohdan", 3.0);

    // --------------------------
    // ПУНКТ 7: визначити 2 масиви об'єктів (використаємо std::array та C-style)
    // Масив 1: std::array статичних Periodical
    std::array<Periodical, 5> periodicals_static = { p1, p2, p3, p4, p5 };

    // Масив 2: C-style масив динамічних Reader (копії значення об'єктів pointed)
    Reader reader_array[5] = { *dr1, *dr2, *dr3, *dr4, *dr5 };

    // --------------------------
    // ПУНКТ 8: продемонструвати роботу з об'єктами в масивах
    std::cout << "\n-- Масив periodicals_static --\n";
    for (const auto& p : periodicals_static) {
        p.PrintInfo();
    }

    std::cout << "\n-- Масив reader_array --\n";
    for (const auto& r : reader_array) {
        r.PrintInfo();
    }

    // --------------------------
    // ПУНКТ 9: продемонструвати роботу усіх методів, описаних у класах.
    // Періодичні: AddReview (перевантажені), CalculateAverageRating, Clone, Save/Load, DebugShowAllFields
    p1.AddReview("Anna", 5, "Дуже цікава стаття про ІІ.");
    p1.AddReview(4, "Корисні поради.");  // перевантажений
    std::cout << "Average rating p1: " << p1.CalculateAverageRating() << "\n";

    Periodical p1_clone = p1.Clone();
    p1_clone.PrintInfo();

    p1.SaveToFile("p1.txt");
    Periodical loaded_p1 = Periodical::LoadFromFile("p1.txt");
    std::cout << "Loaded from file: ";
    loaded_p1.DebugShowAllFields();

    // Reader: Subscribe (перевантажені), LeaveReview, Duplicate, PayForSubscription, File I/O, AllocateAndSortRandomInts
    r1.Subscribe(p2);             // один місяць
    r1.Subscribe(p3, 12);         // підписка на рік (перевантаження)
    r1.LeaveReview(p3, 5, "Чудова добірка матеріалів.");
    Reader r1_copy = r1.Duplicate();
    r1_copy.PrintInfo();

    r1.SaveToFile("r1.txt");
    Reader loaded_r1 = Reader::LoadFromFile("r1.txt");
    std::cout << "Loaded reader: ";
    loaded_r1.PrintInfo();

    // Allocate and sort random ints (п.12)
    r2.AllocateAndSortRandomInts();

    // --------------------------
    // ПУНКТ 10: сценарій взаємодії двох об'єктів
    // Наприклад: читач r4 купує (підписується) на видання p5 та залишає відгук.
    std::cout << "\n-- Сценарій взаємодії (Reader купує Periodical) --\n";
    r4.PrintInfo();
    p5.PrintInfo();
    r4.Subscribe(p5, 6);  // r4 підписується на 6 місяців
    r4.LeaveReview(p5, 5, "Підписка дуже зручна!");
    p5.PrintInfo();
    r4.PrintInfo();

    // --------------------------
    // ПУНКТ 11: використання покажчика на екземпляр класу
    Reader* ptr = &r1;  // показуємо на статичний об'єкт
    std::cout << "\n-- Pointer demo перед збільшенням балансу --\n";
    ptr->PrintInfo();
    ptr->IncreaseBalanceByPointer(15.0);  // змінюємо через вказівник
    std::cout << "-- Після IncreaseBalanceByPointer(15.0) --\n";
    ptr->PrintInfo();

    // також використовуємо smart pointer (демонстрація)
    std::unique_ptr<Reader> up_reader = std::make_unique<Reader>(99, "UniqueReader", 123.0);
    up_reader->PrintInfo();

    // --------------------------
    // ПУНКТ 12 (додатковий метод вже викликано у r2.AllocateAndSortRandomInts())

    // --------------------------
    // ПУНКТ 3: зв'язок двох об'єктів шляхом розміщення об'єкта одного класу в іншому
    // (в Reader::subscriptions_ зберігається Periodical — це показано вище підписками)

    // --------------------------
    // Демо: виклик RateByReader (метод Periodical приймає об'єкт Reader)
    p2.RateByReader(r1, 4);

    // --------------------------
    // ПУНКТ 8 додатково: робота з масивом periodicals_static - демонструємо виклик методів на елементах масиву
    std::cout << "\n-- Оновлення рейтингу всіх періодичних у масиві --\n";
    for (auto& p : periodicals_static) {
        p.AddReview("BatchUser", 4, "Batch review");
        std::cout << p.title << " avg rating: " << p.CalculateAverageRating() << "\n";
    }

    // --------------------------
    // Очищення динамічних об'єктів (п.6)
    delete dp1;
    delete dp2;
    delete dp3;
    delete dp4;
    delete dp5;

    delete dr1;
    delete dr2;
    delete dr3;
    delete dr4;
    delete dr5;

    std::cout << "\n=== Demo finished ===\n";
    return 0;
}