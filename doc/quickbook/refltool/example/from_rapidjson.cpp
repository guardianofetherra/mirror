/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[refltool_example_from_rapidjson_1
#include <refltool/from_rapidjson.hpp>
#include <refltool/enum_to_string.hpp>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <algorithm>
#include <iostream>
//]
//[refltool_example_from_rapidjson_2
enum prize_category
{
	physics,
	chemistry,
	medicine,
	literature,
	peace
};

enum laureate_kind
{
	individual,
	organization
};

struct prize_laureate
{
	laureate_kind kind;
	std::string name;

};

struct nobel_prize
{
	prize_category category;
	int year;
	std::vector<prize_laureate> laureates;
};
//]
//[refltool_example_from_rapidjson_3
int main(void)
{
	using namespace refltool;

	const std::string input(...);

	// parse rapidjson document
	rapidjson::Document doc;
	doc.Parse(input.data(), input.size());

	// load from rapidjson representation
	std::vector<nobel_prize> some_nobel_prizes;
	__from_rapidjson(doc, some_nobel_prizes);

	auto is_org = [](const prize_laureate& l) {
		return l.kind == organization;
	};
	auto is_ind = [](const prize_laureate& l) {
		return l.kind == individual;
	};

	for(const auto& prize : some_nobel_prizes) {

		auto ind_n = std::count_if(
			prize.laureates.begin(),
			prize.laureates.end(),
			is_ind
		);

		auto org_n = std::count_if(
			prize.laureates.begin(),
			prize.laureates.end(),
			is_org
		);

		std::cout
			<< __enum_to_string(prize.category)
			<< " "
			<< prize.year
			<< ": ";

		if(ind_n > 1) {
			std::cout << ind_n << " individuals";
		} else if (ind_n > 0) {
			std::cout << "1 individual";
		}

		if((ind_n > 0) && (org_n > 0)) {
			std::cout << " and ";
		}

		if(org_n > 1) {
			std::cout << org_n << " organizations";
		} else if (org_n > 0) {
			std::cout << "1 organization";
		}
		std::cout << std::endl;
	}

	return 0;
}
//]
//[refltool_example_from_rapidjson_input
[{
	"category" : "physics",
	"year" : 2016,
	"laureates" : [{
		"kind" : "individual",
		"name" : "David J. Thouless"
	},{
		"kind" : "individual",
		"name" : "F. Duncan M. Haldane"
	},{
		"kind" : "individual",
		"name" : "J. Michael Kosterlitz"
	}]
},{
	"category" : "chemistry",
	"year" : 2016,
	"laureates" : [{
		"kind" : "individual",
		"name" : "Jean-Pierre Sauvage"
	},{
		"kind" : "individual",
		"name" : "Sir J. Fraser Stoddart"
	},{
		"kind" : "individual",
		"name" : "Bernard L. Feringa"
	}]
},{
	"category" : "medicine",
	"year" : 2016,
	"laureates" : [{
		"kind" : "individual",
		"name" : "Yoshinori Ohsumi"
	}]
},{
	"category" : "literature",
	"year" : 2016,
	"laureates" : [{
		"kind" : "individual",
		"name" : "Bob Dylan"
	}]
},{
	"category" : "peace",
	"year" : 2015,
	"laureates" : [{
		"kind" : "organization",
		"name" : "National Dialogue Quartet"
	}]
},{
	"category" : "peace",
	"year" : 2007,
	"laureates" : [{
		"kind" : "organization",
		"name" :"Intergovernmental Panel on Climate Change"
	},{
		"kind" : "individual",
		"name" :"Albert Arnold Gore Jr."
	}]
}]
//]
//[refltool_example_from_rapidjson_output
physics 2016: 3 individuals
chemistry 2016: 3 individuals
medicine 2016: 1 individual
literature 2016: 1 individual
peace 2015: 1 organization
peace 2007: 1 individual and 1 organization
//]
