#include <iostream>
#include <string>
#include <vector>

#include <zserio/SerializeUtil.h>
#include <zserio/Enums.h>

#include "tutorial/Employee.h"
#include "StaticMemoryResource.h"

void printHelp()
{
    std::cout << "Usage: ZserioTutorialCpp write_joe|write_boss|read" << std::endl;
}


void writeJoe(const std::string& employeeFile,
        const zserio::pmr::PropagatingPolymorphicAllocator<uint8_t>& allocator)
{
    /* declare an employee - provide the allocator */
    tutorial::Employee joe(allocator);

    /* fill some basic type fields */
    joe.setAge(32);
    /* for longer strings the allocator would be necessary */
    joe.setName(zserio::pmr::string("Joe Smith", allocator));
    joe.setSalary(5000);

    /* set an enum value, in this case the role */
    joe.setRole(tutorial::Role::DEVELOPER);

    /* declare an array which holds a zserio struct - provide the allocator to vector */
    zserio::pmr::vector<tutorial::Experience> skills(allocator);

    /* declare and fill the struct Experience - provide the allocator */
    tutorial::Experience skill1(allocator);
    skill1.setYearsOfExperience(8);
    skill1.setProgrammingLanguage(tutorial::Language::CPP);
    skills.push_back(skill1);

    /* fill a second one... (and provide the allocator) */
    tutorial::Experience skill2(allocator);
    skill2.setYearsOfExperience(4);
    skill2.setProgrammingLanguage(tutorial::Language::PYTHON);
    skills.push_back(skill2);

    joe.setSkills(skills);

    /** serialize to file - will allocate a bit buffer using the default memory resource */
    zserio::serializeToFile(joe, employeeFile);
}

void writeBoss(const std::string& employeeFile)
{
    /* note that we don't need to provide allocator since we are using the default memory resource */

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
    /* note that we don't need to provide allocator since we are using the default memory resource */

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
        const zserio::pmr::vector<tutorial::Experience>& skills  = employee.getSkills();
        for (zserio::pmr::vector<tutorial::Experience>::const_iterator it = skills.begin();
                it != skills.end(); ++it)
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

template <typename MEMORY_RESOURCE>
void reportMemoryUsage(const MEMORY_RESOURCE& memoryResource)
{
    std::cout << memoryResource.getName() << ": numAllocations=" << memoryResource.getNumAllocations() <<
            ", numDeallocations=" << memoryResource.getNumDeallocations() <<
            ", totalAllocatedSize=" << memoryResource.getTotalAllocatedSize() << std::endl;
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
        StaticMemoryResource<32> memoryResource("Joe's memory resource");

        // memory resource which will be used by zserio::pmr allocators when no memory resource is provided
        StaticMemoryResource<32> defaultMemoryResource("Default memory resource");
        zserio::pmr::setDefaultResource(&defaultMemoryResource);

        if (argv[1] == std::string("write_joe"))
        {
            /* writing an employee 'Joe' to file - provide the memory resource */
            /* (note that zserio::pmr::PropagatingPolymorphicAllocator has an implicit constructor) */
            writeJoe(employeeFile, &memoryResource);
        }
        else if (argv[1] == std::string("write_boss"))
        {
            /* writing an employee 'Boss' to file - will use default memory resource */
            writeBoss(employeeFile);
        }
        else if (argv[1] == std::string("read"))
        {
            /* reading an employee from file - will use default memory resource */
            readEmployee(employeeFile);
        }
        else
        {
            printHelp();
            if (argv[1] != std::string("-h") && argv[1] != std::string("--help"))
                return 2;
        }

        reportMemoryUsage(memoryResource);
        reportMemoryUsage(defaultMemoryResource);
    }
    catch (const zserio::CppRuntimeException& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
