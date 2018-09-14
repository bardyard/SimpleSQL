#ifndef __DELETE_H__
#define __DELETE_H__

#include "ast.h"

class Expression;
class Delete;

// Corresponds to a delete statement
// 
class Delete : public ASTNode {
 public:
  const Expression * const exp() const;
  Delete(const Expression& deleteExpression);
 private:
  Delete();
  const Expression * const deleteExpression;
};


#endif  // __DELETE_H__
