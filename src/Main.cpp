#include <iostream>
#include <string>
#include <vector>

#include <zserio/SerializeUtil.h>
#include <zserio/Enums.h>

#include "tutorial/Employee.h"

void printHelp()
{
    std::cout << "Usage: ZserioTutorialCpp write_joe|write_boss|read" << std::endl;
}

void writeJoe(const std::string& employeeFile)
{
    /* declare an employee */
    tutorial::Employee joe;

    /* fill some basic type fields */
    joe.setAge(32);
    joe.setName("Joe Smith");
    joe.setSalary(5000);

    /* set an enum value, in this case the role */
    joe.setRole(tutorial::Role::DEVELOPER);

    /* declare an array which holds a zserio struct */
    std::vector<tutorial::Experience> skills;

    /* declare and fill the struct Experience */
    tutorial::Experience skill1;
    skill1.setYearsOfExperience(8);
    skill1.setProgrammingLanguage(tutorial::Language::CPP);
    skills.push_back(skill1);

    /* fill a second one... */
    tutorial::Experience skill2;
    skill2.setYearsOfExperience(4);
    skill2.setProgrammingLanguage(tutorial::Language::PYTHON);
    skills.push_back(skill2);

    /* assign the zserio object array to object joe */
    joe.setSkills(skills);

    /** serialize to file */
    zserio::serializeToFile(joe, employeeFile);
}

void writeBoss(const std::string& employeeFile)
{
    /* declare an employee */
    tutorial::Employee boss;

    /* fill some basic type fields */
    boss.setAge(43);
    boss.setName("Boss");
    boss.setSalary(9000);

    /* set an enum value, in this case the role */
    boss.setRole(tutorial::Role::TEAM_LEAD);

    /* no programming skills for the boss, but a bonus! */
    boss.setBonus(10000);

    /** serialize to file */
    zserio::serializeToFile(boss, employeeFile);
}

void readEmployee(const std::string& employeeFile)
{
    /* read employee from the file */
    const tutorial::Employee employee = zserio::deserializeFromFile<tutorial::Employee>(employeeFile);

    /* data types that are always available can simply be printed out */
    std::cout << "Name: " << employee.getName() << std::endl;
    std::cout << "Age: " << static_cast<unsigned int>(employee.getAge()) << std::endl;
    std::cout << "Salary: " << employee.getSalary() << std::endl;
    std::cout << "Role: " << zserio::enumToString(employee.getRole()) << std::endl;

    /* we have to check for optionals whether they are in the stream */
    if (employee.isBonusUsed())
        std::cout << "Bonus: " << employee.getBonus() << std::endl;

    /* we also have to check for conditions if they applied */
    if (employee.isSkillsUsed())
    {
        const std::vector<tutorial::Experience>& skills  = employee.getSkills();
        for (std::vector<tutorial::Experience>::const_iterator it = skills.begin(); it != skills.end(); ++it)
        {
            const uint8_t years = it->getYearsOfExperience();
            const tutorial::Language language = it->getProgrammingLanguage();

            /* get string representation of Language enum value */
            const std::string languageString = zserio::enumToString(language);

            std::cout << "Skill: Language " << languageString << ", " << static_cast<unsigned int>(years) <<
                    " years" << std::endl;
        }
    }

    /* print out bit size */
    std::cout << "Bit size of employee: " << employee.bitSizeOf() << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printHelp();
        return 2;
    }

    const std::string employeeFile("employee.zsb");
    try
    {
        if (argv[1] == std::string("write_joe"))
        {
            /* writing an employee 'Joe' to file */
            writeJoe(employeeFile);
        }
        else if (argv[1] == std::string("write_boss"))
        {
            /* writing an employee 'Boss' to file */
            writeBoss(employeeFile);
        }
        else if (argv[1] == std::string("read"))
        {
            /* reading an employee from file */
            readEmployee(employeeFile);
        }
        else
        {
            printHelp();
            if (argv[1] != std::string("-h") && argv[1] != std::string("--help"))
                return 2;
        }
    }
    catch (const zserio::CppRuntimeException& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
