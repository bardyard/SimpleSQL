#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <vector>
#include <memory>

class Visitor;
// Parent class for all ASTNode types. Allows a
// visitor to visit this node.
class ASTNode {
public:
  virtual void accept(Visitor& v) = 0;
  virtual ~ASTNode() {}
 protected:
  ASTNode();
};

// Handles the possible types of a create or
// drop statement. Either these are being
// applied to a database or a table.
enum ASTType {
  DATABASE,
  TABLE,
};

#endif  // __AST_H__
