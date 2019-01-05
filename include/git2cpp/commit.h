#pragma once

#include "tree.h"
#include "repo_fwd.h"

#include <git2/types.h>

struct git_commit;
struct git_oid;
struct git_repository;

namespace git
{
   struct Commit
   {
      size_t parents_num() const;
      Commit parent(size_t i) const;
      git_oid const & parent_id(size_t i) const;

      Tree tree() const;

      explicit operator bool () const { return commit_ != nullptr; }

      git_oid const & id() const;

      git_signature const * author()      const;
      git_signature const * commiter()    const;

      const char *   message()   const;
      const char *   summary()   const;
      git_time_t     time()      const;

      git_oid merge_base(size_t p1, size_t p2) const;

      Repository const & repo() const { return *repo_; }

      Commit(git_commit *, Repository const &);

      Commit();
      Commit              (Commit &&) noexcept;
      Commit& operator =  (Commit &&) noexcept;
      Commit              (Commit const &) = delete;
      Commit& operator =  (Commit const &) = delete;

      ~Commit();

   private:
      friend struct Repository;

      git_commit const * ptr() const { return commit_; }

   private:
      git_commit * commit_;
      Repository const * repo_;
   };
}

