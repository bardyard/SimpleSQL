#ifndef __SELECT_H__
#define __SELECT_H__

#include <string>
#include <memory>
#include <vector>
#include "ast.h"
#include "identifier.h"

class WhereExpr : public ASTNode {
  
};

class GroupByExpr : public ASTNode {


};

// havingExpr :
class HavingExpr : public ASTNode {

};


class OrderByExpr : public ASTNode {

};

// limit ::= LIMIT [<offset>, ] <row_count>
class LimitExpr : public ASTNode {
 public:
  int offset();
  int rows();
  LimitExpr(int offset, int rows);
 private:
  _offset;
  _rows;
  LimitExpr() = delete;  
};


// Correponds to the logical statement at the end of a select command
// select_expr ::= FROM <table_list>
//                        [WHERE <where_expression> ] [GROUP BY <group_defn>]
//                        [HAVING <having_expr> ] [ORDER BY <order_by_defn>]
//                        [LIMIT [<offset>, ] <row_count>] 
class SelectExpression : public ASTNode  {
 public:
  const std::vector<const std::unique_ptr<const Identifier>> table_list() const;
  const WhereExpr where_expr() const;
 private:
  SelectExpression();
  const std::vector<const std::unique_ptr<const Identifer>> _table_list;
  const WhereExpr _where;
  const GroupByExpr _group;
  const HavingExpr _having;
  const OrderByExpr _order;
  const LimitExpr _limit;
};



// Corresponds to a select statement
// select_stmt ::= SELECT {<select_list> | *} [<select_expr>]
class Select : public ASTNode {
 public:
  const SelectExpression exp() const;
  Select(const SelectExpression selectExpression);
 private:
  Select();
  const SelectExpression _selectExpression;
};

class SelectExpressionBuilder {
  
};


#endif  // __SELECT_H__
