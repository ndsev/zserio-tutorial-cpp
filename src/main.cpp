#include <tutorial/Employee.h>
#include <fstream>
#include <iostream>


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "usage: zserio $mode[write_joe, write_boss, read]";
		return 0;
	}

	/* Writing a zserio stream */

	if (argv[1] == std::string("write_joe"))
	{
		/* Declare an employee */
		tutorial::Employee joe;

		/* Fill some basic type fields */
		joe.setAge(32);
		joe.setName("Joe Smith");
		joe.setSalary(5000);

		/* Set an enum value, in this case the role */
		joe.setRole(tutorial::Role::DEVELOPER);

		/* Declare a zserio object array which holds a zserio struct */
		zserio::ObjectArray<tutorial::Experience> skills;

		/* Declare and fill the struct Experience */
		tutorial::Experience skill1;
		skill1.setYearsOfExperience(8);
		skill1.setProgrammingLanguage(tutorial::Language::CPP);
		skills.push_back(skill1);

		/* Fill a second one... */

		tutorial::Experience skill2;
		skill2.setProgrammingLanguage(tutorial::Language::PYTHON);
		skill2.setYearsOfExperience(4);
		skills.push_back(skill2);

		/* Assign the zserio object array to object joe */
		joe.setSkills(skills);

		/* Declare a zserio BitStream writer */
		zserio::BitStreamWriter writer;

		/* Serialize the object joe by passing the BitStream writer to its .write() method */
		try
		{
			joe.write(writer);
		}
		catch (zserio::CppRuntimeException &e)
		{
			std::cout << e.what();
		}

		/* The default constructor of the BitstreamWriter has allocated a buffer */
		size_t size;
		const uint8_t* buffer = writer.getWriteBuffer(size);

		/* Write the buffer to disk */
		std::ofstream os("employee.zsb", std::ofstream::binary);
		os.write(reinterpret_cast<const char*>(buffer), size);
		os.close();
	}

	if (argv[1] == std::string("write_boss"))
	{
		/* Declare an employee */
		tutorial::Employee boss;

		/* Fill some basic type fields */
		boss.setAge(43);
		boss.setName("Joe's Boss");
		boss.setSalary(9000);

		/* Set an enum value, in this case the role */
		boss.setRole(tutorial::Role::TEAM_LEAD);

		/* No programming skills for the boss, but a bonus! */

		boss.setBonus(10000);


		/* Declare a zserio BitStream writer */
		zserio::BitStreamWriter writer;

		/* Serialize the object joe by passing the BitStream writer to its .write() method */
		try
		{
			boss.write(writer);
		}
		catch (zserio::CppRuntimeException &e)
		{
			std::cout << e.what();
		}

		/* The default constructor of the BitstreamWriter has allocated a buffer */
		size_t size;
		const uint8_t* buffer = writer.getWriteBuffer(size);

		/* Write the buffer to disk */
		std::ofstream os("employee.zsb", std::ofstream::binary);
		os.write(reinterpret_cast<const char*>(buffer), size);
		os.close();
	}


	/* Reading a zserio stream */

	if (argv[1] == std::string("read"))
	{
		/* Read the complete buffer from file */
		std::ifstream is("employee.zsb", std::ifstream::binary);
		is.seekg(0, is.end);
		size_t length = is.tellg();
		is.seekg(0, is.beg);
		char* buffer = new char[length];
		is.read(buffer, length);

		/* Declare the zserio BitStreamReader and assign the buffer */
		zserio::BitStreamReader reader((const uint8_t*)buffer, length);

		/* Deserialize the stream to an Employee class */
		tutorial::Employee employee;
		employee.read(reader);

		
		/* Data types that are always available can simply be assigned */
		std::string name = employee.getName();
		std::uint8_t age = employee.getAge();
		std::uint16_t salary = employee.getSalary();
		
		tutorial::Role role = employee.getRole();
		

		/* We have to check for optionals whether they are in the stream */
		std::uint16_t bonus = 0;
		if(employee.hasBonus())
			bonus = employee.getBonus();

		/* We also have to check for conditions if they applied. */
		zserio::ObjectArray<tutorial::Experience> skills;
		if (employee.hasSkills())
			skills = employee.getSkills();
			 
		/* Process all skills. In this case copy all skills to an output string */
		std::stringstream skill_str;

		if (!skills.empty())
		{
			/* Read out each programming skill */
			for (int i = 0; i < skills.size(); i++)
			{
				tutorial::Experience experience = skills[i];

				std::uint8_t years = experience.getYearsOfExperience();
				tutorial::Language lang = experience.getProgrammingLanguage();

				/* Get string representation of Language enum value */
				std::string lang_str = lang.toString();

				/* add to result string stream */
				skill_str << "Language " << lang_str << " --- " << (int)years << " years\n";
			}
		}

		// Print out the contents of Employee
		std::cout << "Name: " << name << "\n";
		std::cout << "Age: " << (int)age << "\n";
		std::cout << "Salary: " << salary << "\n";
		std::cout << "Bonus: " << bonus << "\n";
		std::cout << skill_str.str() ;
	}
	return 0;
}