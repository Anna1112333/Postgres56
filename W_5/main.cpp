#include <iostream>
#include <tuple>
#include <pqxx/pqxx>
#include <Windows.h>
//#pragma execution_character_set( "utf-8" )

class table {
public:
	pqxx::connection& t0;
	table(pqxx::connection& c1): t0{c1} {
	
	};
	pqxx::work t{ t0 };
	//pqxx::result res = t.exec("SELECT 1");

	void create_table() {
		
		std::string table_create, new_table;
		std::cout << "Если вам необходимо создать таблицу для данных введите yes если нет - то no.";
		std::cin >> table_create;
		if (table_create == "yes") { //Создаём таблицу;
			
			std::cout << "Напишите название таблицы: ";
			std::cin >> new_table;

			pqxx::result r = t.exec("create table public." + new_table + " (user_id int4, nane varchar(20),"
				"soname varchar(20), email varchar, phone_number int4);");
					}
		t.commit();
		std::cout << "Ваша таблица "
			<<new_table
			<<" создана и в ней есть поля по умолчанию:user_id, name, soname, email, phone_number\n";
		
	}
	void insert_client(){//работает
		pqxx::result r = t.exec("insert into users (user_id, name, soname) values (12,'Vitor', 'Biriukow');"
		"insert into us_email (user_id_e, email) values (12, 'as@yandex');"
		"insert into us_phone (user_id_ph, phone_number) values (12, 123789);");
	
	t.commit();
	
	}
	void insert_phine(){}
	void change_data_of_client(){}
	void delete_phone(){}
	void delete_client(){

	}
	void faind_client(int r){
		
		for (auto [user_id, name, soname, email, phone_number] : t.query
			<int, std::string, std::string, std::string, long long int>
			("select user_id, coalesce(name, ' ') as name, coalesce(soname, ' ') as soname, "
				"coalesce(email, ' ') as email,  coalesce(phone_number, 0) from "
				"(select * from users left join us_email on users.user_id=us_email.user_id_e) v "
				"left join us_phone on v.user_id=us_phone.user_id_ph order by user_id;"))
		{
			
			std::cout << "user_id = " << user_id << "   name = " << name << "   soname = "
				<< soname << "   email = E" << email << "   phone_number= " << phone_number << std::endl;
		}
	}
};
int main()
{
	
	SetConsoleCP(CP_UTF8);
SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);
	
	setlocale(LC_ALL, "RUS");	 

	try {
		pqxx::connection c(
			"host=localhost " //обязательно пробел
			"port=5432 " //стандартный порт psql
			"dbname=Task5 "
			"user=pq "
			"password=zxc123");
		std::cout << "base exist /n";
	   table a(c);	
	   //a.create_table();
	   int i=0;
	   {             //по русски не выводит
		std::cout << "Insert number for search:  1 by name, 2 by soname, 3 by phone number, 4 by email: ";
		}
	   while (i > 4 || i < 1)
	   {
		std::cin >> i;
		if (i > 4 || i < 1)
			std::cout << "Number was wrong, it should be 1, 2, 3 or 4: ";
	   }

	    a.faind_client(i);
		a.insert_client();
	



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