#include "pch.h"
#include "..\Var1Stack\MyStack.h"

TEST(FirstTest, InitDefaultConstructorStack) {
	MyStack <int> stack;
	ASSERT_EQ(0, stack.getSize());
}

TEST(SecondTest, PushStack) {
	MyStack <int> stack;
	stack.push(100);
	ASSERT_EQ(1, stack.getSize());
}

TEST(ThirdTest, PopStack) {
	MyStack <int> stack;
	stack.push(100);
	stack.pop();
	ASSERT_EQ(0, stack.getSize());
}

TEST(FourthTest, HeadStack) {
	MyStack <int> stack;
	stack.push(100);
	ASSERT_EQ(100, stack.head());
}

TEST(FifthTest, ConstructorOfCopy) {
	MyStack <int> stack;
	stack.push(100);
	MyStack <int> newStack(stack);
	ASSERT_EQ(stack.getSize(), newStack.getSize());
}

TEST(SixthTest, EmptyStack) {
	MyStack <int> stack;
	stack.push(2);
	ASSERT_FALSE(stack.isEmpty());
}

TEST(SeventhTest, PushThenPopThenEmptyStack) {
	MyStack <int> stack;
	stack.push(100);
	stack.pop();
	ASSERT_TRUE(stack.isEmpty());
}

TEST(EighthTest, ThrowStackPop) {
	MyStack <string> stack;
	ASSERT_ANY_THROW(stack.pop());
}

TEST(NinthTest, ThrowStackHead) {
	MyStack <string> stack;
	ASSERT_ANY_THROW(stack.head());
}

TEST(TenthTest, NoThrowStackPop) {
	MyStack <string> stack;
	stack.push("Test");
	ASSERT_NO_THROW(stack.pop());
	ASSERT_EQ(0, stack.getSize());
}