/*
 * main.cpp
 *
 *  Created on: 9 дек. 2016 г.
 *      Author: Dexiz
 */
#include<iostream>
#include "binary_tree.hpp"

int main(void)
{

	Tree* oak = new Tree;

	oak->Add(26);

	oak->Add(13);

	oak->Add(34);

	oak->Add(20);

	oak->Add(30);
	oak->Add(31);
	oak->Add(29);

	oak->ShowFromMinToMax(oak->GetRoot());
	std::cout << std::endl;

	oak->Delete(13);
	oak->Delete(30);

	//Tree* oak = new Tree;
	//oak->DeleteTree();
	oak->ShowFromMinToMax(oak->GetRoot());

	Tree pine;

	pine.Add(10);
	pine.Add(1);
	pine.Add(2);
	pine.Add(32);
	pine.Add(34);

	//Tree maple = pine;

	Tree birch;

	birch.Add(10);
	birch.Add(1);
	birch.Add(2);
	birch.Add(40);
	birch.Add(50);

	Tree furtree;

	birch = furtree = birch - pine;

	//Tree temp = birch - pine;

	return 0;
}

