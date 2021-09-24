#ifndef ZSERIO_SQLITE_EXCEPTION_H_INC
#define ZSERIO_SQLITE_EXCEPTION_H_INC

#include "sqlite3.h"

#include "zserio/CppRuntimeException.h"

namespace zserio
{

/** Wrapper class to work with SQLite error code. */
class SqliteErrorCode
{
public:
    /**
     * Constructor.
     *
     * \param sqliteCode SQLite error code.
     */
    explicit SqliteErrorCode(int sqliteCode) : m_code(sqliteCode)
    {}

    /**
     * Gets SQLite error string appropriate to the error code.
     *
     * \return English language text that describes the error code. Memory to hold the error message string is
     *         managed by SQLite.
     */
    const char* getErrorString() const
    {
        return sqlite3_errstr(m_code);
    }

private:
    int m_code;
};

/** Exception thrown when an error in an SQLite operation occurs. */
class SqliteException : public detail::CppRuntimeExceptionHelper<SqliteException>
{
public:
    using BaseType::CppRuntimeExceptionHelper;
    using BaseType::operator+;

    /**
     * Appends SQLite error string appropriate for given sqlite error code.
     *
     * \param code SQLite error code to append the error string for.
     */
    SqliteException& operator+(SqliteErrorCode code)
    {
        return operator+(code.getErrorString());
    }
};

} // namespace zserio

#endif // ifndef ZSERIO_SQLITE_EXCEPTION_H_INC
