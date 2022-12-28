#pragma once

#include "Box.h"
#include <string>

std::string Box::toString(int boxTabs) const
{
	std::string nestedIndent = "";
	for (int i = 0; i < boxTabs; i++)
	{
		nestedIndent += "	";
	}

	std::string result = "";

	result += nestedIndent + "--------------------------------------------------------" + '\n';
	result += nestedIndent + "The box is:" + '\n';
	result += nestedIndent + "Name: " + this->name + "\n";

	result += nestedIndent + "Souvenirs: ";
	for (int i = 0; i < this->souvenirs.size(); i++)
	{
		std::string souvenir = this->souvenirs[i];
		result += souvenir + (i != this->souvenirs.size() - 1 ? ", " : "");
	}
	result += "\n";

	result += nestedIndent + "Boxes: " + "\n";
	for (int i = 0; i < this->boxes.size(); i++)
	{
		std::shared_ptr<Box> nestedBox = this->boxes[i];
		result += nestedBox->toString(boxTabs + 1) + "\n";
	}

	result += nestedIndent + "--------------------------------------------------------" + '\n';

	return result;
}

void Box::addBox(std::shared_ptr<Box> box)
{
	/*std::cout << "Parent box: " << this << "\n";
	std::cout << "Nested box: " << &box << "\n";*/
	//this->boxes.push_back(box);
	/*auto something = std::make_shared<Box>(box);
	this->boxes.emplace_back(something);*/
	//std::cout << "Nested box: " << &this->boxes[0] << "\n";
	this->boxes.push_back(box);
}

void Box::copy(const Box& other)
{
	this->name = other.name;
	this->souvenirs = other.souvenirs;
	this->boxes = std::vector<std::shared_ptr<Box>>();

	for (std::shared_ptr<Box> box : other.boxes)
	{
		auto newBox = std::make_shared<Box>(*box);
		this->addBox(newBox);
	}
}

void Box::simplifyBox()
{
	for (int i = 0; i < this->boxes.size(); i++)
	{
		auto box = this->boxes[i];

		box->simplifyBox();

		if (box->boxes.size() == 1 && box->souvenirs.size() == 0)
		{
			box = box->boxes[0];
			this->boxes[i] = box;
		}
		else if (box->boxes.size() == 0 && box->souvenirs.size() == 0)
		{
			this->boxes.erase(this->boxes.begin() + i);
			i -= 1;
		}
	}
}