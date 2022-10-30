#ifndef TREAP_H
#define TREAP_H

#include <bits/stdc++.h>
#include <QString>
#include "wNode.h"
using namespace std;

struct tpNode {
  tpNode* ch[2];
  int val, rank;
  int rep_cnt;
  int siz;

  tpNode(int val) : val(val), rep_cnt(1), siz(1) {
    ch[0] = ch[1] = nullptr;
    rank = rand();
  }

  void upd_siz() {
    siz = rep_cnt;
    if (ch[0] != nullptr)
      siz += ch[0]->siz;
    if (ch[1] != nullptr)
      siz += ch[1]->siz;
  }
};

class Treap {
 private:
  tpNode* root;

  vector<wNode> vec;

  enum rot_type { LF = 1, RT = 0 };

  int q_prev_tmp = 0, q_nex_tmp = 0;

  void _rotate(tpNode*& cur, rot_type dir) {  // 0为右旋，1为左旋
    tpNode* tmp = cur->ch[dir];
    cur->ch[dir] = tmp->ch[!dir];
    tmp->ch[!dir] = cur;
    tmp->upd_siz(), cur->upd_siz();
    cur = tmp;
  }

  void _insert(tpNode*& cur, int val) {
    if (cur == nullptr) {
      cur = new tpNode(val);
      return;
    } else if (val == cur->val) {
      cur->rep_cnt++;
      cur->siz++;
    } else if (val < cur->val) {
      _insert(cur->ch[0], val);
      if (cur->ch[0]->rank < cur->rank) {
        _rotate(cur, RT);
      }
      cur->upd_siz();
    } else {
      _insert(cur->ch[1], val);
      if (cur->ch[1]->rank < cur->rank) {
        _rotate(cur, LF);
      }
      cur->upd_siz();
    }
  }

  void _del(tpNode*& cur, int val) {
    if (val > cur->val) {
      _del(cur->ch[1], val);
      cur->upd_siz();
    } else if (val < cur->val) {
      _del(cur->ch[0], val);
      cur->upd_siz();
    } else {
      if (cur->rep_cnt > 1) {
        cur->rep_cnt--, cur->siz--;
        return;
      }
      uint8_t state = 0;
      state |= (cur->ch[0] != nullptr);
      state |= ((cur->ch[1] != nullptr) << 1);
      // 00都无，01有左无右，10，无左有右，11都有
      tpNode* tmp = cur;
      switch (state) {
        case 0:
          delete cur;
          cur = nullptr;
          break;
        case 1:  // 有左无右
          cur = tmp->ch[0];
          delete tmp;
          break;
        case 2:  // 有右无左
          cur = tmp->ch[1];
          delete tmp;
          break;
        case 3:
          rot_type dir = cur->ch[0]->rank < cur->ch[1]->rank ? RT : LF;
          _rotate(cur, dir);
          _del(cur->ch[!dir], val);
          cur->upd_siz();
          break;
      }
    }
  }

  int _query_rank(tpNode* cur, int val) {
    int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
    if (val == cur->val)
      return less_siz + 1;
    else if (val < cur->val) {
      if (cur->ch[0] != nullptr)
        return _query_rank(cur->ch[0], val);
      else
        return 1;
    } else {
      if (cur->ch[1] != nullptr)
        return less_siz + cur->rep_cnt + _query_rank(cur->ch[1], val);
      else
        return cur->siz + 1;
    }
  }

  int _query_val(tpNode* cur, int rank) {
    int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
    if (rank <= less_siz)
      return _query_val(cur->ch[0], rank);
    else if (rank <= less_siz + cur->rep_cnt)
      return cur->val;
    else
      return _query_val(cur->ch[1], rank - less_siz - cur->rep_cnt);
  }

  int _query_prev(tpNode* cur, int val) {
    if (val <= cur->val) {
      if (cur->ch[0] != nullptr)
        return _query_prev(cur->ch[0], val);
    } else {
      q_prev_tmp = cur->val;
      if (cur->ch[1] != nullptr)
        _query_prev(cur->ch[1], val);
      return q_prev_tmp;
    }
    return -1145;
  }

  int _query_nex(tpNode* cur, int val) {
    if (val >= cur->val) {
      if (cur->ch[1] != nullptr)
        return _query_nex(cur->ch[1], val);
    } else {
      q_nex_tmp = cur->val;
      if (cur->ch[0] != nullptr)
        _query_nex(cur->ch[0], val);
      return q_nex_tmp;
    }
    return -1145;
  }

 public:
  Treap(const vector<wNode>& v) : vec(v) {}

  void insert(int val) { _insert(root, val); }

  void del(int val) { _del(root, val); }

  int query_rank(int val) { return _query_rank(root, val); }

  int query_val(int rank) { return _query_val(root, rank); }

  int query_prev(int val) { return _query_prev(root, val); }

  int query_nex(int val) { return _query_nex(root, val); }
};

#endif  // TREAP_H
