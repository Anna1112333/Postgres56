#include <iostream>
#include <tuple>
#include <pqxx/pqxx>
#include <Windows.h>
//#pragma execution_character_set( "utf-8" )

class table {
public:
	
	table(pqxx::connection& c1) : t(c1) {};
	pqxx::work t;
	pqxx::result res = t.exec("SELECT 1");

	void create_table() {
		
		std::string table_create, new_table;
		std::cout << "Если вам необходимо создать таблицу для данных введите yes если нет - то no.";
		std::cin >> table_create;
		if (table_create == "yes") { //Создаём таблицу;
			
			std::cout << "Напишите название таблицы: ";
			std::cin >> new_table;

			pqxx::result r = t.exec("create table " + new_table + " (user_id int, email string);");
					}			
		std::cout << "Ваша таблица "
			<<new_table
			<<" создана и в ней есть поля по умолчанию:user_id, name, soname, email, phone_number\n";
		
	}
	void insert_client(){}
	void insert_phine(){}
	void change_data_of_client(){}
	void delete_phone(){}
	void delete_client(){

	}
	void faind_client(int r){
		setlocale(LC_ALL, "RUS");
		/*for (std::tuple<int, std::string, std::string, std::string, long long int>q1 : t.query<int,
		std::string, std::string, std::string, long long int>("select user_id, name, soname, email, phone_number "
			"from (select * from users"
			" left join us_email on users.user_id=us_email.user_id_e) v"
			" left join us_phone on v.user_id=us_phone.user_id_ph order by user_id;"))
			std::cout << "user_id = " << std::get<0>(q1) << std::endl;
			*/
		for (auto [user_id, name, soname, email, phone_number] : t.query
			<int, std::string, std::string, std::string, long long int>
			("select user_id, name, soname, email, phone_number from "
				"(select * from users left join us_email on users.user_id=us_email.user_id_e) v "
				"left join us_phone on v.user_id=us_phone.user_id_ph order by user_id;"))
		{
			
			std::cout << "user_id = " << user_id << "   name = " << name << "   soname = "
				<< soname << "   email = " << email << "   phone_number= " << phone_number << std::endl;
		}
	}
};
int main()
{
	
	//SetConsoleCP(CP_UTF8);
	//SetConsoleOutputCP(CP_UTF8);
	//setvbuf(stdout, nullptr, _IOFBF, 1000);
	
	setlocale(LC_ALL, "RUS");	 

	try {
		pqxx::connection c(
			"host=localhost " //обязательно пробел
			"port=5432 " //стандартный порт psql
			"dbname=Task5 "
			"user=pq "
			"password=zxc123");
		
	table a(c);	
	a.create_table();
	int i=0;
	{             //по русски не выводит
		std::cout << "Insert number for search:  1 by name, 2 by soname, 3 by phone number, 4 by email: ";
		//setlocale(LC_ALL, "UTF8");
	}
	while (i > 4 || i < 1)
	{
		std::cin >> i;
		if (i > 4 || i < 1)
			std::cout << "Number was wrong, it should be 1, 2, 3 or 4: ";
	}

	a.faind_client(i);	
	



	}
	catch(pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}