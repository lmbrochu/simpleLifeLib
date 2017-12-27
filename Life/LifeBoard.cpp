#include "stdafx.h"
#include "LifeBoard.h"
#include <assert.h>

int mod(int x, int m) {
	int r = x % m;
	return r<0 ? r + m : r;
}
LifeBoard::LifeBoard() :m_rows{}
{
}
LifeBoard::LifeBoard(std::vector<std::vector<bool>> const & rows) : m_rows{ rows }
{
	assert(m_rows.size() != 0);
	assert(_allRowsSameSize());
}
bool LifeBoard::isActive(size_t i, size_t j) {
	assert(i < m_rows.size());
	assert(j < m_rows[0].size());
	return m_rows[i][j];
}
void LifeBoard::switchActive(size_t i , size_t j)
{
	m_rows[i][j] = !m_rows[i][j];
}
void LifeBoard::setValue(size_t i, size_t j , bool value) {
	m_rows[i][j] = value;
}
bool LifeBoard::_allRowsSameSize() {
	bool result;
	if (m_rows.size() == 0) {
		result = true;
	}
	else {
		size_t goalSize = m_rows[0].size();
		for (const std::vector<bool> & row : m_rows) {
			if (row.size() != goalSize) {
				result = false;
				break;
			}
		}
		result = true;
	}
	return result;
}
std::vector<std::vector<bool>> LifeBoard::getData() {
	return m_rows;
}
std::vector<std::pair<size_t,size_t>> LifeBoard::computeNextStep() {
	size_t height = m_rows.size();
	size_t width = m_rows[0].size();
	auto rowsCopy = m_rows;
	std::vector<std::pair<size_t, size_t>> changeVec{};
	for (size_t i = 0; i < m_rows.size(); ++i) {
		for (size_t j = 0; j < m_rows[i].size(); ++j) {
			size_t activeNeighbors = 0;
			//count the number of active neighbors
			bool thisSquareDone = false; //Small optimization: no need to count beyond 4 neighbors.
			for (int y = -1; y <= 1; ++y) {
				for (int x = -1; x <= 1; ++x) {
					if (x == 0 && y == 0) {
						continue;
					}
					else {
						if (m_rows[mod(i+x,height)][mod(j + y,width)] == true) {
							activeNeighbors += 1;
							if (activeNeighbors > 3) {
								thisSquareDone = true;
								break;
							}
						}
					}
				}
				if (thisSquareDone) {
					break;
				}
			}
			bool changeToCell = false;
			if (m_rows[i][j] == false) {
				if (activeNeighbors == 3) {
					rowsCopy[i][j] = true;
					changeToCell = true;
				}
			}
			else {
				if (activeNeighbors <= 1 || activeNeighbors > 3) {
					rowsCopy[i][j] = false;
					changeToCell = true;
				}
			}
			if (changeToCell) {
				changeVec.push_back(std::make_pair(i, j));
			}
		}
	}
	m_rows = std::move(rowsCopy);
	return changeVec;
}
LifeBoard::~LifeBoard()
{
}
