#ifndef PERIODICAL_SYSTEM_H_
#define PERIODICAL_SYSTEM_H_

#include <string>
#include <vector>
#include <iostream> 

// forward declaration для уникнення циклічних include (Reader використовується в Periodical методах).
class Reader;

class Periodical {
public:
	// ---------- ПУНКТ: кожен клас має 3 public та >=5 private полів (п.2, п.1)
	// public поля (3 шт.)
	int id;                         // (public #1)
	std::string title;              // (public #2)
	double price_per_issue;         // (public #3)

	// Конструктори
	Periodical();
	Periodical(int id, const std::string& title, double price);

	// Методи (мінімум 6, два з яких перевантажені) (п.4)
	void AddReview(const std::string& reviewer, int rating, const std::string& text);
	void AddReview(int rating, const std::string& text);  // перевантажений (1)
	double CalculateAverageRating() const;
	void RateByReader(const Reader& r, int rating);      // приймає об'єкт класу (п.4)
	Periodical Clone() const;                            // повертає тип класу (п.4)
	void PrintInfo() const;

	// Файлові операції (п.5)
	bool SaveToFile(const std::string& filename) const;
	static Periodical LoadFromFile(const std::string& filename);

	// Метод-додаток: використовує приватні поля, показує всі поля (п.2)
	void DebugShowAllFields() const;

private:
	// приватні поля (мінімум 5)
	std::string publisher_;
	std::string frequency_;               // наприклад "Щомісяця"
	double rating_sum_;
	int rating_count_;
	std::vector<std::pair<std::string, std::string>> reviews_; // (reviewer, text)

	// додаткові приватні поля, щоб мати >=8 полів загалом
	int issues_per_year_;
	double discount_rate_;  // відсоток знижки для підписок
};

class Reader {
public:
	// public поля (3 шт.)
	int id;                       // (public #1)
	std::string name;             // (public #2)
	double balance;               // (public #3) - гроші на рахунку

	// Конструктори
	Reader();
	Reader(int id, const std::string& name, double balance);

	// Методи (мінімум 6, два перевантажені) (п.4)
	void Subscribe(Periodical& p);                        // підписатися на видання
	void Subscribe(Periodical& p, int months);            // перевантажений (1)
	void LeaveReview(Periodical& p, int rating, const std::string& text); // приймає об'єкт
	Reader Duplicate() const;                             // повертає тип класу (п.4)
	bool PayForSubscription(Periodical& p, int months);
	void PrintInfo() const;

	// Файлові операції (п.5)
	bool SaveToFile(const std::string& filename) const;
	static Reader LoadFromFile(const std::string& filename);

	// Метод, що виділяє випадкову величину динамічної пам'яті,
	// розміщує множину значень одного з цілих полів та сортує їх (п.12)
	void AllocateAndSortRandomInts();

	// Демонстрація вказівника на екземпляр (п.11) — покажчик використовується в main,
	// тут є метод для роботи з покажчиком
	void IncreaseBalanceByPointer(double amount);

private:
	// приватні поля (мінімум 5)
	std::string email_;
	std::string phone_;
	bool is_blacklisted_;
	std::vector<Periodical> subscriptions_; // зв'язок: в Reader розміщено об'єкт(и) Periodical (п.3)
	std::vector<std::pair<int, std::string>> my_reviews_; // (rating, text)

	// додаткові приватні поля
	int active_subscription_months_;
	int total_paid_;
};

#endif 