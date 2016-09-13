#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"


using namespace std;
namespace {
	SMapChipLocInfo mapChipLocInfoTable[] = {
		#include "locationInfo.h"
	};
}

Map::Map()
{

}

Map::~Map()
{
	for (auto& mapChip : mapChipList){
		delete mapChip;
	}
}

void Map::Start()
{
	//�z�u��񂩂�}�b�v���\�z�H
	int tableSize = sizeof(mapChipLocInfoTable) / sizeof(mapChipLocInfoTable[0]);
	for (int i = 0; i < tableSize; i++){
		
		MapChip* mapChip = new MapChip;
		mapChip->Init(&mapChipLocInfoTable[i]);
		mapChipList.push_back(mapChip);
	}
}


void Map::Update()
{
	//�A�b�v�f�[�g�֐��������Ăяo��
	for (auto& mapChip : mapChipList){
		mapChip->Update();
	}
}

void Map::Render()
{
	//Render�֐��������Ăяo��
	for (auto& mapChip : mapChipList){
		mapChip->Render();
	}
}