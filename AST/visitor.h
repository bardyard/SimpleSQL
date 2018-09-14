#ifndef __VISITOR_H__
#define __VISITOR_H__

#include "ast_public.h"
class Visitor {
 public:
  virtual void visitCreateDatabase(const CreateDatabase& node);
  virtual void visitCreateTable(const CreateTable& node);
  virtual void visitColumnDecl(const ColumnDecl& node);
  virtual void visitPrimaryKeyDecl(const PrimaryKeyDecl& node);
  virtual void visitForeignKeyDecl(const ForeignKeyDecl& node);
};

#endif
