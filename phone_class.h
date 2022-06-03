#ifndef PHONE_CLASS_H
#define PHONE_CLASS_H

#include "base_class.h"
#include "controller_class.h"

class PhoneClass : public BaseClass
{
public:

	PhoneClass(string obj_name, BaseClass* parent_ptr);

	void TrySignal(string path, string message) override;

	void TryHandler(string path, string message) override;
private:

	struct phone_struct
	{
		string phone_number = "";
		size_t connected_tower_number = 0;
		string phone_stats = "";
	};

	vector<phone_struct> phones_list_ = {};

	void SetupPhone(string message);

	string get_phones_info(string message);
};

#endif // !PHONE_CLASS_H