#ifndef __CREATE_H__
#define __CREATE_H__

#include <string>
#include <vector>
#include <memory>
#include "ast.h"

class Create;
class CreateBuilder;
class CreateDatabase;
class CreateTable;
class CreateElement;
class ColumnDecl;
class ForeignKeyDecl;
class PrimaryKeyDecl;

// Enumerates the datatypes possible
// for columns
enum Datatype {
  INT_T,
  DOUBLE_T,
  UINT_T,
  UDOUBLE_T,
  CHAR_T,
  VARCHAR_T,
  STRING_T,
  BINARY_T,
  ENUM_T,
  SET_T
};


// Corresponds to a create statement
// create_statement ::= <create_table> | <create_database>
class Create : public ASTNode {
 public:
  const std::string name() const;
  virtual ~Create();
 protected:
  Create(const std::string &name);
 private:
  const std::string _name;
  Create();
};

// Builder class for a create node
class CreateBuilder {
 public:
  const CreateBuilder& type(const ASTType t);
  const CreateBuilder& name(const std::string &name);
  const CreateBuilder& elements(const std::vector<std::shared_ptr<const CreateElement>> &els);
  const Create *build();
 private:
  CreateBuilder() {}
  ASTType _type;
  std::string _name;
  std::vector<std::shared_ptr<const CreateElement>> _els;
  void reset();
};



// Corresponds to a create table statement
// create_table ::= CREATE TABLE <identifier> (<element> {, <element>}*)
class CreateTable : public Create {
 public:
  const std::vector<std::shared_ptr<const CreateElement>> elements() const;
  CreateTable(const std::string& name, const std::vector<std::shared_ptr<const CreateElement>>& els);
  void accept(Visitor& v);
 private:
  void reset();
  const std::vector<std::shared_ptr<const CreateElement>> _elements;
};

// Corresponds to a create database statement
// create_database ::= CREATE DATABASE <identifier>
class CreateDatabase : public Create {
 public:
  CreateDatabase(const std::string& name);
  void accept(Visitor& v);
};


// Elements in a create statement.
// create_element ::= <column_decl> | <primary_key_decl> | <foreign_key_decl>
class CreateElement : public ASTNode {
 public:
  virtual ~CreateElement();
 protected:
  CreateElement();
};

// Corresponds to a column declaration for a create table statement
// column_decl ::= <column_name> 
class ColumnDecl : public CreateElement {
 public:
  const std::string name() const;
  bool nullable() const;
  Datatype type() const;
  int length() const;
  ColumnDecl(const std::string& name, bool nullable, Datatype type, int length);
  void accept(Visitor& v);
 private:
  ColumnDecl();
  const std::string _name;
  const bool _nullable;
  const Datatype _type;
  const int _length;
};

// Builder class to construct ColumnDecls
class ColumnDeclBuilder {
 public:
  const ColumnDeclBuilder& name(const std::string& name);
  const ColumnDeclBuilder& type(Datatype type);
  const ColumnDeclBuilder& nullable(bool nullable);
  const ColumnDeclBuilder& length(int length);
  const ColumnDecl *build();
 private:
  int _length;
  std::string _name;
  bool _nullable;
  Datatype _type;
  void reset();  
};  

// Corresponds to a primary key declaration in a create table statement
class PrimaryKeyDecl : public CreateElement {
 public:
  const std::vector<std::string> keys() const;
  PrimaryKeyDecl(const std::vector<std::string>& keys);
  void accept(Visitor& v);
 private:
  const std::vector<std::string> _keys;
};

// Corresponds to a foreign key declaration in a create table statement
class ForeignKeyDecl : public CreateElement {
 public:
  const std::string foreign_table_name() const;
  const std::vector<std::string> keys() const;
  ForeignKeyDecl(const std::string& foreign_table_name, const std::vector<std::string>& keys);
  void accept(Visitor& v);
 private:
  const std::string _foreign_table_name;
  const std::vector<std::string> _keys;
};

#endif  // __CREATE_H__
