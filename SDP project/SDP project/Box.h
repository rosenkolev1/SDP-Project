#pragma once

#include <iostream>
#include <vector>
#include <string>

class Box
{
private:

	std::string name;
	std::vector<std::string> souvenirs;
	std::vector<std::shared_ptr<Box>> boxes;

	void copy(const Box& other);

public:
	Box()
		:Box("")
	{
	}

	Box(std::string name)
		:Box(name, std::vector<std::string>(), std::vector<std::shared_ptr<Box>>())
	{
		this->name = name;
		this->souvenirs = std::vector<std::string>();
		this->boxes = std::vector<std::shared_ptr<Box>>();
	}

	Box(std::string name, std::vector<std::string> souvenirs)
	{
		this->name = name;
		this->souvenirs = souvenirs;
		this->boxes = std::vector<std::shared_ptr<Box>>();
	}

	Box(std::string name, std::vector<std::string> souvenirs, std::vector<std::shared_ptr<Box>> boxes)
	{
		this->name = name;
		this->souvenirs = souvenirs;
		this->boxes = boxes;
	}

	Box(const Box& other)
	{
		this->copy(other);
	}

	Box& operator= (const Box& other)
	{
		this->copy(other);
		return *this;
	}

	std::string getName() const
	{
		return this->name;
	}

	const std::vector<std::string>& getSouvenirs() const
	{
		return this->souvenirs;
	}

	const std::vector<std::shared_ptr<Box>>& getNestedBoxes() const
	{
		return this->boxes;
	}

	void addBox(std::shared_ptr<Box> box);

	void simplifyBox();

	std::string toString(int boxTabs = 0) const;

	void print(std::ostream& out) const
	{
		out << this->toString(0);
	}
};