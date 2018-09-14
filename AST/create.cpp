/*
 * Copywrite 2018 Tristan Moore
 *
 * This file is part of the SimpleSQL package.
 * Contains the logic for Create statements in the SQL parse tree,
 * including the column options possible to implement in SQL.
 *
 */

#include "create.h"
#include "visitor.h"
#include <cassert>

using std::string;
using std::vector;
using std::shared_ptr;


/*---------------------------------------------
   Create methods
   ------------------------------------------*/

// Returns the name of the table or database to be created
// by this statement
const string Create::name() const {
  return _name;
}

// Creates a new create statement with the given name of the table
// or database to be created
Create::Create(const string &name) : _name(name) {}

Create::~Create() { }

/*--------------------------------------------------
  CreateDatabase Methods
  ------------------------------------------------*/

//Creates a new Create Database statement to create a database of the given
// name
CreateDatabase::CreateDatabase(const string &name) : Create(name) {}

// Handles visitor acceptance logic for create database nodes
void CreateDatabase::accept(Visitor& v) {
  v.visitCreateDatabase(*this);
}

/*-------------------------------------------------
  CreateTable Methods
  ------------------------------------------------*/

// Creates a new Create Table statement to create a table of the given name,
// using the given vector of Create elements.
CreateTable::CreateTable(const string &name, const vector<shared_ptr<const CreateElement>> &els)
  : Create(name), _elements(els) {}

// Handles visitor acceptance logic for create table nodes
void CreateTable::accept(Visitor& v) {
  v.visitCreateTable(*this);
}


/*---------------------------------------------------
  CreateBuilder methods
  --------------------------------------------------*/

// sets the type of the CreateBuilder to given type. Type
// should be either DATABASE or TABLE. Returns a reference
// to the instance of the CreateBuilder
const CreateBuilder& CreateBuilder::type(const ASTType t) {
  _type = t;
  return *this;
}

// Sets the name of the table or database to be created for the
// current CreateBuilder
const CreateBuilder& CreateBuilder::name(const string &name) {
  _name = name;
  return *this;
}

// Sets the Create Table elements to the given vector of elements.
// Only valid in the case that this builder is being used to create
// a Create Table command.
const CreateBuilder& CreateBuilder::elements(const vector<shared_ptr<const CreateElement>> &els) {
  _els = els;
  return *this;
}

// Dynamically allocates a new Create command instance
// based on the data stored in the builder. If this is a create command
// for a database, then the list of elements is assumed to be empty.
// Otherwise, the list of elements is assumed non-empty. Behavior is
// undefined otherwise. Client is responsible for deleting the returned value
const Create *CreateBuilder::build() {
  Create *c;
  if (_type == ASTType::DATABASE) {
    assert(_els.empty());
    c = new CreateDatabase(_name);
  } else {
    assert(!_els.empty());
    c = new CreateTable(_name, _els);
  }
  reset();
  return c;
}

// Resets the CreateBuilder to default settings. Intended to be called
// after using the builder to create a new statement.
void CreateBuilder::reset() {
  *this = CreateBuilder();
}


/*-----------------------------------------------------------------------------
  Create Element Definitions
  ---------------------------------------------------------------------------*/
CreateElement::~CreateElement() {}
CreateElement::CreateElement() {}

/*--------------------------------------------
  ColumnDecl methods
  ------------------------------------------*/

// Returns the name of the column declared
const string ColumnDecl::name() const {
  return _name;
}

// Returns true if null values are to be allowed in
// this column
bool ColumnDecl::nullable() const {
  return _nullable;
}

// Returns the datatype that this column allows
Datatype ColumnDecl::type() const {
  return _type;
}

// Returns the number of entries allowed in the column
int ColumnDecl::length() const {
  return _length;
}


// Handles visitor acceptance logic for ColumnDecl nodes
void ColumnDecl::accept(Visitor& v) {
  v.visitColumnDecl(*this);
}


// Returns a new ColumnDecl with the given name, nullability, type, and length
ColumnDecl::ColumnDecl(const string& name, bool nullable, Datatype type, int length)
  : _name(name), _nullable(nullable), _type(type), _length(length) {}

/*-------------------------------------------
  ColumnDeclBuilder methods
  ------------------------------------------*/

// Sets the name of the ColumnDecl to build to be the given name, and returns
// a reference to the builder
const ColumnDeclBuilder& ColumnDeclBuilder::name(const std::string& name) {
  _name = name;
  return *this;
}

// Sets the nullability of the column, and returns a reference to the builder
const ColumnDeclBuilder& ColumnDeclBuilder::nullable(bool nullable) {
  _nullable = nullable;
  return *this;
}

// Sets the accepted type of the column, and returns a reference to the builder
const ColumnDeclBuilder& ColumnDeclBuilder::type(Datatype type) {
  _type = type;
  return *this;
}

// Sets the maximal length of the fields in the column and returns a reference
// to the builder
const ColumnDeclBuilder& ColumnDeclBuilder::length(int length) {
  _length = length;
  return *this;
}

// Returns a dynamically allocated column declaration that matches the arguments
// given. Client is responsible for deleting the pointer.
const ColumnDecl * ColumnDeclBuilder::build() {
  ColumnDecl * c = new ColumnDecl(_name, _nullable, _type, _length);
  reset();
  return c;
}

void ColumnDeclBuilder::reset() {
  *this = ColumnDeclBuilder();
}

/*-------------------------------------------
  PrimaryKeyDecl methods
  -----------------------------------------*/

// Returns the keys that are declared to be primary by this declaration
const vector<string> PrimaryKeyDecl::keys()  const {
  return _keys;
}


// Handles visitor acceptance logic for primary key declaration nodes
void PrimaryKeyDecl::accept(Visitor& v) {
  v.visitPrimaryKeyDecl(*this);
}


// Constructs a new PrimaryKeyDecl operating on the given vector of keys
PrimaryKeyDecl::PrimaryKeyDecl(const vector<string>& keys) : _keys(keys) {}

/*------------------------------------------
  ForeignKeyDecl methods
  -----------------------------------------*/

// Returns the name of the referenced table
const string ForeignKeyDecl::foreign_table_name() const {
  return _foreign_table_name;
}


// Handles visitor acceptance logic for foreign key declaration nodes
void ForeignKeyDecl::accept(Visitor& v) {
  v.visitForeignKeyDecl(*this);
}


// Returns the list of keys that are being declared foreign
const vector<string> ForeignKeyDecl::keys() const {
  return _keys;
}

// Constructs a new ForeignKeyDecl linking the given keys to the
// given foreign table name
ForeignKeyDecl::ForeignKeyDecl(const string& foreign_table_name, const vector<string>& keys)
  : _foreign_table_name(foreign_table_name), _keys(keys) {}
