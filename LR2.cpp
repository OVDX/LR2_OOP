#include "Admin.h"
#include "DigitalPublication.h"
#include "Publication.h"
#include "Reader.h"
#include "SubscriptionManager.h"
#include <iostream>

int main() {
    std::cout << "\n===  DEMONSTRATION START ===\n\n";

    // 🔹 1️ Ієрархія класів (BaseUser -> Reader / Admin; Publication -> DigitalPublication)
    std::cout << "1️ Створення ієрархії класів та об'єктів:\n";
    Publication p1(1, "Nature", "Science", 150, 4.8, 12, "Nature Ltd");
    DigitalPublication dp(2, "TechWorld", "IT", 99.9, 4.6, 10, "TechGroup",
        25.5, "PDF", "techworld.com/download");
    std::cout << "   -> Publication і DigitalPublication створено успішно.\n\n";

    Reader r1(1, "Erik", "erik@mail.com", "Reader", 500, "12345");
    Admin a1(100, "Alex", "admin@mail.com", "Admin", 1000, "root");
    std::cout << "   -> Reader та Admin створені (наслідування від BaseUser).\n\n";

    // 🔹 2️ Демонстрація public / protected / private доступу
    std::cout << "2️ Демонстрація рівнів доступу (public, protected, private):\n";
    r1.PrintBasicInfo();            // публічний метод
    r1.AccessBaseActions();         // демонстрація protected доступу
    std::cout << "   -> Показано різницю між public/protected/private доступом.\n\n";

    // 🔹 3️ Private inheritance (Admin володіє Reader)
    std::cout << "3️ Private inheritance (Admin створює внутрішні Reader):\n";
    a1.AddReader(r1);
    a1.ShowAllReaders();
    std::cout << "   -> Admin має власних Reader через private успадкування.\n\n";

    // 🔹 4️ Множинне наслідування (SubscriptionManager від Admin + Publication)
    std::cout << "4️ Множинне наслідування (SubscriptionManager):\n";
    SubscriptionManager sm("MGR-01", 10, "Kate", "kate@mail.com",
        "Manager", 600, "pass");
    sm.ManageSubscription();
    std::cout << "   -> SubscriptionManager використовує властивості Admin + Reader.\n\n";

    // 🔹 5️ Передача параметрів базовому класу через конструктор
    std::cout << "5️ Передача параметрів базовому класу через конструктор DigitalPublication:\n";
    DigitalPublication dp2(5, "Science Daily", "Education", 120, 4.7, 7,
        "SciPress", 12.3, "EPUB", "scidaily.com");
    dp2.DisplayInfo();
    std::cout << "   -> Параметри передано до базового класу Publication.\n\n";

    // 🔹 6️ Доступ до членів базового класу через global scope operator та using
    std::cout << "6️ Використання оператора :: та using:\n";
    r1.BaseUser::BlockUser(); // доступ через оператор глобального простору імен
    std::cout << "   -> Викликано метод базового класу через глобальний доступ (::BaseUser).\n\n";

    // 🔹 7️ Порядок виклику конструкторів/деструкторів
    std::cout << "7️ Демонстрація виклику конструкторів та деструкторів:\n";
    {
        Reader tempReader(3, "Mike", "mike@mail.com", "Reader", 100, "2222");
        DigitalPublication tempPub;
        std::cout << "   -> Внутрішній блок завершено, викликаються деструктори...\n";
    }
    std::cout << "   -> Вихід з блоку завершено.\n\n";

    // 🔹 8️ Демонстрація взаємодії трьох об'єктів (асоціація)
    std::cout << "8️ Асоціація: Reader оформлює підписку на Publication через SubscriptionManager:\n";
    sm.CreateSubscription(r1, dp);
    std::cout << "   -> Заявка створена.\n\n";

    // 🔹 9️ Агрегація: Admin керує наявними Reader (Admin має список Reader)
    std::cout << "9️ Агрегація: Admin -> Reader (список користувачів):\n";
    a1.AddReader(Reader(5, "Bob", "bob@mail.com", "Reader", 300, "9999"));
    a1.ShowAllReaders();
    std::cout << "   -> Admin керує Reader, але ті існують самостійно.\n\n";

    // 🔹 10 Композиція: Publication має в собі рейтинг (частина видання)
    std::cout << "10 Композиція: Publication створює власний Rating об'єкт.\n";
    dp.AddRating(5, "Дуже цікаве видання!");
    dp.ShowRatings();
    std::cout << "   -> Rating існує тільки в межах DigitalPublication.\n\n";

    std::cout << "=== DEMONSTRATION END ===\n";
    return 0;


}