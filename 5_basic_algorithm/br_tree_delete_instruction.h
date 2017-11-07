/**
    In a regular binary search tree when deleting a node with two non-leaf children, we find either the maximum element 
    in its left subtree (which is the in-order predecessor) or the minimum element in its right subtree (which is the 
    in-order successor) and move its value into the node being deleted (as shown here). We then delete the node we copied 
    the value from, which must have fewer than two non-leaf children. (Non-leaf children, rather than all children, are 
    specified here because unlike normal binary search trees, red–black trees can have leaf nodes anywhere, so that all 
    nodes are either internal nodes with two children or leaf nodes with, by definition, zero children. In effect, internal 
    nodes having two leaf children in a red–black tree are like the leaf nodes in a regular binary search tree.) Because 
    merely copying a value does not violate any red–black properties, this reduces to the problem of deleting a node with 
    at most one non-leaf child. Once we have solved that problem, the solution applies equally to the case where the node 
    we originally want to delete has at most one non-leaf child as to the case just considered where it has two non-leaf 
    children.
    在常规的二叉查找树中，当删除一个带有两个非叶子节点的节点时，我们会找到该节点左子树中的最大元素（即中序遍历的前序元素），
    或者是它的右子树中的最小元素（即中序遍历的后序元素），随后将找到的元素赋值到将要删除的节点上，最后我们会将这个值原先所在
    的节点删除掉，而这个节点的非叶子节点数应当小于2（这里特别说明不是所有的子节点，而是非叶子节点，因为红黑树和普通的二叉搜索
    树不同，它的叶子节点可能出现在任何位置，所以树中所有的节点可能是带有两个子节点的内部节点，或者根据定义，是没有子节点的叶
    子节点。实际上，红黑树中拥有两个叶子节点的内部节点和普通的二叉搜索树中的叶子节点并无二致）。因为仅仅是值拷贝并不会破坏红
    黑树的特性，这就将问题简化为了删除一个节点的新问题，而这个节点至多带有一个非叶子节点。一旦我们解决了这个问题，其解决方法
    就可以等价的从待删除节点至多有一个非叶子节点的场景下，应用到包含两个非叶子节点的场景下。

    Therefore, for the remainder of this discussion we address the deletion of a node with at most one non-leaf child. We use 
    the label M to denote the node to be deleted; C will denote a selected child of M, which we will also call "its child". If 
    M does have a non-leaf child, call that its child, C; otherwise, choose either leaf as its child, C.
    所以，更具上述讨论，我们先解决至多包含一个非叶子节点的节点的删除问题。我们用M来标识待删除的节点；用C来标识M中选中的子节点。
    如果M包含非叶子节点，接将那个节点成为C，非则的话就将一个叶子节点作为C。

    If M is a red node, we simply replace it with its child C, which must be black by property 4. (This can only occur when M 
    has two leaf children, because if the red node M had a black non-leaf child on one side but just a leaf child on the other 
    side, then the count of black nodes on both sides would be different, thus the tree would violate property 5.) All paths 
    through the deleted node will simply pass through one fewer red node, and both the deleted node's parent and child must be 
    black, so property 3 (all leaves are black) and property 4 (both children of every red node are black) still hold.
    如果M是个红色节点，我们仅仅用它的子节点C替代它即可，因为根据红黑树性质4，它的子节点一定是黑色节点（当且仅当M包含两个叶子节
    点时才会出现这种情况，因为如果红色节点M在一侧子树有一个黑色的非叶子节点C，而另一次只有一个叶子节点，这会导致这两个子树中黑
    色深度不同，从而违背红黑树的性质5）。所有经过删除节点的路径上都会少经过一个红色节点，并且待删除节点的父节点和子节点肯定都为
    黑色节点，所以红黑树的性质3和性质4没有被打破。

    Another simple case is when M is black and C is red. Simply removing a black node could break Properties 4 (“Both children 
    of every red node are black”) and 5 (“All paths from any given node to its leaf nodes contain the same number of black nodes”), 
    but if we repaint C black, both of these properties are preserved.
    另一种简单的情形是，M是黑色而C是红色。此时仅仅移除黑色节点可能会破环红黑树的性质4和性质5，不过在删除之后我们将节点C重新设为红色
    即可解决这个问题。

    The complex case is when both M and C are black. (This can only occur when deleting a black node which has two leaf children, 
    because if the black node M had a black non-leaf child on one side but just a leaf child on the other side, then the count of 
    black nodes on both sides would be different, thus the tree would have been an invalid red–black tree by violation of property 
    5.) We begin by replacing M with its child C. We will relabel this child C (in its new position) N, and its sibling (its new 
    parent's other child) S. (S was previously the sibling of M.) In the diagrams below, we will also use P for N's new parent (M's 
    old parent), SL for S's left child, and SR for S's right child (S cannot be a leaf because if M and C were black, then P's one 
    subtree which included M counted two black-height and thus P's other subtree which includes S must also count two black-height, 
    which cannot be the case if S is a leaf node).
    复杂的情况是当M和C都为黑色节点时（当且仅当删除一个带有两个叶子节点的黑色节点时才会发生，因为如果黑色节点M在一侧有一个黑色的非叶
    子节点，而在另一侧有一个叶子节点，那么这两侧黑色节点的深度就会不同，从而违背红黑树的性质5）。首先，使用C替代节点M，并在新的位置
    上将C标记为N，将C的兄弟节点标记为S（即它的新的父节点的另一个子节点，在替换之前S应该是M的兄弟节点）。在下面的图中，我们使用P标记
    N的父节点（即以前M的父节点），用SL和SR分别标记S的左儿子节点和右儿子节点（S不可能为叶子节点，因为如果M和C都为黑色，那么P节点的一
    个包含M的子树黑色深度就为多出2，这样P的另一个包含S的子树黑色深度也应当多出2，当S为叶子节点时是无法满足这一条件的）。

    Note: In order for the tree to remain well-defined, we need every null leaf to remain a leaf after all transformations (that it 
    will not have any children). If the node we are deleting has a non-leaf (non-null) child N, it is easy to see that the property 
    is satisfied. If, on the other hand, N would be a null leaf, it can be verified from the diagrams (or code) for all the cases 
    that the property is satisfied as well.
    注意：为了使红黑树仍然保持良好的定义，我们需要保证每个叶子节点在经历各种变换后仍然是叶子节点。如果我们删除的节点包含一个非叶子节
    点N，那么在删除后这一性质显然得到满足；然而如果N是一个叶子节点，通过图中的变换可以保证在各种情况下改性质依然满足。

    We can perform the steps outlined above with the following code, where the function replace_node substitutes child into n's place 
    in the tree. For convenience, code in this section will assume that null leaves are represented by actual node objects rather than 
    NULL (the code in the Insertion section works with either representation).
    我们可以将上述的几个步骤用下面的代码说明，其中函数'replace_node(Node* n, Nood* child)'将节点child替换到了树中节点n的位置上。为了方
    便，这一部分涉及的代码中我们会假设叶子节点为实际的节点对象，而非NULL指针。
*/

void delete_one_child(struct node *n)
{
   /*
    * Precondition: n has at most one non-leaf child.
    */
      struct node *child = is_leaf(n->right) ? n->left : n->right;

      replace_node(n, child);
      if (n->color == BLACK) {
          if (child->color == RED)
             child->color = BLACK;
          else
             delete_case1(child);
      }
      free(n);
}