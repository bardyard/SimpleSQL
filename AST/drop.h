#ifndef __DROP_H__
#define __DROP_H__

#include <string>
#include "ast.h"

// Corresponds to a drop statement
// <drop_statement> ::= DROP [TABLE | DATABASE] <name>
class Drop : public ASTNode {
 public:
  const std::string name() const;
 protected:
  Drop(std::string name);
 private:
  Drop();
  const std::string _name;
};

// Corresponds to a drop table statement
class DropTable : public Drop {
 public:
  DropTable(std::string name);
 private:
  DropTable();
};


// Corresponds to a drop database statement
class DropDatabase : public Drop {
 public:
  DropDatabase(std::string name);
 private:
  DropDatabase();
};


#endif  // __DROP_H__
