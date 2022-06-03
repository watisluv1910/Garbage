#ifndef TOWER_CLASS_H
#define TOWER_CLASS_H

#include "base_class.h"
#include "tower_struct.h"

class TowerClass : public BaseClass
{
public:

	TowerClass(string obj_name, BaseClass* parent_ptr);

	void TrySignal(string path, string message) override;

	void TryHandler(string path, string message) override;
private:

	vector<tower_struct> towers_list_ = {};

	bool is_ready_to_work_ = false;

	void SetupTower(string message);

	void ClearTowerStats();

	void UpdateTowers(string message, const string direction = "UPDATE");

	string get_tower_stats(size_t index);
};

#endif // !TOWER_CLASS_H