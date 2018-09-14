#ifndef __INSERT_H__
#define __INSERT_H__

#include <utility>
#include <vector>
#include <memory>
#include <string>
#include "ast.h"
#include "select.h"
#include "identifier.h"

class Insert;
class InsertOption;
class ValuesOption;
class SetOption;
class SelectOption;

// Corresponds to an Insert statement
// insert_stmt ::= INSERT [INTO] { <values_option> | <set_option> | <select_option>}
class Insert : ASTNode {
 public:
  const InsertOption * const option() const;
  Insert(const InsertOption * const option);
  virtual ~Insert();
 private:
  const InsertOption * const _option;
  Insert() = delete;
};

// Corresponds to one of the options for an insert statement
// i.e. a values option, set option, or select option
// All insert option contain a table name
class InsertOption : ASTNode {
 public:
  const std::string table_name() const;
 protected:
  InsertOption(const std::string &name);
 private:
  const std::string _name;
  InsertOption();
};

// Corresponds to a values option in an insert statement
// values_option ::= <table_name> [(<column_name> {, <column_name>}*]
//                            VALUES ( <expr> {,<expr>}*)
class ValuesOption : public InsertOption {
 public:
  const std::vector<std::string> columns() const;
  const std::vector<std::shared_ptr<const Expression>> values() const;
  ValuesOption(const std::vector<std::string> &columns,
	       const std::vector<std::shared_ptr<const Expression>> &values);
 private:
  const std::vector<std::string> _columns;
  const std::vector<std::shared_ptr<const Expression>> _values;
};

// Corresponds to a set option in an insert statement
// set_option ::= <table_name> SET <column_name>=<expr> {,<column_name>=<expr>}*
class SetOption : public InsertOption {
 public:
  const std::vector<const std::pair<const std::string, const Expression>> set() const;
  SetOption(const std::vector<const std::pair<const std::string, const Expression>>& set,
	    const std::string& name);
 private:
  const std::vector<const std::pair<const std::string, const Expression>> _set;
  
};

// Corresponds to a select option in an insert statement
// select_option ::= <table_name> [(<column_name> {,<column_name>}*)] <select_stmt>
class SelectOption : public InsertOption {
 public:
  const std::vector<std::shared_ptr<const Identifier>> column_list() const;
  const Select select() const;
  SelectOption(const Select &select);
 private:
  const std::vector<std::shared_ptr<const Identifier>> _column_list;
  const Select _select;
};


#endif  // __INSERT_H__
