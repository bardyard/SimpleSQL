#include "drop.h"

using std::string;

/**************************************
 Drop Methods
*************************************/
Drop::Drop(const string &name): _name(name) {}

const string name() const {
  return name;
}

/************************
DropTable Methods
************************/
DropTable::DropTable(const string &name): Drop(name) {}

/************************
DropDatabase Methods
************************/
DropDatabase::DropDatabase(const string &name): Drop(name) {}
