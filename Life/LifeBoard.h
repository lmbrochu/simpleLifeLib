#pragma once
#include "stdafx.h"
class LifeBoard
{
public:
	LifeBoard();
	LifeBoard(std::vector<std::vector<bool>> const &);
	~LifeBoard();
	bool isActive(size_t, size_t);
	void switchActive(size_t, size_t);
	void setValue(size_t, size_t, bool);
	std::vector<std::vector<bool>> getData();
	std::vector<std::pair<size_t, size_t>> computeNextStep();
private:
	std::vector<std::vector<bool>> m_rows;
	bool _allRowsSameSize();
};

