package tutorial;

struct Employee
{
    uint8           age : age <= 65; // max age is 65
    string          name;
    uint16          salary;
    optional uint16 bonus;
    Role            role;

    // if employee is a developer, list programming skill
    Experience      skills[] if role == Role.DEVELOPER;
};

struct Experience
{
    bit:6       yearsOfExperience;
    Language    programmingLanguage;
};

enum bit:2 Language
{
    CPP     = 0,
    JAVA    = 1,
    PYTHON  = 2,
    JS      = 3
};

enum uint8 Role
{
    DEVELOPER = 0,
    TEAM_LEAD = 1,
    CTO       = 2
};
