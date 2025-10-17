/*
 * This is the main testing folder, centralising ALL current tests to be ran, makes a general testing easier!
 */
#include <gtest/gtest.h>

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argc);
	return RUN_ALL_TESTS;
}