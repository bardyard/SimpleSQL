#include "insert.h"
#include <vector>
#include <string>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;

/*****************************************
 Insert Methods
****************************************/

const InsertOption * const Insert::option() const {
  return _option;
}

Insert::Insert(const InsertOption * const option) : _option(option) {}

Insert::~Insert() {
  delete _option;
}


/****************************************
InsertOption Methods
****************************************/

const string InsertOption::table_name const {
  return _name;
}

InsertOption::InsertOption(const string &name) : _name(name) {}


/****************************************
ValuesOption Methods
****************************************/

const vector<string> ValuesOption::columns() const {
  return _columns;
}

const vector<shared_ptr<const Expression>> ValuesOption::values() const {
  return _values;
}

ValuesOption::ValuesOption(const vector<string> &columns,
			   const vector<shared_ptr<const Expression>> &values)
  : _columns(columns), _values(values) {}

/*****************************************
SetOption Methods
*****************************************/

const vector<const std::pair<const string, const Expression>> SetOption::set() const {
  return _set;
}

SetOption::SetOption(const vector<const std::pair<const string, const Expression>> &set,
		     const string &name) : InsertOption(name), _set(set) {}

/*****************************************
SelectOption Methods
*****************************************/

const vector<shared_ptr<const Identifier>> SelectOption::column_list() const {
  return _column_list;
}

const Select SelectOption::select() const {
  return _select;
}

SelectOption::SelectOption(const Select &select) : _select(select) {}
