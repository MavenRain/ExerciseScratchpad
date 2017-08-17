#include <iostream>

int StringToInt(char string_[])
{
    if (! string_) return 0;
    bool negative(string_[0] == '-');
    int value(0);
    for (int index = negative; string_[index] >= '0' && string_[index] <= '9'; ++ index) value = 10 * value + (string_[index] - '0');
    return negative ? -1 * value : value;
}

class TrinaryTree
{
    int number;
    TrinaryTree * left;
    TrinaryTree * middle;
    TrinaryTree * right;
public:
    TrinaryTree() : number(0), left(NULL), middle(NULL), right(NULL){}
    TrinaryTree(int Number) : number(Number), left(NULL), middle(NULL), right(NULL){}
    int Number() const { return number; }
    TrinaryTree * Left() const { return left; }
    TrinaryTree * Middle() const { return middle; }
    TrinaryTree * Right() const { return right; }
    TrinaryTree(int Number, TrinaryTree * Left, TrinaryTree * Middle, TrinaryTree * Right) : number(Number), left(Left && number > Left->Number() ? Left : NULL), middle(Middle && number == Middle->Number() ? Middle : NULL), right(Right && number < Right->Number() ? Right : NULL){}
    ~TrinaryTree()
    {
        delete left;
        delete middle;
        delete right;
    }
};

// AddElement:  Returns the root element of the input tree with the proper node added
TrinaryTree * AddElement(const TrinaryTree & tree, int number)
{
    if (tree.Number() == number) return tree.Middle() ? new TrinaryTree(tree.Number(), tree.Left(), AddElement(* tree.Middle(), number), tree.Right()) : new TrinaryTree(tree.Number(), tree.Left(), new TrinaryTree(number), tree.Right());    
    if (tree.Number() < number) return tree.Right() ? new TrinaryTree(tree.Number(), tree.Left(), tree.Middle(), AddElement(* tree.Right(), number)) : new TrinaryTree(tree.Number(), tree.Left(), tree.Middle(), new TrinaryTree(number));
    return tree.Left() ? new TrinaryTree(tree.Number(), AddElement(* tree.Left(), number), tree.Middle(), tree.Right()) : new TrinaryTree(tree.Number(), new TrinaryTree(number), tree.Middle(), tree.Right());
}

TrinaryTree * FindElement(const TrinaryTree & tree, int number)
{
    if (tree.Number() == number) return tree.Middle() ? FindElement(* tree.Middle(), number) : new TrinaryTree(tree.Number(), tree.Left(), tree.Middle(), tree.Right());
    if (tree.Number() < number) return tree.Right() ? FindElement(* tree.Right(), number) : NULL;
    return tree.Left() ? FindElement(* tree.Left(), number) : NULL;
}


void main()
{
    struct TestHarness
    {
        static void Assert(const char * testDescription, bool condition)
        {
            std::cout << testDescription << ": " << (condition ? "PASS" : "FAIL") << std::endl;
        }
    };
    TestHarness::Assert("The null string is converted to int 0", StringToInt(NULL) == 0);
    TestHarness::Assert("The string '456' is converted to int 456", StringToInt("456") == 456);
    TestHarness::Assert("The string '-123' is converted to int -123", StringToInt("-123") == -123);
    TestHarness::Assert("The string 'abc' is converted to int 0", StringToInt("abc") == 0);
    TestHarness::Assert("The tree with the left leaf greater than head is constructed without the left leaf", ! (new TrinaryTree(4, new TrinaryTree(5), NULL, NULL))->Left());
    TestHarness::Assert("The tree with the middle leaf not equal to the head is constructed without the middle leaf", ! (new TrinaryTree(4, NULL, new TrinaryTree(5), NULL))->Middle());
    TestHarness::Assert("The tree with the right leaf less than the head is constructed without the right leaf", ! (new TrinaryTree(4, NULL, NULL, new TrinaryTree(3)))->Right());
    TestHarness::Assert("The number '3' is found in a single-node tree labelled '3'", FindElement(TrinaryTree(3), 3) && FindElement(TrinaryTree(3), 3)->Number() == 3);
    TestHarness::Assert("The number '4' is NOT found in a single-node tree labelled '3'", ! FindElement(TrinaryTree(3), 4));
    TestHarness::Assert("The number '6' can be found in the third level of a constructed tree", FindElement(* AddElement(* AddElement(* AddElement(TrinaryTree(3), 5), 6), 5), 6) && FindElement(* AddElement(* AddElement(* AddElement(TrinaryTree(3), 5), 6), 5), 6)->Number() == 6);
}
