#include "pch.h"
#include "..\Var1Stack\MyStack.h"

TEST(StackTest, InitDefaultConstructorStack) {
	MyStack <int> stack;
	ASSERT_EQ(0, stack.getSize());
}

TEST(StackTest, PushStack) {
	MyStack <int> stack;
	stack.push(100);
	ASSERT_EQ(1, stack.getSize());
}

TEST(StackTest, PopStack) {
	MyStack <int> stack;
	stack.push(100);
	stack.pop();
	ASSERT_EQ(0, stack.getSize());
}

TEST(StackTest, HeadStack) {
	MyStack <int> stack;
	stack.push(100);
	ASSERT_EQ(100, stack.head());
}

TEST(StackTest, ConstructorOfCopy) {
	MyStack <int> stack;
	stack.push(100);
	MyStack <int> newStack(stack);
	ASSERT_EQ(stack.getSize(), newStack.getSize());
}

TEST(StackTest, EmptyStack) {
	MyStack <int> stack;
	stack.push(2);
	ASSERT_FALSE(stack.isEmpty());
}

TEST(StackTest, PushThenPopThenEmptyStack) {
	MyStack <int> stack;
	stack.push(100);
	stack.pop();
	ASSERT_TRUE(stack.isEmpty());
}

TEST(StackTest, ThrowStackPop) {
	MyStack <string> stack;
	ASSERT_ANY_THROW(stack.pop());
}

TEST(StackTest, ThrowStackHead) {
	MyStack <string> stack;
	ASSERT_ANY_THROW(stack.head());
}

TEST(StackTest, NoThrowStackPop) {
	MyStack <string> stack;
	stack.push("Test");
	ASSERT_NO_THROW(stack.pop());
	ASSERT_EQ(0, stack.getSize());
}