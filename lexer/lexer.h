// Tristan Moore
// SimpleSQL: Lexer
//
// This module handles the lexical analysis of
// incoming SQL commands.

#ifndef __LEXER_H__
#define __LEXER_H__
#include <string>
#include <vector>
#include <memory>
// This class represents a token in an incoming SQL command
enum Tokens {
  // SQL Keywords
  // Statement types
  SELECT,
  UPDATE,
  DELETE,
  INSERT,
  INTO,
  CREATE,
  ALTER,
  DROP,
  INDEX,

  // Database/Table (for drop and create)
  DATABASE,
  TABLE,
  
  GROUP,
  BY,
  PROCEDURE,
  EXEC,
  VALUES,
  FROM,
  DISTINCT,
  COUNT,
  WHERE,
  HAVING,
  BETWEEN,
  EXISTS,
  ANY,
  ALL,
  AS,
  LIKE,
  IN,

  // Boolean operators
  AND,
  OR,
  NOT,

  // Ordering keywords
  ORDER,
  ASC,
  DESC,
  IS,
  NUL,
  MIN,
  MAX,
  AVG,
  SUM,

  // Joining keywords
  INNER,
  JOIN,
  LEFT,
  RIGHT,
  FULL,
  OUTER,
  UNION,
  COALESCE,
  
  // Collection types
  SET,
  ENUM,
  
  TOP,
  LIMIT,
  PERCENT,

  // Datatype keywords
  INT,
  DOUBLE,
  UNSIGNED,
  CHAR,
  VARCHAR,
  STRING,
  BINARY,
  ENUM,
  
  // Semantic Symbols
  STAR,
  SEMICOLON,
  EQUAL,
  NEQUAL,
  GTHAN,
  LTHAN,
  GEQ,
  LEQ,
  LPAREN,
  RPAREN,
  COMMA,
  UNDERSCORE,
  PERCENT_SIGN,
  PLUS,

  // Literals
  STRINGLIT,
  INTLIT,
  UINTLIT,
  DOUBLELIT,
  CHARLIT,
    
  // Identifier and Error types
  IDENTIFIER,
  ERROR
};

class Token {
 public:
  const Tokens type() const;
  Token(Tokens type);
  virtual const std::string toString() const;
  virtual ~Token() {}
 protected:
  const Tokens type_;
  Token();
};

class Error: public Token {
 public:
  const std::string& error() const;
  Error(const std::string& error);
  virtual const std::string toString() const;
 private:
  const std::string error_;
  Error();
};

class Identifier: public Token {
 public:
  const std::string& name() const;
  Identifier(const std::string& name);
  virtual const std::string toString() const;
 private:
  const std::string name_;
  Identifier();
};

class StringLit : public Token {
 public:
  const std::string literal() const;
  StringLit(const std::string &literal);
  virtual const std::string toString() const;
 private:
  const std::string _literal;
  StringLit();
};

class IntLit : public Token {
 public:
  int literal() const;
  IntLit(int literal);
  virtual const std::string toString() const;
 private:
  int _literal;
  IntLit();
};

class DoubleLit : public Token {
 public:
  double literal() const;
  DoubleLit(double literal);
  virtual const std::string toString() const;
 private:
  double _literal;
  DoubleLit();
};



std::ostream& operator<< (std::ostream& output, const Error& error);
std::ostream& operator<< (std::ostream& output, const Identifier& identifier);
std::ostream& operator<< (std::ostream& output, const Token& token);

void tokenize_command(const std::string& command, std::vector<std::unique_ptr<const Token>>& result);
#endif  // __LEXER_H__
