#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
using namespace sf;

template <class ClassType1, class ClassType2>
class CollidingGroup
{
public:
	//CollidingGroup();
	CollidingGroup(ClassType1 *group1 = NULL, ClassType2 *group2 = NULL);
	CollidingGroup(vector<ClassType1*> group1, vector<ClassType2*> group2);
	~CollidingGroup();

	vector <ClassType1*> getFirstGroup();
	vector <ClassType2*> getSecondGroup();

	void setFirstGroup(vector <ClassType1*> newFirstGroup);
	void setSecondGroup(vector <ClassType2*> newSecondGroup);

	void addToFirstGroup(ClassType1 &object);
	void addToSecondGroup(ClassType2 &object);

	void removeFromFirstGroup(ClassType1 *object);
	void removeFromFirstGroup(unsigned int objectNumber);
	void removeFromSecondGroup(ClassType2 *object);
	void removeFromSecondGroup(unsigned int objectNumber);

	void clearFirstGroup();
	void clearSecondGroup();

	bool isCollided(ClassType1 *object1, ClassType2 *object2);
	vector< pair<ClassType1*, ClassType2*> > checkCollisions();

	static unordered_map <string, CollidingGroup<ClassType1, ClassType2>> groupsList;

private:
	vector<ClassType1*> group1;
	vector<ClassType2*> group2;
};


template<class ClassType1, class ClassType2>
inline CollidingGroup<ClassType1, ClassType2>::CollidingGroup(ClassType1 * mainObject, ClassType2 * collidingObject)
{
	if (mainObject != NULL) group1.push_back(mainObject);

	if (collidingObject != NULL) group2.push_back(collidingObject);
}

template<class ClassType1, class ClassType2>
inline CollidingGroup<ClassType1, ClassType2>::CollidingGroup(vector<ClassType1*> group1, vector<ClassType2*> group2)
{
	setFirstGroup(group1);

	setSecondGroup(group2);
}

template<class ClassType1, class ClassType2>
inline CollidingGroup<ClassType1, ClassType2>::~CollidingGroup()
{
}

template<class ClassType1, class ClassType2>
inline vector<ClassType1*> CollidingGroup<ClassType1, ClassType2>::getFirstGroup()
{
	return group1;
}

template<class ClassType1, class ClassType2>
inline vector<ClassType2*> CollidingGroup<ClassType1, ClassType2>::getSecondGroup()
{
	return group2;
}

template<class ClassType1, class ClassType2>
inline void CollidingGroup<ClassType1, ClassType2>::setFirstGroup(vector <ClassType1*> newFirstGroup)
{
	group1 = newFirstGroup;
}

template<class ClassType1, class ClassType2>
inline void CollidingGroup<ClassType1, ClassType2>::setSecondGroup(vector<ClassType2*> newSecondGroup)
{
	group2 = newSecondGroup;
}

template<class ClassType1, class ClassType2>
inline void CollidingGroup<ClassType1, ClassType2>::addToFirstGroup(ClassType1 & object)
{
	ClassType1 *pointer = &object;
	if (pointer != NULL)
		group1.push_back(pointer);
	else
		cout << "Error" << endl; //TODO: Napisaæ komunikat b³êdu
}

template<class ClassType1, class ClassType2>
inline void CollidingGroup<ClassType1, ClassType2>::addToSecondGroup(ClassType2 & object)
{
	ClassType2 *pointer = &object;
	if (pointer != NULL)
		group2.push_back(pointer);
	else
		cout << "Error" << endl; //TODO: Napisaæ komunikat b³êdu
}

template<class ClassType1, class ClassType2>
inline void CollidingGroup<ClassType1, ClassType2>::removeFromFirstGroup(ClassType1 * object)
{
	group1.erase(std::remove(group1.begin(), group1.end(), object), group1.end());

	/*for (int i = 0; i < group1.size(); i++)
	{
		if (group1[i] == object) 
		{ 
			group1.erase(group1.begin() + i); 
			break;
		}
	}*/
}

template<class ClassType1, class ClassType2>
inline void CollidingGroup<ClassType1, ClassType2>::removeFromFirstGroup(unsigned int objectNumber)
{
	if (!group1.empty() && objectNumber < group1.size())
		group1.erase(group1.begin() + objectNumber);
}

template<class ClassType1, class ClassType2>
inline void CollidingGroup<ClassType1, ClassType2>::removeFromSecondGroup(ClassType2 * object)
{
	for (int i = 0; i < group2.size(); i++)
	{
		if (group2[i] == object)
		{
			group2.erase(group2.begin() + i); 
			break;
		}
	}
}

template<class ClassType1, class ClassType2>
inline void CollidingGroup<ClassType1, ClassType2>::removeFromSecondGroup(unsigned int objectNumber)
{
	if(!group2.empty() && objectNumber < group2.size()) 
		group2.erase(group2.begin() + objectNumber);
}

template<class ClassType1, class ClassType2>
inline void CollidingGroup<ClassType1, ClassType2>::clearFirstGroup()
{
	group1.clear();
}

template<class ClassType1, class ClassType2>
inline void CollidingGroup<ClassType1, ClassType2>::clearSecondGroup()
{
	group2.clear();
}

template<class ClassType1, class ClassType2>
inline bool CollidingGroup<ClassType1, ClassType2>::isCollided(ClassType1 *object1, ClassType2 *object2)
{
	FloatRect object1Rect = object1->getGlobalBounds();
	FloatRect object2Rect = object2->getGlobalBounds();

	if (object1Rect.intersects(object2Rect)) { cout << "Kolizja" << endl; return true; }
	else return false;
}

template<class ClassType1, class ClassType2>
inline vector< pair<ClassType1*, ClassType2*> > CollidingGroup<ClassType1, ClassType2>::checkCollisions()
{
	vector< pair<ClassType1*, ClassType2*> > collidedObjectsList;
	for (int i = 0; i < group1.size(); i++)
	{
		for (int j = 0; j < group2.size(); j++)
		{
			if (isCollided(group1[i], group2[j]))
			{
				pair<ClassType1*, ClassType2*> objects;
				objects = make_pair(group1[i], group2[j]);
				collidedObjectsList.push_back(objects);
			}
		}
	}

	return collidedObjectsList;
}
