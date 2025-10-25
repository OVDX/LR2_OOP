#ifndef READER_H
#define READER_H

#include "Publication.h"
#include <string>
#include <vector>

class Reader {
private:
	int id_;
	std::string name_;
	std::string email_;
	std::vector<Publication> subscriptions_;
	double balance_;
	int warnings_;
	bool blacklisted_;
	int random_values_count_;
	int* random_values_;

public:
	static int reader_count_;  // спільне поле

	// Конструктори
	Reader();
	Reader(int id, std::string name, std::string email, double balance);
	Reader(const Reader& other);
	~Reader();

	// Методи
	void Subscribe(const Publication& pub);
	void Pay(double amount);
	void PrintInfo() const;
	double CalculateTotal() const;
	double CalculateTotal(bool include_discount) const;
	void AllocateRandomValues(int count);
	void SaveToFile(const std::string& filename) const;
	void LoadFromFile(const std::string& filename);
	static int GetReaderCount();
};

#endif
