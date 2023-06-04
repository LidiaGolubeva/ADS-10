// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <algorithm>

class Tree {
 public:
  explicit Tree(std::vector<char> init) :rootNd(nullptr) {
    createPermutations(init);
  }
  std::vector<std::vector<char>> getPerm() const {
    return permutations;
  }

 private:
  struct Node {
    char character;
    std::vector<Node*> childNds;
    explicit Node(char character_ = '\0') :character(character_) {}
  };
  Node* rootNd;
  std::vector<std::vector<char>> permutations;

  void addNode(Node* newRootNd, std::vector<char> row) {
    if (!newRootNd) {
      rootNd = newRootNd = new Node;
    }
    for (char character : row) {
      Node* tmp = new Node(character);
      newRootNd->childNds.push_back(tmp);
      std::vector<char> newRow(row);
      newRow.erase(std::find(newRow.begin(), \
        newRow.end(), character));
      addNode(tmp, newRow);
    }
  }

  void evadeTree(Node* newRootNd, std::vector<char> row) {
    if (newRootNd != nullptr && newRootNd->character != '\0')
      row.push_back(newRootNd->character);
    if (newRootNd->childNds.empty())
      permutations.push_back(row);
    for (Node* childNds : newRootNd->childNds) {
      evadeTree(childNds, row);
    }
  }

  void createPermutations(std::vector<char> row) {
    addNode(rootNd, row);
    evadeTree(rootNd, {});
  }
};

#endif  // INCLUDE_TREE_H_
