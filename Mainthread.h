#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Compressedstation.h"
#include "Pipeline.h"
#include <set>

#include <algorithm>
#include <stdexcept>
#include "utils.h"




class Mainthread
{
private:

	void EditCompressedstation(Compressedstation& s, int num);

	Pipeline LoadPipeline(std::ifstream& fin);
	Compressedstation LoadCompressedstation(std::ifstream& fin);
	void SavePipeline(std::ofstream& fout, const Pipeline& s);
	void SaveCompressedstation(std::ofstream& fout, const Compressedstation& s);
public:
	std::set<Pipeline> Pipelines;
	std::set<Compressedstation> Compressedstations;
	Mainthread();

	void PipelineMenu();
	void CompressedstationMenu();

	void saveFunction();
	void loadFunction();
	void editCompressedstation(std::vector<std::reference_wrapper<Compressedstation>>& CompressedstationMask);
	void editPipeline(std::vector<std::reference_wrapper<Pipeline>>& PipelineMask);
};



template<typename T>
bool CheckByName(const T& obj, const std::string& param) {
	return obj.getName() == param;
}

template<typename T>
bool CheckByRepair(const T& obj, const int& param) {
	return obj.repair == param;
}

template<typename T>
bool CheckByPercentage(const T& obj, const int& param) {
	double coefficient = static_cast<double>(obj.getLengthOfStableWorkshop()) / obj.getLengthOfWorkshop();
	coefficient = std::isnan(coefficient) ? 0.0 : coefficient;
	switch (param)
	{
	case 1: {
		return (1 >= coefficient && 0.8 <= coefficient);
	}
	case 2: {
		return (0.79 >= coefficient && 0.59 <= coefficient);
	}
	case 3: {
		return (0.58 >= coefficient && 0.38 <= coefficient);
	}
	case 4: {
		return (0.37 >= coefficient && 0.17 <= coefficient);
	}
	case 5: {
		return (0.16 >= coefficient && 0 <= coefficient);
	}
	}
}




template<typename Container, typename FilterFunc, typename Param>
auto FindByFilter(const Container& group, FilterFunc f, Param param) {
	using ElementType = typename Container::value_type;

	std::vector<ElementType> res;

	for (const auto& item : group) {
		if (f(item, param))
			res.push_back(item);
	}
	return res;
}




template<typename T>
T& Select(std::set<T>& g, uint64_t criticalnum = 9999)
{

	if (g.empty()) {
		throw std::runtime_error("No pipelines available");
	}

	std::vector<uint64_t> allowed;
	for (const T& i : g) {
		allowed.push_back(static_cast<uint64_t>(i.getId()));
	}





	allowed.push_back(criticalnum);
	if (criticalnum == 9999) {
		std::cout << "Type id: ";
	}
	else {
		std::cout << "[stop - " + std::to_string(criticalnum) + "]: ";
	}
	uint64_t num = GetCorrectNumberAllowed(allowed);

	if (num == criticalnum) {
		throw std::runtime_error("Stop selected");
	}

	auto it = std::find_if(g.begin(), g.end(),
		[num](const T& station) {
			return static_cast<uint64_t>(station.getId()) == num;
		});

	if (it != g.end()) {
		return const_cast<T&>(*it);
	}

	throw std::runtime_error("Not found");
}




template<typename T>
uint64_t GetMax(std::set<T>& g)
{
	if (g.empty()) {
		throw std::runtime_error("No pipelines available");
	}

	std::vector<uint64_t> allowed;
	for (const T& i : g) {
		allowed.push_back(static_cast<uint64_t>(i.getId()));
	}

	uint64_t max_it = *max_element(allowed.begin(), allowed.end());
	return max_it;
}