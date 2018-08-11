#include <mariadb/result.h>
#include <mariadb/column.h>

#include <mariadb/inline/row.inl>
#include <mariadb/inline/result.inl>

using namespace ::mariadb;

row* result::next()
{
    auto r = mysql_fetch_row(handle());
    if (r)
    {
        ++_rowindex;
        _row.reset(new row(*this, r));
    }
    else
        _row.reset();
    return _row.get();
}

void result::update_columns() const
{
    auto f = mysql_fetch_fields(handle());
    auto c = mysql_num_fields  (handle());
    _columns.clear();
    _columns.reserve(c);
    for (size_t i = 0; i < c; ++i)
        _columns.emplace_back(f[i]);
}

result::~result()
    { free(); }

result_used::~result_used()
    { while(next()); /* fetch rows until none is left */ }