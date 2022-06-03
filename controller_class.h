#ifndef CONTROLLER_CLASS_H
#define CONTROLLER_CLASS_H

#include "base_class.h"

class ControllerClass : public BaseClass
{
public:

	ControllerClass(string obj_name, BaseClass* parent_ptr);

	void TrySignal(string path, string message) override;

	void TryHandler(string path, string message) override;
private:

	size_t current_system_cycle_ = 0;

	struct phones_connection
	{
		string caller_phone = "", respondent_phone = "";

		// Remaining number of cycles for this connection
		long long remaining_cycles_number = 0; 

		string occupied_towers = "";
	};

	phones_connection temp_connection;

	vector<phones_connection> conversations_list_ = {};

	bool IsBusy(string message, bool& respondent_is_busy);

	void set_temp_connection(string message);

	void SortConversations();

	string get_occupied_towers(string message);

	string get_conversation_stats(size_t index);

	void UpdateConversations();
};

#endif // !CONTROLLER_CLASS_H